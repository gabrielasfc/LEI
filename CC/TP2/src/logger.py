# Autores: Gabriela Cunha, Guilherme Varela e Miguel Braga
# Data de criação: 29/10/22
# Data da última atualização: 29/12/22
# Descrição: Implementação de logs
# Última atualização: Documentação atualizada

from datetime import datetime
import sys
import threading


class Logger:
    def __init__(self, log_files_paths, is_debug):
        """
        Construtor de um objeto Log
        :param log_files_paths: Dicionário com os domínios e a respetiva diretoria do seu ficheiro de log
        :param is_debug: Modo de funcionamento (debug ou shy)
        """
        self.log_files_paths = log_files_paths
        self.is_debug = is_debug  # True -> print para stdout
        self.lock = threading.Lock()

    def log_qe(self, domain, ip_address, data):
        """
        Regista log de query enviada
        :param domain: Domínio
        :param ip_address: Endereço IP
        :param data: Dados
        """
        message = "QE " + ip_address + " " + data
        self.add_log(message, domain)

    def log_qr(self, domain, ip_address, data):
        """
        Regista log de query recebida
        :param domain: Domínio
        :param ip_address: Endereço IP
        :param data: Dados
        """
        message = "QR " + ip_address + " " + data                   
        self.add_log(message, domain)

    def log_rp(self, domain, ip_address, data):
        """
        Regista log de query resposta enviada
        :param domain: Domínio
        :param ip_address: Endereço IP
        :param data: Dados
        """
        message = "RP " + ip_address + " " + data                   
        self.add_log(message, domain)

    def log_rr(self, domain, ip_address, data):
        """
        Regista log de query resposta recebida
        :param domain: Domínio
        :param ip_address: Endereço IP
        :param data: Dados
        """
        message = "RR " + ip_address + " " + data                           
        self.add_log(message, domain)

    def log_zt(self, domain, ip_address, data, duration=""):
        """
        Regista log de inicio/conclusão de transferência de zona
        :param domain: Domínio
        :param ip_address: Endereço IP
        :param data: Dados
        :param duration: Duração
        """
        message = "ZT " + ip_address + " " + data + " " + duration
        self.add_log(message, domain)

    def log_ev(self, ip_address, event, event_data, domain=None):
        """
        Regista log de um evento
        :param ip_address: Endereço IP
        :param event: Evento
        :param event_data: Dados do evento
        :param domain: Domínio
        """
        message = "EV " + ip_address + " " + event + " " + event_data
        self.add_log(message, domain)

    def log_er(self, domain, ip_address, info):
        """
        Regista log da receção de um PDU que não foi codificado corretamente
        :param domain: Domínio
        :param ip_address: Endereço IP
        :param info: Informação
        """
        message = "ER " + ip_address + " " + info  # ip_address - source, info - onde ocorreu o erro
        self.add_log(message, domain)

    def log_ez(self, domain, ip_address, data):
        """
        Regista log de um erro na transferência de zona
        :param domain: Domínio
        :param ip_address: Endereço IP
        :param data: Dados
        """
        message = "EZ " + ip_address + " " + data  # data - papel do servidor local
        self.add_log(message, domain)

    def log_fl(self, entry, info, domain=None):
        """
        Regista log de um erro detetado no funcionamento interno de um componente
        :param entry: Entrada
        :param info: Informação
        :param domain: Domínio
        """
        message = "FL 127.0.0.1 | Entry: " + entry + " | " + info  # Info - razão (erros de parsing, erros na descodificação, etc)
        self.add_log(message, domain)

    def log_to(self, info):
        """
        Regista log de um timeout
        :param info: Informação
        """
        message = "TO " + info  # Info - tipo de timeout (ex: numa resposta a query, ou a tentar conectar ao SP para ZT)
        self.add_log(message)

    def log_sp(self, domain, ip_address, info):
        """
        Regista log da paragem de execução de um componente
        :param domain: Domínio
        :param ip_address: Endereço IP
        :param info: Informação
        """
        message = "SP " + ip_address + " " + info               
        self.add_log(message, domain)

    def log_st(self, ip_address, port, timeout, mode):
        """
        Regista log de início da execução de um componente
        :param ip_address: Endereço de IP
        :param port: Porta de atendimento
        :param timeout: Valor de timeout
        :param mode: Modo de funcionamento
        """
        if mode == "shy" or mode == "debug":
            message = "ST " + ip_address + " " + str(port) + " " + str(timeout) + " " + mode
            self.add_log(message)

    def add_log(self, message, domain=None):
        """
        Método chamado pelos restantes responsável pela escrita do log no ficheiro
        :param message: Mensagem a ser registada
        :param domain: Domínio
        """
        self.lock.acquire()
        dt = datetime.now().strftime("%d:%m:%Y.%H:%M:%S:%f")

        if domain in self.log_files_paths.keys():
            domain_fd = open(self.log_files_paths[domain], "a")
            domain_fd.write(dt + " " + message + "\n")
            domain_fd.close()
        else:
            all_fd = open(self.log_files_paths["all."], "a")
            all_fd.write(dt + " " + message + "\n")
            all_fd.close()

        if self.is_debug:
            sys.stdout.write(dt + " " + message + "\n")

        self.lock.release()
