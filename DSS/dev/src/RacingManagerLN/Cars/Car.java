package RacingManagerLN.Cars;

import RacingManagerLN.Exceptions.InvalidDownforceException;

public abstract class Car {
	private int carId;
	private String brand;
	private String model;
	private float pac;
	private int horsePower;
	private int engineCapacity;
	private float reliability;
	private TireType tireType;
	private EngineMode engineMode;
	private float tireState;

	public Car(int carId, String brand, String model, int HP, int engineCapacity, float reliability, float pac, TireType tT, EngineMode eM, float tireState) {
		this.carId = carId;
		this.brand = brand;
		this.model = model;
		this.horsePower = HP;
		this.engineCapacity = engineCapacity;
		this.reliability = reliability;
		this.pac = pac;
		this.tireType = tT;
		this.engineMode = eM;
		this.tireState = tireState;
	}

	public Car(int carId, String brand, String model, int HP, int engineCapacity, float pac){
		this.carId = carId;
		this.brand = brand;
		this.model = model;
		this.horsePower = HP;
		this.engineCapacity = engineCapacity;
		this.pac = pac;
	}

	public int getCarId() {
		return this.carId;
	}

	public String getBrand() {
		return this.brand;
	}

	public String getModel() {
		return this.model;
	}

	public int getHorsePower() {
		return this.horsePower;
	}

	public int getEngineCapacity() {
		return this.engineCapacity;
	}

	public float getReliability() {
		return this.reliability;
	}

	public float getPac() {
		return this.pac;
	}

	public TireType getTireType() {
		return this.tireType;
	}

	public EngineMode getEngineMode() {
		return this.engineMode;
	}

	public float getTireState() {
		return this.tireState;
	}

	public void setCarId(int carId) {
		this.carId = carId;
	}

	public void setBrand(String brand) {
		this.brand = brand;
	}

	public void setModel(String model) {
		this.model = model;
	}

	public void setHorsePower(int horsePower) {
		this.horsePower = horsePower;
	}

	public void setEngineCapacity(int engineCapacity) {
		this.engineCapacity = engineCapacity;
	}

	public void setReliability(float reliability) {
		this.reliability = reliability;
	}

	public void setPac(float pac) throws InvalidDownforceException {
		if (Car.validatePAC(pac)){
			this.pac = pac;
		}
		else throw new InvalidDownforceException("O PAC " + pac + " não é válido!");
	}

	public void setTireType(RacingManagerLN.Cars.TireType tireType) {
		this.tireType = tireType;
	}

	public void setEngineMode(EngineMode engineMode) {
		this.engineMode = engineMode;
	}

	public void setTireState(float tireState) {
		this.tireState = tireState;
	}

	public static boolean validatePAC(float value) {
		return value >= 0 && value <= 1;
	}

	public abstract int getPower();
}