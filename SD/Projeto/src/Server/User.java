package Server;

import java.io.*;
import java.util.concurrent.locks.ReentrantLock;

public class User {
    private String username;
    private String password;
    private boolean notificationsState;
    public ReentrantLock lock;


    /**
     * User's Constructor
     */
    public User() {
        this.username = "";
        this.password = "";
        this.notificationsState = false;
        this.lock = new ReentrantLock();
    }

    /**
     * User's constructor with username and password
     * @param username user's name
     * @param password user's password
     */
    public User(String username, String password) {
        this.username = username;
        this.password = password;
        this.notificationsState = false;
        this.lock = new ReentrantLock();
    }

    /**
     * User's Constructor with an user
     * @param c user
     */
    public User(User c) {
        this.username = c.getUsername();
        this.password = c.getPassword();
        this.notificationsState = c.getNotificationsState();
        this.lock = new ReentrantLock();
    }

    /**
     * Gets username of an user
     * @return user's name
     */
    public String getUsername() {
        return this.username;
    }

    /**
     * Gets the password of an user
     * @return user's password
     */
    public String getPassword() {
        return this.password;
    }

    /**
     * Gets the notification's state
     * @return notification's state
     */
    public Boolean getNotificationsState(){
        return this.notificationsState;
    }

    /**
     * Sets the username
     * @param username user's name
     */
    public void setUsername(String username) {
        this.username = username;
    }

    /**
     * Sets the password
     * @param password password's user
     */
    public void setPassword(String password) {
        this.password = password;
    }

    /**
     * Sets the notification's state
     * @param onOff state
     */
    public void setNotificationsState(Boolean onOff){
        this.notificationsState = onOff;
    }

    /**
     * Serializes an user
     * @return array of bytes
     * @throws IOException Exception
     */
    public byte[] serialize() throws IOException{
        int size = 8 + this.username.length() + this.password.length();

        ByteArrayOutputStream byteArray = new ByteArrayOutputStream(size);
        DataOutputStream os = new DataOutputStream(byteArray);

        os.writeUTF(this.username);
        os.writeUTF(this.password);

        return byteArray.toByteArray();
    }

    /**
     * Deserializes an user
     * @param data data
     * @return New user
     * @throws IOException Exception
     */
    public static User deserialize(byte[] data) throws IOException {
        DataInputStream is = new DataInputStream(new ByteArrayInputStream(data));
        String username = is.readUTF();
        String password = is.readUTF();

        return new User(username, password);
    }
}
