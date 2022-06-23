package src;

import src.Change.Change;

public interface Changeable {
    public void applyChanges();
    public void addChange(Change c);

}
