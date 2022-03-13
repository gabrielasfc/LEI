import java.util.Scanner;
import java.util.Arrays;

public class TesteExercicio2{

    private static int getNota(Scanner sc){ 
        int n = -1;
        
        while (n == -1){
            System.out.print("Introduza uma nota entre 0 e 20: ");
            n = sc.nextInt();

            if (n<0 || n>20){
                System.out.println("Nota inválida. Tente novamente.\n");
                n = -1;
                continue;
            }
        }
        
        return n;
    }

    private static void printMenu(){
        System.out.println("\n------------------------------------------PAUTA DE UMA TURMA-----------------------------------------");
        System.out.println("1.... Ler as notas dos alunos e atualizar o array da pauta");
        System.out.println("2.... Calcular a soma das notas a uma determinada unidade curricular");
        System.out.println("3.... Calcular a média das notas de um aluno (fornecendo o índice da sua posição no array)");
        System.out.println("4.... Calcular a média das notas de uma unidade curricular (fornecendo o índice da unidade curricular");
        System.out.println("5.... Calcular a nota mais alta a todas as unidades curriculares de todos os alunos");
        System.out.println("6.... Calcular a nota mais baixa a todas as unidades curriculares de todos os alunos");
        System.out.println("7.... Devolver o array com as notas acima de um determinado valor");
        System.out.println("8.... Calcular uma String com as notas de todos os alunos do curso a todas as unidades curriculares");
        System.out.println("9.... Determinar o índice da unidade curricular com a média mais elevada");
        System.out.println("0.... Sair");
        System.out.println("-----------------------------------------------------------------------------------------------------\n");
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        Exercicio2 ex2 = new Exercicio2();
        int opcao = -1;

        while (opcao != 0){
            printMenu();

            System.out.print("Introduza a opção: ");
            opcao = sc.nextInt();
            
            switch (opcao){
                case 0:
                    break;
                
                case 1:
                    for (int i=0; i<ex2.nAlunos; i++){
                        for (int j=0; j<ex2.nUC; j++){
                            System.out.println("\nInsira a nota para o aluno nº" + i + " da UC " + j);
                            int nota = getNota(sc);
                            ex2.atualizaPauta(i, j, nota);
                        }
                    }
                    System.out.println("\nPauta atualizada com sucesso.\n");
                    break;

                case 2:
                    System.out.print("\nInsira a UC: ");
                    int uc = sc.nextInt();
                    int soma = ex2.somaNotasUC(uc);
                    System.out.println("\nA soma das notas da UC " + uc + " é: " + soma + "\n");
                    break;

                case 3:
                    System.out.print("\nIntroduza o aluno: ");
                    int aluno = sc.nextInt();
                    float mediaAluno = ex2.mediaAluno(aluno);
                    System.out.println("\nA média do aluno é: " + mediaAluno + "\n");
                    break;
                
                case 4:
                    System.out.print("\nIntroduza a UC: ");
                    int uc2 = sc.nextInt();
                    float mediaUC = ex2.mediaUC(uc2);
                    System.out.println("\nA média da UC é: " + mediaUC + "\n");
                    break;
                
                case 5:
                    int notaMax = ex2.notaMax();
                    System.out.println("\nA nota mais alta é: " + notaMax + "\n");
                    break;
                
                case 6:
                    int notaMin = ex2.notaMin();
                    System.out.println("\nA nota mais baixa é: " + notaMin + "\n");
                    break;
                
                case 7:
                    System.out.print("\nIntroduza a nota limite: ");
                    int lim = sc.nextInt();
                    int[] notasAcima = ex2.notasAcima(lim);
                    System.out.println("\nAs notas acima são: " + Arrays.toString(notasAcima) + "\n");
                    break;
                
                case 8:
                    System.out.print(ex2.printPauta());
                    break;
                
                case 9:
                    int uc3 = ex2.indUCMediaMax();
                    System.out.println("\nA UC com média mais elevada é a: " + uc3 + "\n");
                    break;
                    
                default:
                    System.out.println("\nA alínea introduzida não é válida. Tente novamente.\n");
                    break;
            }
        }
        sc.close();
    }
}

