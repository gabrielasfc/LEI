import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;


class ServerWorker implements Runnable {
    private Socket socket;

    public ServerWorker(Socket socket) {
        this.socket = socket;
    }

    @Override
    public void run() {
        try {
            int sum = 0;
            int counter = 0;

            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream());

            String line;
            while ((line = in.readLine()) != null) {
                counter++;
                int value = Integer.parseInt(line);
                sum += value;

                out.println(sum);
                out.flush();
            }

            if (counter < 1) counter = 1;

            double avg = (double)sum / (double)counter;
            out.println(avg);
            out.flush();

            socket.shutdownOutput();
            socket.shutdownInput();
            socket.close();
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}

public class Server2 {

    public static void main(String[] args) {
        try {
            ServerSocket ss = new ServerSocket(12345);

            while (true) {
                Socket socket = ss.accept();

                Thread worker = new Thread(new ServerWorker(socket));
                worker.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
