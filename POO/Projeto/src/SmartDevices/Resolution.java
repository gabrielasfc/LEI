package src.SmartDevices;

import java.io.Serializable;
import java.util.Objects;

public class Resolution implements Serializable {
    private int resW; // Width (pixels)
    private int resH; // Height (pixels)

    /**
     * Construtor por defeito
     */
    public Resolution(){
        this.resW = 0;
        this.resH = 0;
    }

    /**
     * Construtor que recebe a resolução na forma de dois parâmetros
     * @param resW resolução (width)
     * @param resH resolução (height)
     */
    public Resolution(int resW, int resH) {
        this.resW = resW;
        this.resH = resH;
    }

    /**
     * Construtor que recebe a resolução
     * @param r resolução (px x px)
     */
    public Resolution(Resolution r) {
        this.resW = r.getResW();
        this.resH = r.getResH();
    }

    /**
     * Devolve a resolução (width)
     * @return resolução (width)
     */
    public int getResW() {
        return resW;
    }

    /**
     * Altera a resolução (width)
     * @resW resolução (width)
     */
    public void setResW(int resW) {
        this.resW = resW;
    }

    /**
     * Devolve a resolução (height)
     * @return resolução (height)
     */
    public int getResH() {
        return resH;
    }

    /**
     * Altera a resolução (height)
     * @resH resolução (height)
     */
    public void setResH(int resH) {
        this.resH = resH;
    }

    /**
     * Faz uma cópia da resolução da instância
     * @return a cópia
     */
    public Resolution clone(){
        return new Resolution(this);
    }

    /**
     * Verifica se duas resoluções são iguais
     * @param o Resolução a comparar
     * @return true, se forem iguais, false, caso contrário
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Resolution that = (Resolution) o;
        return resW == that.getResW() && resH == that.getResH();
    }

    /**
     * Devolve uma representação da Resolução na forma de String
     * @return representação da resolução (resW x resH)
     */
    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("resolução: ");
        sb.append(resW + " x ");
        sb.append(resH);

        return sb.toString();
    }
}
