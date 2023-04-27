import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Agreement {
    private int n; //total de threads
    private int counter; //threads em espera
    private int round;
    private int[] values;
    private ReentrantLock lock = new ReentrantLock();
    private Condition waitingForThreads = lock.newCondition();

    Agreement(int N) {
        this.n = N;
        this.counter = 0;
        this.round = 0;
        this.values = new int[N];
    }

    public int propose(int choice) throws InterruptedException {
        try {
            lock.lock();

            this.values[this.counter] = choice;
            this.counter++;

            if (this.counter < this.n){
                int currRound = this.round;
                while (this.round == currRound){
                    waitingForThreads.await();
                }
            }
            else {
                this.counter = 0;
                this.round++;
                waitingForThreads.signalAll();
            }

            int max = Integer.MIN_VALUE;
            for (int value : values) {
                if (value > max) max = value;
            }

            return max;

        } finally {
            lock.unlock();
        }
    }
}
