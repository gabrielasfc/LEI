import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

class ServerWorker implements Runnable {
    Socket socket;
    IControloTrafegoAereo controloTrafegoAereo;

    public ServerWorker(Socket socket, IControloTrafegoAereo controloTrafegoAereo) {
        this.socket = socket;
        this.controloTrafegoAereo = controloTrafegoAereo;
    }

    public void run() {
        BufferedReader is = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        PrintWriter os = new PrintWriter(socket.getOutputStream());

        int opt = Integer.parseInt(is.readLine());

        if (opt == 0) { // pedido aterragem
            int pista = this.controloTrafegoAereo.pedirParaAterrar();
            this.controloTrafegoAereo.aterrou(pista);
        }
        else if (opt == 1) { // pedido descolagem
            int pista = this.controloTrafegoAereo.pedirParaDescolar();
            this.controloTrafegoAereo.descolou(pista);
        }

        socket.close();
    }

}

public class Server {
    public static void main(String[] args) {
        ServerSocket serverSocket = new ServerSocket(12345);
        IControloTrafegoAereo controloTrafegoAereo = new ControloTrafegoAereo();

        while (true) {
            Socket socket = serverSocket.accept();
            Thread worker = new Thread(new ServerWorker(socket, controloTrafegoAereo));
            worker.start();
        }

    }
}
