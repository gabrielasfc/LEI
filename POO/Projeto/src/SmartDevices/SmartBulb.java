package src.SmartDevices;

import java.io.Serializable;

public class SmartBulb extends SmartDevice implements Serializable {
    public static final int WARM = 2;
    public static final int NEUTRAL = 1;
    public static final int COLD = 0;
    
    private int tone;
    private int dimension;


    /**
     * Construtor por defeito
     */
    public SmartBulb() {
        super();
        this.tone = NEUTRAL;
        this.dimension = 0;
        this.setBaseConsumption(0.0075);
    }

    /**
     * Construtor que recebe o modo, a dimensão e o consumo base
     * @param tone modo (Warm, Neutral, Cold)
     * @param dimension tamanho da lâmpada em cms
     * @param baseConsumption consumo base da lâmpada em kw
     */
    public SmartBulb(int tone, int dimension, double baseConsumption) {
        super();
        this.tone = tone;
        this.dimension = dimension;
        this.setBaseConsumption(baseConsumption);
    }

    /**
     * Construtor que recebe o modo e a dimensão
     * @param tone modo (Warm, Neutral, Cold)
     * @param dimension tamanho da lâmpada em cms
     */
    public SmartBulb(int tone, int dimension) {
        super();
        this.tone = tone;
        this.dimension = dimension;
    }

    /**
     * Construtor que recebe as variáveis da superclasses
     * @param costOfInstallation custo de instaação
     * @param onState estado inicial da lâmpada
     */
    public SmartBulb(int costOfInstallation, boolean onState) {
        super(costOfInstallation, onState);
        this.tone = NEUTRAL;
        this.dimension = 0;
        this.setBaseConsumption(0.0075);
    }

    /**
     * Construtor que recebe todos os parâmetros
     * @param tone modo
     * @param dimension dimensão
     * @param baseConsumption consumo base em kw
     * @param costOfInstallation custo de instalação
     * @param onState estado inicial
     */
    public SmartBulb(int tone, int dimension, double baseConsumption, int costOfInstallation, boolean onState) {
        super(costOfInstallation, onState);
        this.tone = tone;
        this.dimension = dimension;
        this.setBaseConsumption(baseConsumption);
    }

    /**
     * Construtor de cópia
     * @param bulb Lâmpada que queremos copiar
     */
    public SmartBulb(SmartBulb bulb) {
        super(bulb);
        this.dimension = bulb.getDimension();
        this.tone = bulb.getTone();
        this.setBaseConsumption(bulb.getBaseConsumption());
    }

    //Getters

    /**
     * Devolve o tone da lâmpada (warm, neutral, cold)
     * @return modo da lâmpada
     */
    public int getTone() {
        return this.tone;
    }

    /**
     * Devolve a dimensão da lâmpada
     * @return
     */
    public int getDimension() {
        return this.dimension;
    }

    //Setters

    /**
     * Altera o modo da lâmpada - acima de warm é warm, abaixo de cold é cold
     * @param t tone da lâmpada (warm, neutral, cold)
     */
    public void setTone(int t) {
        if (t>WARM) this.tone = WARM;
        else if (t<COLD) this.tone = COLD;
        else this.tone = t;
    }

    /**
     * Altera a dimensão da lâmpada
     * @param d nova dimensão (em cms)
     */
    public void setDimension(int d) {
        this.dimension = d;
    }

    /**
     * Devolve o consumo atual da lâmpada em kw
     * @return consumo atual em kw
     */
    public double getConsumption(){
        double toneMult = 0;

        switch(tone) {
            case COLD: toneMult = 0.5; break;
            case NEUTRAL: toneMult = 1; break;
            case WARM: toneMult = 2; break;
        }

        return (this.getBaseConsumption() * toneMult * (this.dimension*0.2) * (this.getOnState() ? 1 : 0));
    }

    //Others

    /**
     * Verifica se duas lâmpadas são iguais
     * @param o Objeto a ser comparado
     * @return true, se forem iguais, false, caso contrário
     */
    @Override
    public boolean equals(Object o){
        if(this == o) return true;
        if(o == null || this.getClass() != o.getClass()) return false;

        SmartBulb sb = (SmartBulb) o;
        
        return this.tone == sb.tone && this.dimension == sb.dimension && super.equals(sb);
    }

    /**
     * Devolve uma cópia da lâmpada da instância
     * @return a cópia
     */
    @Override
    public SmartBulb clone(){
        return new SmartBulb(this);
    }


    /**
     * Devolve a representação da âmpada em modo string
     * @return string que representa a lâmpada
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("\nSmartBulb: ");
        sb.append(super.toString());
        sb.append(" | Intensidade: ");
        switch (this.tone) {
            case 0:
                sb.append("Cold");
                break;
            case 1:
                sb.append("Neutral");
                break;
            case 2:
                sb.append("Warm");
                break;
            default: break;
        }
        sb.append(" | Consumo base: ").append(this.getBaseConsumption());
        sb.append(" | Consumo atual: ").append(this.getConsumption());
        return sb.toString();
    }
}

