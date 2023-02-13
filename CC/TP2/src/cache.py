# Autores: Gabriela Cunha, Guilherme Varela e Miguel Braga
# Data de criação: 30/10/22
# Data da última atualização: 30/12/22
# Descrição: Implementação de sistema de cache de um servidor
# Última atualização: Documentação atualizada

import threading
from resource_record import *
from datetime import datetime


class Cache:
    def __init__(self):
        """
        Construtor de um objeto Cache
        """
        self.domains = dict()
        self.soaexpire = dict()
        self.lock = threading.Lock()

    def __str__(self):
        """
        Devolve a representação em string de um objeto Cache
        """
        return str(self.domains)

    def __repr__(self):
        """
        Devolve a representação oficial em string de um objeto Cache
        :return:
        """
        return str(self.domains)

    def add_entry(self, new_record, domain):
        """
        Adiciona uma nova entrada na cache
        :param new_record: Nova entrada
        :param domain: Domínio do record
        """
        self.lock.acquire()

        if domain not in self.domains.keys():
            self.domains[domain] = [ResourceRecord.create_free_record()]

        entries = self.domains[domain]
        found = False

        if new_record.origin == Origin.SP or new_record.origin == Origin.FILE:
            for i in range(len(entries)):
                record = entries[i]

                if record.origin == Origin.OTHERS and datetime.timestamp(datetime.now()) - record.timestamp > record.ttl:
                    record.status = Status.FREE

                if record.status == Status.FREE:
                    new_record.status = Status.VALID
                    new_record.timestamp = datetime.timestamp(datetime.now())
                    entries[i] = new_record

                    found = True
                    break
        else:
            last_free = -1
            for i in range(len(entries)):
                record = entries[i]

                if record.origin == Origin.OTHERS and datetime.timestamp(datetime.now()) - record.timestamp > record.ttl:
                    record.status = Status.FREE

                if record.status == Status.FREE:
                    last_free = i

                if record.domain == new_record.domain and record.type == new_record.type and record.value == new_record.value \
                    and record.priority == new_record.priority and record.ttl == new_record.ttl:

                    if record.origin == Origin.OTHERS:
                        record.status = Status.VALID
                        record.timestamp = datetime.timestamp(datetime.now())

                    found = True
                    break

                elif last_free != -1:
                    new_record.status = Status.VALID
                    new_record.timestamp = datetime.timestamp(datetime.now())
                    entries[last_free] = new_record

                    found = True
                    break

        if not found:
            new_record.status = Status.VALID
            new_record.timestamp = datetime.timestamp(datetime.now())
            entries.append(new_record)

        self.lock.release()

    def get_file_entries_by_domain(self, domain):
        """
        Obtém as entradas com origem ficheiro de um domínio da cache
        :param domain: Domínio
        :return: Lista com as entradas de um domínio
        """
        self.lock.acquire()

        self.check_expire_domain(domain)

        entries = list()
        for record in self.domains[domain]:
            if record.origin == Origin.FILE:
                entries.append(record)

        self.lock.release()

        return entries

    def get_records_by_domain_and_type(self, domain, type):
        """
        Obtém a lista das entradas correspondentes com o domain e o type
        :param domain: Domínio
        :param type: Tipo
        :return: Lista com as entradas que deram match
        """
        self.lock.acquire()

        self.check_expire_domain(domain)

        entries = list()
        records = []

        for cache_domain in self.domains.keys():
            if cache_domain in domain:
                entries = self.domains[cache_domain]
                break

        for i in range(len(entries)):
            record = entries[i]

            if record.origin == Origin.OTHERS and datetime.timestamp(datetime.now()) - record.timestamp > record.ttl:
                record.status = Status.FREE

            if record.status == Status.VALID and record.domain == domain and record.type == type:
                records.append(record)

        self.lock.release()

        return records

    def free_cache(self, domain):
        """
        Liberta a entradas de um determinado domínio, colocando as entradas a FREE
        :param domain: Domínio
        """
        self.lock.acquire()

        if domain in self.domains.keys():
            entries = self.domains[domain]

            for record in entries:
                record.status = Status.FREE

        self.lock.release()

    def free_sp_entries(self, domain):
        """
        Liberta as entradas do servidor primário para um dado domínio
        :param domain: Domínio
        """
        self.lock.acquire()

        if domain in self.domains.keys():
            entries = self.domains[domain]

            for record in entries:
                if record.origin == Origin.SP:
                    record.status = Status.FREE

        self.lock.release()

    def register_initial_timestamp(self, domain):
        """
        Regista o timestamp após a ZT ter sido realizada para posteriormente verificar se as entradas estão expiradas
        :param domain: Domínio
        :return: Timestamp inicial
        """
        self.soaexpire[domain] = datetime.timestamp(datetime.now())

    def check_expire_domain(self, domain):
        """
        Verifica se as entradas de um domínio provenientes da ZT estão expiradas (SOAEXPIRE)
        :param domain: Domínio
        """
        if domain in self.soaexpire.keys():
            soaexpire = None
            for record in self.domains[domain]:
                if record.type == "SOAEXPIRE":
                    soaexpire = int(record.value)

            if datetime.timestamp(datetime.now()) - self.soaexpire[domain] > soaexpire:
                self.domains.pop(domain)
                self.soaexpire.pop(domain)
