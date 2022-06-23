package src.Change;

import src.Community.Community;

import java.util.function.Consumer;

public class ChangeProviderTax extends Change{
    /**
     * Construtor que guarda a mudança
     * @param newTax novo imposto a aplicar
     * @param provName nome do fornecedor
     */
    public ChangeProviderTax(double newTax, String provName){
        super((Consumer<Community>) c -> c.changeProviderState(provName, p -> p.setTax(newTax)));
    }

    /**
     * Construtor de cópiia
     * @param c Mudança a copiar
     */
    public ChangeProviderTax(ChangeProviderTax c){
        super(c.getChangeFunction());
    }

    /**
     * Devolve uma cópia da mudança
     * @return uma cópia da mudança
     */
    @Override
    public Change clone() {
        return new ChangeProviderTax((ChangeProviderTax) this);
    }
}
