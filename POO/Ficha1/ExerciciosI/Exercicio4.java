import java.util.Scanner;

public class Exercicio4{

    public static int get_temp(Scanner sc){ 
        System.out.println("Introduza a temperatura:");
        int temp = sc.nextInt();
        return temp;
    }


    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        
        int i, var;
        int max = 0, dia_max = 0, temp = 0, temp_ant = 0;
        float media = 0;
        
        System.out.println("Quantas temperaturas pretende introduzir?");
        int nr_temps = sc.nextInt();

        for (i=1; i < nr_temps+1; i++){
            temp_ant = temp;
            temp = get_temp(sc);
            media += temp;
            if (i == 0) temp_ant = temp;
            else{
                if (Math.abs(var = temp - temp_ant) > Math.abs(max)){
                    max = var;
                    dia_max = i;
                }
            }
        }

        media /= nr_temps;
        
        System.out.println("A média das " + nr_temps + " temperaturas foi de " + media + " graus.");
        System.out.println("A maior variação registou-se entre os dias " + (dia_max-1) + " e " + dia_max + ", tendo a temperatura " + ((max > 0) ? "subido " : "descido ") + Math.abs(max) + " graus.");

        sc.close();
    }
}
