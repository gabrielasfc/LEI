package Connections;

import java.io.*;
import java.net.Socket;
import java.util.concurrent.locks.ReentrantLock;

public class TaggedConnection implements AutoCloseable {
    public static class Frame {
        public final int tag;
        public final byte[] data;

        /**
         * Constructor of a Frame
         * @param tag tag
         * @param data data of frame
         */
        public Frame(int tag, byte[] data) {
            this.tag = tag;
            this.data = data;
        }
    }

    private final Socket socket;
    private final DataInputStream is;
    private final DataOutputStream os;
    private final ReentrantLock sendLck = new ReentrantLock();
    private final ReentrantLock receiveLck = new ReentrantLock();

    /**
     * Constructor of a TaggedConnection
     * @param socket socket
     * @throws IOException Exception
     */
    public TaggedConnection(Socket socket) throws IOException {
        this.socket = socket;
        this.is = new DataInputStream(new BufferedInputStream(socket.getInputStream())); // input stream
        this.os =  new DataOutputStream(new BufferedOutputStream(socket.getOutputStream())); // output stream
    }

    /**
     * Sends a frame
     * @param frame Frame
     * @throws IOException Exception
     */
    public void send(Frame frame) throws IOException {
        this.send(frame.tag, frame.data);
    }

    /**
     * Sends data with a tag
     * @param tag tag
     * @param data data
     * @throws IOException Exception
     */
    public void send(int tag, byte[] data) throws IOException {
        try{
            this.sendLck.lock();
            this.os.writeInt(tag);
            this.os.writeInt(data.length);
            this.os.write(data);
            this.os.flush();
        }
        finally {
            this.sendLck.unlock();
        }
    }

    /**
     * Receives a frame
     * @return returns a new frame
     * @throws IOException Exception
     */
    public Frame receive() throws IOException {
        int tag;
        byte[] data;

        try{
            this.receiveLck.lock();
            tag = this.is.readInt();
            int size = this.is.readInt();
            data = new byte[size];

            this.is.readFully(data);
        }
        finally {
            this.receiveLck.unlock();
        }

        return new Frame(tag, data);
    }

    /**
     * Closes a socket
     * @throws IOException Exception
     */
    public void close() throws IOException {
        this.socket.close();
    }
}