package RacingManagerLN.Circuits;

import RacingManagerLN.Exceptions.AlreadyExistingCircuitException;

import java.util.List;

public interface ISubCircuits {

	public void addCircuit(String name, float length, int numLaps, int numCurves, int numChicanes) throws AlreadyExistingCircuitException;

	public List<String> generateCircuits(int numCircuits);

	public void addSector(String circuitName, int gdu, int sectorType);

	public List<String> showCircuitSectors(String circuitName);

	public List<List<String>> showAllCircuits();

	public Circuit getCircuit(String circuitName);
}