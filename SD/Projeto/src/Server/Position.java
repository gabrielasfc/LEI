package Server;

import java.io.*;

public class Position {
    private int x;
    private int y;

    /**
     * Constructor of a Position
     */
    public Position() {
        this.x = 0;
        this.y = 0;
    }

    /**
     * Constructor of a Position given x and y values
     * @param x x value
     * @param y y value
     */
    public Position(int x, int y) {
        this.x = x;
        this.y = y;
    }

    /**
     * Constructor of a Position given a position
     * @param pos Given position
     */
    public Position(Position pos) {
        this.x = pos.getX();
        this.y = pos.getY();
    }

    /**
     * Gets the x value of a Position
     * @return x value
     */
    public int getX() {
        return this.x;
    }

    /**
     * Gets the y value of a Position
     * @return y value
     */
    public int getY() {
        return this.y;
    }

    /**
     * Sets the x value of a Position
     * @param x x value
     */
    public void setX(int x) {
        this.x = x;
    }

    /**
     * Sets the y value of a Position
     * @param y y value
     */
    public void setY(int y) {
        this.y = y;
    }

    /**
     * Checks if the current position is in a given radius of a center position
     * @param center center of the radius
     * @param radius radius of circumference
     */
    public boolean inRadius(Position center, int radius){
        return this.distanceTo(center) <= (double)radius;
    }

    /**
     * Checks if the current position is in a given radius of a center position
     * @param x x value of the center of the radius
     * @param y y value of the center of the radius
     * @param radius radius of circumference
     */
    public boolean inRadius(int x, int y, int radius){
        return this.distanceTo(x, y) <= (double)radius;
    }

    /**
     * Calculates the distance between two points (the current one and other)
     * @param other the other point
     * @return the distance (float) between these two points
     */
    public double distanceTo(Position other){
        return Math.sqrt(Math.pow(this.x - other.x, 2) + Math.pow(this.y - other.y, 2));
    }

    /**
     * Calculates the distance between two points
     * @param x x value
     * @param y y value
     * @return the distance (double) between these two points
     */
    public double distanceTo(int x, int y){
        return Math.sqrt(Math.pow(this.x - x, 2) + Math.pow(this.y - y, 2));
    }

    /**
     * Deserialization of a position
     * @param is Input Stream
     * @return returns a position
     * @throws IOException Exception
     */
    public static Position deserialize(DataInputStream is) throws IOException {
        int x = is.readInt();
        int y = is.readInt();

        return new Position(x,y);
    }

    /**
     * Serializes a position
     * @return returns an array of bytes
     * @throws IOException Exception
     */
    public byte[] serialize() throws IOException{
        ByteArrayOutputStream byteArray = new ByteArrayOutputStream(8);
        DataOutputStream os = new DataOutputStream(byteArray);

        os.writeInt(this.x);
        os.writeInt(this.y);

        return byteArray.toByteArray();
    }

    /**
     *  Gets the string representation of a position
     * @return a position in the form of a string
     */
    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("");
        sb.append("(").append(this.x);
        sb.append(",").append(this.y);
        sb.append(")");
        return sb.toString();
    }

    /**
     * Checks if two positions are equal
     * @param o Object being compared
     * @return true if they are equal, false otherwise
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Position that = (Position) o;
        return this.x == that.getX() && this.y == that.getY();
    }

    /**
     * Clones the instance
     * @return a copy of current instance
     */
    @Override
    public Position clone() {
        return new Position(this);
    }
}
