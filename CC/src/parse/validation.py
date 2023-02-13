# Autores: Gabriela Cunha, Guilherme Varela e Miguel Braga
# Data de criação: 02/11/22
# Data da última atualização: 28/12/22
# Descrição: Validação de endereços IP e portas
# Última atualização: validate_port a receber já um inteiro

def validate_port(port):
    """
    Verifica se uma porta é válida - se está entre 1 e 65535
    :param port: Porta
    :return: Bool
    """
    return 1 < port < 65535


def validate_ip(ip_address):
    """
    Verifica se um endereço IP é válido
    :param ip_address: Endereço IP
    :return: Bool
    """
    ip_parts = ip_address.split('.')
    ip_parts[-1] = (ip_parts[-1].split(':'))[0]  # retirar porta

    length = len(ip_address.split(':'))
    port_bool = True

    if length > 2:
        port_bool = False

    elif length == 2:
        port = (ip_address.split(':'))[-1]
        port_bool = validate_port(int(port))

    return len(ip_parts) == 4 and all(0 <= int(part) < 256 for part in ip_parts) and port_bool