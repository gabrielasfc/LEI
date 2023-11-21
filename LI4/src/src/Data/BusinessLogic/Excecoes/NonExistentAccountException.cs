namespace src.Data.BusinessLogic.Excecoes;
public class NonExistentAccountException : Exception
{

    public NonExistentAccountException(string message)
        : base(message) { }
}

