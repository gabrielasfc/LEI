package src.Change;

import src.Community.SmartHouse;

import java.util.function.Consumer;

public abstract class ChangeLocation extends Change{
    private String location;

    /**
     * Construtor que recebe a divisão e a função que opera a mudança
     * @param location divisão da casa onde todos os dispositivos vão ser alterados
     * @param cons consumer que opera a mudança
     */
    public ChangeLocation(String location, Consumer<SmartHouse> cons){
        super(cons);
        this.location = location;
    }

    /**
     * Devolve a divisão da casa onde vai ser aplicada a mudança
     * @return a divisão da casa
     */
    public String getLocation() {
        return location;
    }

    /**
     * Altera a divisão da casa onde vai ser aplicada a mudança
     * @location a divisão da casa
     */
    public void setLocation(String location) {
        this.location = location;
    }
}
