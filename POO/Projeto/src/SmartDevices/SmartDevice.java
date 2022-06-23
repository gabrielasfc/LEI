package src.SmartDevices;

import java.io.Serializable;

public abstract class SmartDevice implements Serializable {
    private final int id; // Each device has its own id
    private boolean onState; // true - on, false - off
    private int costOfInstallation; // in Euros
    private double baseConsumption;

    private static int idCount = 1; // Para o autoincremento dos ids

    /**
     * Construtor por defeito
     */
    public SmartDevice() {
        this.id = SmartDevice.idCount++;
        this.costOfInstallation = 1;
        this.onState = false;
    }

    /**
     * Devolve o valor do consumo base em Kw
     * @return
     */
    public double getBaseConsumption() {
        return baseConsumption;
    }

    /**
     * Altera o valor do consumo base
     * @param baseConsumption consumo base
     */
    public void setBaseConsumption(double baseConsumption) {
        this.baseConsumption = baseConsumption;
    }

    /**
     * Construtor que recebe os parâmetro que se podem definir
     * @param costOfInstallation Custo de instalação
     * @param onState estado inicial (ligado ou desligado)
     */
    public SmartDevice(int costOfInstallation, boolean onState) {
        this.id = SmartDevice.idCount++;
        this.costOfInstallation = costOfInstallation;
        this.onState = onState;
    }

    /**
     * Construtor de cópia
     * @param d Dispositivo a ser copiado
     */
    public SmartDevice(SmartDevice d) {
        this.id = d.getId();
        this.costOfInstallation = d.getCostOfInstallation();
        this.onState = d.getOnState();
    }

    /**
     * Devolve o id do dispositivo
     * Id é autoincrementado sempre que se cria um novo objeto
     * @return id do dispositivo
     */
    public int getId() {
        return this.id;
    }

    /**
     * Devolve o custo de instalação de um dado dispositivo
     * @return on/off
     */
    public int getCostOfInstallation() {
        return this.costOfInstallation;
    }

    /**
     * Devolve o estado de um dispositivo (on/off)
     * @return
     */
    public boolean getOnState() {
        return this.onState;
    }

    /**
     * Altera o custo de instalação de um SmartDevice
     * @param costOfInstallation custo de instalação
     */
    public void setCostOfInstallation(int costOfInstallation) {
        this.costOfInstallation = costOfInstallation;
    }

    /**
     * Liga o dispositivo
     */
    public void turnOn() {
        this.onState = true;
    }

    /**
     * Desliga o dispositivo
     */
    public void turnOff(){
        this.onState = false;
    }

    /**
     * Devolve o consumo (em Kw) de um dado device
     * A ser implementado nas subclasses
     * @return Consumo (em Kw)
     */
    public abstract double getConsumption();

    /**
     * Devolve a representação em modo string de um dispositivo
     * @return String com o SmartDevice
     */
    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("");
        sb.append("Id: ").append(id);
        sb.append(" | Custo de instalação: ").append(costOfInstallation + "€");
        sb.append(onState ? " | ON" : " | OFF");
        return sb.toString();
    }

    /**
     * Verifica se dois dispositivos são iguais
     * @param o Objeto a ser comparado
     * @return true, se forem iguais, false caso contrário
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        SmartDevice that = (SmartDevice) o;
        return id == that.getId() && costOfInstallation == that.costOfInstallation && onState == that.onState && this.baseConsumption == that.getBaseConsumption();
    }

    /**
     * Faz uma cópia do dispositivo ( a ser implementado nas subclasses
     * @return uma cópia do objeto
     */
    @Override
    public abstract SmartDevice clone();
}