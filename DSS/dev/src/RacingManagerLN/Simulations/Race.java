package RacingManagerLN.Simulations;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

import RacingManagerLN.Cars.Car;
import RacingManagerLN.Cars.EngineMode;

import RacingManagerLN.Cars.*;
import RacingManagerLN.Circuits.*;
import RacingManagerLN.Pilots.Pilot;

public class Race {
	public Weather weather;
	public List<Position> positions;
	public Circuit circuit;
	private int currentLap = 0;

	public Race(Circuit circuit) {
		this.positions = new ArrayList<>();
		this.circuit = circuit;
	}

	/**
	 * Add a new player to the race
	 * @param rec record of the player
	 */
	public void setPosition(Record rec) {
		this.positions.add(new Position(rec));
	}

	/**
	 * Return the current race weather
	 * @return the weather as a string
	 */
	public String showWeather(){
		if (this.weather == null){ // If weather is not setup, setup weather
			boolean isRainy = Race.simulateProbability(0.5f);
			if (isRainy == true){
				this.weather = Weather.RAINY;
			}
			else {
				this.weather = Weather.WET;
			}
		}
		if(this.weather == Weather.RAINY){ // return weather
			return "Rainy";
		}
		else if (this.weather == Weather.WET){
			return "Wet";
		}
		return "";
	}

	/**
	 * Updates the scores of the players in the records, after a race is simulated
	 * Points: last - 0
	 * 		   second-to-last - 1
	 * 		   third-to-last - 2
	 * 		   ...
	 */
	public void updateScores(){
		for(int i=0; i<positions.size(); i++){
			this.positions.get(i).getRecord().updateScore(i);
		}
	}

	/**
	 * Get the grid from this race
	 * @return a list containing the grid
	 */
	public List<List<String>> showGrid(boolean premium) {
		List<List<String>> grid = new ArrayList<>();
		int pos = this.positions.size();

		for (Position p : this.positions) {
			List<String> data = new ArrayList<>();

			Record record = p.getRecord();

			data.add(Integer.toString(pos));
			data.add(record.getUserName());
			data.add(record.getCar().getBrand());
			data.add(record.getCar().getModel());
			data.add(record.getPilot().getName());
			data.add(Integer.toString(record.getNumAdjAvailable()));
			data.add(Integer.toString(record.getScore()));
			data.add(Long.toString(p.getTime()));

			grid.add(data);
			pos--;
		}
		Collections.reverse(grid);
		return grid;
	}

	/**
	 * Simulates a lap in a race, updating all cars positions
	 * @return true if it's the last lap of the race, false if there are more laps
	 */
	public boolean simulateLap() {
		int i;

		for(i=0; i<positions.size(); i++){
			if(this.positions.get(i).isStillRunning()) {
				boolean b1 = this.isBrokenDownCar(i);
				if (b1 == true) {
					this.updateBrokenDownCar(i);
				}
			}
		}

		List<Sector> sectors = this.circuit.getSectors();

		for(Sector s: sectors){
			this.simulateSector(s);
		}

		this.currentLap++;

		if (this.currentLap == this.circuit.getNumLaps()){
			return true;
		}
		return false;
	}

	private long getLapTime(int position) {
		Car c = this.positions.get(position).getRecord().getCar();
		Pilot p = this.positions.get(position).getRecord().getPilot();
		Weather w = this.weather;

		long averageLapTime; // milliseconds
		if (w == Weather.RAINY) {
			averageLapTime = 3000 + (long) (p.getCts() * 1000);
			switch (c.getTireType()) {
				case SOFT -> averageLapTime += 2000;
				case HARD -> averageLapTime += 1000;
			}

		} else {
			averageLapTime = 1000 - (long) (1000 * p.getCts());

			switch (c.getTireType()) {
				case HARD -> averageLapTime += 1000;
				case RAIN -> averageLapTime += 2000;
			}
		}

		averageLapTime += p.getSva() * 1000;
		averageLapTime += c.getPac() * 1000;

		switch (c.getEngineMode()) {
			case CONSERVATIVE -> averageLapTime += 1000;
			case AGGRESSIVE -> averageLapTime -= 1000;
		}

		if (c instanceof C1) {
			averageLapTime += (long) (circuit.getLength() * 23550); // km * s/km = s monaco track
		} else if (c instanceof C2) {
			averageLapTime += (long) (circuit.getLength() * 24550);
		} else if (c instanceof GT) {
			averageLapTime += (long) (circuit.getLength() * 26550);
		} else if (c instanceof SC) {
			averageLapTime += (long) (circuit.getLength() * 27550);
		}

		averageLapTime += (c.getEngineCapacity()/c.getPower()) * 1000L;

		return averageLapTime;
	}

	// Maybe merge the two functions (premium and normal)
	public boolean simulateLapPremium(){
		for(int i=0; i<positions.size(); i++){
			if(this.positions.get(i).isStillRunning()) {
				boolean b1 = this.isBrokenDownCar(i);
				if (b1) {
					this.positions.get(i).setStillRunning(false);
					this.positions.get(i).setTime(1000000000000000L);
				} else {
					long lapTime = this.getLapTime(i);
					this.positions.get(i).addTime(lapTime);
				}
				this.positions.sort((x1,x2) -> Math.toIntExact((int) x2.getTime() - x1.getTime()));
			}
		}

		this.currentLap++;
		return this.currentLap == this.circuit.getNumLaps();
	}

	/**
	 * Simulates a sector in a lap of a race, updating all cars positions
	 * @param s the sector to simulate
	 */
	private void simulateSector(Sector s) {
		int i=0, ln=positions.size();

		while (i<ln){
			boolean outOfTrack = hasCarLeftTrack(i, s);
			if (outOfTrack == true){
				updateLeftTrackCar(i);
			}
			else{
				if (i < ln-1) { // It's only possible to overtake next car if it's not the first already
					boolean b = canOvertakeNextCar(i, s);

					if (b == true) {
						updateOvertakenNextCar(i);
						i++;
					}
				}
			}
			i++;
		}
	}

	/**
	 * Checks if a car breaks down when racing in a lap
	 * @param positionIndex position of the car
	 * @return true if it breaks down, false otherwise
	 */
	private boolean isBrokenDownCar(int positionIndex) {
		Position p = this.positions.get(positionIndex);
		Car playerCar = p.getRecord().getCar();
		float reliability = playerCar.getReliability();
		EngineMode em = playerCar.getEngineMode();

		float engineAddedProb=0;

		switch (em){
			case CONSERVATIVE -> engineAddedProb = +0.1f;
			case AGGRESSIVE -> engineAddedProb = -0.1f;
		}

		// total probability = reliability + engineAddedProb
		return Race.simulateProbability(1 - (reliability + engineAddedProb));
	}

	/**
	 * Updates car state in race when it breaks down
	 * post: player's car is broken down in this race
	 * @param positionIndex position of the car
	 */
	private void updateBrokenDownCar(int positionIndex) {
		positions.get(positionIndex).setStillRunning(false);
		Position p = positions.remove(positionIndex);
		positions.add(0, p);
	}

	/**
	 * Simulates if a car has left track in the current sector
	 * @param positionIndex position of the car
	 * @param s sector to simulate TODO (alterar no VPP)
	 * @return true if it left track or crashed, false otherwise
	 */
	private boolean hasCarLeftTrack(int positionIndex, Sector s) {
		Car c = this.positions.get(positionIndex).getRecord().getCar();
		Pilot p = this.positions.get(positionIndex).getRecord().getPilot();

		float riskFactor = 0;
		switch (s.getGdu()){
			case POSSIBLE -> {
				if (s instanceof Curve){
					riskFactor = 0.2f;
				}
				else if (s instanceof Chicane){
					riskFactor = 0.3f;
				}
				else if (s instanceof Straight){
					riskFactor = 0.1f;
				}
			}
			case HARD -> {
				if (s instanceof Curve){
					riskFactor = 0.4f;
				}
				else if (s instanceof Chicane){
					riskFactor = 0.5f;
				}
				else if (s instanceof Straight){
					riskFactor = 0.3f;
				}
			}
			case IMPOSSIBLE -> {
				if (s instanceof Curve){
					riskFactor = 0.6f;
				}
				else if (s instanceof Chicane){
					riskFactor = 0.7f;
				}
				else if (s instanceof Straight){
					riskFactor = 0.5f;
				}
			}
		}
		if (this.weather == Weather.RAINY) {
			riskFactor += p.getCts() * 0.1;

			switch (c.getTireType()) {
				case HARD -> riskFactor += 0.05;
				case SOFT -> riskFactor += 0.1;
			}

		} else {
			riskFactor += (1 - p.getCts()) * 0.1;
		}

		riskFactor += (1 - p.getSva()) * 0.1;

		return Race.simulateProbability(riskFactor);
	}

	/**
	 * When a car leaves track it will be overtaken by a car
	 * @param positionIndex position of the car before leaving track
	 */
	private void updateLeftTrackCar(int positionIndex) {
		if (positionIndex > 0 && this.positions.get(positionIndex-1).isStillRunning()){ // Swap between the two positions
			this.swapPositions(positionIndex-1, positionIndex);
		}
	}

	/**
	 * Simulates if a car in a certain position can overtake the car in the next position
	 * @param positionIndex position of the car
	 * @param s Sector being simulated
	 * @return true in case of success, false if he couldn't overtake the car he followed
	 */
	private boolean canOvertakeNextCar(int positionIndex, Sector s) {
		Car currentCar = this.positions.get(positionIndex).getRecord().getCar();
		Car nextCar = this.positions.get(positionIndex).getRecord().getCar();
		Pilot currentPilot = this.positions.get(positionIndex).getRecord().getPilot();
		Pilot nextPilot = this.positions.get(positionIndex).getRecord().getPilot();

		float categoriesFactor = Race.calculateCategoryFactor(currentCar, nextCar);
		float svasFactor = currentPilot.getSva() - nextPilot.getSva();
		float tireFactor = currentCar.getTireState()/100 - nextCar.getTireState()/100;
		float downforceFactor = Race.calculateDownforceFactor(currentCar.getPac(), s);
		float sectorFactor = Race.calculateSectorFactor(s);

		return Race.simulateProbability(0.25f + categoriesFactor + svasFactor + tireFactor + downforceFactor + sectorFactor);
	}

	private static float calculateSectorFactor(Sector s){
		switch (s.getGdu()){
			case POSSIBLE -> { return 0.1f; }
			case IMPOSSIBLE -> { return -0.15f; }
			case HARD -> { return -0.1f; }
		}
		return 0;
	}

	private static float calculateDownforceFactor(float pac, Sector s){
		float downforceFactor = 0;
		if (s instanceof Straight){
			if (pac < 0.5){
				downforceFactor = (0.5f - pac)/10;
			}
		} else if (s instanceof Curve){
			if (pac > 0.5){
				downforceFactor = (pac - 0.5f)/10;
			}
		}

		return downforceFactor;
	}

	private static float calculateCategoryFactor(Car current, Car next){
		float categoryFactor;

		if (current instanceof C1 || current instanceof HybridC1){
			if (next instanceof C1 || next instanceof HybridC1){
				categoryFactor = 0;
			} else if (next instanceof C2 || next instanceof HybridC2){
				categoryFactor = 0.05f;
			} else if (next instanceof GT || next instanceof HybridGT){
				categoryFactor = 0.10f;
			} else {
				categoryFactor = 0.15f;
			}
		} else if (current instanceof C2 || current instanceof HybridC2){
			if (next instanceof C1 || next instanceof HybridC1){
				categoryFactor = -0.5f;
			} else if (next instanceof C2 || next instanceof HybridC2){
				categoryFactor = 0;
			} else if (next instanceof GT || next instanceof HybridGT){
				categoryFactor = 0.05f;
			} else {
				categoryFactor = 0.10f;
			}
		} else if (current instanceof GT || current instanceof HybridGT){
			if (next instanceof C1 || next instanceof HybridC1){
				categoryFactor = -0.10f;
			} else if (next instanceof C2 || next instanceof HybridC2){
				categoryFactor = -0.05f;
			} else if (next instanceof GT || next instanceof HybridGT){
				categoryFactor = 0;
			} else {
				categoryFactor = 0.5f;
			}
		} else { // SC
			if (next instanceof C1 || next instanceof HybridC1){
				categoryFactor = -0.15f;
			} else if (next instanceof C2 || next instanceof HybridC2){
				categoryFactor = -0.10f;
			} else if (next instanceof GT || next instanceof HybridGT){
				categoryFactor = -0.05f;
			} else {
				categoryFactor = 0;
			}
		}
		return categoryFactor;
	}

	/**
	 * Updates a car position, assuming that it overtook the next car
	 * @param positionIndex the position before
	 */
	private void updateOvertakenNextCar(int positionIndex) {
		if (positionIndex < this.positions.size()){ // If it is not the first of the race
			this.swapPositions(positionIndex, positionIndex+1);
		}
	}

	/**
	 * Swapp the positions of two cars
	 * @param index1 the index of the first position
	 * @param index2 the index of the second position
	 */
	private void swapPositions(int index1, int index2){
		Position p1 = this.positions.remove(index1);
		Position p2  = this.positions.remove(index1);
		this.positions.add(index1, p2);
		this.positions.add(index2, p1);
	}

	/**
	 * Simulates a random event, given the probability of it hapenning
	 * @param probability the probability of the event happening
	 * @return true, if it happened, false, otherwise
	 * For example: the probability of a car breaking down
	 * If it is 50%, we generate a random number between 0 and 1,
	 * if it is less than 0.5, we return true, if it greater than 0.5, we return false
	 */
	private static boolean simulateProbability(float probability){
		if (probability >= 0 && probability <= 1) {
			Random r = new Random();
			float generatedNumber = r.nextFloat();
			if (generatedNumber < probability) { // Simulate that event happened
				return true;
			} else return false; // Simulate event didn't happen
		} else {
			return false;
		}

	}
}