package src.Exceptions;

public class NonExistantProviderException extends Exception{
    /**
     * Cria uma nova exceção de fornecedor não existente, com a mensagem recebida
     * @param msg Mensagem a imprimir mais tarde
     */
    public NonExistantProviderException (String msg){
        super(msg);
    }
}
