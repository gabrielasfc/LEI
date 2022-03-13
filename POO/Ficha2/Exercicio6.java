public class Exercicio6{

    public int[][] somaMatrizes(int[][] m1, int[][] m2, int l, int c){
        int[][] r = new int[l][c];
        
        for (int i=0; i < l; i++){
            for (int j=0; j < c; j++){
                r[i][j] = m1[i][j] + m2[i][j];
            }
        }
        return r;
    }

    public boolean matrizesIguais(int[][] m1, int[][] m2, int l, int c){
        for (int i=0; i < l; i++){
            for (int j=0; j < c; j++){
                if (m1[i][j] != m2[i][j]) return false;
            }
        }
        return true;
    }

    public int[][] matrizOposta(int[][] m, int l, int c){
        int[][] r = new int[l][c];

        for (int i=0; i < l; i++){
            for (int j=0; j < c; j++){
                r[i][j] = -m[i][j];
            }
        }

        return r;
    }
}
