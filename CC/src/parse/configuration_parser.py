# Autores: Gabriela Cunha, Guilherme Varela e Miguel Braga
# Data de criação: 29/10/22
# Data da última atualização: 01/01/23
# Descrição: Parsing de ficheiros de configuração de servidores
# Última atualização: Fix

from parse.database_parser import *
from logger import *
from exceptions import *
from server import *


def parser_root_servers(file_path):
    """
    Parsing do ficheiro dos root servers
    :param file_path: Ficheiro de root servers
    :return: Lista dos root servers
    """
    f = open(file_path, "r")

    servers = list()

    for line in f:
        if line[0] != "\n" and line[0] != "#":
            line = line.replace("\n", "")
            servers.append(line)

    f.close()

    return servers


def parser_configuration(file_path, port, timeout, handles_recursion, mode):
    """
    Função responsável pelo parse dos ficheiros de configuração
    :param file_path: Ficheiro de configuração
    :param port: Porta
    :param timeout: Timeout
    :param handles_recursion: Indica se o servidor aceita o modo recursivo
    :param mode: Modo (debug/shy)
    :return: Servidor
    """
    config = dict()
    config["DB"] = dict()
    config["SP"] = dict()
    config["SS"] = dict()
    config["DD"] = dict()
    config["LG"] = dict()

    logs = dict()

    is_debug = False
    if mode == "debug":
        is_debug = True

    f = open(file_path, "r")

    for line in f:
        line = line.split("#")[0]  # ignorar comentários
        words = line.split()

        if len(words) > 0:
            if len(words) == 3:
                words[0] = words[0] + "."

                parameter = words[0]
                value_type = words[1]
                value = words[2]

                if value_type == "DB":
                    config[value_type][parameter] = value

                elif value_type == "SP":
                    if not validate_ip(value):
                        raise InvalidIPError

                    config[value_type][parameter] = value

                elif value_type == "SS":
                    if not validate_ip(value):
                        raise InvalidIPError

                    if parameter not in config[value_type].keys():
                        config[value_type][parameter] = list()

                    config[value_type][parameter].append(value)

                elif value_type == "DD":
                    if not validate_ip(value):
                        raise InvalidIPError

                    if parameter not in config[value_type].keys():
                        config[value_type][parameter] = list()

                    config[value_type][parameter].append(value)

                elif value_type == "ST" and parameter == "root.":
                    config[value_type] = parser_root_servers(value)

                elif value_type == "LG":
                    config[value_type][parameter] = value
                    logs[parameter] = value

    f.close()

    log = Logger(logs, is_debug)

    log.log_ev("localhost", "conf-file-read", file_path)
    log.log_st("127.0.0.1", port, timeout, mode)
    for log_file in config["LG"]:
        log.log_ev("localhost", "log-file-create", config["LG"][log_file])

    server = Server(config, log, port, timeout, handles_recursion, is_debug)

    parser_database_caller(server)

    for db_file in config["DB"]:
        log.log_ev("localhost", "db-file-read", config["DB"][db_file])

    return server
