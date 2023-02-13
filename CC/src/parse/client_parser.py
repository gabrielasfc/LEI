# Data de criação: 30/12/22
# Data da última atualização: 30/12/22
# Descrição: Cria um objeto Client a partir dos argumentos de input
# Última atualização: Criação do módulo

import exceptions


def parser_client(args):
    args.pop(0)

    args_split = args[0].split(":")

    ip_address = args_split[0]
    port = 5353  # porta default
    domain = args[1]
    type = args[2]
    flags = "Q"  # Flags default
    timeout = 10  # Valor de timeout default
    debug = True  # Modo debug ligado por default

    if len(args_split) > 1:  # Se a porta for especificada, atualizar
        port = int(args_split[1])

    address = (ip_address, port)

    if 4 <= len(args) <= 6:
        if args[3] == "R":
            flags = "Q+R"

            if len(args) > 4:
                if args[4].isdigit():
                    timeout = int(args[4])

                    if args[5] == "shy":
                        debug = False

                    elif args[5] != "debug":
                        raise exceptions.InvalidArgument("Invalid mode")

                elif args[4] == "shy":
                    debug = False

                elif args[4] != "debug":
                    raise exceptions.InvalidArgument("Invalid timeout or mode")

        elif args[3].isdigit():
            timeout = int(args[3])

            if len(args) > 4:
                if args[4] == "shy":
                    debug = False

                elif args[4] != "debug":
                    raise exceptions.InvalidArgument("Invalid mode")

        elif args[3] == "shy":
            debug = False

        elif args[3] != "debug":
            raise exceptions.InvalidArgument("Invalid flag, timeout or mode")

    return address, domain, type, flags, timeout, debug