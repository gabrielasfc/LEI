# Autores: Gabriela Cunha, Guilherme Varela e Miguel Braga
# Data de criação: 30/12/22
# Data da última atualização: 02/01/23
# Descrição: Implementação de um cliente
# Última atualização: Prioridades implementadas no próximo servidor a contactar

import socket
import sys
from dns_message import DNSMessage


class Client:
    def __init__(self, timeout, debug):
        self.timeout = timeout
        self.debug = debug
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Criar socket UDP
        self.socket.settimeout(timeout)

    def __str__(self):
        return "Timeout: " + str(self.timeout) + "\nDebug: " + str(self.debug)

    def __repr__(self):
        return "Timeout: " + str(self.timeout) + "\nDebug: " + str(self.debug)

    def sendto_socket(self, message, address):
        if self.debug:  # Enviar query para o socket do server
            self.socket.sendto(message.to_string().encode('utf-8'), address)
        else:
            self.socket.sendto(message.serialize(), address)

    def recvfrom_socket(self):
        try:
            message = self.socket.recv(4096)  # Receber resposta do servidor

            if self.debug:  # Descodificação da resposta do servidor
                message = DNSMessage.from_string(message.decode('utf-8'))
            else:
                message = DNSMessage.deserialize(message)

            sys.stdout.write(message.to_string() + "\n")
            return message

        except socket.timeout:
            raise

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

    @staticmethod
    def find_next_step(response, servers_visited=list()):
        """
        Encontra o próximo servidor a ser contactado
        :param response: Resposta recebida
        :param servers_visited: Lista que guarda os servidores já visitados
        :return: Endereço do próximo servidor a ser contactado
        """
        authorities_values = Client.sort_by_priority(response.authorities_values)
        for record1 in authorities_values:
            if record1.domain in response.domain:
                for record2 in response.extra_values:
                    address = Client.parse_address(record2.value)
                    if record1.value == record2.domain and address[0] not in servers_visited:
                        return address
