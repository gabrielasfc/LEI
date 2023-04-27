package RacingManagerLN.Cars;

import RacingManagerDL.CarDAO;
import RacingManagerLN.Exceptions.InvalidEngineCapacityException;
import RacingManagerLN.Exceptions.InvalidPacException;
import RacingManagerLN.Exceptions.InvalidReliabilityException;

import java.util.ArrayList;
import java.util.List;

public class CarsFacade implements ISubCars {
	private CarDAO cars;

	public CarsFacade(){
		this.cars = CarDAO.getInstance();
	}

	public void addC1(String brand, String model, int hp, int engineCapacity, float reliability, float pac, int eletricPower) throws InvalidReliabilityException,InvalidPacException {
		Car c;
		if (!C1.validateReliabilty(reliability)) throw new InvalidReliabilityException("Invalid reliability, C1 car reliability is arround 95%.");
		if (pac>1 || pac<0) throw new InvalidPacException("Invalid pac, pac is between 0 and 1.");

		if (eletricPower>0) {
			c = new HybridC1(-1,brand,model,hp,engineCapacity,reliability,pac,TireType.SOFT,EngineMode.NORMAL,100,eletricPower);
		} else {
			c = new C1(-1,brand,model,hp,engineCapacity,reliability,pac,TireType.SOFT,EngineMode.NORMAL,100);
		}
		this.cars.put(c.getCarId(),c);
	}

	public void addC2(String brand, String model, int hp, int engineCapacity, float pac, int electricPower) throws InvalidPacException, InvalidEngineCapacityException {
		Car c;
		if (pac>1 || pac<0) throw new InvalidPacException("PAC inválido, o valor deve estar entre 0 e 1.");
		if (!C2.validateEngineCapacity(engineCapacity)) throw new InvalidEngineCapacityException("Cilindrada inválida, a cilindrada de um C2 deve estar entre 3000 e 5000.");

		if (electricPower>0) {
			c = new HybridC2(-1,brand,model,hp,engineCapacity, (float) (0.75 + engineCapacity * 0.1),pac,TireType.SOFT,EngineMode.NORMAL,100,electricPower);
		} else {
			c = new C2(-1,brand,model,hp,engineCapacity,(float) (0.75 + engineCapacity * 0.1),pac,TireType.SOFT,EngineMode.NORMAL,100);
		}
		this.cars.put(c.getCarId(),c);
	}

	public void addSC(String brand, String model, int hp, float pac) throws InvalidPacException {
		if (pac>1 || pac<0) throw new InvalidPacException("PAC inválido, o valor deve estar entre 0 e 1.");
		Car c = new SC(-1,brand,model,hp, 1 - (float) ((0.75*2500)/10000),pac,TireType.SOFT,EngineMode.NORMAL,100);
		this.cars.put(c.getCarId(),c);
	}

	public void addGT(String brand, String model, int hp, int engineCapacity, float pac, int electricPower) throws InvalidPacException, InvalidEngineCapacityException{
		if (pac>1 || pac<0) throw new InvalidPacException("PAC inválido, o valor deve estar entre 0 e 1.");
		if (!GT.validateEngineCapacity(engineCapacity)) throw new InvalidEngineCapacityException("Cilindrada inválida, a cilindrada de um C2 deve estar entre 3000 e 5000.");
		Car c;

		if (electricPower>0) {
			c = new HybridGT(-1,brand,model,hp,engineCapacity, 1 - engineCapacity/10000f,pac,TireType.SOFT,EngineMode.NORMAL,100,electricPower);
		} else {
			c = new GT(-1,brand,model,hp,engineCapacity, 1 - engineCapacity/10000f,pac,TireType.SOFT,EngineMode.NORMAL,100);
		}
		this.cars.put(c.getCarId(),c);
	}

	public Car getCar(int carId) {
		return cars.get(carId);
	}

	public List<List<String>> showAllCars() {
		List<List<String>> cars = new ArrayList<>();

		for(Car car : this.cars.values()){
			List<String> data = new ArrayList<>();

			data.add(Integer.toString(car.getCarId()));
			data.add(car.getBrand());
			data.add(car.getModel());
			data.add(Integer.toString(car.getPower()));
			data.add(Integer.toString(car.getEngineCapacity()));
			data.add(Float.toString(car.getPac()));

			if (car instanceof HybridC1 || car instanceof HybridC2 || car instanceof HybridGT){
				data.add(Integer.toString(((Hybrid) car).getEletricPower()));
			}

			cars.add(data);
		}

		return cars;
	}

	public String showCategories() {
		throw new UnsupportedOperationException();
	}
}