package RacingManagerLN.Championships;

import RacingManagerDL.ChampionshipDAO;
import RacingManagerLN.Circuits.Circuit;
import RacingManagerLN.Exceptions.AlreadyExistingChampionshipException;
import RacingManagerLN.Exceptions.NonExistentChampionshipException;

import java.util.ArrayList;
import java.util.List;

public class ChampionshipsFacade implements ISubChampionships{
	private ChampionshipDAO championships;

	public ChampionshipsFacade() {
		this.championships = ChampionshipDAO.getInstance();
	}

	public void addChampionship(String champName, List<Circuit> circuits, int maxPlayers) throws AlreadyExistingChampionshipException {
		if (this.championships.containsKey(champName)) throw new AlreadyExistingChampionshipException("Já existe um campeonato com o mesmo nome!");
		Championship c = new Championship(maxPlayers,champName,circuits);
		championships.put(champName,c);
	}

	/**
	 * Gets all the championships in the system in a "pretty" way
	 * @return a list of list os strings with all the championships registered
	 */
	public List<List<String>> showChampionships() {
		List<List<String>> championships = new ArrayList<>();

		for (Championship champ : this.championships.values()){
			List<String> data = new ArrayList<>();

			data.add(champ.getName());
			data.add(Integer.toString(champ.getMaxPlayers()));

			for(Circuit circuit : champ.getCircuits()){
				data.add(circuit.getName());
				data.add(Integer.toString(circuit.getNumLaps()));
				data.add(Float.toString(circuit.getLength()));
			}

			championships.add(data);
		}

		return championships;
	}


	public Championship getChampionship(String nameChamp) throws NonExistentChampionshipException {
		Championship c = this.championships.get(nameChamp);

		if (c != null){
			return c;
		}
		else throw new NonExistentChampionshipException("A simulação " + nameChamp + " não existe!");
	}
}