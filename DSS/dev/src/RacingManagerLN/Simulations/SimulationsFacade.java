package RacingManagerLN.Simulations;

import RacingManagerDL.CarDAO;
import RacingManagerDL.SimulationDAO;
import RacingManagerLN.Cars.Car;
import RacingManagerLN.Championships.Championship;
import RacingManagerLN.Exceptions.*;
import RacingManagerLN.Pilots.Pilot;

import java.time.LocalDate;
import java.util.*;

public class SimulationsFacade implements ISubSimulations {
	private SimulationDAO simulations;
	private Simulation currentSimulation;

	public SimulationsFacade(){
		this.simulations = SimulationDAO.getInstance();
	}

	private Simulation getSimulation(String champName) {
		throw new UnsupportedOperationException();
	}

	private List<List<String>> showScores(Map<String, Integer> scores) {
		List<List<String>> classification = new ArrayList<>();

		for(String username : scores.keySet()){
			List<String> data = new ArrayList<>();

			data.add(username);
			data.add(Integer.toString(scores.get(username)));

			classification.add(data);
		}

		return classification;
	}

	/**
	 * Adds a simulation to the existing simulations
	 * @param simulationName name of the simulation
	 * @param champ The championship that gave origin to this simulation
	 * @throws AlreadyExistingSimulationException if there is already a simulation with that name
	 */
	public void addSimulation(String simulationName, Championship champ) throws AlreadyExistingSimulationException {
		if (this.simulations.containsKey(simulationName)){
			throw new AlreadyExistingSimulationException("A simulação " + simulationName + " já existe!");
		}
		else{
			Simulation sim = new Simulation(simulationName, champ.getMaxPlayers(), champ.getName(), champ.getCircuits());
			this.simulations.put(simulationName, sim);
		}

	}

	/**
	 * Adds a new record to the simulation
	 * @param simulationName the name of the simulation
	 * @param car the car of the participating user
	 * @param pilot the pilot chosen by the user
	 * @param username the username of the player
	 * @throws NonExistentSimulationException if there is no simulation with that name
	 */
	public void addRecord(String simulationName, Car car, Pilot pilot, String username) throws NonExistentSimulationException {
		Simulation sim = this.simulations.get(simulationName); // Get from the db

		if (sim != null){
			Car cp = CarDAO.getInstance().put(car.getCarId(), car);
			sim.addRecord(cp, pilot, username);
			this.simulations.put(sim.getName(), sim); // Must update in the db
		}
		else {
			throw new NonExistentSimulationException("A simulação " + simulationName + " não existe!");
		}

	}

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
	public void addAdjustment(String simulationName, String userName, float valueDownforce, int engineMode) throws NonExistentSimulationException, InvalidDownforceException, NonExistentRecordException, NoAdjustementsLeftException {
		//Simulation sim = this.simulations.get(simulationName);
		this.currentSimulation.addAdjustment(userName,valueDownforce,engineMode);
		/*if (sim != null){
			sim.addAdjustment(userName, valueDownforce, engineMode); // E os tire types??
			this.simulations.put(sim.getName(), sim); // If car updates, must update in the bd
		}
		else throw new NonExistentSimulationException("A simulação " + simulationName + " não existe!");*/
	}


	/**
	 * Starts the simulation for a given championship
	 * @param simulationName name of the simulation championship
	 * @throws NonExistentSimulationException if there is no simulation with that name
	 * @return the starting grid or null if the simulation of the championship is over
	 */
	public List<List<String>> startSimulation(String simulationName) throws NonExistentSimulationException{
		Simulation s = simulations.get(simulationName);

		if (s != null){
			List<List<String>> grid = s.startSimulation();
			this.currentSimulation = s;
			//this.simulations.put(simulationName, s); // Must update in the bd
			return grid;
		}
		else throw new NonExistentSimulationException("A simulação " + simulationName + " não existe!");
	}

	/**
	 * Updates simulation info after a race is simulated
	 * Also updates in the DB the simulation
	 * @param simulationName the name of the simulation
	 * @return a map with the scores of the players in the simulation
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 */
	public Map<String, Integer> finishSimulation(String simulationName) throws NonExistentSimulationException{
		Simulation s = this.currentSimulation;

		if (s != null){
			Map<String, Integer> map = s.finishSimulation();
			this.simulations.put(simulationName, s);
			return map;
		}
		else throw new NonExistentSimulationException("A simulação " + simulationName + " não existe!");
	}

	/**
	 * Get the starting grid from a particular simulation
	 *
	 * @param simulationName the name of the simulated championship
	 * @return the string containing the grid
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 */
	public List<List<String>> showGrid(String simulationName, boolean premium) throws NonExistentSimulationException {
		Simulation s = this.currentSimulation;

		if (s != null){
			return s.showGrid(premium);
		}
		else throw new NonExistentSimulationException("A simulação " + simulationName + " não existe!");
	}

	/**
	 * Get the weather of the next race of a given simulation
	 * @param simulationName name of the simulation
	 * @return a string with the weather
	 * @throws NonExistentSimulationException if there is no simulation with that name
	 */
	public String getWeather(String simulationName) throws NonExistentSimulationException{
		Simulation s = this.currentSimulation; // WHen we get weather the race must already be start so the simulation is already in memory

		if (s != null){
			return s.getWeather();
		}
		else throw new NonExistentSimulationException("A simulação " + simulationName + " não existe!");

	}

	/**
	 * Update the type of tires of a car in a simulation (Does not affect the number of adjustements available to the user)
	 * @param simulationName the name of the simulation
	 * @param userName the name of the user that makes the update
	 * @param tiresType the new type of tires
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 * @throws NonExistentRecordException if player is not found in records collection
	 */
	public void setTiresType(String simulationName, String userName, int tiresType) throws NonExistentSimulationException, NonExistentRecordException {
		Simulation sim = this.currentSimulation;

		if (sim == null){
			throw new NonExistentSimulationException("A simulação " + simulationName + " não existe!");
		}
		else {
			sim.setTiresType(userName, tiresType);
		}
	}

	/**
	 * Get the classification of a given simulated championship
	 * @param simulationName name of the simulation
	 * @return a string containing the players classification
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 */
	public List<List<String>> getChampionshipClassification(String simulationName) throws NonExistentSimulationException{
		Simulation sim = simulations.get(simulationName);

		if (sim == null){
			throw new NonExistentSimulationException("A simulação " + simulationName + " não existe!");
		}
		else {
			return sim.getClassification();
		}
	}


	/**
	 * Calculates the global classification (of all simulations) between two dates
	 * @param fromDate the initial date
	 * @param toDate the final date
	 * @return a string with the classification
	 */
	public List<List<String>> getGlobalClassification(LocalDate fromDate, LocalDate toDate) {
		Map<String, Integer> scores = new TreeMap<>();

		for(Simulation s: this.simulations.values()){
			s.gatherRecords(scores, fromDate, toDate);
		}

		return this.showScores(scores); // TODO
	}

	/**
	 * Gets the current classification of a given simulation for a given category
	 * @param simulationName name of the simulation
	 * @param category category we want
	 * @return a string with the classification
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 */
	public List<List<String>> getCategoryClassification(String simulationName, String category) throws NonExistentSimulationException {
		Simulation s = this.simulations.get(simulationName);

		if (s != null){
			return s.getCategoryClassification(category);
		}
		else throw new NonExistentSimulationException("A simulação " + simulationName + " não existe!");
	}

	/**
	 * Simulates the next lap in a simulation
	 * @param simulationName the name of the simulation
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 * @return true se já chegou ao fim da corrida, false se há mais voltas
	 */
	public boolean simulateNextLap(String simulationName) throws NonExistentSimulationException {
		Simulation s = this.currentSimulation; // WHen we get weather the race must already be start so the simulation is already in memory

		if (s != null){
			return s.simulateNextLap();
		}

		else throw new NonExistentSimulationException("A simulação " + simulationName + " não existe!");
	}

	/**
	 * Simulates the next lap in a simulation in the premium mode
	 * Calculations are based in the time difference between two cars
	 * @param simulationName the name of the simulation
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 * @return true se já chegou ao fim da corrida, false se há mais voltas
	 */
	public boolean simulateNextLapPremium(String simulationName) throws NonExistentSimulationException {
		Simulation s = this.currentSimulation;

		if (s != null){
			return s.simulateNextLapPremium();
		}

		else throw new NonExistentSimulationException("A simulação " + simulationName + " não existe!");
	}

	/**
	 * Gets the string representation of all the simulations stored in the database
	 * @return string with all the simulations data
	 */
	public List<List<String>> showSimulations() {
		List<List<String>> simulations = new ArrayList<>();

		for(Simulation simulation: this.simulations.values()){
			if (simulation.getCurrentRace()<this.simulations.get(simulation.getName()).getRaces().size()) {
				List<String> data = new ArrayList<>();

				data.add(simulation.getName());
				data.add(Integer.toString(simulation.getMaxPlayers()));
				data.add(simulation.getInitialDate().toString());
				data.add(simulation.getChampionshipName());

				simulations.add(data);
			}
		}

		return simulations;
	}

}