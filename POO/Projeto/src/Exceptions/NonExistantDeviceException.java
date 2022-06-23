package src.Exceptions;

public class NonExistantDeviceException extends Exception{
    /**
     * Cria uma nova exceção de dispositivo não existente, com a mensagem recebida
     * @param msg Mensagem a imprimir mais tarde
     */
    public NonExistantDeviceException(String msg){
        super(msg);
    }
}
