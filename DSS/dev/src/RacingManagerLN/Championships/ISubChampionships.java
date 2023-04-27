package RacingManagerLN.Championships;

import RacingManagerLN.Circuits.Circuit;
import RacingManagerLN.Exceptions.AlreadyExistingChampionshipException;
import RacingManagerLN.Exceptions.NonExistentChampionshipException;

import java.util.List;

public interface ISubChampionships {

	public void addChampionship(String champName, List<Circuit> circuits, int maxPlayers) throws AlreadyExistingChampionshipException;

	public List<List<String>> showChampionships();

	public Championship getChampionship(String nameChamp) throws NonExistentChampionshipException;
}