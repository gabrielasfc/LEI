import java.util.Scanner;
import java.util.Arrays;

public class TesteExercicio7{

    private static int[] registaNumeros(Scanner sc){
        int i=0;
        int[] numeros = new int[5];

        System.out.println("Introduza os números da sua aposta:");

        while (i < 5){
            int x = sc.nextInt();
            if (x > 0 && x <= 50) numeros[i++] = x;
            else{
                System.out.println("Os números devem estar contidos entre 1 e 50. Tente novamente.");
                continue;
            }
        }

        return numeros;                 
    }

    private static int[] registaEstrelas(Scanner sc){
        System.out.println("\nIntroduza as estrelas da sua aposta:");
        int i=0;
        int[] estrelas = new int[2];

        while (i < 2){
            int x = sc.nextInt();
            if (x > 0 && x <= 12) estrelas[i++] = x;
            else{
                System.out.println("As estrelas devem estar contidas entre 1 e 12. Tente novamente.");
                continue;
            }
        }

        return estrelas;
    }

    private static String replicate(int n, char c){
        String res = "";
        for (int i=0; i<n; i++) res += c;
        return res;
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        Exercicio7 ex7 = new Exercicio7();
        
        System.out.println("\nBem-vindo ao Euromilhões!\n");
        int[] numeros = registaNumeros(sc);
        int[] estrelas = registaEstrelas(sc);
        System.out.println("\nAposta registada com sucesso.\n");

        int[] nrComuns = ex7.comparaNumeros(numeros);
        int[] estrComuns = ex7.comparaEstrelas(estrelas);

        if (nrComuns.length == 5 && estrComuns.length == 2){
            System.out.println("Parabéns! Acertou toda a chave!");
            
            int it = 0;
            while (it < 50){
                int col = 0;
                String str = replicate(col, ' ');
                System.out.println(str + "Numeros: " + Arrays.toString(numeros));
                System.out.println(str + "Estrelas: " + Arrays.toString(estrelas) + "\n");
                col += 2;
            }
        }
        else if (nrComuns.length == 0 && estrComuns.length == 0){
            System.out.println("Infelizmente não acertou nada!\n");
        }
        else{
            System.out.println("Parabéns! Acertou " + nrComuns.length + " números e " + estrComuns.length + " estrelas.");
            System.out.println("Numeros: " + Arrays.toString(nrComuns));
            System.out.println("Estrelas: " + Arrays.toString(estrComuns) + "\n");
        }
        sc.close();
    }
}

