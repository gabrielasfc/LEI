import java.util.Scanner;

public class TesteExercicio6{

    private static int[][] getMatriz(Scanner sc){
        System.out.print("\nIntroduza o número de linhas: ");
        int l = sc.nextInt();
        System.out.print("Introduza o número de colunas: ");
        int c = sc.nextInt();
        System.out.println();

        int[][] m = new int[l][c];

        for(int i=0; i < l; i++){
            for(int j=0; j < c; j++){
                System.out.print("(" + i + "," + j + ") -> ");
                m[i][j] = sc.nextInt();
            }
        }
        System.out.println("\nMatriz registada com sucesso.\n");
        return m;
    }

    private static void printMatriz(int[][] m){
        for (int i=0; i < m.length; i++){
            for(int j=0; j < m[i].length; j++){
                System.out.print(m[i][j] + " ");
            }
            System.out.println();
        }
    }

    private static void printMenu(){
        System.out.println("\n---------------------MATRIZES---------------------");
        System.out.println("1.... Ler uma matriz");
        System.out.println("2.... Somar matrizes e devolver a matriz resultado");
        System.out.println("3.... Determinar se 2 matrizes são iguais");
        System.out.println("4.... Determinar a matriz oposta de uma matriz");
        System.out.println("0.... Sair");
        System.out.println("--------------------------------------------------\n");
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        Exercicio6 ex6 = new Exercicio6();
        int opcao = -1;

        while (opcao != 0){
            printMenu();

            System.out.println("Introduza a opção:");
            opcao = sc.nextInt();
            
            switch (opcao){
                case 0:
                    break;
                
                case 1:
                    getMatriz(sc);
                    break;

                case 2:
                    int aux = -1;
                    int[][] m1B = new int[0][0], m2B = new int[0][0];
                
                    while (aux == -1){
                        System.out.print("\n---Primeira matriz---");
                        m1B = getMatriz(sc);
                        System.out.print("---Segunda matriz---");
                        m2B = getMatriz(sc);
                        
                        if (m1B.length != m2B.length || m1B[0].length != m2B[0].length){
                            System.out.println("\nAs duas matrizes devem ter as mesmas dimensões. Tente novamente.\n");
                            continue;
                        }
                        else aux = 0;
                    }
                    
                    int[][] mRes = ex6.somaMatrizes(m1B, m2B, m1B.length, m1B[0].length);
                    System.out.println("A matriz resultante é: ");
                    printMatriz(mRes);
                    System.out.println();
                    break;

                case 3:
                    System.out.print("\n---Primeira matriz---");
                    int[][] m1C = getMatriz(sc);
                    System.out.print("---Segunda matriz---");
                    int[][] m2C = getMatriz(sc);

                    if (m1C.length == m2C.length && m1C[0].length == m2C[0].length && ex6.matrizesIguais(m1C, m2C, m1C.length, m1C[0].length)){
                            System.out.println("\nAs matrizes são iguais.\n");
                    }
                    else System.out.println("\nAs matrizes não são iguais.\n");
                    break;

                case 4:
                    int[][] m = getMatriz(sc);
                    int[][] mf = ex6.matrizOposta(m, m.length, m[0].length);
                    System.out.println("\nA matriz oposta é:");
                    printMatriz(mf); System.out.println();
                    break;
                
                default:
                    System.out.println("\nA alínea introduzida não é válida. Tente novamente.\n");
                    break;
            }
        }
        sc.close();
    }
}

