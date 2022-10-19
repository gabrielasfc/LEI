package ex1;

import java.util.*;
import java.util.concurrent.locks.ReentrantLock;

class Bank {
    private ReentrantLock lockBanco = new ReentrantLock();

    private static class Account {
        private ReentrantLock lockAcc = new ReentrantLock();
        private int balance;
        Account(int balance) { this.balance = balance; }
        int balance() { return balance; }
        boolean deposit(int value) {
            balance += value;
            return true;
        }
        boolean withdraw(int value) {
            if (value > balance)
                return false;
            balance -= value;
            return true;
        }
    }

    private Map<Integer, Account> map = new HashMap<Integer, Account>();
    private int nextId = 0;

    // create account and return account id
    public int createAccount(int balance) {
        Account c;
        try {
            this.lockBanco.lock(); //o nextId tem de ser atualizado antes que se tente criar outra conta
            c = new Account(balance);
            int id = this.nextId;
            map.put(id, c);
            this.nextId += 1;

            return id;
        } finally {
            this.lockBanco.unlock();
        }
    }

    // close account and return balance, or 0 if no such account
    public int closeAccount(int id) {
        Account c;
        // lock banco
        try {
            this.lockBanco.lock();
            c = this.map.remove(id);
            if (c == null) return 0;

            c.lockAcc.lock();
        } finally {
            this.lockBanco.unlock(); //unlock só depois do lock da conta -> 2-phase locking
                                     //pode ser demorado consoante as operações que estão a ser feitas na conta
                                     //o lock do banco só é libertado quando as operações sobre a conta forem todas
                                     // acabadas e esta operação poder finalmente adquirir o lock da conta
        }
        try {
            return c.balance();
        } finally {
            c.lockAcc.unlock();
        }
    }

    // account balance; 0 if no such account
    public int balance(int id) {
        Account c;
        try {
            this.lockBanco.lock();
            c = map.get(id);
            if (c == null) return 0;
            c.lockAcc.lock();
        } finally {
            this.lockBanco.unlock();
        }
        try {
            return c.balance();
        }
        finally {
            c.lockAcc.unlock();
        }
    }

    // deposit; fails if no such account
    public boolean deposit(int id, int value) {
        Account c;
        try {
            this.lockBanco.lock();
            c = map.get(id);
            if (c == null) return false;
            c.lockAcc.lock(); //lock na conta antes de unlock no banco para garantir que nenhuma operaçao
                           //(que vai ter o lock do banco a seguir) consegue aceder à conta antes desta
        } finally {
            this.lockBanco.unlock();
        }

        try {
            return c.deposit(value);
        } finally {
            c.lockAcc.unlock();
        }
    }

    // withdraw; fails if no such account or insufficient balance
    public boolean withdraw(int id, int value) {
        Account c;
        try {
            this.lockBanco.lock();
            c = map.get(id);
            if (c == null) return false;
            c.lockAcc.lock();
        } finally {
            this.lockBanco.unlock();
        }
        try {
            return c.withdraw(value);
        } finally {
            c.lockAcc.unlock();
        }
    }

    // transfer value between accounts;
    // fails if either account does not exist or insufficient balance
    public boolean transfer(int from, int to, int value) {
        Account cfrom, cto;
        try {
            this.lockBanco.lock();
            cfrom = map.get(from); cto = map.get(to);
            if (cfrom == null || cto ==  null) return false;
            cfrom.lockAcc.lock(); cto.lockAcc.lock();

        } finally {
            this.lockBanco.unlock();
        }
        try {
            return cfrom.withdraw(value) && cto.deposit(value);
        }
        finally {
            cfrom.lockAcc.unlock(); cto.lockAcc.unlock();
        }

    }

    // sum of balances in set of accounts; 0 if some does not exist
    public int totalBalance(int[] ids) {
        int total = 0;
        ArrayList<Integer> contasLocked = new ArrayList(ids.length);
        try {
            this.lockBanco.lock();
            for (int id : ids) {
                if (this.map.containsKey(id)) {
                    this.map.get(id).lockAcc.lock();
                    contasLocked.add(id);
                }
            }
        }
        finally {
            this.lockBanco.unlock();
            for (int id : contasLocked) {
                total += this.map.get(id).balance();
                this.map.get(id).lockAcc.unlock();
            }
        }

        return total;
    }

}