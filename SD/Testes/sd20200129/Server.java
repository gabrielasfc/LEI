import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.List;

class ServerWorker implements Runnable {
    private Socket socket;
    private IFicheiros ficheiros;

    public ServerWorker(Socket socket, IFicheiros ficheiros) {
        this.socket = socket;
        this.ficheiros = ficheiros;
    }

    public void run() {
        BufferedReader is = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        PrintWriter os = new PrintWriter(socket.getOutputStream());

        int opt = Integer.parseInt(is.readLine());

        if (opt == 1) { // usar ficheiro
            String path = is.readLine();
            this.ficheiros.using(path);

            // deixar de usar ficheiro
            int modified = Integer.parseInt(is.readLine());
            if (modified == 0) this.ficheiros.notUsing(path, false);
            else if (modified == 1) this.ficheiros.notUsing(path, true);
        }

        else if (opt == 2) { // backup
            List<String> paths = this.ficheiros.startBackup();

            for (String path : paths) {
                os.println(path);
            }
            os.flush();

            //terminar backup
            int end = Integer.parseInt(is.readLine());
            if (end == 3) {
                this.ficheiros.endBackup();
            }
        }

        socket.close();
    }
}

public class Server {
    public static void main(String[] args) {
        ServerSocket serverSocket = new ServerSocket(12345);
        IFicheiros ficheiros = new Ficheiros();

        while (true) {
            Socket socket = serverSocket.accept();
            Thread worker = new Thread(new ServerWorker(socket, ficheiros));
            worker.start();
        }
    }
}
