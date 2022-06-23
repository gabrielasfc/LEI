package src.Exceptions;

public class NonExistantLocationException extends Exception{
    /**
     * Cria uma nova exceção de divisão não existente, com a mensagem recebida
     * @param msg Mensagem a imprimir mais tarde
     */
    public NonExistantLocationException (String msg){
        super(msg);
    }
}
