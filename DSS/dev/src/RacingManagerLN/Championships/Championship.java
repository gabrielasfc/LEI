package RacingManagerLN.Championships;

import RacingManagerLN.Circuits.Circuit;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class Championship {
	private int maxPlayers;
	private String name;
	private List<Circuit> circuits = new ArrayList<Circuit>();

	public Championship(){
		this.maxPlayers = 10;
		this.name = "My Championship";
	}

	public Championship(int maxPlayers, String name){
		this.maxPlayers = maxPlayers;
		this.name = name;
	}

	public Championship(int maxPlayers, String name, List<Circuit> circuits){
		this.maxPlayers = maxPlayers;
		this.name = name;
		this.circuits = new ArrayList<>();

		for(Circuit c: circuits){
			this.circuits.add(c.clone());
		}
	}

	public int getMaxPlayers() {
		return this.maxPlayers;
	}

	public void setMaxPlayers(int maxPlayers) {
		this.maxPlayers = maxPlayers;
	}

	public String getName() {
		return this.name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public List<Circuit> getCircuits() {
		return this.circuits.stream().map(Circuit::clone).collect(Collectors.toList());
	}

	public void setCircuits(List<Circuit> circuits) {
		this.circuits = circuits;
	}

	/**
	 * Returns a string representation of a championship
	 * @return a string with the championship info
	 */
	public String toString(){
		return this.name + " , " + this.maxPlayers + "\n";
	}
}