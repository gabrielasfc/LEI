package Tests;

import Server.Position;
import Server.Reward;
import Server.ScooterManagerI;

import java.util.ArrayList;
import java.util.List;

public class Test4 {
    public static void main(String[] args) throws InterruptedException {
        ScooterManagerI sm = new ScooterManagerI(20, 20, 11);

        int threadNum = 10;
        Thread t[] = new Thread[threadNum*2];
        int i=0;
        for (; i<threadNum; i++){
            int finalI = i;
            t[i] = new Thread(() -> {
                try{
                    sm.register(Integer.toString(finalI), "pass");
                    sm.login(Integer.toString(finalI), "pass");

                    List<Reward> rewards = sm.userNotifications(Integer.toString(finalI), new Position(1,2), new ArrayList<>());
                    if (rewards != null){
                        for(Reward r: rewards){
                            System.out.println(r.toString());
                        }
                    }
                    System.out.println(Thread.currentThread().getName() + " finished!");

                } catch(Exception e){
                    System.out.println("Fail in thread " + Thread.currentThread().getName());
                }
            });
            t[i].start();
            //Thread.sleep(10);
        }

        for (; i<threadNum*2; i++){
            int finalI = i;
            t[i] = new Thread(() -> {
                try {
                    sm.register(Integer.toString(finalI), "pass");
                    sm.login(Integer.toString(finalI), "pass");

                    System.out.println(Thread.currentThread().getName() + " finished!");
                    sm.activateScooter(new Position(1, 1), Integer.toString(finalI));

                } catch (Exception e) {
                    System.out.println("Fail in thread " + Thread.currentThread().getName());
                }
            });
            t[i].start();
            Thread.sleep(1000);
        }

        for(int j=0; j<threadNum*2; j++){
            t[j].join();
        }

        System.out.println("Terminei");
    }
}
