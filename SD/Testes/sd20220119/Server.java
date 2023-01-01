import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

class ServerWorker implements Runnable {
    private Socket socket;
    private Votacao votacao;

    public ServerWorker(Socket socket, Votacao votacao) {
        this.socket = socket;
        this.votacao = votacao;
    }

    public void run() {
        BufferedReader is = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
        PrintWriter os = new PrintWriter(socket.getOutputStream();

        int cabine;

        int id = Integer.parseInt(is.readLine());

        if (!this.votacao.verifica(id)) {
            os.println("INVALIDO");
        }
        else {
            cabine = this.votacao.esperaPorCabine();
            os.println("VOTE NA CABINE " + cabine);
        }

        os.flush();

        int voto = Integer.parseInt(is.readLine());
        this.votacao.vota(voto);
        this.votacao.desocupaCabine(cabine);

        os.println("1");
        os.flush();

        socket.close();
    }
}

public class Server {
    public static void main(String[] args) {
        ServerSocket serverSocket = new ServerSocket(12345);
        Votacao votacao = new Votacao();

        while (true) {
            Socket socket = serverSocket.accept();
            Thread worker = new Thread(new ServerWorker(socket, votacao));
            worker.start();
        }
    }
}
