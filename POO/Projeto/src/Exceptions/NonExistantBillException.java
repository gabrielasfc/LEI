package src.Exceptions;

public class NonExistantBillException extends Exception{
    /**
     * Cria uma nova exceção de fatura não existente, com a mensagem recebida
     * @param msg Mensagem a imprimir mais tarde
     */
    public NonExistantBillException(String msg){
        super(msg);
    }
}