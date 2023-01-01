import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

interface IControloTrafegoAereo {
    int pedirParaDescolar();
    int pedirParaAterrar();
    void descolou(int pista);
    void aterrou(int pista);
}

public class ControloTrafegoAereo implements IControloTrafegoAereo {
    Map<Integer, Boolean> pistas; // guarda as pistas e se estão livres ou não
    ReentrantLock lock;
    Condition esperarPorPista; // esperar por pista livre para descolar ou aterrar
    int proximoPedido; // proximo pedido a ser atendido : 0-> aterragem, 1 -> descolagem

    public ControloTrafegoAereo() {
        this.pistas = new HashMap<>();
        this.lock = new ReentrantLock();
        this.esperarPorPista = lock.newCondition();
        this.proximoPedido = 0;

    }

    private List<Integer> procuraPistasLivres() {
        List<Integer> pistasLivres = new ArrayList<>();

        for (int pista : this.pistas.keySet()) {
            if (this.pistas.get(pista)) pistasLivres.add(pista);
        }

        return pistasLivres;
    }

    public int pedirParaDescolar() {
        try {
            lock.lock();
            List<Integer> pistasLivres = this.procuraPistasLivres();

            while (pistasLivres.size() == 0 || (pistasLivres.size() == 1 && this.proximoPedido != 1)) {
                esperarPorPista.await();
                pistasLivres = this.procuraPistasLivres();
            }

            int pista = pistasLivres.get(0);
            this.pistas.put(pista, false);
            this.proximoPedido = 0;

            return pista;
        } finally {
            lock.unlock();
        }
    }

    public int pedirParaAterrar() {
        try {
            lock.lock();
            List<Integer> pistasLivres = this.procuraPistasLivres();

            while (procuraPistasLivres().size() == 0 || (pistasLivres.size() == 1 && this.proximoPedido != 0)) {
                esperarPorPista.await();
                pistasLivres = this.procuraPistasLivres();
            }

            int pista = pistasLivres.get(0);
            this.pistas.put(pista, false);
            this.proximoPedido = 1;

            return pista;
        } finally {
            lock.unlock();
        }

    }

    public void descolou(int pista) {
        try {
            lock.lock();

            this.pistas.put(pista, true);
            esperarPorPista.signalAll();
        } finally {
            lock.unlock();
        }
    }

    public void aterrou(int pista) {
        try {
            lock.lock();

            this.pistas.put(pista, true);
        } finally {
            lock.unlock();
        }
    }
}
