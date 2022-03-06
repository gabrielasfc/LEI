import java.util.Scanner;

public class TestePrograma{

    public static void main(String[] args){
        Ficha1 ficha1 = new Ficha1();
        Scanner sc = new Scanner(System.in);

        int num_exec = -1;

        while (num_exec != 0){            
            System.out.println("Introduza o número do exercício:");
            System.out.println("Caso pretenda sair introduza 0");
            
            num_exec = sc.nextInt();

            switch (num_exec){
                case 0:
                    System.out.println("\nSaída com sucesso.");
                    break;
                
                case 1:
                    System.out.println("\nIntroduza temperatura:");
                    double tempC = sc.nextDouble();
                    double tempF = ficha1.celsiusToFarenheit(tempC);
                    System.out.println("A temperatura em Farenheit é: " + tempF + "\n");
                    break;

                case 2:
                    System.out.println("\nIntroduza o primeiro número:");
                    int num1 = sc.nextInt();
                    System.out.println("Introduza o segundo número:");
                    int num2 = sc.nextInt();
                    int result_ex2 = ficha1.maximoNumeros(num1, num2);
                    System.out.println("O máximo é: " + result_ex2 + "\n");
                    break;

                case 3:
                    System.out.println("\nIntroduza o nome:");
                    String nome = sc.next();
                    System.out.println("Introduza o saldo:");
                    double saldo = sc.nextDouble();
                    String result_ex3 = ficha1.criaDescricaoConta(nome, saldo);
                    System.out.println(result_ex3 + "\n");
                    break;

                case 4:
                    System.out.println("\nIntroduza o valor em euros:");
                    double valor = sc.nextDouble();
                    System.out.println("Introduza a taxa de conversão");
                    double taxa = sc.nextDouble();
                    double result_ex4 = ficha1.eurosParaLibras(valor, taxa);
                    System.out.println("O valor em libras é: " + result_ex4 + "\n");
                    break;

                case 5:
                    System.out.println("\nIntroduza o primeiro número:");
                    int a = sc.nextInt();
                    System.out.println("Introduza o segundo número:");
                    int b = sc.nextInt();
                    double media = (double) (a + b) / 2;
                    System.out.printf("\nValores por ordem descrescente: %d %d\n", a > b ? a : b, a < b ? a : b);
                    System.out.println("Média: " + media + "\n");
                    break;

                case 6:
                    System.out.println("\nIntroduza o inteiro:");
                    int num = sc.nextInt();
                    long fact = ficha1.factorial(num);
                    System.out.println("O fatorial de " + num + " é: " + fact + "\n");
                    break;

                case 7:
                    long t_exec = ficha1.tempoGasto();
                    System.out.println("O tempo de execução foi " + t_exec + "\n");
                    break;

                default:
                    System.out.println("\nO número que escreveu não corresponde a um exercício válido.\n");
                    break;
            }
        }

        sc.close();
    }
}
