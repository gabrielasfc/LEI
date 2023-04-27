package RacingManagerLN.Cars;

public class HybridC2 extends C2 implements Hybrid {
	private int electricPower;

	public HybridC2(int carId, String brand, String model, int HP, int engineCapacity,
					float reliability, float pac, TireType type, EngineMode mode, float tireState, int electricPower) {
		super(carId, brand, model, HP, engineCapacity, reliability, pac, type, mode, tireState);
		this.electricPower = electricPower;
	}

	public int getPower() {
		return this.electricPower  + this.getHorsePower();
	}

	@Override
	public int getEletricPower() {
		return this.electricPower;
	}
}