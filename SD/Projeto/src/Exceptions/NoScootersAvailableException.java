package Exceptions;

public class NoScootersAvailableException extends Exception{
    /**
     * Exception in case of no scooters available
     * @param msg message
     */
    public NoScootersAvailableException(String msg){
        super(msg);
    }
}
