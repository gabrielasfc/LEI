package Exceptions;

public class NotificationsDisabledException extends Exception {
    /**
     * Exception in case of notifications disabler doesnt work
     * @param msg message
     */
    public NotificationsDisabledException(String msg) {
        super(msg);
    }
}
