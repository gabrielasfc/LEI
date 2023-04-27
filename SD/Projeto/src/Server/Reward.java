package Server;

import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class Reward {
    private Position initialPosition;
    private Position finalPosition;
    private double value;

    /**
     * Constructor of a Reward
     * @param initPos initial Position
     * @param finalPos final Position
     */
    public Reward(Position initPos, Position finalPos) {
        this.initialPosition = initPos;
        this.finalPosition = finalPos;
        this.value = this.calculateValue();
    }

    /**
     * Gets the initial position of a Reward
     * @return Initial Position
     */
    public Position getInitialPosition() {
        return this.initialPosition.clone();
    }

    /**
     * Gets the final position od a reward
     * @return final position
     */
    public Position getFinalPosition() {
        return this.finalPosition.clone();
    }

    /**
     * Gets the value of a reward
     * @return value of a reward
     */
    public double getValue() {
        return this.value;
    }

    /**
     * Sets the initial position of a reward
     * @param pos position
     */
    public void setInitialPosition(Position pos) {
        this.initialPosition = pos;
    }

    /**
     * Sets the final position of a reward
     * @param pos final position
     */
    public void setFinalPosition(Position pos) {
        this.finalPosition = pos;
    }

    /**
     * Sets the value of a reward
     * @param value value
     */
    public void setValue(double value) {
        this.value = value;
    }

    /**
     * Calculates the value of a reward
     * @return value of a reward
     */
    private double calculateValue(){
        double distance = this.initialPosition.distanceTo(this.finalPosition);
        return distance * 1; // 1 euro / km ??
    }

    /**
     * Serialization of a Reward
     * @return returns an array of bytes
     * @throws IOException Exception
     */
    public byte[] serialize() throws IOException {
        ByteArrayOutputStream byteArray = new ByteArrayOutputStream(16);
        DataOutputStream os = new DataOutputStream(byteArray);

        os.write(this.initialPosition.serialize());
        os.write(this.finalPosition.serialize());

        return byteArray.toByteArray();
    }

    /**
     * Deserialization of a reward
     * @param is input stream
     * @return returns a reward
     * @throws IOException Exception
     */
    public static Reward deserialize(DataInputStream is) throws IOException {
        Position initialPosition = Position.deserialize(is);
        Position finalPosition = Position.deserialize(is);

        return new Reward(initialPosition, finalPosition);
    }

    /**
     *  Gets the string representation of a reward
     * @return a reward in the form of a string
     */
    public String toString(){
        return initialPosition.toString() + " -> " + finalPosition.toString();
    }


    /**
     * Checks if two rewards are equal
     * @param o Object being compared
     * @return true if they are equal, false otherwise
     */
    public boolean equals(Object o){
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Reward that = (Reward) o;

        return this.initialPosition.equals(that.initialPosition) && this.finalPosition.equals(that.finalPosition) && this.value == that.value;
    }
}
