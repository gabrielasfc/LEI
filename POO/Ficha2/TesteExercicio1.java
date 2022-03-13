import java.util.Scanner;
import java.util.Arrays;

public class TesteExercicio1{

    private static int[] getArray(Scanner sc){
        System.out.println("Indique o tamanho do array: ");
        int size = sc.nextInt();
        int[] arr = new int[size];

        System.out.println("Indique os números para o array: ");
        for(int i=0; i < size; i++) arr[i] = sc.nextInt();

        return arr;
    }

    private static void printMenu(){
        System.out.println("\n---------------------------------ARRAYS DE INTEIROS--------------------------------");
        System.out.println("1.... Ler inteiros para um array e determinar o valor mínimo desse array");
        System.out.println("2.... Ler um array e 2 índices e determinar os valores do array entre esses índices");
        System.out.println("3.... Ler dois arrays e determinar o array com os elementos comuns aos dois arrays");
        System.out.println("0.... Sair");
        System.out.println("-----------------------------------------------------------------------------------\n");
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        Exercicio1 ex1 = new Exercicio1();
        int opcao = -1;

        while (opcao != 0){
            printMenu();

            System.out.println("Introduza a opção:");
            opcao = sc.nextInt();
            
            switch (opcao){
                case 0:
                    break;
                
                case 1:
                    int[] arr = getArray(sc);
                    int min = ex1.min_array(arr);
                    System.out.println("\nO mínimo do array é: " + min + "\n");
                    break;

                case 2:
                    int[] array = getArray(sc);
                    System.out.println("\nIntroduza o índice correspondente ao limite inferior: ");
                    int limInf = sc.nextInt();
                    System.out.println("Introduza o índice correspondente ao limite superior: ");
                    int limSup = sc.nextInt();

                    int[] arrayBet = ex1.array_between(array, limInf, limSup);
                    System.out.println("\nO array é: " + Arrays.toString(arrayBet) + "\n");
                    break;

                case 3:
                    System.out.println("\nPrimeiro array:");
                    int[] arr1 = getArray(sc);
                    System.out.println("\nSegundo array:");
                    int[] arr2 = getArray(sc);

                    int[] comuns = ex1.array_intersect(arr1, arr2);
                    System.out.println("\nOs números comuns entre os 2 arrays são: " + Arrays.toString(comuns) + "\n");
                    break;

                default:
                    System.out.println("\nA alínea introduzida não é válida. Tente novamente.\n");
                    break;
            }
        }
        sc.close();
    }
}
