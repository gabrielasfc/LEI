import java.time.LocalDateTime;
import java.time.Duration;

public class Ficha1{
    //1
    public double celsiusToFarenheit(double degrees){
        double result = 1.8 * degrees + 32;
        return result;
    }

    //2
    public int maximoNumeros(int a, int b){
        int result = a;
        if (b>a) result = b;
        return result;
    }

    //3
    public String criaDescricaoConta(String nome, double saldo){
        return "Nome: " + nome + " | Saldo: " + saldo + "€";
    }

    //4
    public double eurosParaLibras(double valor, double taxaConversao){
        return valor * taxaConversao;
    }

    //6
    public long factorial(int num){
        int res = num;
        while (num-1>0){
            res = res * (num-1);
            num--;
        }
        return res;
    }

    //7
    public long tempoGasto(){
        LocalDateTime start = LocalDateTime.now();
        factorial(5000);
        LocalDateTime end = LocalDateTime.now();
        Duration t_exec = Duration.between(start, end);
        return t_exec.toMillis();
    }
}
