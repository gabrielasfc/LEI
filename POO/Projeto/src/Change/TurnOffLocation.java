package src.Change;

import src.Community.SmartHouse;

import java.util.function.Consumer;

public class TurnOffLocation extends ChangeLocation{
    /**
     * Construtor que guarda a mudança
     * @param location Divisão onde vão ser desligados todos os dispositivos
     */
    public TurnOffLocation(String location){
        super(location, (Consumer<SmartHouse>) sH -> sH.applyToLocation(location, sD -> sD.turnOff()));
    }

    /**
     * Construtor de cópiia
     * @param c Mudança a copiar
     */
    public TurnOffLocation(TurnOffLocation c){
        super(c.getLocation(), (Consumer<SmartHouse>)c.getChangeFunction());
    }

    /**
     * Devolve uma cópia da mudança
     * @return uma cópia da mudança
     */
    public Change clone(){
        return new TurnOffLocation((TurnOffLocation) this);
    }
}
