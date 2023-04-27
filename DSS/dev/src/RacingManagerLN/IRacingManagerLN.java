package RacingManagerLN;

import RacingManagerLN.Championships.Championship;
import RacingManagerLN.Exceptions.*;

import java.time.LocalDate;
import java.util.List;

public interface IRacingManagerLN {

	public void loginUser(String username, String password) throws NonExistentUsernameException;

	public void addPlayer(String username, String password, String country) throws NonExistentUsernameException;

	public void setAdmin(String username, String password);

	public List<List<String>> getGlobalClassification();

	public List<List<String>> getGlobalClassification(String country);

	public void addPilot(String name, float valueCTS, float valueSVA) throws InvalidCtsException, InvalidSvaException, AlreadyExistingPilotException;

	public void addPilot(String name) throws InvalidCtsException, InvalidSvaException, AlreadyExistingPilotException;

	public List<List<String>> showAllPilots();

	public void addC1(String brand, String model, int hp, int engineCapacity, float reliability, float pac, int electricPower) throws InvalidReliabilityException, InvalidPacException ;

	public void addC2(String brand, String model, int hp, int engineCapacity, float pac, int eletricPower) throws InvalidPacException, InvalidEngineCapacityException;

	public void addSC(String brand, String model, int hp, float pac) throws InvalidPacException;

	public void addGT(String brand, String model, int hp, int engineCapacity, float pac, int electricPower)  throws InvalidPacException, InvalidEngineCapacityException;

	public List<List<String>> showAllCars();

	public String showCategories();

	public List<String> generateCircuits(int numCircuits);

	public void addCircuit(String name, float length, int numLaps, int numCurves, int numChicanes) throws AlreadyExistingCircuitException;

	public void addSector(String circuitName, int gdu, int sectorType);

	public List<String> showCircuitSectors(String circuitName);

	public List<List<String>> showAllCircuits();

	public void addChampionship(String name, List<String> circuits, int maxPlayers) throws AlreadyExistingChampionshipException;

	public Championship getChampionship(String nameChamp) throws NonExistentChampionshipException;

	/**
	 * Gets all the championships in the system in a "pretty" way
	 * @return a string with all the championships registered
	 */
	public List<List<String>> showChampionships();

	/**
	 * Adds a simulation to the simulations subsystem
	 * @param simulationName name of the simulation
	 * @param champName name of the original championship
	 * @throws NonExistentChampionshipException if there are no championships with that name
	 * @throws AlreadyExistingSimulationException if there is already a simulation with that name
	 */
	public void addSimulation(String simulationName, String champName) throws NonExistentChampionshipException, AlreadyExistingSimulationException;

	public void addRecord(String simulationName, int carID, String pilotName, String username) throws NonExistentSimulationException, NonExistentCarException, NonExistentPilotException, NonExistentUsernameException;

	/**
	 * Update a player car in a simulation
	 * @param simulationName name of the simulation
	 * @param userName username of the player in control of that car
	 * @param valueDownforce value of the new downforce
	 * @param engineMode new engineMode
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 * @throws InvalidDownforceException if downforce value is not correct
	 * @throws NonExistentRecordException if player is not found in records collection
	 * @throws NoAdjustementsLeftException if player has got no more adjustements left
	 */
	public void addAdjustment(String simulationName, String userName, float valueDownforce, int engineMode) throws NonExistentSimulationException, InvalidDownforceException, NonExistentRecordException, NoAdjustementsLeftException;

	public List<List<String>> startSimulation(String simulationName) throws NonExistentSimulationException;

	public boolean finishSimulation(String simulationName) throws NonExistentSimulationException;

	public List<List<String>> showGrid(String simulationName, boolean premium) throws NonExistentSimulationException;

	/**
	 * Get the weather of the next race of a given simulation
	 * @param simulationName name of the simulation
	 * @return a string with the weather
	 * @throws NonExistentSimulationException if there is no simulation with that name
	 */
	public String getWeather(String simulationName) throws NonExistentSimulationException;

	public void setTiresType(String simulationName, String userName, int tiresType) throws NonExistentSimulationException, NonExistentRecordException;

	public boolean simulateNextLap(String simulationName) throws NonExistentSimulationException;

	public boolean simulateNextLapPremium(String simulationName) throws NonExistentSimulationException;

	/**
	 * Gets the current classification of a given simulation
	 * @param simulationName name of the simulation
	 * @return a string with the classification
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 */
	public List<List<String>> getChampionshipClassification(String simulationName) throws NonExistentSimulationException;

	/**
	 * Gets the current classification of a given simulation for a given category
	 * @param simulationName name of the simulation
	 * @param category category we want
	 * @return a string with the classification
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 */
	public List<List<String>> getCategoryClassification(String simulationName, String category) throws NonExistentSimulationException;

	public List<List<String>> getGlobalClassification(LocalDate fromDate, LocalDate toDate);

	/**
	 * Get all the simulations currently in the system
	 * @return a string containing all the simulations
	 */
	public List<List<String>> showSimulations();
}