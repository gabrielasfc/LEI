package src.SmartDevices;

import java.io.Serializable;
import java.util.Objects;

public class SmartCamera extends SmartDevice implements Serializable {
    private Resolution r;
    private int fileSize;


    /**
     * Construtor por defeito
     */
    public SmartCamera(){
        super();
        this.r = new Resolution();
        this.fileSize = 0;
        this.setBaseConsumption(0.001);
    }

    /**
     * Construtor que recebe a resolução e o tamanho do ficheiro de gravação
     * @param dimX dim no eixo do X (width)
     * @param dimY dim no eixo do Y (height)
     * @param fileSize tamanho do ficheiro
     */
    public SmartCamera(int dimX, int dimY, int fileSize){
        this.r = new Resolution(dimX, dimY);
        this.fileSize = fileSize;
    }

    /**
     * Construtor que recebe a resolução, o tamanho do ficheiro e o consumo base
     * @param r resolução
     * @param fileSize tamanho do ficheiro de gravação
     * @param baseConsumption consumo base em kw
     */
    public SmartCamera(Resolution r, int fileSize, double baseConsumption) {
        super();
        this.r = r.clone();
        this.fileSize = fileSize;
        this.setBaseConsumption(baseConsumption);
    }

    /**
     * Construtor que recebe as variáveis de SmartDevice
     * @param costOfInstallation custo de instalação
     * @param onState estado inicial
     */
    public SmartCamera(int costOfInstallation, boolean onState) {
        super(costOfInstallation, onState);
        this.r = new Resolution();
        this.fileSize = 0;
        this.setBaseConsumption(0.001);
    }

    /**
     * Construtor que recebe todas as variáveis
     * @param costOfInstallation custo de instalação
     * @param onState estado inicial
     * @param r resolução
     * @param fileSize tamanho do ficheiro em Mb
     * @param baseConsumption consumo base em kw
     */
    public SmartCamera(int costOfInstallation, boolean onState, Resolution r, int fileSize, double baseConsumption) {
        super(costOfInstallation, onState);
        this.r = r.clone();
        this.fileSize = fileSize;
        this.setBaseConsumption(baseConsumption);
    }

    /**
     * Construtor de cópia
     * @param camera camera a ser copiada para esta instância
     */
    public SmartCamera(SmartCamera camera) {
        super(camera);
        this.r = camera.getResolution();
        this.fileSize = camera.getFileSize();
        this.setBaseConsumption(camera.getBaseConsumption());
    }

    /**
     * Devolve a resolução
     * @return resolução (px * px)
     */
    public Resolution getResolution() {
        return this.r.clone();
    }

    /**
     * Devolve o tamanho do ficheiro de gravação em Mb
     * @return
     */
    public int getFileSize() {
        return this.fileSize;
    }

    /**
     * Altera a resolução
     * @param r resolução
     */
    public void setResolution(Resolution r) {
        this.r = r.clone();
    }

    /**
     * Altera o tamanho do ficheiro de gravação (em Mb)
     * @param fileSize tamanho do ficheiro em Mb
     */
    public void setFileSize(int fileSize) {
        this.fileSize = fileSize;
    }


    /**
     * Devolve o consumo atual da câmara inteligente (em kw)
     * @return consumo em kw
     */
    public double getConsumption(){
        double file = 0.00000008 * this.fileSize;
        double res = this.r.getResH() * 0.000002 + 0.000001 * this.r.getResW();

        return (this.getBaseConsumption() + file + res) * (this.getOnState() ? 1 : 0);
    }

    /**
     * Verifica se duas câmaras são iguais
     * @param o Objeto a ser comparado
     * @return true, se forem iguais, false, caso contrário
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        SmartCamera that = (SmartCamera) o;
        return this.fileSize == that.fileSize && this.r.equals(that.getResolution()) && super.equals(that);
    }

    /**
     * Devolve a representação de uma câmara inteligente
     * @return string que representa a câmara
     */
    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("\nSmartCamera: ");
        sb.append(super.toString());
        sb.append(" | ").append(this.r.toString());
        sb.append(" | Tamanho do ficheiro: ").append(this.fileSize + "MB");
        sb.append(" | Consumo base: ").append(this.getBaseConsumption());
        sb.append(" | Consumo atual: ").append(this.getConsumption());

        return sb.toString();
    }

    /**
     * Devolve uma cópia da câmara inteligente
     * @return a cópia
     */
    @Override
    public SmartCamera clone(){
        return new SmartCamera(this);
    }
}
