package Server;

import Connections.TaggedConnection;
import Exceptions.*;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;


class ServerWorker implements Runnable{
    private TaggedConnection connection;
    private ScooterManager scooterManager;
    private String clientUsername;

    /**
     * ServerWorker's constructor
     * @param connection TaggedConnection
     * @param scooterManager ScooterManager
     */
    public ServerWorker(TaggedConnection connection, ScooterManager scooterManager){
        this.connection = connection;
        this.scooterManager = scooterManager;
        this.clientUsername = null;
    }

    @Override
    public void run(){
        try{
            while (true){
                TaggedConnection.Frame frame = this.connection.receive();

                if (frame.tag != 1 && frame.tag != 2 && clientUsername == null){
                    continue;
                }

                if(frame.tag == 1){
                    User user = User.deserialize(frame.data);
                    try{
                        this.scooterManager.register(user.getUsername(), user.getPassword());

                        ByteArrayOutputStream byteStream = new ByteArrayOutputStream(1);
                        DataOutputStream os = new DataOutputStream(byteStream);
                        os.writeBoolean(true); // All good

                        this.connection.send(1, byteStream.toByteArray());
                    }
                    catch(UsernameAlreadyExistsException e){
                        ByteArrayOutputStream byteStream = new ByteArrayOutputStream(1);
                        DataOutputStream os = new DataOutputStream(byteStream);
                        os.writeBoolean(false); // Something went wrong

                        this.connection.send(1, byteStream.toByteArray());
                    }
                }
                else if(frame.tag == 2){
                    User user = User.deserialize(frame.data);

                    try{
                        this.scooterManager.login(user.getUsername(), user.getPassword());

                        ByteArrayOutputStream byteStream = new ByteArrayOutputStream(1);
                        DataOutputStream os = new DataOutputStream(byteStream);
                        os.writeBoolean(true); // All good

                        this.clientUsername = user.getUsername();

                        this.connection.send(2, byteStream.toByteArray());
                    }
                    catch(Exception e){
                        ByteArrayOutputStream byteStream = new ByteArrayOutputStream(1);
                        DataOutputStream os = new DataOutputStream(byteStream);
                        os.writeBoolean(false); // Something went wrong

                        this.connection.send(2, byteStream.toByteArray());
                    }
                }
                else if(frame.tag == 3){
                    ByteArrayInputStream byteInputStream = new ByteArrayInputStream(frame.data);
                    DataInputStream is = new DataInputStream(byteInputStream);
                    Position p = Position.deserialize(is);
                    List<Position> positions = this.scooterManager.listFreeScooters(p);

                    ByteArrayOutputStream byteStream = new ByteArrayOutputStream(4 + positions.size()*8);
                    DataOutputStream os = new DataOutputStream(byteStream);

                    os.writeInt(positions.size()); // Comprimento da lista
                    for(Position pos : positions){
                        os.write(pos.serialize());
                    }

                    this.connection.send(3, byteStream.toByteArray());
                }
                else if (frame.tag == 4) {
                    ByteArrayInputStream byteInputStream = new ByteArrayInputStream(frame.data);
                    DataInputStream is = new DataInputStream(byteInputStream);
                    Position p = Position.deserialize(is);
                    List<List<Position>> rewards = this.scooterManager.listRewards(p);

                    ByteArrayOutputStream byteStream = new ByteArrayOutputStream(4 + rewards.size()*8);
                    DataOutputStream os = new DataOutputStream(byteStream);

                    os.writeInt(rewards.size());
                    for (List<Position> list : rewards) {
                        os.write(list.get(0).serialize());
                        os.write(list.get(1).serialize());
                    }

                    this.connection.send(4, byteStream.toByteArray());
                }
                else if (frame.tag == 5) {
                    ByteArrayInputStream byteInputStream = new ByteArrayInputStream(frame.data);
                    DataInputStream is = new DataInputStream(byteInputStream);
                    Position p = Position.deserialize(is);

                    try {
                        Reservation reservation = this.scooterManager.activateScooter(p, this.clientUsername);

                        ByteArrayOutputStream byteStream = new ByteArrayOutputStream(12); // (x) 4 bytes + (y) 4 bytes + (reservation_id) 4 bytes
                        DataOutputStream os = new DataOutputStream(byteStream);
                        os.writeInt(reservation.getReservationID());
                        os.write(reservation.getInitialPosition().serialize());

                        this.connection.send(5, byteStream.toByteArray());
                    }
                    catch (Exception e){
                        ByteArrayOutputStream byteStream = new ByteArrayOutputStream(4);
                        DataOutputStream os = new DataOutputStream(byteStream);
                        os.writeInt(-1); // Something went wrong

                        this.connection.send(5, byteStream.toByteArray());
                    }
                }
                else if (frame.tag == 6) {
                    ByteArrayInputStream byteInputStream = new ByteArrayInputStream(frame.data);
                    DataInputStream is = new DataInputStream(byteInputStream);

                    Position p = Position.deserialize(is);


                    int reservationID = is.readInt();

                    try{
                        double cost = this.scooterManager.parkScooter(reservationID, p);

                        ByteArrayOutputStream byteStream = new ByteArrayOutputStream(8);  // 8 - double
                        DataOutputStream os = new DataOutputStream(byteStream);
                        os.writeDouble(cost);

                        this.connection.send(6, byteStream.toByteArray());
                    }
                    catch (InvalidReservationIDException e){

                    }
                }
                else if (frame.tag == 7){
                    ByteArrayInputStream byteInputStream = new ByteArrayInputStream(frame.data);
                    DataInputStream is = new DataInputStream(byteInputStream);
                    boolean notificationsOn = is.readBoolean();
                    this.scooterManager.changeNotificationsState(this.clientUsername, notificationsOn);

                    if (!notificationsOn){
                        ByteArrayOutputStream byteStream = new ByteArrayOutputStream(1);  // 1 - boolean
                        DataOutputStream os = new DataOutputStream(byteStream);
                        os.writeBoolean(notificationsOn);

                        this.connection.send(7, byteStream.toByteArray());
                    }
                    else if (notificationsOn){ // Ler a posição
                        int x = is.readInt();
                        int y = is.readInt();
                        Position p = new Position(x, y);

                        List<Reward> lastRewards = new ArrayList<>();
                        List<Reward> newRewards;

                        while(true){ // Notificações ligadas
                            try{
                                newRewards = this.scooterManager.userNotifications(this.clientUsername, p, lastRewards);
                                lastRewards = newRewards;
                            }
                            catch (NotificationsDisabledException e){
                                break;
                            }

                            ByteArrayOutputStream byteStream = new ByteArrayOutputStream(4);  // 4 - int
                            DataOutputStream os = new DataOutputStream(byteStream);

                            os.writeBoolean(true);

                            int numRewards = newRewards.size();
                            if (numRewards > 0) {
                                os.writeInt(numRewards);

                                for (Reward r : newRewards) {
                                    os.write(r.serialize());
                                }

                                this.connection.send(7, byteStream.toByteArray());
                            }
                        }
                    }
                }
            }
        }
        catch (IOException ignored){}
    }
}

public class Server {
    final static int WORKERS_PER_CONNECTION = 3;
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(12345);
        ScooterManager scooterManager = new ScooterManagerI(2, 10, 15);

        while(true){
            Socket socket = serverSocket.accept();
            TaggedConnection connection = new TaggedConnection(socket);
            ServerWorker serverWorker = new ServerWorker(connection, scooterManager);

            for(int i = 0; i < WORKERS_PER_CONNECTION; i++){
                new Thread(serverWorker).start();
            }
        }
    }
}
