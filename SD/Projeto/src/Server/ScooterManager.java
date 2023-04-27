package Server;

import Exceptions.*;
import java.util.List;

public interface ScooterManager {
    /**
     * Changes the notifications state on a user
     * @param username Username
     * @param notificationsState New notifications state
     */
    void changeNotificationsState(String username, boolean notificationsState);

    /**
     * Register a user in the server
     * @param username username of the user
     * @param password password of the user
     * @throws UsernameAlreadyExistsException error if the username is already registered
     */
    void register(String username, String password) throws UsernameAlreadyExistsException;

    /**
     * Login a user in the server
     * @param username username of the user
     * @param password password of the user
     * @throws NonExistentUsernameException error if the username doesn't exist in the users collection
     */
    void login(String username, String password) throws NonExistentUsernameException, WrongPasswordException;

    /**
     * List the available scooters in a radius D (pre-configured) of p
     * @param p center of radius where free scooters will be checked
     * @return a list of the positions of the free scooters
     */
    List<Position> listFreeScooters(Position p);

    /**
     * List the available rewards in a radius D (pre-configured) of p
     * @param p center of radius where rewards will be checked
     * @return a list of the positions(initial and final) of the rewards available
     */
    List<List<Position>> listRewards(Position p);

    /**
     * Tries to activate a scooter the closest to a given position, limited by a radius D (pre-configured)
     * @param p center of radius where free scooters will be checked
     * @param username username of the client who activates the scooter
     * @return a reservation containing a reservation code and the position of the scooter found
     * @throws NoScootersAvailableException error if there are no available scooters
     */
    Reservation activateScooter(Position p, String username) throws NoScootersAvailableException;

    /**
     * Parks a scooter given the reservation code and the final position of the ride
     * @param reservationId reservation code
     * @param parkingPosition final position of the scooter
     * @return the cost of the ride or the reward (if applicable)
     */
    double parkScooter(int reservationId, Position parkingPosition) throws InvalidReservationIDException;

    /**
     * Check if there are new rewards on the radius of a given position and waits for that otherwise
     * @param username User to check if its notifications are activated
     * @param p Position
     * @param lastRewards Stores the rewards from last notification (empty at the beginning)
     * @return List of rewards on the radius of a given position
     */
    List<Reward> userNotifications(String username, Position p, List<Reward> lastRewards) throws NotificationsDisabledException;
}
