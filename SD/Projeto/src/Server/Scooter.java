package Server;

import java.util.concurrent.locks.ReentrantLock;

public class Scooter {
    private Position position;
    public ReentrantLock lockScooter;
    private boolean isFree;

    /**
     * Scooter's Constructor
     */
    public Scooter() {
        this.position = null;
        this.lockScooter = new ReentrantLock();
        this.isFree = true;
    }

    /**
     * Scooter's Constructor with a position
     * @param position position
     */
    public Scooter(Position position) {
        this.position = position;
        this.lockScooter = new ReentrantLock();
        this.isFree = true; // mudar
    }

    /**
     * Scooter's Constructor with a scooter
     * @param other
     */
    public Scooter(Scooter other){
        this.position = other.position.clone();
        this.lockScooter = new ReentrantLock();
        this.isFree = true; // mudar
    }

    /**
     * Gets the position of a scooter
     * @return position
     */
    public Position getPosition() {
        return this.position.clone();
    }

    /**
     * Sets the position of a scooter
     * @param pos position
     */
    public void setPosition(Position pos) {
        this.position = pos;
    }

    /**
     * Gets the state of a scooter
     * @return state of a scooter
     */
    public boolean getIsFree() { return this.isFree; }

    /**
     * Sets the state of a scooter
     * @param b state
     */
    public void setIsFree(boolean b) { this.isFree = b; }

    /**
     * Clones a scooter
     * @return Cloned scooter
     */
    public Scooter clone(){
        return new Scooter(this);
    }
}
