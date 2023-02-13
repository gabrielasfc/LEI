# Data de criação: 30/12/22
# Data da última atualização: 30/12/22
# Descrição: Cria um objeto Server a partir dos argumentos de input
# Última atualização: Criação do módulo

from parse.configuration_parser import *


def parser_server(args):
    config_path = args[1]  # Ficheiro de configuração
    port = int(args[2])  # Porta onde o servidor vai estar à escuta
    timeout = int(args[3])  # Tempo que o servidor vai esperar por uma resposta
    handles_recursion = int(args[4])  # Indica se o servidor aceita ou não o modo recursivo

    if handles_recursion == 1:
        handles_recursion = True
    elif handles_recursion == 0:
        handles_recursion = False

    if len(args) > 5:
        mode = args[5]  # Modo (Debug/Shy)
    else:
        mode = "debug"  # Modo debug por default

    if mode != "shy" and mode != "debug":
        raise InvalidArgument("Invalid mode")

    if not validate_port(port):
        raise InvalidPortError

    try:
        server = parser_configuration(config_path, port, timeout, handles_recursion, mode)  # Parser dos dados

    except InvalidIPError:
        raise

    return server
