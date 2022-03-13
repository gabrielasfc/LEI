import java.util.Arrays;

public class Exercicio4{

    private int[] arr;

    public Exercicio4(int size, int[] arrInput){
        this.arr = new int[size];
        this.arr = arrInput.clone();
    }

    public void sort(){
        for (int i=0; i < this.arr.length-1; i++){  
            for (int j = 0; j < this.arr.length-i-1; j++){ 
                if (this.arr[j] > this.arr[j+1]){  
                    int tmp = this.arr[j];
                    this.arr[j] = this.arr[j+1];
                    this.arr[j+1] = tmp;
                }  
            } 
        }
        //Arrays.sort(this.arr);
    }

    public String arrStr(){
        return Arrays.toString(this.arr);
    }

    public boolean binSearch(int val){
        int inic = 0, fim = this.arr.length-1;
        int mid = (inic+fim)/2;

        for (; inic <= fim; mid = (inic+fim)/2){
            if (this.arr[mid] == val) return true;
            if (this.arr[mid] < val) inic = mid+1;
            else fim = mid-1;
        }

        return false;
    }
}
