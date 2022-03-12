public class Exercicio1{

    public int min_array(int[] arr){
        int min = Integer.MAX_VALUE;

        for(int nr : arr){
            if (nr < min) min = nr;
        }

        return min;
    }

    public int[] array_between(int arr[], int i1, int i2){
        int len = i2 - i1 + 1;
        int[] res = new int[len];

        System.arraycopy(arr, i1, res, 0, len);

        return res;
    }

    public int[] array_intersect(int arr1[], int arr2[]){
        int[] aux = new int[arr1.length];
        int ind = 0;

        for (int i=0; i < arr1.length; i++){
            for (int j=0; j < arr2.length; j++){
                if (arr1[i] == arr2[j]) aux[ind++] = arr1[i];
            }
        }

        int[] comuns = new int[ind];
        System.arraycopy(aux, 0, comuns, 0, ind);
        
        return comuns;
    }
}
