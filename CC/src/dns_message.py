# Autores: Gabriela Cunha, Guilherme Varela e Miguel Braga
# Data de criação: 08/11/22
# Data da última atualização: 02/01/23
# Descrição: Representação de queries
# Última atualização: Proridade a ser enviada como inteiro para o construtor

from bitstring import BitArray, ConstBitStream
from resource_record import *
import re


class DNSMessage:
    def __init__(self, message_id, flags, response_code, domain, type, response=list(), authorities=list(), extra=list()):
        """
        Construtor de um objeto DNSMessage
        :param message_id: ID da mensagem
        :param flags: Flags
        :param response_code : Response code
        :param domain: Domínio
        :param type: Tipo
        :param response: Response values
        :param authorities: Authorities values
        :param extra: Extra values
        """
        self.message_id = message_id
        self.flags = flags
        self.response_code = response_code
        self.num_response = len(response)
        self.num_authorities = len(authorities)
        self.num_extra = len(extra)
        self.domain = domain
        self.type = type
        self.response_values = response
        self.authorities_values = authorities
        self.extra_values = extra

    def __str__(self):
        """
        Devolve a representação em string do objeto DNSMessage
        :return: String
        """
        return str(self.message_id) + " " + str(self.flags) + " " + str(self.response_code) + " " \
               + str(self.num_response) + " " + str(self.num_authorities) + " " \
               + str(self.num_extra) + " " + str(self.domain) + " " + str(self.type) + "\n" \
               + str(self.response_values) + "\n" + str(self.authorities_values) + "\n" + str(self.extra_values)

    def __repr__(self):
        """
        Devolve a representação oficial em string do objeto DNSMessage
        :return: String
        """
        return str(self.message_id) + " " + str(self.flags) + " " + str(self.response_code) + " " \
               + str(self.num_response) + " " + str(self.num_authorities) + " "  \
               + str(self.num_extra) + " " + str(self.domain) + " " + str(self.type) + "\n" \
               + str(self.response_values) + "\n" + str(self.authorities_values) + "\n" + str(self.extra_values)

    def to_string(self):
        """
        Transforma um objeto DNSMessage numa string
        :return: String
        """
        string = str(self.message_id) + "," + str(self.flags) + "," + str(self.response_code) + "," \
                 + str(self.num_response) + "," + str(self.num_authorities) + "," \
                 + str(self.num_extra) + ";" + str(self.domain) + "," + str(self.type) + ";\n"

        for record in self.response_values:
            string += record.resource_record_to_string() + ",\n"

        string = string[:-2] + ";\n"

        for record in self.authorities_values:
            string += record.resource_record_to_string() + ",\n"

        string = string[:-2] + ";\n"

        for record in self.extra_values:
            string += record.resource_record_to_string() + ",\n"

        string = string[:-2] + ";"

        return string

    @staticmethod
    def from_string(query):
        """
        Transforma uma string num objeto DNSMessage
        :param query: Mensagem (string)
        :return: Objeto DNSMessage
        """
        (message_id, flags, response_code, num_response_values, num_authorities_values,
         num_extra_values, domain, type, response_values, authorities_values, extra_values) = DNSMessage.parse(query)

        response = list()
        authorities = list()
        extra = list()

        for value in response_values:
            fields = value.split(" ")
            priority = -1

            if len(fields) > 4:
                priority = fields[4]

            record = ResourceRecord(fields[0], fields[1], fields[2], int(fields[3]), int(priority))
            response.append(record)

        for value in authorities_values:
            fields = value.split(" ")
            priority = -1

            if len(fields) > 4:
                priority = fields[4]

            record = ResourceRecord(fields[0], fields[1], fields[2], int(fields[3]), int(priority))
            authorities.append(record)

        for value in extra_values:
            fields = value.split(" ")
            priority = -1

            if len(fields) > 4:
                priority = fields[4]

            record = ResourceRecord(fields[0], fields[1], fields[2], int(fields[3]), int(priority))
            extra.append(record)

        return DNSMessage(message_id, flags, response_code, domain, type, response, authorities, extra)

    @staticmethod
    def parse(message):
        """
        Parse de uma mensagem
        :param message: Mensagem
        :return: Valores para as variáveis do objeto
                 Response values, authorities values e extra values são listas de strings
        """
        message = message.replace("\n", "")
        fields = re.split(";|,", message)
        fields = fields[:-1]

        message_id = fields[0]
        flags = fields[1]
        response_code = fields[2]
        num_response_values = fields[3]
        num_authorities_values = fields[4]
        num_extra_values = fields[5]
        name = fields[6]
        type = fields[7]

        response_values = list()
        authorities_values = list()
        extra_values = list()

        for i in range(int(num_response_values)):
            response_values.append(fields[8 + i])

        for i in range(int(num_authorities_values)):
            authorities_values.append(fields[8 + int(num_response_values) + i])

        for i in range(int(num_extra_values)):
            extra_values.append(fields[8 + int(num_response_values) + int(num_authorities_values) + i])

        return (int(message_id), flags, int(response_code), int(num_response_values), int(num_authorities_values),
                int(num_extra_values), name, type, response_values, authorities_values, extra_values)

    def encode_flags(self):
        """
        Codificação das flags
        :return: Flags codificadas num bitarray de 3 bits
        """
        if self.flags == "":
            flags = 0
        elif self.flags == "Q":
            flags = 1
        elif self.flags == "R":
            flags = 2
        elif self.flags == "A":
            flags = 3
        elif self.flags == "Q+R":
            flags = 4
        elif self.flags == "R+A":
            flags = 5

        return BitArray(uint=flags, length=3)

    @staticmethod
    def decode_flags(flags):
        """
        Descodificação das flags
        :param flags: Flags codificadas em bits
        :return: Flags
        """
        if flags == 0:
            flags = ""
        elif flags == 1:
            flags = "Q"
        elif flags == 2:
            flags = "R"
        elif flags == 3:
            flags = "A"
        elif flags == 4:
            flags = "Q+R"
        elif flags == 5:
            flags = "R+A"

        return flags

    def serialize(self):
        """
        Codificação de uma mensagem
        :return: Mensagem codificada
        """
        bit_array = BitArray()

        # MessageID - 2 bytes
        msg_id = BitArray(uint=self.message_id, length=16)
        bit_array.append(msg_id)

        bit_array.append(self.encode_flags())

        response_code = BitArray(uint=self.response_code, length=2)
        bit_array.append(response_code)

        n_response = BitArray(uint=self.num_response, length=8)
        n_authorities = BitArray(uint=self.num_authorities, length=8)
        n_extra = BitArray(uint=self.num_extra, length=8)

        bit_array.append(n_response)
        bit_array.append(n_authorities)
        bit_array.append(n_extra)

        # Query Name
        len_domain = BitArray(uint=len(self.domain), length=8)
        domain = ResourceRecord.string_to_bit_array(self.domain)

        bit_array.append(len_domain)
        bit_array.append(domain)
        bit_array.append(ResourceRecord.encode_type(self.type))

        for record in self.response_values:
            bit_array.append(record.serialize())

        for record in self.authorities_values:
            bit_array.append(record.serialize())

        for record in self.extra_values:
            bit_array.append(record.serialize())

        bit_array.append(BitArray(uint=0, length=8 - len(bit_array) % 8))  # Completar multiplo de 8

        return bit_array.bytes

    @staticmethod
    def deserialize(bytes):
        """
        Descodificação de uma mensagem
        :param bytes: Mensagem codificada
        :return: Objeto DNSMessage
        """
        stream = ConstBitStream(bytes)

        msg_id = stream.read('uint:16')
        flags = DNSMessage.decode_flags(stream.read('uint:3'))
        response_code = stream.read('uint:2')

        num_response = stream.read('uint:8')
        num_authorities = stream.read('uint:8')
        num_extra = stream.read('uint:8')

        len_domain = stream.read('uint:8')
        domain = ResourceRecord.bit_array_to_string(stream, len_domain)

        type = ResourceRecord.decode_type(stream.read('uint:4'))

        response = list()
        authorities = list()
        extra = list()

        i = 0
        while i < num_response:
            record = ResourceRecord.deserialize(stream)
            response.append(record)
            i += 1

        i = 0
        while i < num_authorities:
            record = ResourceRecord.deserialize(stream)
            authorities.append(record)
            i += 1

        i = 0
        while i < num_extra:
            record = ResourceRecord.deserialize(stream)
            extra.append(record)
            i += 1

        return DNSMessage(msg_id, flags, response_code, domain, type, response, authorities, extra)
