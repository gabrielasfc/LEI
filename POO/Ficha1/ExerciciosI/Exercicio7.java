import java.util.Scanner;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Exercicio7{

    public static long idadeHoras(LocalDateTime nasc, LocalDateTime curr){
        long ano = curr.getYear() - nasc.getYear();
        long dias = ano*365 + (ano/4) + (curr.getDayOfYear() - nasc.getDayOfYear());
        long horas = dias*24 + (curr.getHour() - nasc.getHour());
        return horas;
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm");
        
        System.out.println("Introduza o dia de nascimento:");
        int dia_nasc = sc.nextInt();
        System.out.println("Introduza o mês de nascimento:");
        int mes_nasc = sc.nextInt();
        System.out.println("Introduza o ano de nascimento:");
        int ano_nasc = sc.nextInt();

        LocalDateTime nasc = LocalDateTime.of(ano_nasc, mes_nasc, dia_nasc, 0, 0);
        LocalDateTime curr = LocalDateTime.now();
        
        long idadeHoras = idadeHoras(nasc, curr);
        System.out.println("\nA idade atual é: " + idadeHoras + " horas\nNa data " + formatter.format(curr));

        sc.close();
    }
}
