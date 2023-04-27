package RacingManagerLN.Cars;

public class GT extends Car {

	public GT(int carId, String brand, String model, int HP, int engineCapacity,
			  float reliability, float pac, TireType type, EngineMode mode, float tireState) {
		super(carId, brand, model, HP, engineCapacity, reliability, pac, type, mode, tireState);
	}

	public static boolean validateEngineCapacity(int eCap) {
		if (eCap >= 2000 && eCap <= 4000) return true;
		return false;
	}

	public float getReliability(int numLaps) {
		float reliability = 0.5f;
		reliability -= 0.01 * numLaps;
		reliability += 0.1 - this.getEngineCapacity()/100000;
		return reliability;
	}

	public int getPower() {
		return super.getHorsePower();
	}

}