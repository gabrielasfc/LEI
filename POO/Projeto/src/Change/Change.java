package src.Change;

import src.Changeable;

import java.io.Serializable;
import java.util.function.Consumer;

public abstract class Change implements Serializable {
    // Guardamos uma função que aplica uma mudança numa dada instância que implementa a interface Changeable
    private Consumer<? extends Changeable> changeFunction;

    /**
     * Construtor que recebe a função por parâmetro
     * @param changeFunction Consumer que aplica a mudança
     */
    public Change(Consumer<? extends Changeable> changeFunction) {
        this.changeFunction = changeFunction;
    }

    /**
     * Construtor de cópia
     * @param c Change a copiar para esta instância
     */
    public Change(Change c){
        this.changeFunction = c.getChangeFunction();
    }

    /**
     * Devolve a função que opera a mudança
     * @return
     */
    public Consumer<? extends Changeable> getChangeFunction() {
        return changeFunction;
    }

    /**
     * Método clone (abstrato porque queremos que a instância seja criada pelas subclasses
     * @return Uma cópia da mudança
     */
    public abstract Change clone();
}