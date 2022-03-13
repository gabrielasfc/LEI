import java.util.Scanner;
import java.util.Arrays;

public class TesteExercicio5{

    private static String[] getStrArray(Scanner sc){
        System.out.print("\nIndique o tamanho do array: ");
        int size = sc.nextInt();
        String[] arr = new String[size];

        System.out.println("Indique as strings para o array: ");
        for(int i=0; i < size; i++) arr[i] = sc.next();

        return arr;
    }

    private static void printMenu(){
        System.out.println("\n---------------------------ARRAYS DE STRINGS-------------------------");
        System.out.println("1.... Determinar o array com as Strings existentes (sem repetições)");
        System.out.println("2.... Determinar a maior String inserida");
        System.out.println("3.... Determinar um array com as Strings que aparecem mais de uma vez");
        System.out.println("4.... Determinar quantas vezes uma determinada String ocorre no array");
        System.out.println("0.... Sair");
        System.out.println("---------------------------------------------------------------------\n");
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        String[] strArr = getStrArray(sc);
        Exercicio5 ex5 = new Exercicio5(strArr.length, strArr);
        int opcao = -1;

        while (opcao != 0){
            printMenu();

            System.out.println("Introduza a opção:");
            opcao = sc.nextInt();
            
            switch (opcao){
                case 0:
                    break;
                
                case 1:
                    System.out.println("\nArray: " + ex5.printArray());
                    System.out.println("Array sem repetições: " + Arrays.toString(ex5.semReps()) + "\n");
                    break;

                case 2:
                    System.out.println("\nA maior string é: " + ex5.maiorString() + "\n");
                    break;

                case 3:
                    System.out.println("\nArray: " + ex5.printArray());
                    System.out.println("Repetidos: " + Arrays.toString(ex5.repetidos()) + "\n");
                    break;

                case 4:
                    System.out.println("\nIntroduza a string para contar:");
                    String str = sc.next();
                    int n = ex5.conta(str);
                    System.out.println("\nA string aparece " + n + " vezes no array\n");
                    break;
                
                default:
                    System.out.println("\nA alínea introduzida não é válida. Tente novamente.\n");
                    break;
            }
        }
        sc.close();
    }
}

