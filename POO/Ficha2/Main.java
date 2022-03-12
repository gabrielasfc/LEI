import java.util.Scanner;
import java.time.LocalDate;

public class Main{

    private static int[] getArray(Scanner sc){
        System.out.println("Indique o tamanho do array: ");
        int size = sc.nextInt();
        int[] arr = new int[size];

        System.out.println("Indique os números para o array: ");
        for(int i=0; i < size; i++) arr[i] = sc.nextInt();

        return arr;
    }

    private static void exercicio1a(Scanner sc, Exercicio1 ex1){
        int[] arr = getArray(sc);
        int min = ex1.min_array(arr);
        System.out.println("\nO mínimo do array é: " + min + "\n");
    }

    private static void exercicio1b(Scanner sc, Exercicio1 ex1){
        int[] arr = getArray(sc);
        System.out.println("\nIntroduza o índice correspondente ao limite inferior: ");
        int limInf = sc.nextInt();
        System.out.println("Introduza o índice correspondente ao limite superior: ");
        int limSup = sc.nextInt();

        int[] arrayBet = ex1.array_between(arr, limInf, limSup);
        System.out.println("\nO array é: ");
        for(int val : arrayBet) System.out.print(val + " "); System.out.println("\n");
    }

    private static void exercicio1c(Scanner sc, Exercicio1 ex1){
        System.out.println("\nPrimeiro array:");
        int[] arr1 = getArray(sc);
        System.out.println("\nSegundo array:");
        int[] arr2 = getArray(sc);

        int[] comuns = ex1.array_intersect(arr1, arr2);
        System.out.println("\nOs números comuns entre os 2 arrays são:");
        for (int val : comuns) System.out.print(val + " "); System.out.println("\n");
    }

    public static int getNota(Scanner sc){ 
        int n = -1;
        
        while (n == -1){
            System.out.println("Introduza uma nota entre 0 e 20:");
            n = sc.nextInt();

            if (n<0 || n>20){
                System.out.println("Nota inválida. Tente novamente.\n");
                n = -1;
                continue;
            }
        }
        
        return n;
    }

    private static void exercicio2a(Scanner sc, Exercicio2 ex2){
        for (int i=0; i<ex2.nAlunos; i++){
            for (int j=0; j<ex2.nUC; j++){
                System.out.println("\nInsira a nota para o aluno nº" + i + " da UC " + j);
                int nota = getNota(sc);
                ex2.atualizaPauta(i, j, nota);
            }
        }
        System.out.println("\nPauta atualizada com sucesso.\n");
    }

    private static void exercicio2b(Scanner sc, Exercicio2 ex2){
        System.out.println("\nInsira a UC à qual pretende fazer a soma das notas:");
        int uc = sc.nextInt();
        int soma = ex2.somaNotasUC(uc);
        System.out.println("\nA soma das notas da UC " + uc + " é: " + soma + "\n");
    }

    private static void exercicio2c(Scanner sc, Exercicio2 ex2){
        System.out.println("\nIntroduza o aluno para calcular a sua média:");
        int aluno = sc.nextInt();
        float media = ex2.mediaAluno(aluno);
        System.out.println("\nA média do aluno é: " + media + "\n");
    }

    private static void exercicio2d(Scanner sc, Exercicio2 ex2){
        System.out.println("\nIntroduza a UC para calcular a sua média:");
        int uc = sc.nextInt();
        float media = ex2.mediaUC(uc);
        System.out.println("\nA média da UC é: " + media + "\n");
    }

    private static void exercicio2g(Scanner sc, Exercicio2 ex2){
        System.out.println("\nIntroduza a nota limite para obter as notas da pauta acima:");
        int lim = sc.nextInt();
        int[] notasAcima = ex2.notasAcima(lim);
        for (int nota : notasAcima) System.out.print(nota + " ");
        System.out.println("\n");
    }

    private static void exercicio3a(Scanner sc, Exercicio3 ex3){
        System.out.print("Insira o ano: ");
        int ano = sc.nextInt();
        System.out.print("Insira o mes: ");
        int mes = sc.nextInt();
        System.out.print("Insira o dia: ");
        int dia = sc.nextInt();
        LocalDate data = LocalDate.of(ano, mes, dia);
        ex3.insereData(data);
        System.out.println("\nData inserida com sucesso.\n");
    }

    private static void exercicio3b(Scanner sc, Exercicio3 ex3){
        System.out.print("Insira o ano: ");
        int ano = sc.nextInt();
        System.out.print("Insira o mes: ");
        int mes = sc.nextInt();
        System.out.print("Insira o dia: ");
        int dia = sc.nextInt();
        LocalDate data = LocalDate.of(ano, mes, dia);
        LocalDate dataProx = ex3.dataMaisProxima(data);
        System.out.println("\nA data mais próxima é: " + dataProx.toString() + "\n");   
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        Exercicio1 ex1 = new Exercicio1();
        Exercicio2 ex2 = new Exercicio2();
        Exercicio3 ex3 = new Exercicio3();
        
        int exercicio = -1;
        String alinea;
        
        while (exercicio != 0){
            System.out.println("Sair.................0");
            System.out.println("Introduza o exercício: ");
            exercicio = sc.nextInt();
    
            switch (exercicio){
                case 0:
                    System.out.println("\nSaída com sucesso.");
                    break;

                case 1:
                    System.out.println("Introduza a alínea:");
                    alinea = sc.next();

                    switch (alinea){
                        case "a":
                            exercicio1a(sc, ex1);
                            break;

                        case "b":
                            exercicio1b(sc, ex1);
                            break;

                        case "c":
                            exercicio1c(sc, ex1);
                            break;

                        default:
                            System.out.println("\nA alínea introduzida não é válida. Tente novamente.\n");
                            break;
                    }
                    break;
                
                case 2:
                    System.out.println("Introduza a alínea:");
                    alinea = sc.next();

                    switch (alinea){
                        case "a":
                            exercicio2a(sc, ex2);
                            break;

                        case "b":
                            exercicio2b(sc, ex2);
                            break;

                        case "c":
                            exercicio2c(sc, ex2);
                            break;
                        
                        case "d":
                            exercicio2d(sc, ex2);
                            break;
                        
                        case "e":
                            int notaMax = ex2.notaMax();
                            System.out.println("\nA nota mais alta é: " + notaMax + "\n");
                            break;

                        case "f":
                            int notaMin = ex2.notaMin();
                            System.out.println("\nA nota mais baixa é: " + notaMin + "\n");
                            break;
                        
                        case "g":
                            exercicio2g(sc, ex2);
                            break;

                        case "h":
                            System.out.print(ex2.printPauta());
                            break;
                        
                        case "i":
                            int uc = ex2.indUCMediaMax();
                            System.out.println("\nA UC com média mais elevada é a: " + uc + "\n");
                            break;

                        default:
                            System.out.println("\nA alínea introduzida não é válida. Tente novamente.\n");
                            break;
                    }
                    break;

                case 3:
                    System.out.println("Introduza a alínea:");
                    alinea = sc.next();

                    switch (alinea){
                        case "a":
                            exercicio3a(sc, ex3);
                            break;
                    
                        case "b":
                            exercicio3b(sc, ex3);
                            break;
                    
                        case "c":
                        System.out.println(ex3.toString());
                        break;
                    
                        default:
                            System.out.println("\nA alínea introduzida não é válida. Tente novamente.\n");
                            break;
                    }
                    break;

                default:
                    System.out.println("\nO exercício introduzido não é válido. Tente novamente.\n");
                    break;
            }
        }

        sc.close();
    }
}

