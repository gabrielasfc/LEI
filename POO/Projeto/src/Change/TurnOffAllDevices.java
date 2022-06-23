package src.Change;

import src.Community.SmartHouse;

import java.util.function.Consumer;

public class TurnOffAllDevices extends Change{
    /**
     * Construtor que guarda a mudança
     */
    public TurnOffAllDevices(){
        super((Consumer<SmartHouse>) sH -> sH.applyToAll(sD -> sD.turnOff()));
    }

    /**
     * Construtor de cópiia
     * @param c Mudança a copiar
     */
    public TurnOffAllDevices(TurnOffAllDevices c){
        super((Consumer<SmartHouse>) c.getChangeFunction());
    }

    /**
     * Devolve uma cópia da mudança
     * @return uma cópia da mudança
     */
    public Change clone(){
        return new TurnOffAllDevices((TurnOffAllDevices) this);
    }
}