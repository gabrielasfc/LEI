import java.util.Arrays;

public class Exercicio5{

    private String[] arr;

    public Exercicio5(int size, String[] arrInput){
        this.arr = new String[size];
        this.arr = arrInput.clone();
    }

    private int procuraReps(String[] arr, String val, int i){
        int conta = 0;
        for(; i < this.arr.length; i++){
            if(arr[i].equals(val)) conta++;
        }
        return conta;
    }

    public String[] semReps(){
        String[] aux = new String[this.arr.length];
        int pos = 0;

        for (int i=0; i < this.arr.length; i++){
            if (procuraReps(this.arr, this.arr[i], i+1) == 0){
                aux[pos++] = this.arr[i];
            }
        }

        String[] res = new String[pos];
        System.arraycopy(aux, 0, res, 0, pos);
        return res;
    }

    String maiorString(){
        int max = Integer.MIN_VALUE;
        String sMax = "";

        for (String str : this.arr){
            if(str.length() > max){
                max = str.length();
                sMax = str;
            }
        }

        return sMax;
    }

    public String[] repetidos(){
        String[] aux = new String[this.arr.length];
        int pos = 0;

        for (int i=0; i < this.arr.length; i++){
            if (procuraReps(this.arr, this.arr[i], i+1) == 1){
                aux[pos++] = this.arr[i];
            }
        }

        String[] res = new String[pos];
        System.arraycopy(aux, 0, res, 0, pos);
        return res;
    }

    public int conta(String s){
        int count = 0;
        for (String str : this.arr){
            if(str.equals(s)) count++;
        }
        return count;
    }

    public String printArray(){
        return Arrays.toString(this.arr);
    }
}
