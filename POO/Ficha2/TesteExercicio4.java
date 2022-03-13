import java.util.Scanner;

public class TesteExercicio4{

    private static int[] getArray(Scanner sc){
        System.out.println("\nIndique o tamanho do array: ");
        int size = sc.nextInt();
        int[] arr = new int[size];

        System.out.println("Indique os números para o array: ");
        for(int i=0; i < size; i++) arr[i] = sc.nextInt();

        return arr;
    }

    private static void printMenu(){
        System.out.println("\n-----------------ARRAYS DE INTEIROS---------------");
        System.out.println("1.... Ordenar por ordem crescente");
        System.out.println("2.... Procura binária de um valor");
        System.out.println("0.... Sair");
        System.out.println("--------------------------------------------------\n");
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int[] arr = getArray(sc);
        Exercicio4 ex4 = new Exercicio4(arr.length, arr);
        int opcao = -1;

        while (opcao != 0){
            printMenu();

            System.out.print("Introduza a opção: ");
            opcao = sc.nextInt();
            
            switch (opcao){
                case 0:
                    break;

                case 1:
                    System.out.println("\nArray inicial: " + ex4.arrStr());
                    ex4.sort();
                    System.out.println("\nArray ordenado: " + ex4.arrStr() + "\n");
                    break;

                case 2:
                    System.out.print("\nIntroduza o número a procurar: ");
                    int val = sc.nextInt();
                    boolean ret = ex4.binSearch(val);
                    System.out.println("\nO elemento " + (ret ? "foi " : "não foi ") + "encontrado\n");
                    break;

                default:
                    System.out.println("\nA alínea introduzida não é válida. Tente novamente.\n");
                    break;
            }
        }
        sc.close();
    }
}
