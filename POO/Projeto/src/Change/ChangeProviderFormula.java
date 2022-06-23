package src.Change;

import src.Community.Community;

import java.util.function.Consumer;

public class ChangeProviderFormula extends Change{
    /**
     * Construtor que guarda a mudança
     * @param newFormula nova fórmula a aplicar
     * @param provName nome do fornecedor
     */
    public ChangeProviderFormula(String newFormula, String provName){
        super((Consumer<Community>) c -> c.changeProviderState(provName, p -> p.setformula(newFormula)));
    }

    /**
     * Construtor de cópiia
     * @param c Mudança a copiar
     */
    public ChangeProviderFormula(ChangeProviderFormula c){
        super(c.getChangeFunction());
    }

    /**
     * Devolve uma cópia da mudança
     * @return uma cópia da mudança
     */
    @Override
    public Change clone() {
        return new ChangeProviderFormula((ChangeProviderFormula) this);
    }
}
