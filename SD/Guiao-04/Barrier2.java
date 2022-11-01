import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Barrier2 {
    private int n; //total de threads
    private int counter; //threads em espera
    private int round;
    private ReentrantLock lock = new ReentrantLock();
    private Condition waitingForThreads = lock.newCondition();

    Barrier2(int N) {
        this.n = N;
        this.counter = 0;
        this.round = 0;
    }

    void await() throws InterruptedException {
        try {
            lock.lock();
            this.counter++;

            if (this.counter < this.n) {
                int currRound = this.round;
                while (this.round == currRound) {
                    waitingForThreads.await();
                }
            }
            else {
                this.counter = 0;
                this.round++;
                waitingForThreads.signalAll();
            }
        } finally {
            lock.unlock();
        }
    }
}
