namespace src.Data.BusinessLogic.Excecoes;
public class AlreadyRegisteredException : Exception
{
    public AlreadyRegisteredException(string message)
        : base(message) { }   
}

