import java.util.Arrays;

public class Exercicio7{

    private int[] keyNums;
    private int[] keyEsts;

    public Exercicio7(){
        this.keyNums = new int[5];
        for (int i=0; i < 5; i++){
            this.keyNums[i] = (int) (Math.random() * (50-1)) + 1;
            for (int j=0; j < i; j++){
                while (this.keyNums[j] == this.keyNums[i]) this.keyNums[i] = (int) (Math.random() * (50-1)) + 1;
            }
        }

        this.keyEsts = new int[2];
        for (int i=0; i < 2; i++) {
            this.keyEsts[i] = (int) (Math.random() * (9-1)) + 1;
            for (int j=0; j < i; j++){
                while (this.keyEsts[j] == this.keyEsts[i]) this.keyEsts[i] = (int) (Math.random() * (9-1)) + 1;
            }
        }
    }

    public int[] comparaNumeros(int[] nrs){
        int ind = 0;
        boolean flag = false;
        int[] aux = new int[5];

        for (int i=0; i < nrs.length; i++){
            for (int j=0; j < this.keyNums.length && !flag; j++){
                if (nrs[i] == this.keyNums[j]){
                    flag = true;
                    aux[ind++] = nrs[i];
                }
            }
        }

        int[] comuns = new int[ind];
        System.arraycopy(aux, 0, comuns, 0, ind);
        return comuns;
    }

    public int[] comparaEstrelas(int[] estr){
        int ind = 0;
        boolean flag = false;
        int[] aux = new int[2];

        for (int i=0; i < estr.length; i++){
            for (int j=0; j < this.keyEsts.length && !flag; j++){
                if (estr[i] == this.keyEsts[j]){
                    flag = true;
                    aux[ind++] = estr[i];
                }
            }
        }

        int[] comuns = new int[ind];
        System.arraycopy(aux, 0, comuns, 0, ind);
        return comuns;
    }
}
