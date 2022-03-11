import java.util.Scanner;

public class Exercicio3{

    public static int get_nota(Scanner sc){ 
        System.out.println("Introduza uma nota entre 0 e 20:");
        int n = sc.nextInt();

        if (n != -1 && (n<0 || n>20)){
            System.out.println("Nota inválida. Tente novamente\n");
            System.out.println("Introduza uma nota entre 0 e 20:");
            n = sc.nextInt();
        }
        
        return n;
    }
    
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        int zerocinco = 0, cincodez = 0, dezquinze = 0, quinzevinte = 0;

        System.out.println("Quantas notas pretende introduzir?");
        int nr_notas = sc.nextInt();

        while (nr_notas > 0){
            int nota = get_nota(sc);
            if (nota < 5) zerocinco++;
            else if (nota >= 5 && nota < 10) cincodez++;
            else if (nota >= 10 && nota < 15) dezquinze++;
            else if (nota >= 15) quinzevinte++;
            nr_notas--;
        }

        System.out.println("\nEntre 0 e 5: " + zerocinco);
        System.out.println("Entre 5 e 10: " + cincodez);
        System.out.println("Entre 10 e 15: " + dezquinze);
        System.out.println("Entre 15 e 20: " + quinzevinte);

        sc.close();
    }
}