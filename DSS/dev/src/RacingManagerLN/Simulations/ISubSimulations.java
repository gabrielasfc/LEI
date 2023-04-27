package RacingManagerLN.Simulations;

import RacingManagerLN.Cars.Car;
import RacingManagerLN.Championships.Championship;
import RacingManagerLN.Exceptions.*;
import RacingManagerLN.Pilots.Pilot;

import java.time.LocalDate;
import java.util.List;
import java.util.Map;

public interface ISubSimulations {

	/**
	 * Adds a simulation to the existing simulations
	 * @param simulationName name of the simulation
	 * @param champ The championship that gave origin to this simulation
	 * @throws AlreadyExistingSimulationException if there is already a simulation with that name
	 */
	public void addSimulation(String simulationName, Championship champ) throws AlreadyExistingSimulationException;

	/**
	 * Adds a new record to the simulation
	 * @param simulationName the name of the simulation
	 * @param car the car of the participating user
	 * @param pilot the pilot chosen by the user
	 * @param username the username of the player
	 * @throws NonExistentSimulationException if there is no simulation with that name
	 */
	public void addRecord(String simulationName, Car car, Pilot pilot, String username) throws NonExistentSimulationException;

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

	/**
	 * Starts the simulation of the next race for a given championship
	 * @param simulationName name of the simulation championship
	 * @throws NonExistentSimulationException if there is no simulation with that name
	 * @return the starting grid or null if the simulation of the championship is over
	 */
	public List<List<String>> startSimulation(String simulationName) throws NonExistentSimulationException;

	/**
	 * Updates simulation info after a race is simulated
	 * @param simulationName the name of the simulation
	 * @return a map with the scores of the players in the simulation
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 */
	public Map<String, Integer> finishSimulation(String simulationName) throws NonExistentSimulationException;

	/**
     * Get the starting grid from a particular simulation
     *
     * @param simulationName the name of the simulated championship
     * @return the string containing the grid
     * @throws NonExistentSimulationException if there are no simulations with that name
     */
	public List<List<String>> showGrid(String simulationName, boolean premium) throws NonExistentSimulationException;

	/**
	 * Get the weather of the next race of a given simulation
	 * @param simulationName name of the simulation
	 * @return a string with the weather
	 * @throws NonExistentSimulationException if there is no simulation with that name
	 */
	public String getWeather(String simulationName) throws NonExistentSimulationException;

	// TODO
	public void setTiresType(String simulationName, String userName, int tiresType) throws NonExistentSimulationException, NonExistentRecordException;

	/**
	 * Gets the string representation of all the simulations stored in the database
	 * @return string with all the simulations data
	 */
	public List<List<String>> showSimulations();

	public List<List<String>> getChampionshipClassification(String simulationName) throws NonExistentSimulationException;

	public List<List<String>> getGlobalClassification(LocalDate fromDate, LocalDate toDate);

	/**
	 * Gets the current classification of a given simulation for a given category
	 * @param simulationName name of the simulation
	 * @param category category we want
	 * @return a string with the classification
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 */
	public List<List<String>> getCategoryClassification(String simulationName, String category) throws NonExistentSimulationException;

	/**
	 * Simulates the next lap in a simulation
	 * @param simulationName the name of the simulation
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 * @return true se já chegou ao fim da corrida, false se há mais voltas
	 */
	public boolean simulateNextLap(String simulationName) throws NonExistentSimulationException;

	/**
	 * Simulates the next lap in a simulation
	 * @param simulationName the name of the simulation
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 * @return true se já chegou ao fim da corrida, false se há mais voltas
	 */
	public boolean simulateNextLapPremium(String simulationName) throws NonExistentSimulationException;
}