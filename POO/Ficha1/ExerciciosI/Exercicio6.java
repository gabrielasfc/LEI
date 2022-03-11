import java.util.Scanner;

public class Exercicio6{

    public static boolean isPrimo(int x){
        int i;

        if (x == 0 || x == 1) return false;

        for (i=2; i <= x/2; i++){
            if (x % i == 0) return false;
        }
        
        return true;
    }


    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        
        System.out.println("Introduza o número máximo:");
        int max = sc.nextInt();
        System.out.println("\nNúmeros primos até " + max + ":");

        for(int i=0; i < max; i++){
            if (isPrimo(i)) System.out.println(i);
        }

        sc.close();
    }
}
