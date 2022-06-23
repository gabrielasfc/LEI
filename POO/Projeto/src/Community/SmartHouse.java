package src.Community;

import src.Bill.Bill;
import src.Bill.DateInterval;
import src.Change.*;
import src.Changeable;
import src.Exceptions.NonExistantBillException;
import src.SmartDevices.SmartDevice;

import java.io.Serializable;
import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;
import java.util.*;
import java.util.function.Consumer;
import java.util.function.Predicate;


/**
 * A SmartHouse faz a gestão dos SmartDevices que existem e dos 
 * espaços (as salas) que existem na casa.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class SmartHouse implements Comparable<SmartHouse>, Serializable, Changeable {
    private int id;
    private String address;
    private String ownerName;
    private int ownerNif;
    private String providerName;
    private double currentConsumption; // Consumo atual de todos os dispositivos somados
    private double totalKwh; // Total kwh acumulados desde a última fatura
    private double accumCost; // Custo acumulado dos preços de instalação
    private Map<String, Set<Integer>> locations;
    private Map<Integer, SmartDevice> devices;
    private Set<Bill> bills;
    private List<Change> changes;
    private LocalDateTime lastBill;
    private LocalDateTime lastChange;

    private static int idCount = 1;

    /**
     * Default constructor
     */
    public SmartHouse() {
        this.id = SmartHouse.idCount++;
        this.address = "";
        this.ownerName = "";
        this.providerName = "";
        this.ownerNif = 0;
        this.locations = new HashMap<>();
        this.devices = new HashMap<>();
        this.bills = new TreeSet<>();
        this.changes = new ArrayList<>();
        this.currentConsumption = 0;
        this.totalKwh = 0;
        this.accumCost = 0;
    }

    /**
     * Complete constructor
     * @param a house address
     * @param o owner name
     * @param nif owner nif
     * @param locations map with the devices at each location of the house
     * @param devices map with the devices of that house
     * @param providerName Nome do fornecedor
     * @param bills List with the bills associated with that house
     * @param c List with the current changes in provider
     * @param currentConsumption Consumption of that house, in that state, in KW
     */
    public SmartHouse(String a, String o, int nif, Map<String, Set<Integer>> locations, Map<Integer, SmartDevice> devices, String providerName, List<Bill> bills, Map<Integer, List<Change>> c, double currentConsumption, double totalKwh, double accumCost) {
        this.id = SmartHouse.idCount++;
        this.address = a;
        this.ownerName = o;
        this.ownerNif = nif;
        this.providerName = providerName;

        this.locations = new HashMap<>();
        Set<Map.Entry<String, Set<Integer>>> entries = locations.entrySet();

        for(Map.Entry<String, Set<Integer>> entry : entries) {
            Set<Integer> deviceIds = new HashSet<>();
            for(Integer i: entry.getValue()){
                deviceIds.add(i);
            }
            locations.put(entry.getKey(), deviceIds);
        }

        this.devices = new HashMap<>();

        for(SmartDevice d: devices.values()){
            this.devices.put(d.getId(), d.clone());
        }

        this.bills = new TreeSet<>();

        for(Bill bill: bills){
            this.bills.add(bill.clone());
        }

        this.changes = new ArrayList<>();
        this.currentConsumption = currentConsumption;
        this.totalKwh = totalKwh;
        this.accumCost = accumCost;
    }

    /**
     * Constructor without data structures
     * @param address house address
     * @param ownerName owner name
     * @param ownerNif owner nif
     * @param providerName Nome do fornecedor
     */
    public SmartHouse(String address, String ownerName, int ownerNif, String providerName){
        this.id = SmartHouse.idCount++;
        this.address = address;
        this.ownerName = ownerName;
        this.ownerNif = ownerNif;
        this.locations = new HashMap<>();
        this.devices = new HashMap<>();
        this.providerName = providerName;
        this.bills = new TreeSet<>();
        this.changes = new ArrayList<>();
    }

    /**
     * Constructor
     * @param address house address
     * @param ownerName owner name
     * @param ownerNif owner nif
     */
    public SmartHouse(String address, String ownerName, int ownerNif){
        this.id = SmartHouse.idCount++;
        this.address = address;
        this.ownerName = ownerName;
        this.ownerNif = ownerNif;
        this.locations = new HashMap<>();
        this.devices = new HashMap<>();
        this.bills = new TreeSet<>();
        this.changes = new ArrayList<>();
    }

    /**
     * Construtor for the setup document
     * @param ownerName owner name
     * @param ownerNif owner nif
     */
    public SmartHouse(String ownerName, int ownerNif){
        this.id = SmartHouse.idCount++;
        this.address = "";
        this.ownerName = ownerName;
        this.ownerNif = ownerNif;
        this.locations = new HashMap<>();
        this.devices = new HashMap<>();
        this.bills = new TreeSet<>();
        this.changes = new ArrayList<>();
    }

    /**
     * Copy constructor
     * @param house House
     */
    public SmartHouse(SmartHouse house){
        this.id = house.getId();
        this.address = house.address;
        this.ownerName = house.ownerName;
        this.ownerNif = house.ownerNif;
        this.locations = house.getLocations();
        this.devices = house.getDevices();
        this.providerName = house.getProviderName();
        this.bills = house.getBills();
        this.changes = house.getChanges();
        this.currentConsumption = house.currentConsumption;
        this.totalKwh = house.totalKwh;
        this.accumCost = house.accumCost;
    }

    //Getters

    /**
     * Get id of the house
     * @return id
     */
    public int getId() {
        return this.id;
    }

    /**
     * Get address of the house
     * @return address
     */
    public String getAddress(){
        return this.address;
    }

    /**
     * Get owner name
     * @return owner name
     */
    public String getOwnerName(){
        return this.ownerName;
    }

    /**
     * Get owner nif
     * @return owner nif
     */
    public int getOwnerNif(){
        return this.ownerNif;
    }

    /**
     * Get devices in house locations (a map)
     * @return map with <Location, List of Devices in that location>
     */
    public Map<String, Set<Integer>> getLocations(){
        HashMap<String, Set<Integer>> locations = new HashMap<String, Set<Integer>>();

        Set<Map.Entry<String, Set<Integer>>> entries = this.locations.entrySet();

        for(Map.Entry<String, Set<Integer>> entry : entries) {
            Set<Integer> deviceIds = new HashSet<>();
            for(Integer i: entry.getValue()){
                deviceIds.add(i);
            }
            locations.put(entry.getKey(), deviceIds);
        }
        return locations;
    }

    /**
     * Get the devices installed in the house
     * @return map with <deviceId, device>
     */
    public Map<Integer, SmartDevice> getDevices(){
        Iterator<Map.Entry<Integer, SmartDevice>> it = this.devices.entrySet().iterator();
        Map<Integer, SmartDevice> devices = new HashMap<>();

        while(it.hasNext()){
            Map.Entry<Integer, SmartDevice> entry = it.next();
            Integer key = entry.getKey();
            SmartDevice value = entry.getValue().clone();

            devices.put(key, value);
        }

        return devices;
    }

    /**
     * Get provider name
     * @return provider name
     */
    public String getProviderName(){
        return this.providerName;
    }

    /**
     * Get bills issued to that house
     * @return list containing all the bills
     */
    public Set<Bill> getBills(){
        Set<Bill> res = new TreeSet<>();
        Iterator<Bill> it = this.bills.iterator();

        while(it.hasNext()){
            Bill b = it.next();
            res.add(b.clone());
        }

        return res;
    }

    /**
     * Get changes in provider
     * @return List of provider changes
     */

    public List <Change> getChanges(){
        List <Change> res = new ArrayList<>();

        for (Change c : this.changes){
            res.add(c.clone());
        }
        return res;
    }


    /**
     * Get the first bill in the tree
     * @return bill
     */
    public Bill getFirstBill() throws NonExistantBillException {
        if (this.bills.isEmpty()) throw new NonExistantBillException("ERROR: Não existem faturas nesta casa.");

        return ((TreeSet<Bill>) this.bills).last().clone();
    }

    //Setters

    /**
     * Set house id
     * @param id new id
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * Set house address
     * @param address new address
     */
    public void setAddress(String address){
        this.address = address;
    }

    /**
     * Set owner name
     * @param ownerName new owner name
     */
    public void setOwnerName(String ownerName){
        this.ownerName = ownerName;
    }

    /**
     * Set owner nif
     * @param ownerNif new owner nif
     */
    public void setOwnerNif(int ownerNif){
        this.ownerNif = ownerNif;
    }

    /**
     * Set locations map
     * @param locations new map containing the devices for each location
     */
    public void setLocations(Map<String, Set<Integer>> locations){
        this.locations = new HashMap<>(locations);
    }

    /**
     * Set devices
     * @param devices new map containing the new devices
     */
    public void setDevices(Map<Integer, SmartDevice> devices){
        this.devices = new HashMap<>();

        Iterator<Map.Entry<Integer, SmartDevice>> it = devices.entrySet().iterator();

        while(it.hasNext()){
            Map.Entry<Integer, SmartDevice> entry = it.next();
            Integer key = entry.getKey();
            SmartDevice value = entry.getValue();

            this.devices.put(key, value.clone());
        }

    }

    /**
     * Altera o nome do fornecedor
     * @param p Nome do novo fornecedor
     */
    public void setProviderName(String p){
        this.providerName = p;
    }

    /**
     * Set bills
     * @param bills new list with the bills
     */
    public void setBills(List<Bill> bills){
        this.bills = new TreeSet<>();
        Iterator<Bill> it = bills.iterator();

        while(it.hasNext()){
            Bill b = it.next();
            this.bills.add(b.clone());
        }
    }

    /**
     * Determina o início da simulação para aquela casa naquela data
     * @param initialDate
     */
    public void startSimulation(LocalDateTime initialDate){
        this.lastBill = initialDate;
        this.lastChange = initialDate;
    }

    /**
     * For each device in the house apply given function
     * @param applyFunction Function to be applied to each device (ex: turnOn, turnOff)
     */
    public void applyToAll(Consumer<SmartDevice> applyFunction){
        this.devices.values().forEach(sd -> applyFunction.accept(sd));
    }

    /**
     * Apply given function to all devices in a given location of the house
     * @param location Location of the house
     * @param applyFunction Function to be applied to all devices in that location
     */
    public void applyToLocation(String location, Consumer<SmartDevice> applyFunction){
        for(Integer i: this.locations.get(location)){
            applyFunction.accept(this.devices.get(i));
        }
    }

    /**
     * Check if two smart houses are equal: same addresses, owner, ...
     * @param o house to be compared
     * @return true if equals, false otherwise
     */
    @Override
    public boolean equals(Object o){
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;

        SmartHouse house = (SmartHouse) o;

        return this.id == house.id && this.address.equals(house.address) && this.ownerName.equals(house.ownerName) &&
               this.ownerNif == house.ownerNif;
    }

    /**
     * Clones the instance house
     * @return the clone
     */
    @Override
    public SmartHouse clone(){
        return new SmartHouse(this);
    }

    /**
     * Gets the string representation of the house
     * @return a string containing info of the house
     */
    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("\nCasa ").append(this.id);
        sb.append("\nMorada: ").append(this.address);
        sb.append("\nDono: ").append(this.ownerName);
        sb.append("\nNIF: ").append(this.ownerNif + "\n");
        for(Map.Entry<String, Set<Integer>> entry: this.locations.entrySet()){
            sb.append("\n\n" + entry.getKey() + "...\n");
            for(Integer i: entry.getValue()){
                SmartDevice d = this.devices.get(i);
                sb.append(d);
            }
        }
        sb.append("\nFornecedor: " + this.providerName);
        return sb.toString();
    }

    /**
     * Used to compare two houses (mandatory for treeSet)
     * @param o house to be compared
     * @return lexical difference between owner names (to be changed)
     */
    @Override
    public int compareTo(SmartHouse o) {
        return this.ownerName.compareTo(o.ownerName);
    }

    public String showBills(){
        StringBuilder sb = new StringBuilder("Faturas da casa ").append(this.id + ":\n");
        Iterator<Bill> it = this.bills.iterator();

        while(it.hasNext()){
            Bill b = it.next();
            sb.append(b);
        }
        sb.append("\n");

        return sb.toString();
    }

    public void addBill(Bill b){
        this.bills.add(b.clone());
    }

    /**
     * Adiciona um dispositivo a uma dada divisão (composição)
     * @param sd Dispositivo a adicionar
     * @param location Divisão onde o queremos adicionar
     */
    public void addDevice(SmartDevice sd, String location){
        Set<Integer> ids = this.locations.get(location);

        // Adicionar o id à lista de devices de uma divisão
        if(ids==null){
            ids = new HashSet<>();
            ids.add(sd.getId());
            this.locations.put(location, ids);
        }
        else{
            ids.add(sd.getId());
        }

        this.devices.put(sd.getId(), sd.clone());
        this.accumCost +=sd.getCostOfInstallation();
    }

    // House advance of time and bill/consumption management

    public void setLastBill(LocalDateTime lastBill) {
        this.lastBill = lastBill;
    }

    public void setLastChange(LocalDateTime lastChange) {
        this.lastChange = lastChange;
    }

    public void setCurrentConsumption(double currentConsumption) {
        this.currentConsumption = currentConsumption;
    }

    public void setTotalKwh(double totalKwh) {
        this.totalKwh = totalKwh;
    }

    public void setAccumCost(double accumCost) {
        this.accumCost = accumCost;
    }

    public double getCurrentConsumption() {
        return currentConsumption;
    }

    public double getTotalKwh() {
        return totalKwh;
    }

    public double getAccumCost() {
        return accumCost;
    }

    public LocalDateTime getLastBill() {
        return lastBill;
    }

    public LocalDateTime getLastChange() {
        return lastChange;
    }

    public void startNewInterval(LocalDateTime currDate){
        this.totalKwh = 0;
        this.lastChange = lastBill;
    }

    /**
     * Acumula o consumo realizado no último intervalo
     * @param currDate data atual (para calcular o nº de horas que se passaram desde a última mudança)
     */
    public void updateTotalKwh(LocalDateTime currDate){
        long hoursPassed = ChronoUnit.HOURS.between(this.lastChange, currDate);
        this.totalKwh += this.currentConsumption*hoursPassed;
    }

    /**
     * Calcula o consumo de uma casa dentro de um dado período
     * @param start início do período
     * @param end fim do período
     * @return consumo (em kwh)
     */
    public double calculateConsumptionPeriod(LocalDateTime start, LocalDateTime end){
        double consumption = 0;
        Iterator<Bill> it = this.bills.iterator();

        while(it.hasNext()){
            Bill b = it.next();
            DateInterval interval = b.getPeriod();

            if(interval.inTheInterval(start, end)) consumption += b.getConsumption();
        }

        return consumption;
    }

    /**
     * Soma os consumos de todos os dispositivos da casa (a ser usada no modo menu)
     * Calcula o consumo em Kwh, com base no consumo em Kw
     * @param hours Nº de horas do período de simulação
     */
    public void calculateAndSetConsumption(int hours){ // Kw
        this.currentConsumption = this.devices.values().stream().mapToDouble(sd -> sd.getConsumption()).sum();
        this.totalKwh = this.currentConsumption*hours;
    }


    /**
     * Turns a device on or off
     * @param id id do dispositivo
     * @param function função que define se queremos ligar ou desligar
     */
    public void turnDevice(int id, Consumer<SmartDevice> function){
        SmartDevice sd = this.devices.get(id);

        function.accept(sd);
    }

    /**
     * Mudança é aplicada apenas quando se faz o avanço do tempo
     * @param c
     */
    public void addChange(Change c){
        this.changes.add(c.clone());
    }

    /**
     * Aplica uma mudança na hora (modo automatização), atualizando
     * os valores do consumo atual (em Kw)
     * e o valor do consumo acumulado (em Kwh)
     * @param c Mudança a aplicar
     * @param currDate Data atual
     */
    public void addChange(Change c, LocalDateTime currDate){
        long hoursPassed = ChronoUnit.HOURS.between(this.lastChange, currDate);
        int id;
        if (c instanceof TurnOnDevice){
            c = (ChangeDevice) c;
            id = ((TurnOnDevice) c).getDeviceId();
            SmartDevice d = this.devices.get(id);

            // Primeiro atualiza o consumo em Kwh e só depois o consumo em Kw
            this.totalKwh += hoursPassed*this.currentConsumption;

            if (d.getOnState() == false){
                this.applyChange(c);
                this.currentConsumption += d.getConsumption();
            }

            this.lastChange = currDate;
        }
        else if (c instanceof TurnOffDevice){
            c = (ChangeDevice) c;
            id = ((TurnOffDevice) c).getDeviceId();
            SmartDevice d = this.devices.get(id);

            this.totalKwh += hoursPassed*this.currentConsumption;

            if (d.getOnState() == true){
                this.currentConsumption -= d.getConsumption();
                this.applyChange(c);
            }


            // Só podemos desligar depois, para antes sabermos o consumo

            this.lastChange = currDate;

        }
        else if (c instanceof ChangeProvider){
            // Muda de fornecedor
            this.applyChange(c);
        }
        else if (c instanceof TurnOnAllDevices){
            this.totalKwh += hoursPassed*this.currentConsumption;

            for(SmartDevice d: this.devices.values()){
                if (d.getOnState() == false){
                    d.turnOn();
                    this.currentConsumption += d.getConsumption();
                }
            }
            this.lastChange = currDate;
        }
        else if (c instanceof TurnOffAllDevices){
            this.totalKwh += hoursPassed*this.currentConsumption;

            for(SmartDevice d: this.devices.values()){
                if (d.getOnState() == true){
                    this.currentConsumption -= d.getConsumption();
                    d.turnOff();
                }
            }
            this.applyChange(c);
            this.lastChange = currDate;
        }
        else if (c instanceof TurnOnLocation){
            this.totalKwh += hoursPassed*this.currentConsumption;

            Set<Integer> locationIds = this.locations.get(((TurnOnLocation) c).getLocation());
            for(Integer i: locationIds){
                SmartDevice d = this.devices.get(i);
                if (d.getOnState() == false){
                    d.turnOn();
                    this.currentConsumption += d.getConsumption();
                }
            }
            this.lastChange = currDate;
        }
        else if (c instanceof TurnOnLocation){
            this.totalKwh += hoursPassed*this.currentConsumption;

            Set<Integer> locationIds = this.locations.get(((TurnOnLocation) c).getLocation());
            for(Integer i: locationIds){
                SmartDevice d = this.devices.get(i);
                if (d.getOnState() == true){
                    this.currentConsumption -= d.getConsumption();
                    d.turnOff();
                }
            }

            this.lastChange = currDate;
        }
    }

    /**
     * Aplica todas as mudanças, seja de dispositivos, seja de fornecedor
     */
    public void applyChanges(){
        if (this.changes != null){
            for(Change c: this.changes){
                this.applyChange(c);
            }
            this.changes.clear();
        }
    }

    /**
     * Aplica uma única mudança (Dispositivo ou fornecedor)
     * @param c Mudança a aplicar
     */
    public void applyChange(Change c){
        Consumer<SmartHouse> function = (Consumer<SmartHouse>) c.getChangeFunction();
        function.accept(this);
    }

    /**
     * Verifica se a casa atual tem um determinado dispositivo
     * @param deviceId Id do dispositivo
     * @return true, se o dispositivo estiver na casa, false, caso contrário
     */
    public boolean hasDevice(int deviceId){
        return this.devices.get(deviceId) != null;
    }

    /**
     * Verifica se a casa atual tem uma dada divisão
     * @param location Divisão a verificar existência
     * @return true, caso a divisão exista, false caso contrário
     */
    public boolean hasLocation(String location) {
        return this.locations.get(location) != null;
    }
}