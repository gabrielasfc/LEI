package Exceptions;

public class UsernameAlreadyExistsException extends Exception{
    /**
     * Exceção para erro caso já exista um nome igual
     * @param msg Mensagem
     */
    public UsernameAlreadyExistsException(String msg){
        super(msg);
    }
}
