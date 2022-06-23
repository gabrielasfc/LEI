package src.Change;

import src.Community.SmartHouse;

import java.util.function.Consumer;

public class TurnOnAllDevices extends Change{
    /**
     * Construtor que guarda a mudança
     */
    public TurnOnAllDevices(){
        super((Consumer<SmartHouse>) sH -> sH.applyToAll(sD -> sD.turnOn()));
    }

    /**
     * Construtor de cópiia
     * @param c Mudança a copiar
     */
    public TurnOnAllDevices(TurnOnAllDevices c){
        super((Consumer<SmartHouse>) c.getChangeFunction());
    }

    /**
     * Devolve uma cópia da mudança
     * @return uma cópia da mudança
     */
    public Change clone(){
        return new TurnOnAllDevices((TurnOnAllDevices) this);
    }
}
