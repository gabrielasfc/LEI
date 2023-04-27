package RacingManagerLN.Cars;

import RacingManagerLN.Exceptions.InvalidEngineCapacityException;
import RacingManagerLN.Exceptions.InvalidPacException;
import RacingManagerLN.Exceptions.InvalidReliabilityException;

import java.util.List;

public interface ISubCars {
	public void addC1(String brand, String model, int hp, int engineCapacity, float reliability, float pac, int eletricPower) throws InvalidReliabilityException, InvalidPacException;

	public void addC2(String brand, String model, int hp, int engineCapacity, float pac, int electricPower) throws InvalidPacException, InvalidEngineCapacityException;

	public void addSC(String brand, String model, int hp, float pac) throws InvalidPacException;

	public void addGT(String brand, String model, int hp, int engineCapacity, float pac, int electricPower) throws InvalidPacException, InvalidEngineCapacityException;

	public Car getCar(int carId);

	public List<List<String>> showAllCars();

	public String showCategories();
}