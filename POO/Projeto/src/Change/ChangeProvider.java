package src.Change;

import src.Community.SmartHouse;

import java.util.function.Consumer;

public class ChangeProvider extends Change{
    /**
     * Construtor que guarda a mudança
     * @param providerName Nome do novo fornecedor
     */
    public ChangeProvider(String providerName){
        super((Consumer<SmartHouse>) c -> c.setProviderName(providerName));
    }

    /**
     * Construtor de cópiia
     * @param c Mudança a copiar
     */
    public ChangeProvider(ChangeProvider c){
        super(c.getChangeFunction());
    }

    /**
     * Devolve uma cópia da mudança
     * @return uma cópia da mudança
     */
    public Change clone(){
        return new ChangeProvider((ChangeProvider) this);
    }
}
