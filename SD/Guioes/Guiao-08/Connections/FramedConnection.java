package Connections;

import java.io.*;
import java.net.Socket;
import java.util.concurrent.locks.ReentrantLock;

public class FramedConnection implements AutoCloseable {
    private final Socket socket;
    private final DataInputStream is;
    private final DataOutputStream os;
    private final ReentrantLock sendLock = new ReentrantLock();
    private final ReentrantLock receiveLock = new ReentrantLock();
    //lock para input e output stream, para aumentar eficiencia
    //read write lock, exclusivo em escrita e partilhado em leituras

    public FramedConnection(Socket socket) throws IOException {
        this.socket = socket;
        this.is = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
        this.os =  new DataOutputStream(new BufferedOutputStream(socket.getOutputStream()));
    }

    public void send(byte[] data) throws IOException {
        try {
            sendLock.lock();
            os.writeInt(data.length); //envio do tamanho dos dados
            os.write(data);
            os.flush();
        } finally {
            sendLock.unlock();
        }
    }

    public byte[] receive() throws IOException {
        byte[] data;

        try {
            receiveLock.lock();
            int size = is.readInt();
            data = new byte[size];

            is.readFully(data); //desbloqueia quando le tudo, garante q nao lemos bocados de mensagens
        } finally {
            receiveLock.unlock();
        }

        return data;
    }

    public void close() throws IOException {
        socket.close();
    }
}

