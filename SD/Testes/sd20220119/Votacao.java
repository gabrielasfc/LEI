import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

interface IVotacao {
    boolean verifica(int identidade);
    int esperaPorCabine();
    void vota(int escolha);
    void desocupaCabine(int i);
    int vencedor();
}

public class Votacao implements IVotacao {
    private Set<Integer> ids;
    private HashMap<Integer, Boolean> cabines; // guardar cabines e a sua ocupação
    private HashMap<Integer, Integer> votos; //registar numero de votos
    private ReentrantLock lock;
    private Condition esperarPorCabine; // esperar por cabine
    private boolean end; // terminar a votação
    private int AVotar; // número de pessoas a votar no momento
    private Condition esperarPorVotos; // esperar por todos acabarem de votar

    public Votacao() {
        this.ids = new HashSet<>();
        this.cabines = new HashMap<>();
        this.votos = new HashMap<>();
        this.lock = new ReentrantLock();
        this.esperarPorCabine = lock.newCondition();
        this.esperarPorVotos = lock.newCondition();
    }

    public boolean verifica(int identidade) {
        try {
            lock.lock();

            boolean votou = false;

            if (!this.end) { // só podem votar se as votações ainda estiverem abertas
                votou = this.ids.contains(identidade);

                if (!votou) {
                    this.ids.add(identidade);
                    this.AVotar++;
                }
            }
            return votou;

        } finally {
            lock.unlock();
        }
    }


    public void vota(int escolha) {
        try {
            lock.lock();

            if (this.votos.containsKey(escolha)) {
                this.votos.put(escolha, this.votos.get(escolha) + 1);
            }
            else this.votos.put(escolha, 1);

            this.AVotar--;
            this.esperarPorVotos.signalAll();
        } finally {
            lock.unlock();
        }
    }

    public void desocupaCabine(int cabine) {
        try {
            lock.lock();
            this.cabines.put(cabine, true);
            esperarPorCabine.signalAll();
        } finally {
            lock.unlock();
        }
    }

    public int procuraCabine() {
        int cabine = -1;

        for (int key : this.cabines.keySet()){
            if (this.cabines.get(key)) {
                cabine = key;
                break;
            }
        }

        return cabine;
    }

    public int esperaPorCabine() {
        int cabine;

        try {
            lock.lock();

            while ((cabine = procuraCabine()) == -1){
                esperarPorCabine.await();
            }

            return cabine;
        } finally {
            lock.unlock();
        }
    }

    public int vencedor() {
        try {
            lock.lock();
            this.end = true;

            while(this.AVotar != 0){
                esperarPorVotos.await();
            }
        }
        finally {
            this.lock.unlock();
        }

        int vencedor = -1;
        int numVotosVencedor = -1;

        for (int escolha : this.votos.keySet()) {
            if(this.votos.get(escolha) > numVotosVencedor){
                numVotosVencedor = this.votos.get(escolha);
                vencedor = escolha;
            }
        }

        return vencedor;
    }
}

