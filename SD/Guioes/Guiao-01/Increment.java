class Increment implements Runnable {
    public void run() {
        final long I = 100;

        for (long i = 0; i < I; i++)
            System.out.println(i);
    }
}

class MainEx1 {
    public static void main(String[] args) {
        int N = 10;
        Thread threads[] = new Thread[N];

        //1. criar threads (instanciar objetos)
        for (int i=0; i<N; i++) {
            threads[i] = new Thread(new Increment());
        }

        //2. iniciar threads (start)
        for (int i=0; i<N; i++) {
            threads[i].start();
        }

        //3. esperar por threads
        for (int i=0; i<N; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                System.out.println(e.getMessage());
            }
        }

        //4. imprimir "fim"
        System.out.println("fim");
    }
}