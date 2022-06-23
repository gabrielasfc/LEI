package src.Change;

import src.Changeable;
import src.Community.SmartHouse;

import java.util.function.Consumer;

public class TurnOffDevice extends ChangeDevice{
    /**
     * Construtor que guarda a mudança
     * @param id id do dispositivo que vai ser desligado
     */
    public TurnOffDevice(int id){
        super(id, sH -> sH.turnDevice(id, sD -> sD.turnOff()));
    }

    /**
     * Construtor de cópiia
     * @param c Mudança a copiar
     */
    public TurnOffDevice(TurnOffDevice c){
        super(c.getDeviceId(), (Consumer<SmartHouse>) c.getChangeFunction());
    }

    /**
     * Devolve uma cópia da mudança
     * @return uma cópia da mudança
     */
    public Change clone(){
        return new TurnOffDevice((TurnOffDevice) this);
    }

}
