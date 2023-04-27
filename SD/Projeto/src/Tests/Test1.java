package Tests;

import Exceptions.NonExistentUsernameException;
import Exceptions.UsernameAlreadyExistsException;
import Exceptions.WrongPasswordException;
import Server.Position;
import Server.Reservation;
import Server.ScooterManagerI;

public class Test1 {
    public static void main(String[] args) throws UsernameAlreadyExistsException, NonExistentUsernameException, WrongPasswordException, InterruptedException {
        ScooterManagerI sm = new ScooterManagerI(20, 20, 10);
        sm.register("miguel", "mike");
        sm.login("miguel", "mike");

        int threadNum = 10;
        Thread t[] = new Thread[threadNum];

        for (int i=0; i<threadNum; i++){
            t[i] = new Thread(() -> {
                Reservation r=null;
                try{
                    r = sm.activateScooter(new Position(1,1), "miguel");
                } catch(Exception e){
                    System.out.println(e.getMessage());
                }
                if (r != null) System.out.println(r.toString());
            });
            t[i].start();
        }

        for(int i=0; i<threadNum; i++){
            t[i].join();
        }

        System.out.println("Terminei");


    }

}
