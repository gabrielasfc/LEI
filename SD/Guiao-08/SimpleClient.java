import java.net.Socket;
import Connections.FramedConnection;

// camada no cliente e servidor que abstrai mensagens (FramedConnection)
// cliente e servidor não querem saber o que a mensagem é, são apenas bytes
public class SimpleClient {
    public static void main(String[] args) throws Exception {
        Socket s = new Socket("localhost", 12345);
        FramedConnection c = new FramedConnection(s);

        // send requests
        c.send("Ola".getBytes());
        c.send("Hola".getBytes());
        c.send("Hello".getBytes());

        // get replies
        byte[] b1 = c.receive();
        byte[] b2 = c.receive();
        byte[] b3 = c.receive();
        //ordem chega trocada porque o servidor é multi threaded
        //acrescentar uma etiqueta nos pedidos para sabermos a ordem no final -> TaggedConnection

        System.out.println("Some Reply: " + new String(b1));
        System.out.println("Some Reply: " + new String(b2));
        System.out.println("Some Reply: " + new String(b3));

        c.close();
    }
}
