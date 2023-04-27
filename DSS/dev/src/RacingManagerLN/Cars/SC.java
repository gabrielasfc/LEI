package RacingManagerLN.Cars;

public class SC extends Car {

	public SC(int carId, String brand, String model, int HP,
			  float reliability, float pac, TireType type, EngineMode mode, float tireState) {
		super(carId, brand, model, HP, 2500, reliability, pac, type, mode, tireState);
	}

	public float getReliability(float sva, float cts) {
		float reliability = 0.75f*(1-sva) + 0.25f*this.getEngineCapacity()/10000;
		return reliability;
	}

	public int getPower() {
		return super.getHorsePower();
	}
}