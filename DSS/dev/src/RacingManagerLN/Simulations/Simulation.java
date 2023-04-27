package RacingManagerLN.Simulations;

import java.time.LocalDate;
import java.util.*;

import RacingManagerLN.Cars.Car;
import RacingManagerLN.Cars.TireType;
import RacingManagerLN.Circuits.Circuit;
import RacingManagerLN.Exceptions.InvalidDownforceException;
import RacingManagerLN.Exceptions.NoAdjustementsLeftException;
import RacingManagerLN.Exceptions.NonExistentRecordException;
import RacingManagerLN.Exceptions.NonExistentSimulationException;
import RacingManagerLN.Pilots.Pilot;


public class Simulation {
	private String name;
	private LocalDate initialDate;
	private LocalDate endDate;
	private int maxPlayers;
	private int currentRace;
	private List<Race> races;
	private String championshipName;
	private Map<String, Record> records;

	public Map<String, Record> getRecords() {
		return records; // Clone?? // Can be a list
	}


	public Simulation(String name, int maxPlayers, String champName, List<Circuit> circuits) {
		this.name = name;
		this.maxPlayers = maxPlayers;
		this.initialDate = LocalDate.now();
		this.currentRace = 0;
		this.championshipName = champName;
		this.races = new ArrayList<>();
		this.records = new HashMap<>();

		if (circuits != null){
			Iterator<Circuit> it = circuits.iterator();
			int i = 0;
			while (it.hasNext()){
				Circuit circuit = it.next();
				this.races.add(i, new Race(circuit));
				i++;
			}
		}
	}

	public Simulation(String name, int maxPlayers, LocalDate initialDate,
					  String champName, List<Circuit> circuits, List<Record> records, int currentRace) {
		this.name = name;
		this.maxPlayers = maxPlayers;
		this.initialDate = initialDate;
		this.currentRace = 0;
		this.championshipName = champName;
		this.races = new ArrayList<>();
		this.records = new HashMap<>();
		this.currentRace = currentRace;

		if (circuits != null){
			Iterator<Circuit> it = circuits.iterator();
			int i = 0;
			while (it.hasNext()){
				Circuit circuit = it.next();
				this.races.add(i, new Race(circuit));
				i++;
			}
		}

		if (records != null){
			for(Record record : records){
				this.records.put(record.getUserName(), record);
			}
		}

	}

	public Simulation(String name, int maxPlayers, LocalDate initialDate, LocalDate endDate,
					  String champName, List<Circuit> circuits, List<Record> records, int currentRace) {
		this.name = name;
		this.maxPlayers = maxPlayers;
		this.initialDate = initialDate;
		this.endDate = endDate;
		this.championshipName = champName;
		this.races = new ArrayList<>();
		this.records = new HashMap<>();
		this.currentRace = currentRace;

		if (circuits != null){
			Iterator<Circuit> it = circuits.iterator();
			int i = 0;
			while (it.hasNext()){
				Circuit circuit = it.next();
				this.races.add(i, new Race(circuit));
				i++;
			}
		}

		if (records != null){
			for(Record record : records){
				this.records.put(record.getUserName(), record);
			}
		}

	}

	/**
	 * Returns the classification of a simulation, sorted by score
	 * @return the classification of the simulation
	 */
	public List<List<String>> getClassification(){
		List<List<String>> classification = new ArrayList<>();

		for(Record r: this.records.values()){
			List<String> record = new ArrayList<>();
			record.add(0, r.getUserName());
			record.add(1, Integer.toString(r.getScore()));
			classification.add(record);
		}

		return classification;
	}

	/**
	 * Gets the current classification of the current simulation for a given category
	 * @param category category we want
	 * @return a string with the classification
	 * @throws NonExistentSimulationException if there are no simulations with that name
	 */
	public List<List<String>> getCategoryClassification(String category) {
		Set<Record> categoryRecords = new TreeSet<>((Record r1, Record r2) -> Integer.compare(r1.getScore(), r2.getScore()));

		List<List<String>> classification = new ArrayList<>();

		for(Record r: this.records.values()){
			if (r.getCar().getClass().getName().equals(category)){
				categoryRecords.add(r);
			}
		}

		return this.showClassification(categoryRecords);
	}

	/**
	 * Returns the weather generated for the next race
	 * @return a string with the weather
	 */
	public String getWeather() {
		Race currRace = this.races.get(this.currentRace);
		return currRace.showWeather();
	}

	/**
	 * Update a player car in a simulation
	 * @param userName the username of the player
	 * @param valueDownforce the new value of the downforce
	 * @param engineMode the new engine mode
	 * @throws InvalidDownforceException if downforce value is not correct
	 * @throws NonExistentRecordException if player is not found in records collection
	 * @throws NoAdjustementsLeftException if player has got no more adjustements left
	 */
	public void addAdjustment(String userName, float valueDownforce, int engineMode) throws InvalidDownforceException, NonExistentRecordException, NoAdjustementsLeftException {
		Record r = this.records.get(userName);

		if (r != null){
			r.configCar(valueDownforce, engineMode);
		}
		else throw new NonExistentRecordException("O record relativo ao user " + userName + " na simulação " + this.name + " não existe!");
	}

	/**
	 * Starts the simulation of the next circuit setting the positions of the players
	 * @return the grid containing the player positions
	 */
	public List<List<String>> startSimulation() {
		List<Record> orderedRecords = this.orderRecordsRandomly();
		Race currentRace = this.races.get(this.currentRace);

		for(Record r: orderedRecords){
			currentRace.setPosition(r);
		}

		return currentRace.showGrid(false);
	}

	/**
	 * Updates simulation info after a race is simulated
	 * Increments race number
	 * If last race was simulated, returns the scores of the players in the simulation
	 * Also updates endDate of simulation
	 * @return a map with the scores of the players in the simulation
	 */
	public Map<String, Integer> finishSimulation(){
		this.races.get(currentRace).updateScores();
		currentRace++;

		Map<String, Integer> map = null;
		if (currentRace == races.size()){
			this.endDate = LocalDate.now();
			map = getScoresByUsername();
		}

		return map;
	}

	/**
	 * Adds a new record to the collecction of records
	 * @param car car chosen
	 * @param pilot pilot chosen
	 * @param username user playing
	 */
	public void addRecord(Car car, Pilot pilot, String username) {
		Record newRecord = new Record(car, pilot, username, (2*this.races.size())/3, 0); // initialAdjustements = 2/3 * numRaces
		this.records.put(username, newRecord);
	}

	/**
	 * Update the tires of the car of a player in the current simulation
	 * @param userName the name of the player
	 * @param tiresType the type of the tires
	 */
	public void setTiresType(String userName, int tiresType) throws NonExistentRecordException {
		Record r = this.records.get(userName);

		if (r != null){
			r.setTiresType(tiresType);
		}
		else throw new NonExistentRecordException("Record relative to name " + userName + " in simulation " + this.name + " doesn't exist!");
	}

	/**
	 * Get the starting grid from this simulation
	 * @return the string containing the grid
	 */
	public List<List<String>> showGrid(boolean premium) {
		return this.races.get(this.currentRace).showGrid(premium);
	}

	/**
	 * Updates scores map with the scores of the players in this simulation if it occured between fromDate and toDate
	 * @param scores a map of the user scores
	 * @param fromDate the start of the period to consider
	 * @param toDate the end of the period to consider
	 */
	public void gatherRecords(Map<String, Integer> scores, LocalDate fromDate, LocalDate toDate) {
		if (this.endDate != null && fromDate.isBefore(this.initialDate) && toDate.isAfter(this.endDate)){
			for(Record r: this.records.values()){ // Adds all scores to map
				r.addRecordToMap(scores);
			}
		}
	}

	/**
	 * Simulates the next lap in a simulation
	 * @return true se já chegou ao fim da corrida, false se há mais voltas
	 */
	public boolean simulateNextLap() {
		Race nextRace = this.races.get(currentRace);
		boolean isFinalLap = nextRace.simulateLap();
		//this.currentRace++; // Increment race number
		return isFinalLap;
	}

	public boolean simulateNextLapPremium(){
		Race nextRace = this.races.get(currentRace);
		boolean isFinalLap = nextRace.simulateLapPremium();

		return isFinalLap;
	}

	/**
	 * Gets a random list of records of a simulation
	 * @return the list randomized
	 */
	private List<Record> orderRecordsRandomly() {
		List<Record> randomizedList = new ArrayList<>();

		for (Record r: this.records.values()){
			randomizedList.add(r);
		}

		return randomizedList;
	}

	private List<List<String>> showClassification(Set<Record> records) {
		List<List<String>> classification = new ArrayList<>();

		for (Record r : records){
			List<String> data = new ArrayList<>();

			data.add(r.getUserName());
			data.add(r.getCar().getBrand());
			data.add(r.getCar().getModel());
			data.add(r.getPilot().getName());
			data.add(Integer.toString(r.getScore()));

			classification.add(data);
		}

		return classification;
	}

	private Record getRecord(String userName) {
		throw new UnsupportedOperationException();
	}

	/**
	 * Gets a map with the scores of the users in this simulation
	 * @return the map with the scores of the users
	 */
	private Map<String, Integer> getScoresByUsername() {
		Map<String, Integer> map = new HashMap<>();
		for(String user: this.records.keySet()){
			int userScore = this.records.get(user).getScore();
			map.put(user, userScore);
		}

		return map;
	}

	/**
	 * Returns the string matching the simulation
	 * @return the string presenting the information
	 */
	public String toString(){
		return this.name + " , " + this.maxPlayers + " , " + this.initialDate.toString() + "\n";
	}

	public String getChampionshipName() {
		return championshipName;
	}

	public void setChampionshipName(String championshipName) {
		this.championshipName = championshipName;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public LocalDate getInitialDate() {
		return initialDate;
	}

	public void setInitialDate(LocalDate initialDate) {
		this.initialDate = initialDate;
	}

	public LocalDate getEndDate() {
		return endDate;
	}

	public void setEndDate(LocalDate endDate) {
		this.endDate = endDate;
	}

	public int getMaxPlayers() {
		return maxPlayers;
	}

	public void setMaxPlayers(int maxPlayers) {
		this.maxPlayers = maxPlayers;
	}

	public int getCurrentRace() {
		return currentRace;
	}

	public void setCurrentRace(int currentRace) {
		this.currentRace = currentRace;
	}

	public List<Race> getRaces() {
		return races;
	}
}