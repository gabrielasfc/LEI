package RacingManagerLN.Cars;

public class C1 extends Car {
	private static float range;

	public C1(int carId, String brand, String model, int HP, int engineCapacity,
			  float reliability, float pac, TireType type, EngineMode mode, float tireState) {
		super(carId, brand, model, HP, engineCapacity, reliability, pac, type, mode, tireState);
	}

	public static boolean validateReliabilty(float value) {
		if (value >= 0.90 && value <= 1) return true;
		return false;
	}

	public int getPower() {
		return this.getHorsePower();
	}
}