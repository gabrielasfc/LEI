package RacingManagerLN.Cars;

public class C2 extends Car {

	public C2(int carId, String brand, String model, int HP, int engineCapacity,
			  float reliability, float pac, TireType type, EngineMode mode, float tireState) {
		super(carId, brand, model, HP, engineCapacity, reliability, pac, type, mode, tireState);
	}

	public static boolean validateEngineCapacity(int eCap) {
		if (eCap >= 3000 && eCap <= 5000) return true;
		return false;
	}

	public int getPower() {
		return this.getHorsePower();
	}

}