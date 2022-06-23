package src.SmartDevices;

import java.io.Serializable;

public class SmartSpeaker extends SmartDevice implements Serializable {
    public static final int MAX = 20; //volume máximo    
    private int volume; // Current volume (between 0 and MAX=20)
    private String channel; // Radio channel currently
    private String brand; // Speaker brand

    /**
     * Construtor por defeito
     */
    public SmartSpeaker() {
        super();
        this.volume = 10;
        this.channel = "";
        this.brand = "";
        this.setBaseConsumption(0.0019);
    }

    /**
     * Construtor que recebe todos os parâmetros da subclasse
     * @param volume volume no qual a coluna opera inicialmente
     * @param channel estação inicial
     * @param brand marca da coluna
     * @param baseConsumption consumo base (em kw)
     */
    public SmartSpeaker(int volume, String channel, String brand, double baseConsumption) {
        super();
        if (volume > 0 && volume < SmartSpeaker.MAX) this.volume = volume;
        else this.volume = 0;
        this.channel = channel;
        this.brand = brand;
        this.setBaseConsumption(baseConsumption);
    }

    /**
     * Construtor que não recebe o consumo base
     * @param volume volume no qual a coluna opera inicialmente
     * @param channel estação inicial
     * @param brand marca da coluna
     */
    public SmartSpeaker(int volume, String channel, String brand) {
        super();
        if (volume > 0 && volume < SmartSpeaker.MAX) this.volume = volume;
        else this.volume = 0;
        this.channel = channel;
        this.brand = brand;
    }


    /**
     * Construtor que recebe o custo de instalação e o estado inicial
     * @param costOfInstallation custo de instalação
     * @param onState estado inicial (on/off)
     */
    public SmartSpeaker(int costOfInstallation, boolean onState) {
        super(costOfInstallation, onState);
        this.volume = 10;
        this.channel = "";
        this.brand = "";
        this.setBaseConsumption(0.0019);
    }

    /**
     * Construtor que recebe todos os argumentos
     * @param volume volume no qual a coluna opera
     * @param channel estação de rádio atual
     * @param brand marca da coluna
     * @param baseConsumption consumo base em kw
     * @param costOfInstallation custo de instalação
     * @param onState estado inicial (on/off)
     */
    public SmartSpeaker(int volume, String channel, String brand, double baseConsumption, int costOfInstallation, boolean onState) {
        super(costOfInstallation, onState);
        if (volume > 0 && volume < SmartSpeaker.MAX) this.volume = volume;
        else this.volume = 0;
        this.channel = channel;
        this.brand = brand;
        this.setBaseConsumption(baseConsumption);
    }

    /**
     * Construtor de cópia
     * @param speaker coluna a copiar para esta instância
     */
    public SmartSpeaker(SmartSpeaker speaker) {
        super(speaker);
        if (speaker.volume > 0 && speaker.volume < SmartSpeaker.MAX) this.volume = speaker.volume;
        else this.volume = 0;
        this.channel = speaker.getChannel();
        this.brand = speaker.getBrand();
        this.setBaseConsumption(speaker.getBaseConsumption());
    }

    /**
     * Devolve a estação atual
     * @return estação atual da coluna
     */
    public String getChannel() {
        return this.channel;
    }

    /**
     * Devolve a marca da coluna
     * @return marca da coluna
     */
    public String getBrand() {
        return this.brand;
    }

    /**
     * Devolve o volume atual da coluna
     * @return o volume atual da coluna
     */
    public int getVolume() {
        return this.volume;
    }

    /**
     * Altera a estação da coluna
     * @param c nova estação
     */
    public void setChannel(String c) {
        this.channel = c;
    }

    /**
     * Altera a marca da coluna
     * @param b marca da coluna a alterar
     */
    public void setBrand(String b) {
        this.brand = b;
    }

    /**
     * Altera o volume da coluna
     * @param vol novo volume
     */
    public void setVolume(int vol){
        if (vol > 0 && vol < SmartSpeaker.MAX) this.volume = vol;
        else this.volume = 0;
    }

    /**
     * Devolve o consumo da coluna (método abstrato implementado)
     * @return consumo atual (em kw)
     */
    public double getConsumption(){
        return (this.getBaseConsumption() + (0.00003 * this.volume)) * (this.getOnState() ? 1 : 0);
    }

    /**
     * Verifica se duas colunas sao iguais
     * @param o Objeto a ser comparado
     * @return true, se forem iguais, false, caso contrário
     */
    @Override
    public boolean equals(Object o){
        if(this == o) return true;
        if(o == null || this.getClass() != o.getClass()) return false;


        SmartSpeaker sp = (SmartSpeaker ) o;
        return this.volume == sp.volume && this.channel.equals(sp.channel) && this.brand.equals(sp.brand) && super.equals(sp);
    }

    /**
     * Devolve a representação na forma de uma String
     * @return a representação da coluna inteligente
     */
    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("\nSmartSpeaker: ");
        sb.append(super.toString());
        sb.append(" | Volume: ").append(this.volume);
        sb.append(" | Canal: ").append(this.channel);
        sb.append(" | Marca: ").append(this.brand);
        sb.append(" | Consumo base: ").append(this.getBaseConsumption());
        sb.append(" | Consumo atual: ").append(this.getConsumption());

        return sb.toString();
    }

    /**
     * Devolve uma cópia da instância atual
     * @return a cópia
     */
    @Override
    public SmartSpeaker clone(){
        return new SmartSpeaker(this);
    }

}
