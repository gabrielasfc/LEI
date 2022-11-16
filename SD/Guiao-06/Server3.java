import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.locks.ReentrantLock;

class Register {
        private int sum;
        private int counter;
        private ReentrantLock lock;

        public Register() {
            this.sum = 0;
            this.counter = 0;
            lock = new ReentrantLock();
        }

        public void add(int value) {
            try {
                lock.lock();

                this.counter++;
                this.sum += value;
            } finally {
                lock.unlock();
            }
        }

        public double avg() {
            try {
                lock.lock();

                if (this.counter < 1) this.counter = 1;
                return (double)this.sum / (double)this.counter;
            } finally {
                lock.unlock();
            }
        }
}

class ServerWorker2 implements Runnable {
    private Socket socket;
    private Register register;

    public ServerWorker2(Socket socket, Register register) {
        this.socket = socket;
        this.register = register;
    }

    @Override
    public void run() {
        try {
            int sum = 0;

            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream());

            String line;
            while ((line = in.readLine()) != null) {
                int value = Integer.parseInt(line);
                sum += value;
                register.add(value);

                out.println(sum);
                out.flush();
            }

            out.println(register.avg());
            out.flush();

            socket.shutdownOutput();
            socket.shutdownInput();
            socket.close();
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}

public class Server3 {

    public static void main(String[] args) {
        try {
            ServerSocket ss = new ServerSocket(12345);
            Register reg = new Register();

            while (true) {
                Socket socket = ss.accept();

                Thread worker = new Thread(new ServerWorker2(socket, reg));
                worker.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
