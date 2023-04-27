package RacingManagerUI;

import RacingManagerLN.Exceptions.*;
import RacingManagerLN.IRacingManagerLN;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.List;

public class Controller {
    private IRacingManagerLN facade;
    private String simulation;
    public Controller(IRacingManagerLN facade){
        this.facade = facade;
    }

    public List<List<String>> startSimulation(String simulation) throws NonExistentSimulationException {
        this.simulation = simulation;
        return this.facade.startSimulation(simulation);
    }

    public String getWeather() throws NonExistentSimulationException {
        return this.facade.getWeather(simulation);
    }

    public void addAdjustment(String username, float valueDownforce, int engineMode) throws NoAdjustementsLeftException, NonExistentRecordException, InvalidDownforceException, NonExistentSimulationException {
        this.facade.addAdjustment(simulation, username, valueDownforce, engineMode);
    }

    public void setTiresType(String username, int type) throws NonExistentRecordException, NonExistentSimulationException {
        this.facade.setTiresType(simulation, username, type);
    }
    public boolean simulateLap() throws NonExistentSimulationException {
        boolean b = this.facade.simulateNextLap(simulation);
        return b;
    }
    public boolean finishSimulation() throws NonExistentSimulationException {
        return this.facade.finishSimulation(simulation);
    }

    public List<List<String>> showGrid() throws NonExistentSimulationException {
        return this.facade.showGrid(simulation, false);
    }

    public List<List<String>> getChampionshipClassification() throws NonExistentSimulationException{
        return this.facade.getChampionshipClassification(this.simulation);
    }

    public List<List<String>> showAllPilots(){
        return this.facade.showAllPilots();
    }

    public List<List<String>> showAllCars(){
        return this.facade.showAllCars();
    }

    public List<List<String>> showSimulations(){
        return this.facade.showSimulations();
    }

    public List<List<String>> showChampionships(){
        return this.facade.showChampionships();
    }

    public void addRecord(String simulationName, int carID, String pilotName, String username) throws NonExistentCarException, NonExistentSimulationException, NonExistentPilotException, NonExistentUsernameException {
        this.facade.addRecord(simulationName, carID, pilotName, username);
    }

    public void addSimulation(String simulation, String championship) throws NonExistentChampionshipException, AlreadyExistingSimulationException {
        this.facade.addSimulation(simulation, championship);
    }

    public void loginUser(String username, String password) throws NonExistentUsernameException {
        this.facade.loginUser(username, password);
    }

    public void addPlayer(String username, String password, String country) throws NonExistentUsernameException {
        this.facade.addPlayer(username, password, country);
    }

    public List<List<String>> getGlobalClassification(){
        return this.facade.getGlobalClassification();
    }

    public List<List<String>> getGlobalClassification(String country){
        return this.facade.getGlobalClassification(country);
    }

    public List<List<String>> getGlobalClassification(String initialDate, String finalDate){
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        LocalDate dataInicial = LocalDate.parse(initialDate, formatter);
        LocalDate dataFinal = LocalDate.parse(finalDate, formatter);
        return this.facade.getGlobalClassification(dataInicial,dataFinal);
    }

    public void addPilot(String name) throws AlreadyExistingPilotException, InvalidCtsException, InvalidSvaException {
        this.facade.addPilot(name);
    }

    public void addPilot(String name, Float cts, Float sva) throws AlreadyExistingPilotException, InvalidCtsException, InvalidSvaException {
        this.facade.addPilot(name, cts, sva);
    }

    public void addC1(String brand, String model, int power, float reliability, float pac, int electricPower) throws InvalidReliabilityException, InvalidPacException {
        this.facade.addC1(brand, model, power, 6000, reliability, pac, electricPower);
    }

    public void addC2(String brand, String model, int hp, int engineCapacity, float pac, int electricPower) throws InvalidPacException, InvalidEngineCapacityException {
        this.facade.addC2(brand, model, hp, engineCapacity, pac, electricPower);
    }

    public void addSC(String brand, String model, int hp, float pac) throws InvalidPacException {
        this.facade.addSC(brand, model, hp, pac);
    }

    public void addGT(String brand, String model, int hp, int engineCapacity, float pac, int electricPower) throws InvalidPacException, InvalidEngineCapacityException {
        this.facade.addGT(brand, model, hp, engineCapacity, pac, electricPower);
    }

    public List<List<String>> showAllCircuits(){
        return this.facade.showAllCircuits();
    }

    public void addChampionship(String champName, List<String> circuits, int maxPlayers) throws AlreadyExistingChampionshipException {
        this.facade.addChampionship(champName, circuits, maxPlayers);
    }

    public List<String> generateCircuits(int numCircuits){
        return this.facade.generateCircuits(numCircuits);
    }

    public void addCircuit(String name, float length, int numLaps, int numCurves, int numChicanes) throws AlreadyExistingCircuitException {
        this.facade.addCircuit(name, length, numLaps, numCurves, numChicanes);
    }

    public List<String> showCircuitSectors(String circuit){
        return this.facade.showCircuitSectors(circuit);
    }

    public void addSector(String circuitName, int gdu, int sectorType){
        this.facade.addSector(circuitName, gdu, sectorType);
    }
}
