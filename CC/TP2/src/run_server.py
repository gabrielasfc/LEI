# Data de criação: 13/11/22
# Data da última atualização: 30/12/22
# Descrição: Executa um servidor
# Última atualização: Separação do parse do servidor em outro módulo

from parse.server_parser import *
from exceptions import *


def main():
    """
    Programa que corre um servidor
    """
    try:
        server = parser_server(sys.argv)

    except InvalidIPError:
        sys.stdout.write("Error running server configuration: Invalid IP address")
        return
    except InvalidPortError:
        sys.stdout.write("Error running server configuration: Invalid Port")
        return
    except InvalidArgument as e:
        sys.stdout.write("Error running server configuration: " + e.message)
        return

    if len(server.config["SS"].values()) != 0:  # Só recebe pedidos de ZT se for primário para algum domínio
        threading.Thread(target=server.sp_zone_transfer).start()

    for domain in server.config["SP"].keys():  # Vai pedir ZT para todos os seus servidores primários
        threading.Thread(target=server.ss_zone_transfer, args=(domain,)).start()

    threading.Thread(target=server.receive_queries).start()  # Thread para receber mensagens (socket UDP)


if __name__ == "__main__":
    main()
