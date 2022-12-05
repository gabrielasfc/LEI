package Connections;

import java.io.*;
import java.net.Socket;
import java.util.concurrent.locks.ReentrantLock;

//TaggedConnection -> Primeiro escrevemos a tag e dps a frame (tag | size | data)
public class TaggedConnection implements AutoCloseable {
    private final Socket socket;
    private final DataInputStream is;
    private final DataOutputStream os;
    private final ReentrantLock sendLock = new ReentrantLock();
    private final ReentrantLock receiveLock = new ReentrantLock();

    public static class Frame {
        public final int tag;
        public final byte[] data;

        public Frame(int tag, byte[] data) {
            this.tag = tag;
            this.data = data;
        }
    }

    public TaggedConnection(Socket socket) throws IOException {
        this.socket = socket;
        this.is = new DataInputStream(new BufferedInputStream(socket.getInputStream())); // input stream
        this.os =  new DataOutputStream(new BufferedOutputStream(socket.getOutputStream())); // output stream
    }

    public void send(Frame frame) throws IOException {
        this.send(frame.tag, frame.data);
    }

    public void send(int tag, byte[] data) throws IOException {
        try {
            sendLock.lock();

            os.writeInt(tag);
            os.writeInt(data.length);
            os.write(data);
            os.flush();
        } finally {
            sendLock.unlock();
        }
    }

    public Frame receive() throws IOException {
        int tag;
        byte[] data;

        try {
            receiveLock.lock();

            tag = is.readInt();
            int size = is.readInt();
            data = new byte[size];

            is.readFully(data);
        } finally {
            receiveLock.unlock();
        }

        return new Frame(tag, data);
    }

    public void close() throws IOException {
        socket.close();
    }
}