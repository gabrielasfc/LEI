namespace src.Data.BusinessLogic.Excecoes;

public class WrongPasswordException : Exception
{

    public WrongPasswordException(string message)
        : base(message) { }
}

