package src.Bill;

import java.io.Serializable;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.temporal.ChronoUnit;

public class DateInterval implements Comparable<DateInterval>, Serializable {
    private LocalDateTime start;
    private LocalDateTime end;

    /**
     * Construtor por defeito
     */
    public DateInterval() {
        this.start = LocalDateTime.now();
        this.end = LocalDateTime.now();
    }

    /**
     * Construtor que recebe os extremos do intervalo
     * @param start início do intervalo
     * @param end fim do intervalo
     */
    public DateInterval(LocalDateTime start, LocalDateTime end) {
        this.start = start;
        this.end = end;
    }

    /**
     * Construtor que recebe o início e a duração do intervalo
     * @param start início do intervalo
     * @param hoursPassed duração do intervalo
     */
    public DateInterval(LocalDateTime start, long hoursPassed){
        this.start = start;
        this.end = this.start.plusHours(hoursPassed);
    }

    /**
     * Construtor de cópia
     * @param d Intervalo de datas a copiar
     */
    public DateInterval(DateInterval d){
        this.start = d.getStart();
        this.end = d.getEnd();
    }

    /**
     * Devolve o início do intervalo
     * @return início do intervalo
     */
    public LocalDateTime getStart() {
        return start;
    }

    /**
     * Altera o início do intervalo
     * @param start início do intervalo
     */
    public void setStart(LocalDateTime start) {
        this.start = start;
    }

    /**
     * Devolve o fim do intervalo
     * @return fim do intervalo
     */
    public LocalDateTime getEnd() {
        return end;
    }

    /**
     * Altera o fim do intervalo
     * @param end fim do intervalo
     */
    public void setEnd(LocalDateTime end) {
        this.end = end;
    }

    /**
     * Verifica se dois intervalos são iguais (mesmo início e mesmo fim)
     * @param o Objeto a comparar
     * @return true, se forem iguais, false caso contrário
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        DateInterval that = (DateInterval) o;
        return this.start.equals(that.getStart()) && this.end.equals(that.getEnd());
    }

    /**
     * Devolve a string correspondente
     * @return a string correspondente ao intervalo
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH");
        sb.append("Início = ").append(start.format(formatter)).append("\n");
        sb.append("Fim = ").append(end.format(formatter)).append("\n");
        return sb.toString();
    }

    /**
     * Faz uma cópia do intervalo
     * @return a cópia
     */
    public DateInterval clone(){
        return new DateInterval(this);
    }

    /**
     * Devolve o nº de horas do intervalo
     * @return diferença (em horas) entre o fim e o início do intervao
     */
    public long hoursInBetween(){
        return ChronoUnit.HOURS.between(this.start, this.end);
    }

    /**
     * Compara dois intervalos
     * @param date Intervalo a comparar
     * @return inteiro positivo se o fim do intervalo atual for depois do fim do intervalo passado como parâmetro
     */
    public int compareTo(DateInterval date){
        return this.end.compareTo(date.end); // ??
    }

    /**
     * Verifica o intervalo passado como argumento está dentro do intervalo desta instância
     * @param start início do intervao
     * @param end fim do intervalo
     * @return true, caso isso se verifique, false, caso contrário
     */
    public boolean inTheInterval(LocalDateTime start, LocalDateTime end){
        boolean b1 =this.start.isAfter(start);
        boolean b2 =this.start.equals(start);
        boolean b3 =this.end.isBefore(end);
        boolean b4 =this.end.equals(end);
        if((b1 || b2) && (b3 || b4)) return true;
        else return false;
    }
}
