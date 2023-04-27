package RacingManagerLN;

import RacingManagerDL.DAOconfig;
import RacingManagerLN.Cars.Car;
import RacingManagerLN.Cars.CarsFacade;
import RacingManagerLN.Cars.*;
import RacingManagerLN.Championships.Championship;
import RacingManagerLN.Championships.ChampionshipsFacade;
import RacingManagerLN.Championships.ISubChampionships;
import RacingManagerLN.Circuits.Circuit;
import RacingManagerLN.Circuits.CircuitsFacade;
import RacingManagerLN.Circuits.ISubCircuits;
import RacingManagerLN.Exceptions.*;
import RacingManagerLN.Pilots.ISubPilots;
import RacingManagerLN.Pilots.Pilot;
import RacingManagerLN.Pilots.PilotsFacade;
import RacingManagerLN.Simulations.ISubSimulations;
import RacingManagerLN.Simulations.SimulationsFacade;
import RacingManagerLN.Users.ISubUsers;
import RacingManagerLN.Users.User;
import RacingManagerLN.Users.UsersFacade;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class RacingManagerLN implements IRacingManagerLN {
	private ISubCars cars;
	private ISubUsers users;
	private ISubCircuits circuits;
	private ISubPilots pilots;
	private ISubSimulations simulations;
	private ISubChampionships championships;

	public RacingManagerLN(){
		DAOconfig.createDB();
		cars = new CarsFacade();
		users = new UsersFacade();
		circuits = new CircuitsFacade();
		pilots = new PilotsFacade();
		championships = new ChampionshipsFacade();
		simulations = new SimulationsFacade();
	}

	public void loginUser(String username, String password) throws NonExistentUsernameException {
		users.loginUser(username,password);
	}

	public void addPlayer(String username, String password, String country) throws NonExistentUsernameException {
		users.addPlayer(username, password, country);
	}

	public void setAdmin(String username, String password) {
		users.setAdmin(username,password);
	}

	public List<List<String>> getGlobalClassification() {
		return users.getGlobalClassification();
	}

	public List<List<String>> getGlobalClassification(String country) {
		return users.getGlobalClassification(country);
	}

	public void addPilot(String name, float valueCTS, float valueSVA) throws InvalidCtsException, InvalidSvaException, AlreadyExistingPilotException{
		pilots.addPilot(name,valueCTS,valueSVA);
	}

	public void addPilot(String name) throws AlreadyExistingPilotException{
		pilots.addPilot(name);
	}


	/**
	 * Gets all the pilots available
	 * @return A list of lists of attributes of pilots
	 * List of attributes: pilotName, cts, sva
	 */
	public List<List<String>> showAllPilots() {
		return pilots.showAllPilots();
	}

	public void addC1(String brand, String model, int hp, int engineCapacity, float reliability, float pac, int electricPower) throws InvalidReliabilityException, InvalidPacException {
		cars.addC1(brand,model,hp,engineCapacity,reliability,pac,electricPower);
	}

	public void addC2(String brand, String model, int hp, int engineCapacity, float pac, int eletricPower) throws InvalidPacException, InvalidEngineCapacityException{
		cars.addC2(brand,model,hp,engineCapacity,pac,eletricPower);
	}

	public void addSC(String brand, String model, int hp, float pac) throws InvalidPacException{
		cars.addSC(brand,model,hp,pac);
	}

	public void addGT(String brand, String model, int hp, int engineCapacity, float pac, int electricPower) throws InvalidPacException, InvalidEngineCapacityException{
		cars.addGT(brand,model,hp,engineCapacity,pac,electricPower);
	}

	public List<List<String>> showAllCars() {
		return cars.showAllCars();
	}

	public String showCategories() {
		return cars.showCategories();
	}

	public List<String> generateCircuits(int numCircuits) {
		List<String> l = circuits.generateCircuits(numCircuits);
		List<String> strings = new ArrayList<>(l);
		return strings;
	}

	public void addCircuit(String name, float length, int numLaps, int numCurves, int numChicanes) throws AlreadyExistingCircuitException {
		circuits.addCircuit(name,length,numLaps,numCurves,numChicanes);
	}

	public void addSector(String circuitName, int gdu, int sectorType) {
		circuits.addSector(circuitName,gdu,sectorType);
	}

	public List<String> showCircuitSectors(String circuitName) {
		return null;
	}

	public void addChampionship(String name, List<String> circuits, int maxPlayers) throws AlreadyExistingChampionshipException {
		List<Circuit> l = new ArrayList<>();
		for (String str : circuits) {
			l.add(this.circuits.getCircuit(str));
		}
		championships.addChampionship(name,l,maxPlayers);
	}

	public Championship getChampionship(String nameChamp) throws NonExistentChampionshipException {
		return championships.getChampionship(nameChamp);
	}

	/**
	 * Gets all the championships in the system in a "pretty" way
	 * @return a string with all the championships registered
	 */
	public List<List<String>> showChampionships() {
		return this.championships.showChampionships();
	}

	/**
	 * Adds a new record to the simulation
	 * @param simulationName the name of the simulation
	 * @param carID the id of the chosen car
	 * @param pilotName the name of the chosen pilot
	 * @param username the username of the player
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 * @throws NonExistentCarException if there are no cars with that id
	 * @throws NonExistentPilotException if there are no pilots with that name
	 */
	public void addRecord(String simulationName, int carID, String pilotName, String username) throws NonExistentSimulationException, NonExistentCarException, NonExistentPilotException, NonExistentUsernameException {
		Car partCar = this.cars.getCar(carID); // Composition
		if (partCar == null){
			throw new NonExistentCarException("Car with id " + carID + " doesn't exist!");
		}

		Pilot partPilot = this.pilots.getPilot(pilotName); // Composition
		if (partPilot == null){
			throw new NonExistentPilotException("Pilot with name " + pilotName + " doesn't exist!");
		}

		if (!this.users.existsUser(username)) throw new NonExistentUsernameException("Username " + username + " doens't exist!");

		this.simulations.addRecord(simulationName, partCar, partPilot, username);
	}

	/**
	 * Starts the simulation for a given championship
	 * @param simulationName name of the simulation championship
	 * @throws NonExistentSimulationException if there is no simulation with that name
	 * @return the starting grid
	 */
	public List<List<String>> startSimulation(String simulationName) throws NonExistentSimulationException{
		return this.simulations.startSimulation(simulationName);
	}

	/**
	 * Get the weather of the next race of a given simulation
	 * @param simulationName name of the simulation
	 * @return a string with the weather
	 * @throws NonExistentSimulationException if there is no simulation with that name
	 */
	public String getWeather(String simulationName) throws NonExistentSimulationException{
		return this.simulations.getWeather(simulationName);
	}

	/**
	 * Simulates the next lap in a simulation
	 * @param simulationName the name of the simulation
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 * @return true se já chegou ao fim da corrida, false se há mais voltas
	 */
	public boolean simulateNextLap(String simulationName) throws NonExistentSimulationException {
		return simulations.simulateNextLapPremium(simulationName);
	}


	/**
	 * Simulates the next lap in a simulation
	 * @param simulationName the name of the simulation
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 * @return true se já chegou ao fim da corrida, false se há mais voltas
	 */
	public boolean simulateNextLapPremium(String simulationName) throws NonExistentSimulationException {
		return simulations.simulateNextLapPremium(simulationName);
	}

	/**
	 * Update a player car in a simulation
	 * @param simulationName name of the simulation
	 * @param userName username of the player in control of that car
	 * @param valueDownforce value of the new downforce
	 * @param engineMode new engineMode
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 * @throws InvalidDownforceException if downforce value is not correct
	 * @throws NoAdjustementsLeftException if player has got no more adjustements left
	 */
	public void addAdjustment(String simulationName, String userName, float valueDownforce, int engineMode) throws NonExistentSimulationException, InvalidDownforceException, NonExistentRecordException, NoAdjustementsLeftException {
		this.simulations.addAdjustment(simulationName, userName, valueDownforce, engineMode);
	}

	public void setTiresType(String simulationName, String userName, int tiresType) throws NonExistentSimulationException, NonExistentRecordException {
		simulations.setTiresType(simulationName,userName,tiresType);
	}

	/**
	 * Gets the current classification of a given simulation
	 * @param simulationName name of the simulation
	 * @return a string with the classification
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 */
	public List<List<String>> getChampionshipClassification(String simulationName) throws NonExistentSimulationException {
		return simulations.getChampionshipClassification(simulationName);
	}

	/**
	 * Gets the current classification of a given simulation for a given category
	 * @param simulationName name of the simulation
	 * @param category category we want
	 * @return a string with the classification
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 */
	public List<List<String>> getCategoryClassification(String simulationName, String category) throws NonExistentSimulationException{
		return this.simulations.getCategoryClassification(simulationName, category);
	}

	public List<List<String>> getGlobalClassification(LocalDate fromDate, LocalDate toDate) {
		return simulations.getGlobalClassification(fromDate,toDate);
	}

	/**
	 * Get the starting grid from a particular simulation
	 * @param simulationName the name of the simulated championship
	 * @return the string containing the grid
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 */
	public List<List<String>> showGrid(String simulationName, boolean premium) throws NonExistentSimulationException{
		return this.simulations.showGrid(simulationName, true);
	}

	/**
	 * Get all the simulations currently in the system
	 * @return a string containing all the simulations
	 */
	public List<List<String>> showSimulations() {
		return this.simulations.showSimulations();
	}

	/**
	 * Updates simulation info after a race is simulated
	 * @param simulationName the name of the simulation
	 * @return true if it is the final race, false otherwise
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 */
	public boolean finishSimulation(String simulationName) throws NonExistentSimulationException{
		Map<String, Integer> userScores = this.simulations.finishSimulation(simulationName);

		if (userScores != null){
			users.updateScore(userScores);
			return true;
		}

		return false;
	}

	/**
	 * Adds a simulation to the simulations subsystem
	 * @param simulationName name of the simulation
	 * @param champName name of the original championship
	 * @throws NonExistentChampionshipException if there are no championships with that name
	 * @throws AlreadyExistingSimulationException if there is already a simulation with that name
	 */
	public void addSimulation(String simulationName, String champName) throws NonExistentChampionshipException, AlreadyExistingSimulationException {
		Championship champ = this.championships.getChampionship(champName); // Get the original championship (by composition)

		if(champ != null){ // If it does not exist
			this.simulations.addSimulation(simulationName, champ);
		}
		else {
			throw new NonExistentChampionshipException("Championship with name " + champName + "doesn't exist!");
		}


	}

	public List<List<String>> showAllCircuits() {
		return circuits.showAllCircuits();
	}

}