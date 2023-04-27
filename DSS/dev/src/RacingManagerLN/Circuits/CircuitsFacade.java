package RacingManagerLN.Circuits;

import RacingManagerDL.CircuitDAO;
import RacingManagerLN.Exceptions.AlreadyExistingCircuitException;
import RacingManagerLN.Exceptions.AlreadyExistingPilotException;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class CircuitsFacade implements ISubCircuits {
	public CircuitDAO circuits;

	public CircuitsFacade(){
		this.circuits = CircuitDAO.getInstance();
	}

	public void addCircuit(String name, float length, int numLaps, int numCurves, int numChicanes) throws AlreadyExistingCircuitException {
		if(this.circuits.containsKey(name)) throw new AlreadyExistingCircuitException("Já existe um circuito com o mesmo nome!");
		this.circuits.put(name, new Circuit(name, length, numLaps, numCurves, numChicanes));
	}

	public List<String> generateCircuits(int numCircuits) {
		List<String> circuitsNames = new ArrayList<>();
		List<String> allCircuits = new ArrayList<>(this.circuits.keySet());
		Random random = new Random();

		for (int i=0; i<numCircuits; i++) {
			circuitsNames.add(allCircuits.get(random.nextInt(0,allCircuits.size())));
		}
		return circuitsNames;
	}

	public void addSector(String circuitName, int gdu, int sectorType) {
		this.circuits.putSector(circuitName,sectorType,gdu);
	}

	public List<String> showCircuitSectors(String circuitName) {
		return this.circuits.get(circuitName).showCircuitSectors();
	}

	public List<List<String>> showAllCircuits() {
		List<List<String>> circuits = new ArrayList<>();

		for(Circuit circuit : this.circuits.values()){
			List<String> data = new ArrayList<>();

			data.add(circuit.getName());
			data.add(Integer.toString(circuit.getNumLaps()));
			data.add(Float.toString(circuit.getLength()));
			data.add(Integer.toString(circuit.getNumStraights()));
			data.add(Integer.toString(circuit.getNumCurves()));
			data.add(Integer.toString(circuit.getNumChicanes()));

			circuits.add(data);
		}

		return circuits;
	}

	public Circuit getCircuit(String circuitName) {
		return this.circuits.get(circuitName);
	}

}