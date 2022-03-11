import java.util.Scanner;

public class Exercicio5{

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        float base = 1, altura = 1;

        while (base != 0){
            System.out.println("Introduza a base:");
            base = sc.nextFloat();
            if (base == 0) continue;

            System.out.println("Introduza a altura:");
            altura = sc.nextFloat();

            System.out.printf("Área: %.5f\n\n", (base*altura)/2);
        }

        sc.close();
    }
}