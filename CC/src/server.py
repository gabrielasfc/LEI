# Autores: Gabriela Cunha, Guilherme Varela e Miguel Braga
# Data de criação: 30/10/22
# Data da última atualização: 02/01/23
# Descrição: Implementação de um servidor
# Última atualização: Documentação

import random
import socket
import threading
import time
import exceptions
from dns_message import *
from resource_record import ResourceRecord


class Server:
    def __init__(self, config, log, port, timeout, handles_recursion, is_debug):
        """
        Construtor de um objeto Server
        :param config: Estrutura com os dados de configuração
        :param log: Objetos Log
        :param port: Porta de atendimento
        :param timeout: Timeout
        :param handles_recursion: Aceita ou não modo recursivo
        """
        self.config = config
        self.log = log
        self.port = port
        self.timeout = timeout
        self.handles_recursion = handles_recursion
        self.is_debug = is_debug

        self.cache = None

    def __str__(self):
        """
        Devolve a representação em string do objeto Server
        :return: String
        """
        return str(self.config) + str(self.log) + str(self.port) + str(self.timeout) + \
               "handles recursion: " + str(self.handles_recursion) + "modo debug: " + self.is_debug

    def __repr__(self):
        """
        Devolve a representação oficial em string do objeto Server
        :return: String
        """
        return str(self.config) + str(self.log) + str(self.port) + str(self.timeout) + \
               "handles recursion: " + str(self.handles_recursion) + "modo debug: " + self.is_debug

    @staticmethod
    def parse_address(address):
        """
        Separa um endereço em endereço e porta
        :param address: Endereço IP
        :return: Endereço e porta
        """
        substrings = address.split(":")
        ip_address = substrings[0]

        if len(substrings) > 1:
            port = int(substrings[1])
        else:
            port = 5353  # porta default

        return ip_address, port

    def sendto_socket(self, socket, message, address):
        """
        Envia uma mensagem serializada e regista os respetivos logs
        :param socket: Socket
        :param message: Mensagem a enviar
        :param address: Endereço do servidor para o qual vai enviar
        """
        if not self.is_debug:
            socket.sendto(message.serialize(), address)
        else:
            socket.sendto(message.to_string().encode('utf-8'), address)

        if "Q" in message.flags:
            self.log.log_qe(message.domain, str(address), message.to_string())
        else:
            self.log.log_rp(message.domain, str(address), message.to_string())

    def recvfrom_socket(self, socket):
        """
        Recebe uma mensagem, desserializa-a e regista os respetivos logs
        :param socket: Socket
        :return: Mensagem, endereço do servidor da origem da mensagem
        """
        message, address = socket.recvfrom(4096)

        if message:
            if not self.is_debug:
                message = DNSMessage.deserialize(message)
            else:
                message = DNSMessage.from_string(message.decode('utf-8'))

            if "Q" in message.flags:
                self.log.log_qr(message.domain, str(address), message.to_string())
            else:
                self.log.log_rr(message.domain, str(address), message.to_string())

        return message, address

    def receive_queries(self):
        """
        Recebe queries através de um socket udp e cria uma thread para cada query (thread-per-connection)
        """
        socket_udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Criar socket UDP
        socket_udp.bind(("", self.port))

        while True:
            message, address = self.recvfrom_socket(socket_udp)
            threading.Thread(target=self.interpret_message, args=(message, address)).start()  # Thread per connection

        socket_udp.close()

    def is_root_server(self):
        """
        Verifica se o servidor é um servidor de topo
        :return: True caso seja um ST, False caso contrário
        """
        return "." in self.config["DB"].keys()

    def is_resolution_server(self):
        """
        Verifica se o servidor é um servidor de resolução
        :return: True caso seja um SR, False caso contrário
        """
        return len(self.config["SS"].keys()) == 0 and len(self.config["SP"].keys()) == 0 and len(
            self.config["DB"].keys()) == 0

    def is_name_server(self):
        """
        Verifica se o servidor é um name server
        :return: True caso seja um ST/SP/SS, False caso contrário
        """
        return len(self.config["SS"].keys()) != 0 or len(self.config["SP"].keys()) != 0 or len(
            self.config["DB"].keys()) != 0

    def is_domain_in_dd(self, domain):
        """
        Verifica se o domínio está nos domínios por defeito
        :param domain: Domínio a procurar
        :return: True caso o domínio esteja nos DD's, False caso contrário
        """
        return domain in self.config["DD"].keys()

    def has_default_domains(self):
        """
        Verifica se o servidor tem domínios por defeito
        :return: True caso tenha DD's, False caso contrário
        """
        return len(self.config["DD"].keys()) != 0

    @staticmethod
    def find_next_domain(domain):
        """
        Encontra o domínio acima do domínio dado na hierarquia
        :param domain: Domínio dado
        :return: Domínio acima na hierarquia
        """
        ret = domain.split(".", 1)[1]

        if ret == "":
            ret = "."

        return ret

    @staticmethod
    def sort_by_priority(records):
        """
        Ordena os records contidos nos authorities values de uma mensagem por prioridade
        :param records: Lista de records
        :return: Lista dos records ordenados por prioridade
        """
        no_priority = list()
        priority = list()
        for record in records:
            if record.priority == -1:
                no_priority.append(record)
            else:
                priority.append(record)

        priority.sort(key=lambda x: x.priority)

        return priority + no_priority

    def find_next_step(self, query, servers_visited=list()):
        """
        Encontra o próximo servidor a ser contactado
        :param query: Query recebida
        :param servers_visited: Lista de servidores já visitados (para evitar contactar servidores repetidos)
        :return: Endereço do próximo servidor a ser contactado
        """
        authorities_values = Server.sort_by_priority(query.authorities_values)
        for record1 in authorities_values:
            if record1.domain in query.domain:
                for record2 in query.extra_values:
                    address = Server.parse_address(record2.value)
                    if record1.value == record2.domain and address[0] not in servers_visited:
                        return address

        if self.is_domain_in_dd(query.domain):  # antes ou depois
            for address in self.config["DD"][query.domain]:
                address = Server.parse_address(address)
                if address[0] not in servers_visited:
                    return address

        for address in self.config["ST"]:
            address = Server.parse_address(address)
            if address[0] not in servers_visited:
                return address

    def fill_extra_values(self, response_values, authorities_values):
        """
        Preenche os extra values relativos a uma query
        :param response_values: Lista com os response values
        :param authorities_values: Lista com os authorities values
        :return: Lista extra values preenchida
        """
        extra_values = list()

        for record in response_values:
            records = self.cache.get_records_by_domain_and_type(record.value, "A")
            extra_values += records

        for record in authorities_values:
            records = self.cache.get_records_by_domain_and_type(record.value, "A")
            extra_values += records

        return extra_values

    def fill_root_servers(self, message):
        """
        Preenche os authorities e extra values de uma mensagem com informação dos servidores de topo
        :param message: Mensagem
        :return: Mensagem atualizada
        """
        for i in range(len(self.config["ST"])):
            name = "root" + str(i) + ".root."
            message.authorities_values.append(ResourceRecord("root.", "NS", name, 0, -1))
            message.extra_values.append(ResourceRecord(name, "A", self.config["ST"][i], 0, -1))

        message.num_authorities = len(message.authorities_values)
        message.num_extra = len(message.extra_values)
        message.flags = ""
        message.response_code = 1

        return message

    def change_flags(self, query):
        """
        Altera as flags de uma query consoante o modo e a autoridade do servidor
        :param query: Query
        :return: Flags
        """
        authoritative = False

        for domain in self.config["DB"].keys():
            if domain == query.domain:
                authoritative = True
                break

        if self.handles_recursion:
            if "Q" in query.flags:
                query.flags = "Q+R"
            elif authoritative:
                query.flags = "R+A"
            else:
                query.flags = "R"
        else:
            if "Q" in query.flags:
                query.flags = "Q"
            elif authoritative:
                query.flags = "A"
            else:
                query.flags = ""

    def register_response_on_cache(self, response):
        """
        Adiciona os dados da resposta na cache
        :param response: Resposta
        """
        for record in response.response_values:
            record.origin = Origin.OTHERS
            self.cache.add_entry(record, response.domain)

        for record in response.authorities_values:
            record.origin = Origin.OTHERS
            self.cache.add_entry(record, response.domain)

        for record in response.extra_values:
            record.origin = Origin.OTHERS
            self.cache.add_entry(record, response.domain)

    def search_on_cache(self, message):
        """
        Procura na cache informação para responder à mensagem recebida
        :param message: Mensagem a responder
        :return: Mensagem atualizada
        """
        response_values = list()
        authorities_values = list()
        extra_values = list()

        found = False
        domain = message.domain

        
        response_values = self.cache.get_records_by_domain_and_type(domain, message.type)
        while not found:
            if len(response_values) == 0 and message.type == "A":  # Vai ver o seu CNAME
                cname = self.cache.get_records_by_domain_and_type(domain, "CNAME")
                if len(cname) > 0:
                    domain = cname[0].value
                    response_values = self.cache.get_records_by_domain_and_type(domain, message.type)

            authorities_values = self.cache.get_records_by_domain_and_type(domain, "NS")
            extra_values = self.fill_extra_values(response_values, authorities_values)

            if len(response_values) == 0 and len(authorities_values) == 0 and len(extra_values) == 0:
                domain = Server.find_next_domain(domain)

                if domain == ".":  # Mudar
                    break
            else:
                found = True

        message.num_response = len(response_values)
        message.num_authorities = len(authorities_values)
        message.num_extra = len(extra_values)
        message.response_values = response_values
        message.authorities_values = authorities_values
        message.extra_values = extra_values

        if len(message.response_values) != 0:
            message.response_code = 0
            message.flags = ""
            self.change_flags(message)
        elif found:
            message.response_code = 1
            message.flags = ""
            self.change_flags(message)
        elif not found and "Q" not in message.flags:
            message.response_code = 2
            message.flags = ""
            self.change_flags(message)

        return message

    def message_resolver(self, message, socket_udp):
        """
        Processo de resolução de uma mensagem
        :param message: Mensagem
        :param socket_udp: Socket
        :return Mensagem atualizada
        """
        servers_visited = list()
        next_server = self.find_next_step(message)
        self.change_flags(message)

        response_code = 1
        while response_code == 1 or "Q" in message.flags:
            self.sendto_socket(socket_udp, message, next_server)

            try:
                message, address = self.recvfrom_socket(socket_udp)

            except socket.timeout:
                self.log.log_to("Foi detetado um timeout numa resposta a uma query.")

                servers_visited.append(next_server[0])
                if next_server == self.find_next_step(message, servers_visited):
                    break

            response_code = message.response_code
            next_server = self.find_next_step(message, servers_visited)
            self.change_flags(message)

        if response_code == 0:
            self.register_response_on_cache(message)

        return message

    def interpret_message(self, message, client):
        """
        Processo de resposta a uma mensagem
        :param message: Mensagem DNS
        :param client: Endereço de onde foi enviada a mensagem
        """
        socket_udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Criar socket UDP para enviar mensagens
        socket_udp.settimeout(self.timeout)

        if self.is_name_server():  # SP/SS/ST/SDT
            if self.has_default_domains():
                if self.is_domain_in_dd(message.domain):  # Pode responder
                    message = self.search_on_cache(message)
                    self.sendto_socket(socket_udp, message, client)
                else:
                    self.log.log_to("Server has no permission to attend the query domain!")

            else:  # Se não tiver domínios por defeito, pode responder a queries de qualquer domínio
                flags = message.flags
                response = self.search_on_cache(message)

                if "R" in flags and (response.response_code == 1 or "Q" in response.flags):  # Mensagem recursiva
                    if "Q" in flags or self.handles_recursion:  # Query ou servidor aceita modo recursivo
                        response = self.message_resolver(response, socket_udp)

                elif "Q" in response.flags:  # Não encontrou informação sobre o domínio da query na cache, responde com informação dos ST's
                    response = self.fill_root_servers(response)

                self.sendto_socket(socket_udp, response, client)

        elif self.is_resolution_server():  # SR
            flags = message.flags
            response = self.search_on_cache(message)

            if "R" in flags and (response.response_code == 1 or "Q" in response.flags):  # Mensagem recursiva
                if "Q" in flags or self.handles_recursion:  # Query ou servidor aceita modo recursivo
                    response = self.message_resolver(response, socket_udp)

            elif "Q" in response.flags:  # Não encontrou informação sobre o domínio da query na cache, responde com informação dos ST's
                response = self.fill_root_servers(response)

            self.sendto_socket(socket_udp, response, client)

        socket_udp.close()

    # ===========================================   TRANSFERÊNCIA DE ZONA   ==============================================

    def sp_zone_transfer(self):
        """
        Cria o socket TCP e executa a transferência de zona para cada ligação estabelecida
        """
        socket_tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        socket_tcp.bind(("", self.port))
        socket_tcp.listen()

        while True:
            connection, address_from = socket_tcp.accept()

            threading.Thread(target=self.sp_zone_transfer_process, args=(connection, address_from)).start()

        socket_tcp.close()

    def sp_zone_transfer_process(self, connection, address_from):
        """
        Processo de transferência de zona
        :param connection: Conexão estabelecida
        :param address_from: Endereço do servidor secundário
        """
        connection.settimeout(self.timeout)
        domain = None

        while True:
            try:
                message, address = self.recvfrom_socket(connection)
            except socket.timeout:
                self.log.log_ez(domain, str(address_from), "SP")
                self.log.log_to("Timeout a receber mensagem DNS na transferência de zona!")
                break

            if not message:
                break

            domain = message.domain

            if message.flags == "Q":  # Pedir versão/transferência de zona e envia
                if message.type == "AXFR":
                    t_start = time.time()
                    self.log.log_zt(domain, str(address_from), "SP : Zone transfer started")
                    response = self.axfr_response(message)
                elif message.type == "SOASERIAL":
                    response = self.search_on_cache(message)

                # Envia query a pedir a versão da BD
                if not self.is_debug:
                    connection.sendall(response.serialize())
                else:
                    connection.sendall(response.to_string().encode('utf-8'))

                self.log.log_rp(domain, str(address_from), response.to_string())

            elif message.response_code == 0:  # Secundário aceitou linhas e respondeu com o nº de linhas
                entries = self.cache.get_file_entries_by_domain(message.domain)
                index = 1
                for record in entries:
                    if record.origin == Origin.FILE:
                        record = str(
                            index) + " " + record.resource_record_to_string() + "\n"
                        connection.sendall(record.encode('utf-8'))
                        index += 1

                t_end = time.time()
                self.log.log_zt(domain, str(address_from), "SP : All entries sent",
                                str(round(t_end - t_start, 5)) + "s")
                break

        connection.close()

    def axfr_response(self, query):
        """
        Retorna o número de entradas da DB de um certo domínio (resposta a uma query AXFR)
        :param query: Query que contém o domínio
        :return: Resposta à query AXFR
        """
        record = ResourceRecord(query.domain, query.type,
                                str(len(self.cache.get_file_entries_by_domain(query.domain))), 0, -1, Origin.SP)
        query.flags = "A"
        query.response_code = 0
        query.response_values.append(record)
        query.num_response = 1

        return query

    def ss_zone_transfer(self, domain):  # Ir aos seus SPs
        """
        Processo de transferência de zona por parte do SS
        :param domain: Domínio
        """
        soaretry = 10
        wait = soaretry  # soaretry default

        while True:
            socket_tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            try:
                socket_tcp.connect(Server.parse_address(self.config["SP"][domain]))
                socket_tcp.settimeout(int(self.timeout))

                self.ss_ask_version(socket_tcp, domain)

                start = time.time()
                self.log.log_zt(domain, str(Server.parse_address(self.config["SP"][domain])),
                                "SS : Zone Transfer started")

                num_entries = self.ss_ask_zone_transfer(socket_tcp, domain)
                self.ss_receive_records(socket_tcp, domain, num_entries)

                end = time.time()
                self.log.log_zt(domain, str(Server.parse_address(self.config["SP"][domain])),
                                "SS : Zone Transfer concluded successfully", str(round(end - start, 5)) + "s")

                socket_tcp.close()

                soarefresh = int(self.cache.get_records_by_domain_and_type(domain, "SOAREFRESH")[0].value)
                soaretry = int(self.cache.get_records_by_domain_and_type(domain, "SOARETRY")[0].value)
                wait = soarefresh

            except exceptions.ZoneTransferFailed as e:
                self.log.log_ez(domain, self.config["SP"][domain], "SS: " + e.message)
                socket_tcp.close()
                wait = soaretry

            except exceptions.ZoneTransferDatabaseIsUpToDate as e:
                self.log.log_ez(domain, self.config["SP"][domain], "SS: " + e.message)
                socket_tcp.close()

            except socket.timeout as e:
                self.log.log_to(e.args[0])
                socket_tcp.close()
                wait = soaretry # verificar

            except socket.error:
                self.log.log_ez(domain, self.config["SP"][domain], "SS: Failed to connect to primary server")

            time.sleep(wait)

    def get_version(self, domain):
        """
        Obtém a versão da base de dados do servidor secundário
        :return: Versão
        """
        list = self.cache.get_records_by_domain_and_type(domain, "SOASERIAL")

        if len(list) == 0:
            ss_version = -1
        else:
            ss_version = list[0].value

        return ss_version

    def ss_ask_version(self, socket_tcp, domain):
        """
        Pergunta a versão ao servidor primário e liberta as entradas em cache caso a versão do SP seja mais recente
        :param socket_tcp: Socket TCP
        :param domain: Domínio
        """
        query = DNSMessage(random.randint(1, 65535), "Q", 0, domain, "SOASERIAL")

        if not self.is_debug:
            socket_tcp.sendall(query.serialize())  # Envia query a pedir a versão da BD
        else:
            socket_tcp.sendall(query.to_string().encode('utf-8'))
        self.log.log_qe(domain, str(Server.parse_address(self.config["SP"][domain])), query.to_string())

        try:
            message, address = self.recvfrom_socket(socket_tcp)

            ss_version = self.get_version(domain)
            sp_version = message.response_values[0].value

            if float(sp_version) > float(ss_version):
                self.cache.free_sp_entries(domain)
            else:
                raise exceptions.ZoneTransferDatabaseIsUpToDate("Database is up to date")

        except socket.timeout:
            raise socket.timeout('Attempt of getting the database version.')

    def ss_ask_zone_transfer(self, socket_tcp, domain):
        """
        Processo de transferência de zona do servidor secundário
        :param socket_tcp: Socket TCP
        :param domain: Domínio
        :return: Número esperado de entradas da DB do SP a receber
        """
        query = DNSMessage(random.randint(1, 65535), "Q", 0, domain, "AXFR")  # Query AXFR

        if not self.is_debug:
            socket_tcp.sendall(query.serialize())  # Envia query a pedir a transferência
        else:
            socket_tcp.sendall(query.to_string().encode('utf-8'))

        self.log.log_qe(domain, str(Server.parse_address(self.config["SP"][domain])), query.to_string())

        try:
            message, address = self.recvfrom_socket(socket_tcp)
            num_entries = int(message.response_values[0].value)

            if not self.is_debug:
                socket_tcp.sendall(message.serialize())
            else:
                socket_tcp.sendall(message.to_string().encode('utf-8'))

            self.log.log_rp(domain, str(address), message.to_string())

            return num_entries

        except socket.timeout:
            raise socket.timeout('Attempt of starting zone transfer.')

    def ss_receive_records(self, socket_tcp, domain, num_entries):
        """
        Recebe as entradas da base de dados do SP e regista-as na cache
        :param socket_tcp: Socket TCP
        :param domain: Domínio
        :param num_entries: Número esperado de entradas a receber
        """
        try:
            database_lines = Server.receive_database_records(socket_tcp, num_entries)
            self.add_records_to_db(database_lines, domain)
            self.cache.register_initial_timestamp(domain)

        except exceptions.ZoneTransferFailed:
            raise

    @staticmethod
    def receive_database_records(socket_tcp, num_entries):
        """
        Recebe as linhas da base de dados do SP
        :param socket_tcp: Socket TCP
        :param num_entries: Número esperado de entradas a receber
        :return: Linhas recebidas
        """
        end = time.time() + 10
        success = False

        database_lines = ""
        while time.time() < end:
            message = socket_tcp.recv(2048)

            if not message:
                success = True
                break

            database_lines += message.decode('utf-8')

        if not success:
            raise exceptions.ZoneTransferFailed("Timeout occurred")

        database_lines = database_lines[:-1].split("\n")
        last_record = database_lines[-1]
        last_record_index = int(last_record.split(" ")[0])

        if last_record_index != num_entries:
            raise exceptions.ZoneTransferFailed("Unexpected number of entries")

        return database_lines

    def add_records_to_db(self, database_lines, domain):
        """
        Adiciona as entradas recebidas do servidor primário à cache
        :param database_lines: Linhas recebidas
        :param domain: Domínio
        """
        expected_value = 1

        for line in database_lines:
            index, record = Server.remove_index(line)

            if index != expected_value:
                raise exceptions.ZoneTransferFailed("Unexpected record")

            self.cache.add_entry(ResourceRecord.to_record(record, Origin.SP), domain)
            expected_value += 1

    @staticmethod
    def remove_index(record):
        """
        Remove o índice de cada linha
        :param record: Linha
        :return: Índice, Linha sem o índice
        """
        fields = record.split(" ")
        index = int(fields[0])
        fields.remove(fields[0])

        record = " ".join(fields)

        return index, record
