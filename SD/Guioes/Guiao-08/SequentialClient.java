import java.net.Socket;
import Connections.TaggedConnection;
import static Connections.TaggedConnection.Frame;

public class SequentialClient {

    public static void main(String[] args) throws Exception {
        Socket s = new Socket("localhost", 12345);
        TaggedConnection c =  new TaggedConnection(s);

        // send request
        c.send(1, "Ola".getBytes());

        // one-way (não há resposta)
        c.send(0, ":-p".getBytes());

        // get reply
        Frame f = c.receive();
        assert f.tag == 1;
        System.out.println("Reply: " + new String(f.data));

        // get stream of messages until empty msg
        c.send(2, "ABCDE".getBytes());

        for (;;) {
            f = c.receive();

            assert f.tag == 2;
            if (f.data.length == 0) break;

            System.out.println("From stream: " + new String(f.data));
        }

        c.close();
    }
}
