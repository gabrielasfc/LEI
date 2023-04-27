package Exceptions;

public class WrongPasswordException extends Exception {
    /**
     * Exceção para erro caso a password introduzida não coincidir com a do username inserido
     * @param msg Mensagem
     */
    public WrongPasswordException(String msg){
        super(msg);
    }
}
