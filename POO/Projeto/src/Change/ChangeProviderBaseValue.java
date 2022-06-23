package src.Change;

import src.Community.Community;

import java.util.function.Consumer;

public class ChangeProviderBaseValue extends Change {
    /**
     * Construtor que guarda a mudança
     * @param newBaseValue Novo valor base
     * @param provName Nome do fornecedor
     */
    public ChangeProviderBaseValue(double newBaseValue, String provName){
        super((Consumer<Community>) c -> c.changeProviderState(provName, p -> p.setBaseValue(newBaseValue)));
    }

    /**
     * Construtor de cópiia
     * @param c Mudança a copiar
     */
    public ChangeProviderBaseValue(ChangeProviderBaseValue c){
        super(c.getChangeFunction());
    }

    /**
     * Devolve uma cópia da mudança
     * @return uma cópia da mudança
     */
    @Override
    public Change clone() {
        return new ChangeProviderBaseValue((ChangeProviderBaseValue) this);
    }
}
