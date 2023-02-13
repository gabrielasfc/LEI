# Autores: Gabriela Cunha, Guilherme Varela e Miguel Braga
# Data de criação: 04/12/22
# Data da última atualização: 30/12/22
# Descrição: Exceções
# Última atualização: Argumentos inválidos ao executar o cliente


class InvalidIPError(Exception):
    def __init__(self, message=""):
        self.message = message
        super().__init__("Error running server configurations: Invalid IP address")


class InvalidPortError(Exception):
    def __init__(self, message=""):
        self.message = message
        super().__init__("Error running server configurations: Invalid Port")


class ArgumentsMissingError(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__("Arguments missing")


class TooManyArgumentsError(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__("Too many arguments")


class InvalidArgument(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__("Invalid value")


class InvalidValueTTL(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__("Invalid value for TTL")


class InvalidValuePriority(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__("Invalid value for priority")


class InvalidType(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__("Invalid entry type")


class NameNotFoundError(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__("Name not found")


class InvalidValueSoaserial(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__("Invalid value for SOASERIAL")


class InvalidValueSoarefresh(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__("Invalid value for SOAREFRESH")


class InvalidValueSoaretry(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__("Invalid value for SOARETRY")


class InvalidValueSoaexpire(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__("Invalid value for SOAEXPIRE")


class ZoneTransferFailed(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__("Zone transfer failed")


class ZoneTransferDatabaseIsUpToDate(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__("Database is up to date")
