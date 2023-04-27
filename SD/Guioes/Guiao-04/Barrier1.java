import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Barrier1 {
    private int n; //total de threads
    private int counter; //threads em espera
    private ReentrantLock lock = new ReentrantLock();
    private Condition waitingForThreads = lock.newCondition();

    Barrier1(int N) {
        this.n = N;
        this.counter = 0;
    }

    void await() throws InterruptedException {
        try {
            lock.lock();
            this.counter++;

            if (this.counter < this.n) { //para apenas a última thread sinalizar
                while (this.counter < this.n) {
                    waitingForThreads.await();
                }
            }
            else waitingForThreads.signalAll();
        } finally {
            lock.unlock();
        }
    }
}
