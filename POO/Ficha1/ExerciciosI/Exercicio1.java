import java.util.Scanner;

public class Exercicio1{

    public static int dia_da_semana(int dia, int mes, int ano){
        int total_dias = (ano - 1900) * 365;
        total_dias += (ano - 1900) / 4;
        if (ano % 4 == 0 && (mes == 1 || mes == 2)) total_dias--;

        for (int i=1; i<mes; i++){
            if (i == 2) total_dias += 28;
            else if (i == 4 || i == 6 || i == 9 || i == 11) total_dias += 30;
            else total_dias += 31;
        }
        total_dias += dia;

        return (total_dias % 7);
    }

    
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        System.out.println("Introduza o dia: ");
        int dia = sc.nextInt();
        System.out.println("Introduza o mês: ");
        int mes = sc.nextInt();
        System.out.println("Introduza o ano: ");
        int ano = sc.nextInt();

        int res = dia_da_semana(dia, mes, ano);

        switch (res){
            case 0:
                System.out.println("\nDomingo\n");
                break;
            case 1:
                System.out.println("\nSegunda\n");
                break;
            case 2:
                System.out.println("\nTerça\n");
                break;  
            case 3:
                System.out.println("\nQuarta\n");
                break;
            case 4:
                System.out.println("\nQuinta\n");
                break;
            case 5:
                System.out.println("\nSexta\n");
                break;
            case 6:
                System.out.println("\nSábado\n");
                break;
            default: break;
        }

        sc.close();
    }
}