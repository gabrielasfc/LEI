package src.Change;

import src.Changeable;
import src.Community.SmartHouse;
import src.SmartDevices.SmartDevice;

import java.util.function.Consumer;

public abstract class ChangeDevice extends Change{
    private int deviceId;

    /**
     * Construtor que recebe o id do dispositivo e o consumer que opera a mudança na casa
     * @param deviceId id do dispositivo
     * @param cons consumer (função que faz a mudança)
     */
    public ChangeDevice(int deviceId, Consumer<SmartHouse> cons){
        super(cons);
        this.deviceId = deviceId;
    }

    /**
     * Devolve o id do dispositivo em que a mudança vai ser feita
     * @return id do dispositivo
     */
    public int getDeviceId() {
        return this.deviceId;
    }

    /**
     * Altera o id do dispositivo onde a mudança vai ser feita
     * @param deviceId id do dispositivo
     */
    public void setDeviceId(int deviceId){
        this.deviceId = deviceId;
    }

}
