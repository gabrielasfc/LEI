package Server;

import java.time.LocalDateTime;

public class Reservation {

    private int reservationID;
    private Scooter scooter;
    private Position initialPosition;
    private LocalDateTime timestamp;
    private String username;
    private static int idCount = 0;

    /**
     * Constructor of a reservation of a scooter to a determined user
     * @param scooter scooter
     * @param username user
     */
    public Reservation(Scooter scooter, String username) {
        this.reservationID = idCount++;
        this.scooter = scooter;
        this.initialPosition = scooter.getPosition();
        this.timestamp = LocalDateTime.now();
        this.username = username;
    }

    /**
     * Constructor of a reservation
     * @param codReservation code reservation
     * @param p Position
     */
    public Reservation(int codReservation, Position p) {
        this.reservationID = codReservation;
        this.initialPosition = p;
    }

    /**
     * Gets the reservation id
     * @return Reservation ID
     */
    public int getReservationID() {
        return this.reservationID;
    }

    /**
     * Gets a scooter
     * @return Returns a scooter
     */
    public Scooter getScooter(){
        return this.scooter;
    }

    /**
     * Gets the initial position of a scooter
     * @return Position
     */
    public Position getInitialPosition(){
        return this.initialPosition.clone();
    }

    /**
     * Gets the time of a reservation
     * @return time
     */
    public LocalDateTime getTimestamp() {
        return this.timestamp;
    }

    /**
     * Gets the username of the user who made the reservation
     * @return username
     */
    public String getUsername() {
        return this.username;
    }

    /**
     * Sets the initial position of a reservation
     * @param initialPosition initial position
     */
    public void setInitialPosition(Position initialPosition){
        this.initialPosition = initialPosition.clone();
    }

    /**
     * Sets time of a reservation
     * @param timestamp time
     */
    public void setTimestamp(LocalDateTime timestamp) {
        this.timestamp = timestamp;
    }

    /**
     * Sets the username of the user who made the reservation
     * @param username name
     */
    public void setUsername(String username) {
        this.username = username;
    }

    /**
     * Gets the string representation of a reservation
     * @return a reservation in the form of a string
     */
    @Override
    public String toString(){
        return this.reservationID + " , " + this.initialPosition + " , " + this.username + " , " + this.timestamp + "\n";
    }
}
