package Tests;

import Server.ScooterManagerI;

public class UltimateDeadlockTest {
    public static void main(String[] args) throws InterruptedException {
        ScooterManagerI sm = new ScooterManagerI(20,20,1000,2);

        int numThreads = 20000;
        Thread t[] = new Thread[numThreads];

        for(int i=0; i<numThreads; i++){
            t[i] = new Thread(() -> {
                new RandomizeRequest(sm).doStuff();
            });
            t[i].start();
        }

        for(int i=0; i<numThreads; i++){
            t[i].join();
        }

        System.out.println("Todas terminaram");

    }
}
