import java.time.LocalDateTime;
import java.util.*;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

interface IFicheiros {
    void using(String path);
    void notUsing(String path, boolean modified);
    List<String> startBackup();
    void endBackup();
}

public class Ficheiros implements IFicheiros {
    private class Ficheiro {
        public LocalDateTime ultimaModificacao;
        public Boolean aSerUsado;
    }

    private Map<String, Ficheiro> ficheiros;
    private LocalDateTime ultimoBackup;
    private ReentrantLock lock;
    private Condition esperarPorFicheiros; // esperar por ficheiros ficarem livres para fazer backup

    public Ficheiros() {
        this.ficheiros = new HashMap<>();
        this.ultimoBackup = null;
        this.lock = new ReentrantLock();
        this.esperarPorFicheiros = lock.newCondition();
    }

    public void using(String path) {
        try {
            lock.lock();

            Ficheiro ficheiro = this.ficheiros.get(path);

            if (!ficheiro.aSerUsado) {
                ficheiro.aSerUsado = true;
                //this.ficheiros.put(path, ficheiro);
            }
        } finally {
            lock.unlock();
        }

    }

    public void notUsing(String path, boolean modified) {
        try {
            lock.lock();

            Ficheiro ficheiro = this.ficheiros.get(path);
            ficheiro.aSerUsado = false;

            if (modified) {
                ficheiro.ultimaModificacao = LocalDateTime.now();
            }

            this.esperarPorFicheiros.signalAll();
        } finally {
            lock.unlock();
        }
    }

    private boolean todosLivres() {
        for (Ficheiro ficheiro : this.ficheiros.values()) {
            if (ficheiro.aSerUsado) return false;
        }

        return true;
    }

    public List<String> startBackup() {
        try {
            lock.lock();

            while (!this.todosLivres()) {
                this.esperarPorFicheiros.await();
            }

            List<String> paths = new ArrayList<>();

            for (String key : ficheiros.keySet()) {
                if (this.ultimoBackup == null || this.ultimoBackup.isBefore(this.ficheiros.get(key).ultimaModificacao)) {
                    paths.add(key);
                }
            }

            return paths;
        } finally {
            lock.unlock();
        }
    }

    public void endBackup() {
        this.ultimoBackup = LocalDateTime.now();
    }
}
