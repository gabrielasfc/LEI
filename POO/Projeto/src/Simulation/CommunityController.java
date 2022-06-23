package src.Simulation;

import src.Change.*;
import src.Community.*;
import src.Exceptions.*;
import src.SmartDevices.*;

import java.io.*;
import java.time.LocalDateTime;

public class CommunityController {
    private Community community;

    /**
     * Construtor que recebe a comunidade
     * @param c comunidade
     */
    public CommunityController(Community c){
        this.community = c;
    }

    /**
     * Construtor de cópia (agregação)
     * @param cc Controlador a ser copiado
     */
    public CommunityController(CommunityController cc){
        this.community = cc.getCommunity();
    }

    /**
     * Devolve a comunidade pertencente ao controlador (agregação)
     * @return a comunidade
     */
    public Community getCommunity() {
        return this.community;
    }

    /**
     * Lê o estado inicial a partir de um ficheiro de texto
     * @param fileName Nome do ficheiro
     */
    public void setUpReadFromTextFile(String fileName){
        Parser p = new Parser();
        p.parse(fileName);

        this.community = p.getCommunity();
    }

    // Métodos que permitem à view (menus) adicionar fornecedores, casas e dispositivos à comunidade

    /**
     * Adiciona um fornecedor à comundade
     * @param name Nome do fornecedor
     * @param baseValue Valor base do cálculo do valor a emitir pelo fornecedor
     * @param tax Imposto a aplicar
     * @param formula Fórmula para o cálculo do preço
     */
    public void addProvider(String name, double baseValue, double tax, String formula){
        Provider p = new Provider(name, baseValue, tax, formula);
        this.community.addProvider(p);
    }

    /**
     * Define a data inicial de simulação para todas as casas
     * @param initialDate data inicial de simulação
     */
    public void startSimulation(LocalDateTime initialDate){
        this.community.startSimulation(initialDate);
    }

    /**
     * Adiciona uma casa à comunidade
     * @param address Endereço da casa
     * @param propName Nome do proprietário
     * @param nif Nif do proprietário
     * @param providerName Nome do fornecedor
     * @return Id da casa
     * @throws NonExistantProviderException
     */
    public int addHouse(String address, String propName, int nif, String providerName) throws NonExistantProviderException {
        SmartHouse sH = new SmartHouse(address, propName, nif);
        int houseId = this.community.addHouse(sH, providerName);
        return houseId;
    }

    /**
     * Adiciona uma SmartBulb a uma dada divisão de uma casa da comunidade
     * @param tone Tone do SmartBulb
     * @param size Tamanho (em cms)
     * @param location Divisão onde vamos inserir
     * @param houseId Id da casa
     */
    public void addSmartBulb(int tone, int size, String location, int houseId){
        SmartBulb sB = new SmartBulb(tone, size);
        this.community.addDeviceToHouseLocation(sB, location, houseId); // Adiciona dispositivo por composição na casa, através da comunidade
    }

    /**
     * Adiciona uma SmartCamera a uma dada divisão de uma casa da comunidade
     * @param dimX dimensão da resolução (x)
     * @param dimY dimensão da resolução (y)
     * @param fileSize Tamanho do ficheiro de gravação
     * @param location Divisão onde vamos inserir
     * @param houseId Id da casa
     */
    public void addSmartCamera(int dimX, int dimY, int fileSize, String location, int houseId){
        SmartCamera sC = new SmartCamera(dimX, dimY, fileSize);
        this.community.addDeviceToHouseLocation(sC, location, houseId);
    }

    /**
     * Adiciona uma SmartSpeaker a uma dada divisão de uma casa da comunidade
     * @param volume Volume da coluna atual
     * @param channel Estação de rádio atual
     * @param brand Marca da coluna
     * @param location Divisão onde vamos inserir
     * @param houseId Id da casa
     */
    public void addSmartSpeaker(int volume, String channel, String brand, String location, int houseId){
        SmartSpeaker sS = new SmartSpeaker(volume, channel, brand);
        this.community.addDeviceToHouseLocation(sS, location, houseId);
    }

    /**
     * Avança o tempo na comunidade
     * @param hours Nº de horas a avançar
     */
    public void advance(int hours){
        this.community.advance(hours);
    }

    /**
     * Mostra as faturas de todas as casas
     * @return String com as faturas de cada casa
     */
    public String showHouseBills(){
        return this.community.showHouseBills();
    }

    /**
     * Mostra todos os fornecedores da comunidade
     * @return String com todos os fornecedores
     */
    public String showProviders(){
        return this.community.showProviders();
    }

    /**
     * Mostra todas as casas da comunidade
     * @return String com todas as casas
     */
    public String showHouses(){
        return this.community.showHouses();
    }

    public String showHouse(int id){
        return this.community.showHouse(id);
    }

    // Métodos que adicionam mudanças a serem aplicadas no início do próximo período de simulação

    /**
     * Adiciona uma mudança no valor do fornecedor
     * @param newValue Novo valor base
     * @param providerName Nome do fornecedor
     * @throws NonExistantProviderException
     */
    public void addChangeProviderBaseValue(double newValue, String providerName) throws NonExistantProviderException{
        Change c = new ChangeProviderBaseValue(newValue, providerName);
        if (this.community.hasProvider(providerName) == false) throw new NonExistantProviderException("Provider " + providerName + " não existe");
        this.community.addChange(c);
    }

    /**
     * Adiciona uma mudança no imposto do fornecedor
     * @param newTax Novo imposto a aplicar
     * @param providerName Nome do fornecedor
     * @throws NonExistantProviderException
     */
    public void addChangeProviderTax(double newTax, String providerName) throws NonExistantProviderException{
        Change c = new ChangeProviderTax(newTax, providerName);
        if (this.community.hasProvider(providerName) == false) throw new NonExistantProviderException("Provider " + providerName + " não existe");
        this.community.addChange(c);
    }

    /**
     * Adiciona uma mudança na fórmula do fornecedor
     * @param newFormula Nova fórmula a aplicar
     * @param providerName Nome do fornecedor
     * @throws NonExistantProviderException
     */
    public void addChangeProviderFormula(String newFormula, String providerName) throws NonExistantProviderException{
        Change c = new ChangeProviderFormula(newFormula, providerName);
        if (this.community.hasProvider(providerName) == false) throw new NonExistantProviderException("Provider " + providerName + " não existe");
        this.community.addChange(c);
    }

    /**
     * Adiciona uma mudança a uma casa
     * @param houseId Id da casa
     * @param deviceId Id do dispositivo
     * @param mode Tipo de mudança (0 - desligar, 1 - ligar)
     * @throws NonExistantDeviceException
     * @throws NonExistantHouseException
     */
    public void addTurnChangeToHouse(int houseId, int deviceId, int mode) throws NonExistantDeviceException, NonExistantHouseException {
        if (this.community.houseHasDevice(houseId, deviceId) == false) throw new NonExistantDeviceException("Device " + deviceId + " não existe na casa " + houseId);
        else {
            Change c;
            if (mode == 0){ // Para desligar
                c = new TurnOffDevice(deviceId);
            }
            else { // Para ligar
                c = new TurnOnDevice(deviceId);
            }

            this.community.addChangeToHouse(houseId, c);
        }

    }

    /**
     * Adiciona uma mudança (todos os dispositivos de uma dada divisão) numa casa
     * @param houseId id da casa
     * @param location divisão
     * @param mode Tipo de mudança (0 - desligar, 1 - ligar)
     * @throws NonExistantHouseException
     * @throws NonExistantLocationException
     */
    public void addTurnChangeToHouse(int houseId, String location, int mode) throws NonExistantHouseException, NonExistantLocationException {
        Change c;
        if (mode == 0){ // Para desligar
            c = new TurnOffLocation(location);
            if (this.community.houseHasLocation(houseId, location) == false){
                throw new NonExistantLocationException("Não existe a divisão  " + location);
            }
        }
        else { // Para ligar
            c = new TurnOnLocation(location);
            if (this.community.houseHasLocation(houseId, location) == false){
                throw new NonExistantLocationException("Não existe a divisão  " + location);
            }
        }

        this.community.addChangeToHouse(houseId, c);
    }

    /**
     * Adiciona uma mudança (todos os dispositivos de uma casa)
     * @param houseId id da casa
     * @param mode Tipo de mudança (0 - desligar, 1 - ligar)
     * @throws NonExistantHouseException
     */
    public void addTurnChangeToHouse(int houseId, int mode) throws NonExistantHouseException {
        Change c;
        if (mode == 0){ // Para desligar
            c = new TurnOffAllDevices();
        }
        else { // Para ligar
            c = new TurnOnAllDevices();
        }

        this.community.addChangeToHouse(houseId, c);
    }

    /**
     * Adiciona uma mudança no fornecedor de uma casa
     * @param houseId Id da casa
     * @param newProvider Nome do fornecedor
     * @throws NonExistantHouseException
     * @throws NonExistantProviderException
     */
    public void addChangeProviderToHouse(int houseId, String newProvider) throws NonExistantHouseException, NonExistantProviderException{
        Change c = new ChangeProvider(newProvider);
        if (this.community.hasProvider(newProvider) == false) throw new NonExistantProviderException("Provider " + newProvider + " não existe");

        this.community.addChangeToHouse(houseId, c);
    }

    /**
     * Lê de ficheiro o estado da comundade
     * @param fileName Nome do ficheiro a ler
     * @throws IOException
     * @throws ClassNotFoundException
     */
    public void setUpReadFromBinaryFile(String fileName) throws IOException, ClassNotFoundException {
        FileInputStream fis = new FileInputStream(fileName);
        ObjectInputStream ois = new ObjectInputStream(fis);
        this.community = (Community) ois.readObject();
        ois.close();
    }

    /**
     * Guarda o estado da comunidade em ficheiro binário
     * @param fileName Nome do ficheiro
     * @throws FileNotFoundException
     * @throws IOException
     */
    public void storeState(String fileName) throws FileNotFoundException, IOException {
        FileOutputStream fos = new FileOutputStream(fileName);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        oos.writeObject(this.community);
        oos.flush();
        oos.close();
    }

    // Queries

    /**
     * Devolve uma ordenação das casas com maior consumo dentro do período especificado
     * @param start início desse periodo
     * @param end fim do período
     * @return uma string com essa ordenação
     * @throws NonExistantHouseException
     */
    public String topConsumers(LocalDateTime start, LocalDateTime end) throws NonExistantHouseException {
       return this.community.topConsumers(start, end);
    }

    /**
     * Devolve uma representação da casa que mais gastou no último período de simulação
     * @return uma string com a representação da casa
     * @throws NonExistantHouseException
     * @throws NonExistantBillException
     */
    public String highestConsumption() throws NonExistantHouseException, NonExistantBillException {
        return this.community.highestConsumption().toString();
    }

    /**
     * Devolve uma string com os dados do fornecedor com maior volume emitido de faturação
     * @return a string com os dados do fornecedor
     * @throws NonExistantProviderException
     * @throws NonExistantBillException
     */
    public String highestBill() throws NonExistantProviderException, NonExistantBillException {
        Provider p = this.community.highestBill();
        return p.toString() + p.getCurrentCost();
    }

    /**
     * Devolve uma string com as faturas emitidas por um dado fornecedor
     * @param name nome do fornecedor
     * @return a string
     * @throws NonExistantProviderException
     * @throws NonExistantBillException
     */
    public String billsFromProvider(String name) throws NonExistantProviderException, NonExistantBillException {
        return this.community.billsFromProvider(name);
    }
}
