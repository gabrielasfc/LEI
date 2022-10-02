import java.util.concurrent.locks.ReentrantLock;

class Bank {
    ReentrantLock lock = new ReentrantLock();

    private static class Account {
        private int balance;
        Account(int balance) { this.balance = balance; }
        int balance() { return balance; }
        boolean deposit(int value) {
            balance += value;
            return true;
        }
    }

    // Our single account, for now
    private Account savings = new Account(0);

    // Account balance
    public int balance() {
        try {
            lock.lock();
            return savings.balance();
        } finally {
            lock.unlock();
        }
    }

    // Deposit
    boolean deposit(int value) {
        try {
            lock.lock();
            return savings.deposit(value);
        } finally {
            lock.unlock();
        }
    }
}

class Deposit implements Runnable {
    private Bank bank;

    public Deposit(Bank b) {
        this.bank = b;
    }

    public void run() {
        final long I = 1000;

        for (int i=0; i<I; i++) {
            this.bank.deposit(100);
        }
    }
}

class MainEx2 {
    public static void main(String[] args) throws InterruptedException {
        int N = 10;
        Thread threads[] = new Thread[N];
        Bank b = new Bank();

        for (int i=0; i<N; i++) {
            threads[i] = new Thread(new Deposit(b));
        }

        for (int i=0; i<N; i++) {
            threads[i].start();
        }

        for (int i=0; i<N; i++) {
            threads[i].join();
        }

        System.out.println(b.balance());

    }
}