import java.util.Scanner;
import java.time.LocalDate;

public class TesteExercicio3{

    private static void printMenu(){
        System.out.println("\n------------------------------------------------ARRAYS DE DATAS-----------------------------------------------");
        System.out.println("1.... Inserir nova data no array");
        System.out.println("2.... Dada uma data, determinar a data do array que está mais próxima (em termos de proximidade de calendário)");
        System.out.println("3.... Devolver uma String com todas as datas do array");
        System.out.println("0.... Sair");
        System.out.println("--------------------------------------------------------------------------------------------------------------\n");
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        Exercicio3 ex3 = new Exercicio3();
        int opcao = -1;

        while (opcao != 0){
            printMenu();

            System.out.print("Introduza a opção: ");
            opcao = sc.nextInt();
            
            switch (opcao){
                case 0:
                    break;
                
                case 1:
                    System.out.print("\nInsira o ano: ");
                    int ano = sc.nextInt();
                    System.out.print("Insira o mes: ");
                    int mes = sc.nextInt();
                    System.out.print("Insira o dia: ");
                    int dia = sc.nextInt();

                    LocalDate data = LocalDate.of(ano, mes, dia);
                    ex3.insereData(data);

                    System.out.println("\nData inserida com sucesso.\n");
                    break;

                case 2:
                    System.out.print("\nInsira o ano: ");
                    int ano2 = sc.nextInt();
                    System.out.print("Insira o mes: ");
                    int mes2 = sc.nextInt();
                    System.out.print("Insira o dia: ");
                    int dia2 = sc.nextInt();

                    LocalDate data2 = LocalDate.of(ano2, mes2, dia2);
                    LocalDate dataProx = ex3.dataMaisProxima(data2);

                    System.out.println("\nA data mais próxima é: " + dataProx.toString() + "\n");   
                    break;

                case 3:
                    System.out.println(ex3.toString());
                    break;

                default:
                    System.out.println("\nA alínea introduzida não é válida. Tente novamente.\n");
                    break;
            }
        }
        sc.close();
    }
}
