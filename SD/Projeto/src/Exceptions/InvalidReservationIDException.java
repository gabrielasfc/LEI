package Exceptions;

public class InvalidReservationIDException extends Exception{
    /**
     * Exception in case of an invalid reservation id
     * @param msg message
     */
    public InvalidReservationIDException(String msg){
        super(msg);
    }
}
