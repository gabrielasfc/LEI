package Exceptions;

public class NonExistentUsernameException extends Exception{
    /**
     * Exception in case of a non existent username
     * @param msg message
     */
    public NonExistentUsernameException(String msg){
        super(msg);
    }
}
