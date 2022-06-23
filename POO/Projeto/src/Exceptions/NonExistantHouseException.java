package src.Exceptions;

public class NonExistantHouseException extends Exception{
    /**
     * Cria uma nova exceção de casa não existente, com a mensagem recebida
     * @param msg Mensagem a imprimir mais tarde
     */
    public NonExistantHouseException (String msg){
        super(msg);
    }
}
