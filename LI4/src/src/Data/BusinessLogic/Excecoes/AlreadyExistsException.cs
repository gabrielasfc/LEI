namespace src.Data.BusinessLogic.Excecoes;
public class AlreadyExistsException : Exception
{
    public AlreadyExistsException(string message) 
        : base(message) { }
}

