package src.Community;

import java.io.Serializable;
import java.util.*;

import net.objecthunter.exp4j.Expression;
import net.objecthunter.exp4j.ExpressionBuilder;
import src.Bill.Bill;

public class Provider implements Serializable{
    private String name;
    private double baseValue;
    private double tax;
    private double currentCost;
    private String formula;
    private Set<Bill> bills;

    /**
     * Construtor por defeito
     */
    public Provider() {
        this.name = "";
        this.baseValue = 0.15;
        this.tax = 0.23;
        this.currentCost = 0;
        this.formula = "";
        this.bills = new HashSet<>();
    }

    /**
     * Construtor que recebe todos os atributos menos as faturas
     * @param name Nome do fornecedor
     * @param baseValue Valor base
     * @param tax Imposto
     * @param formula Formula a aplicar
     */
    public Provider(String name, double baseValue, double tax, String formula) {
        this.name = name;
        this.baseValue = baseValue;
        this.tax = tax;
        this.currentCost = 0;
        this.formula = formula;
        this.bills = new HashSet<>();
    }

    /**
     * Construtor de cópia
     * @param p Fornecedor a ser copiado para esta instância
     */
    public Provider(Provider p){
        this.name = p.name;
        this.baseValue = p.baseValue;
        this.tax = p.tax;
        this.currentCost =  p.currentCost;
        this.formula = p.formula;
        this.bills = p.getBills();
    }

    /**
     * Construtor que apenas recebe o nome e a fórmula a aplicar
     * @param name Nome do fornecedor
     * @param formula Fórmula a aplicar
     */
    public Provider(String name, String formula){
        this.name = name;
        this.baseValue = 0.15;
        this.tax = 0.23;
        this.formula = formula;
        this.currentCost = 0;
        this.bills = new HashSet<>();
    }

    //Getters

    /**
     * Devolve o nome do fornecedor
     * @return nome do fornecedor
     */
    public String getName() {
        return name;
    }

    /**
     * Devolve o valor base do fornecedor
     * @return valor base do fornecedor
     */
    public double getBaseValue(){
        return this.baseValue;
    }

    /**
     * Devolve o imposto do fornecedor
     * @return imposto do fornecedor
     */
    public double getTax(){
        return this.tax;
    }

    /**
     * Devolve o valor faturado por esse fornecedor até este momento
     * @return valor faturado até agora
     */
    public double getCurrentCost(){
        return this.currentCost;
    }

    /**
     *  Devolve a fórmula do fornecedor
     * @return fórmula do fornecedor
     */
    public String getformula() {
        return this.formula;
    }


    /**
     * Devolve uma cópia do conjunto de faturas emitidas pelo fornecedor
     * @return conjunto das faturas do fornecedor (cópia)
     */
    public Set<Bill> getBills(){
        Set<Bill> ret = new HashSet<>();

        Set<Bill> billsSet = this.bills;

        if (billsSet != null) {
            Iterator<Bill> it = this.bills.iterator();

            while (it.hasNext()) {
                Bill b = it.next().clone(); // Faz a cópia

                ret.add(b);
            }
        }

        return ret;
    }

    //Setters

    /**
     * Altera o nome do fornecedor
     * @param name novo nome
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Altera o valor base de um fornecedor
     * @param baseValue novo valor base
     */
    public void setBaseValue(double baseValue){
        this.baseValue = baseValue;
    }

    /**
     * Altera o imposto de um fornecedor
     * @param tax novo imposto a aplicar pelo fornecedor
     */
    public void setTax(double tax){
        this.tax = tax;
    }

    /**
     * Altera o valor faturado pelo fornecedor
     * @param cost novo valor faturado
     */
    public void setCurrentCost(double cost){
        this.currentCost = cost;
    }

    /**
     * Altera a fórmula do fornecedor
     * @param formula nova fórmula
     */
    public void setformula(String formula) { this.formula = formula; }

    /**
     * Altera o conjunto das faturas de um fornecedor (por composição)
     * @param bills novo conjunto de faturas
     */
    public void setBills(Set<Bill> bills){
        this.bills = new HashSet<>();
        Iterator<Bill> it = bills.iterator();

        while(it.hasNext()){
            Bill b = it.next().clone(); // Cópia

            this.bills.add(b);
        }
    }

    //Others

    /**
     * Verifica se dois fornecedores são iguais
      * @param o Objeto a ser comparado
     * @return true, se forem iguais, false, caso contrário
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Provider p = (Provider) o;
        boolean isEqual;
        isEqual = this.name.equals(p.getName()) && this.baseValue == p.getBaseValue() && this.tax == p.getTax() && this.currentCost == p.getCurrentCost() && this.formula.equals(p.getformula());
        Iterator<Bill> it1 = this.bills.iterator();
        Iterator<Bill> it2 = p.bills.iterator();

        // Dois conjuntos de faturas são iguais se estiverem pela mesma ordem e tiverem os mesmos elementos
        while (it1.hasNext() && it2.hasNext()) {
            isEqual = it1.next().equals(it2.next());
        }

        isEqual = (it1.hasNext() == false) && (it2.hasNext() == false);

        return isEqual;
    }

    /**
     * Devolve a cópia da instância atual
     * @return a cópia
     */
    @Override
    public Provider clone() {
        return new Provider(this);
    }

    /**
     * Devolve a representação de um fornecedor
     * @return a string como representação do fornecedor
     */
    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("");
        sb.append("Nome: ").append(this.name);
        sb.append(" | Fórmula: ").append(this.formula);
        sb.append(" | Valor base: ").append(this.baseValue);
        sb.append(" | Taxa: ").append(this.tax + "\n");

        return sb.toString();
    }

    /**
     * Calcula o custo (em euros) de um dado consumo (em kwh)
     * @param consumption consumo em kwh
     * @return custo em euros
     */
    public double calculateCost(double consumption) {
        Expression exp = new ExpressionBuilder(this.formula)
                .variables("b", "t", "c")
                .build()
                .setVariable("b", this.baseValue)
                .setVariable("t", this.tax)
                .setVariable("c", consumption);

        return exp.evaluate();
    }

    /**
     * Adiciona uma fatura ao conjunto das faturas deste fornecedor
     * @param b fatura a adicionar
     */
    public void addBill(Bill b){
        this.bills.add(b.clone());
        this.currentCost += b.getCost();
    }

}