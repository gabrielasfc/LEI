package src.Bill;

import java.io.Serializable;
import java.time.LocalDateTime;

public class Bill implements Comparable<Bill>, Serializable {
    private int houseID;
    private DateInterval period;
    private double consumption; // KW H
    private double cost; // IN euros

    /**
     * Construtor por defeito
     */
    public Bill(){
        this.houseID = 0;
        this.period = new DateInterval();
        this.consumption = 0;
        this.cost = 0;
    }

    /**
     * Construtor que recebe todos os campos
     * @param houseID Id da casa à qual foi emitida a fatura
     * @param period Período no qual a fatura foi emitida
     * @param consumption Consumo (em kwh) desse período
     * @param cost Custo associado a esse consumo
     */
    public Bill(int houseID, DateInterval period, double consumption, double cost) {
        this.houseID = houseID;
        this.period = period.clone();
        this.consumption = consumption;
        this.cost = cost;
    }

    /**
     * Construtor que recebe todos os campos
     * @param houseID Id da casa à qual foi emitida a fatura
     * @param start início do período de faturação
     * @param end fim do período de faturação
     * @param consumption Consumo (em kwh) desse período
     * @param cost Custo associado a esse consumo
     */
    public Bill(int houseID, LocalDateTime start, LocalDateTime end, double consumption, double cost) {
        this.houseID = houseID;
        this.period = new DateInterval(start, end);
        this.consumption = consumption;
        this.cost = cost;
    }

    /**
     * Construtor de cópia
     * @param b Fatura a copiar
     */
    public Bill(Bill b){
        this.houseID = b.houseID;
        this.period = b.getPeriod();
        this.consumption = b.getConsumption();
        this.cost = b.getCost();
    }

    /**
     * Devolve o id da casa associada à fatura
     * @return id da casa
     */
    public int getHouseID(){
        return this.houseID;
    }

    /**
     * Altera o id da casa associada à fatura
     * @param houseID id da casa
     */
    public void setHouseID(int houseID){
        this.houseID = houseID;
    }

    /**
     * Devolve o período de faturação
     * @return o período de faturação
     */
    public DateInterval getPeriod() {
        return this.period.clone();
    }

    /**
     * Altera o período de faturação
     * @param period o período de faturação
     */
    public void setPeriod(DateInterval period) {
        this.period = period.clone();
    }

    /**
     * Devolve o consumo associado à fatura, naquele intervalo
     * @return consumo (em kwh)
     */
    public double getConsumption() {
        return consumption;
    }

    /**
     * Altera o consumo da fatura
     * @param consumption novo consumo (em kwh)
     */
    public void setConsumption(double consumption) {
        this.consumption = consumption;
    }

    /**
     * Devove o custo da fatura
     * @return o custo (em €)
     */
    public double getCost() {
        return cost;
    }

    /**
     * Altera o custo da fatura
     * @param cost custo (em €)
     */
    public void setCost(double cost) {
        this.cost = cost;
    }

    /**
     * Verifica se duas faturas são iguais
     * @param o Objeto a comparar
     * @return true, se forem iguais, faso caso contrário
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Bill bill = (Bill) o;
        return this.consumption == bill.getConsumption() && this.cost == bill.getCost() && this.period.equals(bill.getPeriod()) && this.houseID == bill.getHouseID();
    }

    /**
     * Devolve a string correspondente à fatura
     * @return string com a fatura
     */
    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("------------------------------------\n");
        sb.append("Período : \n").append(period);
        sb.append("Casa : ").append(this.houseID).append("\n");
        sb.append("Consumo : ").append(String.format("%.2f", this.consumption)).append("kWh\n");
        sb.append("Custo : ").append(String.format("%.2f", this.cost)).append("€\n");
        sb.append("------------------------------------\n");

        return sb.toString();
    }

    /**
     * Faz uma cópia da fatura
     * @return a cópia
     */
    @Override
    public Bill clone(){
        return new Bill(this);
    }

    /**
     * Compara duas faturas (noção de ordem natural)
     * Comparação com base no período de emissão (para as queries)
     * @param b fatura a comparar
     * @return
     */
    @Override
    public int compareTo(Bill b){
        return this.period.compareTo(b.period);
    }
}
