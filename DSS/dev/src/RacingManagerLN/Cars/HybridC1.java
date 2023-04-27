package RacingManagerLN.Cars;

public class HybridC1 extends C1 implements Hybrid {
	private int electricPower;

	public HybridC1(int carId, String brand, String model, int HP, int engineCapacity,
					float reliability, float pac, TireType type, EngineMode mode, float tireState, int electricPower) {
		super(carId, brand, model, HP, engineCapacity, reliability, pac, type, mode, tireState);
		this.electricPower = electricPower;
	}

	public int getPower() {
		return this.getHorsePower() + this.electricPower;
	}

	@Override
	public int getEletricPower() {
		return this.electricPower;
	}
}