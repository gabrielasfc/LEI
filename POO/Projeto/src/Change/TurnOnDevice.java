package src.Change;

import src.Community.SmartHouse;

import java.util.function.Consumer;

public class TurnOnDevice extends ChangeDevice {
    /**
     * Construtor que guarda a mudança
     * @param id id do dispositivo que vai ser ligado
     */
    public TurnOnDevice(int id){
        super(id, sH -> sH.turnDevice(id, sD -> sD.turnOn()));
    }

    /**
     * Construtor de cópiia
     * @param c Mudança a copiar
     */
    public TurnOnDevice(TurnOnDevice c){
        super(c.getDeviceId(), (Consumer<SmartHouse>) c.getChangeFunction());
    }

    /**
     * Devolve uma cópia da mudança
     * @return uma cópia da mudança
     */
    public Change clone(){
        return new TurnOnDevice((TurnOnDevice) this);
    }
}
