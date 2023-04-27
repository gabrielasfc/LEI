package RacingManagerLN.Simulations;

import RacingManagerLN.Cars.Car;
import RacingManagerLN.Exceptions.InvalidDownforceException;
import RacingManagerLN.Exceptions.NoAdjustementsLeftException;
import RacingManagerLN.Pilots.Pilot;
import java.util.Map;

import static RacingManagerLN.Cars.EngineMode.*;
import static RacingManagerLN.Cars.TireType.*;

public class Record {
	private Car car;
	private Pilot pilot;
	private String userName;
	private int numAdjAvailable;
	private int score;

	public Record(Car car, Pilot pilot, String userName, int initialAdj, int score) {
		this.car = car;
		this.pilot = pilot;
		this.userName = userName;
		this.numAdjAvailable = initialAdj;
		this.score = score;
	}

	public Car getCar() {
		return car; // Falta composição?
	}

	public Pilot getPilot(){
		return pilot; // Falta composição?
	}

	public String getUserName(){
		return this.userName;
	}

	public int getNumAdjAvailable() {
		return numAdjAvailable;
	}

	public int getScore() {
		return score;
	}

	public void setUserName(String userName) {
		this.userName = userName;
	}

	/**
	 * Returns the string matching a given record
	 * @return the string presenting the information
	 */
	@Override
	public String toString(){
		return this.userName + " , " + this.score + " , " + this.numAdjAvailable + " , " + "\n";
	}

	/**
	 * Set the type of tires of the car in this record
	 * @param tiresType the type of tires (0-HARD, 1-SOFT, 2-RAIN)
	 */
	public void setTiresType(int tiresType) {
		if (tiresType == 0) this.car.setTireType(HARD);
		else if (tiresType == 1) this.car.setTireType(SOFT);
		else if (tiresType == 2) this.car.setTireType(RAIN);
	}

	/**
	 * Increments the number of points of a given player
	 * @param points the number of points to increment
	 */
	public void updateScore(int points) {
		this.score += points;
	}

	/**
	 * Update car attributes (engineMode), decrementing available configurations for that player
	 * @param engineMode new engineMode
	 * @throws InvalidDownforceException if downforce value is not correct
	 * @throws NoAdjustementsLeftException if player has got no more adjustements left
	 */
	public void configCar(int engineMode) throws NoAdjustementsLeftException {
		this.numAdjAvailable--;
		if (engineMode == 0) this.car.setEngineMode(NORMAL);
		else if (engineMode == 1) this.car.setEngineMode(AGGRESSIVE);
		else if (engineMode == 2) this.car.setEngineMode(CONSERVATIVE);
	}

	/**
	 * Update car attributes (downforce and engineMode), decrementing available configurations for that player
	 * @param valueDownforce new downforce
	 * @param engineMode new engineMode
	 * @throws InvalidDownforceException if downforce value is not correct
	 * @throws NoAdjustementsLeftException if player has got no more adjustements left
	 */
	public void configCar(float valueDownforce, int engineMode) throws InvalidDownforceException, NoAdjustementsLeftException {
		if (this.numAdjAvailable == 0) throw new NoAdjustementsLeftException("Não há mais adjustments disponíveis!");
		this.numAdjAvailable--;
		this.car.setPac(valueDownforce);
		if (engineMode == 0) this.car.setEngineMode(NORMAL);
		else if (engineMode == 1) this.car.setEngineMode(AGGRESSIVE);
		else if (engineMode == 2) this.car.setEngineMode(CONSERVATIVE);
	}

	/**
	 * Adds the score of the user to the map of scores
	 * @param scores the map of scores to update
	 */
	public void addRecordToMap(Map<String, Integer> scores) {
		int score=0;
		if (scores.containsKey(this.getUserName())){
			score = scores.get(this.getUserName());
		}
		score += this.score;
		scores.put(this.getUserName(), score);
	}

}