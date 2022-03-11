import java.util.Scanner;
import java.time.LocalDateTime;

public class Exercicio2{

    public static LocalDateTime get_data(Scanner sc){
        System.out.println("Introduza o ano:");
        int ano = sc.nextInt();
        System.out.println("Introduza o mês:");
        int mes = sc.nextInt();
        System.out.println("Introduza o dia:");
        int dia = sc.nextInt();
        System.out.println("Introduza a hora:");
        int hora = sc.nextInt();
        System.out.println("Introduza o minuto:");
        int min = sc.nextInt();
        System.out.println("Introduza o segundo:");
        int seg = sc.nextInt();
        
        LocalDateTime data = LocalDateTime.of(ano, mes, dia, hora, min, seg);
        return data;
    }
    
    public static String soma_datas(LocalDateTime data1, LocalDateTime data2){
        int seg = data2.getSecond();
        int min = data2.getMinute();
        int hora = data2.getHour();
        int dia = data2.getDayOfMonth();
        
        seg += data1.getSecond();
        while (seg >= 60){
            min++;
            seg -= 60;
        }

        min += data1.getMinute();
        while (min >= 60){
            hora++;
            min -= 60;
        }

        hora += data1.getHour();
        while (hora >= 24){
            dia++;
            hora -= 24;
        }

        dia += data1.getDayOfMonth();
        
        return (dia + "D " + hora + "H " + min + "m " + seg + "s");
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        System.out.println("Introduza a primeira data:");
        LocalDateTime data1 = get_data(sc);
        System.out.println("Introduza a segunda data:");
        LocalDateTime data2 = get_data(sc);

        String res = soma_datas(data1, data2);
        System.out.println("\n" + res + "\n");

        sc.close();
    }
}