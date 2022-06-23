package src.Community;

import src.Bill.*;
import src.Change.*;
import src.Changeable;
import src.Exceptions.*;
import src.SmartDevices.SmartDevice;

import java.io.Serializable;
import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;
import java.util.*;
import java.util.function.Consumer;

public class Community implements Serializable, Changeable {
    private Map<Integer, SmartHouse> houses;
    private Map<String, Provider> providers;
    private LocalDateTime currentDateTime;
    private List<Change> providerChanges;

    /**
     * Construtor por defeito
     */
    public Community(){
        this.houses = new HashMap<>();
        this.providers = new HashMap<>();
        this.currentDateTime = LocalDateTime.now();
        this.providerChanges = new ArrayList<Change>();
    }

    /**
     * Construtor 1
     * @param houses map já com as casas
     * @param providers map já com os fornecedores
     * @param currentDate data inicial do sistema
     */
    public Community(Map<Integer, SmartHouse> houses, Map<String, Provider> providers, LocalDateTime currentDate) {
        this.houses = new HashMap<>();

        for(Integer id: houses.keySet()){ // Adiciona todas as casas ao conjunto de casas
            this.houses.put(id, houses.get(id).clone());
        }

        this.providers = new HashMap<>();
        for(String name: providers.keySet()){ // Adiciona todos os fornecedores ao conjunto de fornecedores
            this.providers.put(name, providers.get(name).clone());
        }
        this.providerChanges = new ArrayList<Change>();
        this.currentDateTime = currentDate;
    }

    /**
     * Construtor de cópia
     * @param c Comunidade que queremos copiar para esta instância
     */
    public Community(Community c){
        this.houses = c.getHouses();
        this.providers = c.getProviders();
        this.currentDateTime = c.getCurrentDateTime();
        this.providerChanges = c.getProviderChanges();
    }

    //GETTERS

    /**
     * Devolve um map (cópia) com as casas
     * @return map <Id,CasaInteligente> com as casas
     */
    public Map<Integer, SmartHouse> getHouses() {
        Map<Integer, SmartHouse> houses = new HashMap<>();
        for(Integer id: this.houses.keySet()){
            houses.put(id, this.houses.get(id).clone());
        }
        return houses;
    }

    /**
     * Devolve um map (cópia) com os fornecedores
     * @return map <Nome,Fornecedor> com as casas
     */
    public Map<String, Provider> getProviders() {
        Map<String,Provider> providers = new HashMap<String, Provider>();
        for(Provider prov: this.providers.values()){
            providers.put(prov.getName(), prov.clone());
        }
        return providers;
    }

    /**
     * Devolve a data atual do sistema
     * @return a data da comunidade
     */
    public LocalDateTime getCurrentDateTime() {
        return currentDateTime;
    }

    /**
     * Devove a lista (cópia) das mudanças nos fornecedores
     * @return a lista com as mudanças
     */
    public List<Change> getProviderChanges() {
        List<Change> changes = new ArrayList<Change>();
        for(Change c: this.providerChanges){
            changes.add(c.clone());
        }
        return changes;
    }

    /**
     * Devolve o conjunto das faturas de um dado fornecedor
     * @param name nome do fornecedor
     * @return uma cópia das faturas de um dado fornecedor
     * @throws NonExistantProviderException
     */
    public Set<Bill> getProviderBillsByID(String name) throws NonExistantProviderException {
        Provider p = this.providers.get(name);

        if (p == null) throw new NonExistantProviderException("ERROR: O fornecedor indicado não existe.");

        return p.getBills();
    }

    //SETTERS

    /**
     * Atualiza o map das casas da comunidade
     * @param houses map que vai ser copiado para esta comunidade
     */
    public void setHouses(Map<Integer, SmartHouse> houses) {
        Map<Integer, SmartHouse> newHouses = new HashMap<Integer, SmartHouse>();
        for(Integer id: houses.keySet()){ // Adiciona todas as casas ao conjunto de casas
            newHouses.put(id, houses.get(id).clone());
        }
        this.houses = newHouses;
    }

    /**
     * Atualiza o map dos fornecedores da comunidade
     * @param providers map que vai ser copiado para esta comunidade
     */
    public void setProviders(Map<String, Provider> providers) {
        Map<String, Provider> newProviders = new HashMap<String,Provider>();
        for(String name: providers.keySet()){ // Adiciona todos os fornecedores ao conjunto de fornecedores
            newProviders.put(name, providers.get(name).clone());
        }
        this.providers = newProviders;
    }

    /**
     * Atualiza a data atual da comunidade
     * @param currentDateTime data que queremos atualizar
     */
    public void setCurrentDate(LocalDateTime currentDateTime) {
        this.currentDateTime = currentDateTime;
    }

    /**
     * Compara duas comunidade, verificando se são iguais
     * @param o Objeto a ser comparado
     * @return true, se os dois objetos forem iguais, false, caso contrário
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Community community = (Community) o;

        boolean isEqual = true;

        Iterator<SmartHouse> it1 = this.houses.values().iterator();
        while (isEqual && it1.hasNext()){
            isEqual = community.hasHouse((SmartHouse) (it1.next()));
        }

        Iterator<Provider> it2 = this.providers.values().iterator();
        while (isEqual && it2.hasNext()){
            isEqual = community.hasProvider((Provider) (it2.next()));
        }

        isEqual = isEqual && this.currentDateTime == community.currentDateTime;
        return isEqual;
    }

    /**
     * Devolve uma representação da comunidade na forma de string
     * @return string com a representação da comunidade
     */
    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("Community: ");
        sb.append("\nCasas:\n").append(houses);
        sb.append("\nFornecedores:\n ").append(providers);
        sb.append("\nData atual: ").append(currentDateTime.toString());
        return sb.toString();
    }

    /**
     * Verifica se uma dada casa está presente na comunidade
     * @param h casa a procurar
     * @return true, caso a casa exista, false, caso contrário
     */
    public boolean hasHouse(SmartHouse h){ return this.houses.values().stream().anyMatch(house -> house.equals(h)); }

    /**
     * Verifica se um dado fornecedor está presente na comunidade
     * @param provider fornecedor a procurar
     * @return true, caso o fornecedor exista, false, caso contrário
     */
    public boolean hasProvider(Provider provider) {
        return this.providers.containsValue(provider);
    }

    /**
     * Verifica se um dado fornecedor está presente na comunidade
     * @param providerName nome do fornecedor
     * @return true, caso o fornecedor exista, false , caso contrário
     */
    public boolean hasProvider(String providerName) {
        return this.providers.get(providerName) != null;
    }

    /**
     * Adiciona uma casa à comunidade, adicionando ainda um fornecedor a essa casa
     * @param house Casa a adicionar
     * @param providerName Nome do fornecedor para aquela casa
     * @return id da casa adicionada
     * @throws NonExistantProviderException
     */
    public int addHouse(SmartHouse house, String providerName) throws NonExistantProviderException{
        Provider p = this.providers.get(providerName);
        if (p == null) throw new NonExistantProviderException("Provider " + providerName + " não existe");
        else {
            house.setProviderName(providerName);
            this.houses.put(house.getId(), house.clone());
            return house.getId();
        }
    }

    /**
     * Adiciona um fornecedor à comunidade por composição
     * @param p Fornecedor a adicionar
     */
    public void addProvider(Provider p){
        this.providers.put(p.getName(), p.clone());
    }

    /**
     * Adiciona um dispositivo a uma dada divisão da casa
     * @param d Dispositivo a adicionar
     * @param location divisão onde queremos adicionar o dispositivo
     * @param houseId id da casa onde o dispositivo vai ser adicionado
     */
    public void addDeviceToHouseLocation(SmartDevice d, String location, int houseId){
        this.houses.get(houseId).addDevice(d, location);
    }

    /**
     * Adiciona uma mudança à comunidade (mudança nos fornecedores) (modo menu)
     * @param c
     */
    public void addChange(Change c){
        this.providerChanges.add(c.clone());
    }

    /**
     * Adiciona uma mudança a uma dada casa (modo menu)
     * @param id id da casa onde vamos adicionar a mudança
     * @param c mudança a adicionar
     * @throws NonExistantHouseException
     */
    public void addChangeToHouse(int id, Change c) throws NonExistantHouseException{
        SmartHouse sH = this.houses.get(id);
        if (sH == null){
            throw new NonExistantHouseException("A casa com id " + id + " não existe!");
        }
        sH.addChange(c); // Clone é feito na casa
    }

    /**
     * Aplica uma mudança a uma casa na hora (modo automatização)
     * @param id Id da casa
     * @param c Alteração a efetuar
     * @throws NonExistantHouseException
     */
    public void addChangeToHouseNow(int id, Change c) throws NonExistantHouseException{
        SmartHouse sH = this.houses.get(id);
        if (sH == null){
            throw new NonExistantHouseException("A casa com id " + id + " não existe!");
        }
        sH.addChange(c, this.currentDateTime);
    }

    /**
     * Aplica uma mudança ao fornecedor de uma casa na hora (modo automatização)
     * @param id Id da casa
     * @param providerName Nome do fornecedor
     * @throws NonExistantHouseException
     */
    public void addChangeToHouseProviderNow(int id, String providerName) throws NonExistantHouseException{
        SmartHouse sH = this.houses.get(id);
        Change c;
        if (sH == null){
            throw new NonExistantHouseException("A casa com id " + id + " não existe!");
        }
        c = new ChangeProvider(providerName);

        sH.updateTotalKwh(this.currentDateTime);
        this.issueBill(id);
        sH.startNewInterval(this.currentDateTime);
        sH.addChange(c, this.currentDateTime);
    }

    /**
     * Aplica uma mudança no estado de um fornecedor, emitindo as faturas respetivas para as casas que foram afetadas (modo automatização)
     * @param name Nome do fornecedor
     * @param c Mudança a aplicar
     */
    public void changeProviderStateNow(String name, Change c){
        for(SmartHouse h: this.houses.values()){
            if (h.getProviderName().equals(name)){
                h.updateTotalKwh(this.currentDateTime);
                this.issueBill(h.getId());
                h.startNewInterval(this.currentDateTime);
            }
        }

        this.applyChange(c);
    }

    /**
     * Changes state of provider according to change Function (used in Changes)
     * @param name name of the provider
     * @param applyFunction function to be applied to provider
     */
    public void changeProviderState(String name, Consumer<Provider> applyFunction){
        applyFunction.accept(this.providers.get(name));
    }

    /**
     * Começa um novo intervalo de simulação para cada uma das casas (modo automatização)
     */
    public void startNewInterval(){
        // Todas as casas começam um novo intervalo de simulação
        for(SmartHouse h: this.houses.values()){
            h.updateTotalKwh(this.currentDateTime); // Acumula o consumo realizado no último intervalo
            this.issueBill(h.getId()); // Emite fatura para a casa
            h.startNewInterval(this.currentDateTime); // Começa um novo período de faturação
        }
    }

    /**
     * Aplica as mudanças existentes na comunidade (providers) (modo menu)
     */
    public void applyChanges(){
        for(Change c: this.providerChanges){
            this.applyChange(c);
        }
    }

    /**
     * Aplica uma dada mudança na comunidade
     * @param c
     */
    public void applyChange(Change c){
        Consumer<Community> cons = (Consumer<Community>)c.getChangeFunction();
        cons.accept(this);
    }

    /**
     * Devolve uma string com as faturas de todas as casas
     * @return a string com as faturas
     */
    public String showHouseBills(){
        StringBuilder sb = new StringBuilder();

        Iterator<SmartHouse> it = this.houses.values().iterator();

        while(it.hasNext()){
            sb.append(it.next().showBills());
        }

        return sb.toString();
    }

    /**
     * Devolve uma string com todos os fornecedores
     * @return a string com os fornecedores
     */
    public String showProviders(){
        StringBuilder sb = new StringBuilder();

        Iterator<Provider> it = this.providers.values().iterator();

        while(it.hasNext()){
            sb.append(it.next());
        }

        return sb.toString();
    }

    /**
     * Devolve uma string com todas as casas
     * @return a string com as casas
     */
    public String showHouses(){
        StringBuilder sb = new StringBuilder("Casa nº ");
        Iterator<SmartHouse> it = this.houses.values().iterator();

        while(it.hasNext()){
            SmartHouse house = it.next();

            sb.append("===========================================================================================================================");;
            sb.append(house + "\n");
            sb.append("===========================================================================================================================\n");
        }

        return sb.toString();
    }

    /**
     * Devolve uma string com uma casa
     * @param id id da casa
     * @return a string com a casa
     */
    public String showHouse(int id){
        SmartHouse h = this.houses.get(id);
        return h.toString();
    }

    /**
     * Verifica se um dado dispositivo está numa casa
     * @param houseId Id da casa
     * @param deviceId Id do dispositivo
     * @return true, se o dispositivo estiver na casa, false, caso contrário
     */
    public boolean houseHasDevice(int houseId, int deviceId){
        SmartHouse sH = this.houses.get(houseId);
        if (sH == null) return false;

        return sH.hasDevice(deviceId);
    }

    /**
     * Verifica se uma dada casa tem uma certa divisão
     * @param houseId Id da casa
     * @param location Divisão a procurar
     * @return true, se a casa tiver essa divisão, false caso contrário
     */
    public boolean houseHasLocation(int houseId, String location){
        SmartHouse sH = this.houses.get(houseId);

        return sH.hasLocation(location);
    }

    /**
     * Indica a todas as casas qual é a hora do início de simulação (todas começam ao mesmo tempo)
     * @param initialDate hora inicial da simulação
     */
    public void startSimulation(LocalDateTime initialDate){
        this.setCurrentDate(initialDate);
        for(SmartHouse h: this.houses.values()){
            h.startSimulation(initialDate);
        }
    }

    /**
     * Emite uma fatura para uma dada casa (ambos os modos)
     * @param houseId Id da casa
     */
    public void issueBill(int houseId){
        SmartHouse h = this.houses.get(houseId);
        Provider p = this.providers.get(h.getProviderName());
        if (p == null){
            System.out.println("null");
        }
        // Calcula o custo, com base na fórmula do fornecedor e
        // adiciona a fatura à lista

        double cost = p.calculateCost(h.getTotalKwh());

        Bill b = new Bill(h.getId(), new DateInterval(h.getLastBill(), this.currentDateTime), h.getTotalKwh(), cost + h.getAccumCost());

        h.addBill(b);
        p.addBill(b);

        h.setLastBill(this.currentDateTime);
        h.setAccumCost(0);
    }

    /**
     * Promove o avanço do tempo, na simulação (modo menu)
     * @param hours Número de horas a avançar
     */
    public void advance(int hours){
        // Para cada casa na comunidade:
        // , altera o valor do consumo (KwH) da casa
        // , emite uma fatura com este valor
        // , aplica as novas mudanças (que só vão ser aplicadas no período seguinte)

        // Avança o tempo da comunidade
        this.currentDateTime = this.currentDateTime.plus((long) hours, ChronoUnit.HOURS); // LocalDateTime é imutável

        for(SmartHouse h: this.houses.values()){
            h.calculateAndSetConsumption(hours);
            this.issueBill(h.getId());
            //h.issueBill(currentDateTime);
            h.applyChanges();
        }
        // Aplica as mudanças dos fornecedores, globais às casas
        this.applyChanges();
    }

    //QUERIES

    /**
     * Devolve uma string com a ordenação das casas que mais gastaram energia num dado período
     * @param start início do período
     * @param end fim do período
     * @return a string
     * @throws NonExistantHouseException
     */
    public String topConsumers(LocalDateTime start, LocalDateTime end) throws NonExistantHouseException {
        StringBuilder sb = new StringBuilder("Maiores consumidores:\n");

        Set<SmartHouse> houses = new TreeSet<>(
                new Comparator<SmartHouse>() {
                    @Override
                    public int compare(SmartHouse sh1, SmartHouse sh2) {
                        int cmp = (int) sh1.calculateConsumptionPeriod(start, end) - (int) sh2.calculateConsumptionPeriod(start, end);
                        if (cmp != 0) return cmp;
                        return sh1.getId() - sh2.getId();
                    }
                }
        );

        Map<Integer, SmartHouse> housesMap = this.houses;

        if (housesMap.isEmpty()) throw new NonExistantHouseException("ERROR: Não existem casas na comunidade.");

        Iterator<SmartHouse> it = housesMap.values().iterator();
        while(it.hasNext()){
            SmartHouse sH = it.next();
            houses.add(sH.clone());
        }

        it = houses.iterator();
        while(it.hasNext()){
            SmartHouse sH = it.next();
            sb.append(sH.getId() + " : " + sH.calculateConsumptionPeriod(start, end)).append('\n');
        }

        return sb.toString();
    }


    /**
     * Devolve a casa que mais gastou no (último) período de faturação
     * @return a casa que mais gastou
     * @throws NonExistantHouseException
     * @throws NonExistantBillException
     */
    public SmartHouse highestConsumption() throws NonExistantHouseException, NonExistantBillException {
        Map<Integer, SmartHouse> houses = this.houses;
        Iterator<SmartHouse> it = houses.values().iterator();
        double maxConsumption = 0;
        SmartHouse ret = null;
        boolean noBillsFlag = true;

        while(it.hasNext()){
            SmartHouse house = it.next();

            Bill firstBill = house.getFirstBill();
            LocalDateTime billEndDate = firstBill.getPeriod().getEnd();
            LocalDateTime communityDate = this.getCurrentDateTime();

            if(billEndDate.isEqual(communityDate)){
                double consumption = firstBill.getConsumption();

                if(consumption >= maxConsumption) {
                    maxConsumption = consumption;
                    ret = house;
                }

                noBillsFlag = false;
            }
        }

        if (ret == null) throw new NonExistantHouseException("ERROR: Não existem casas na comunidade.");
        if(noBillsFlag && ret != null) throw new NonExistantBillException("ERROR : Não existem faturas.");

        return ret.clone();
    }

    /**
     * Devolve o fornecedor com maior faturação
     * @return o fornecedor que mais faturou naquela simulação
     * @throws NonExistantProviderException
     * @throws NonExistantBillException
     */
    public Provider highestBill() throws NonExistantProviderException, NonExistantBillException {
        Map<String, Provider> providers = this.providers;
        Iterator<Provider> it = providers.values().iterator();
        double maxCost = 0;
        Provider ret = null;

        while(it.hasNext()){
            Provider p = it.next();
            double cost = p.getCurrentCost();

            if(cost >= maxCost) {
                maxCost = cost;
                ret = p;
            }
        }

        if (ret == null) throw new NonExistantProviderException("ERROR: Não existem fornecedores na comunidade.");
        if (maxCost == 0) throw new NonExistantBillException("ERROR: Não existem fornecedores com faturas emitidas.");

        return ret.clone();
    }

    /**
     * Devolve as faturas emitidas por um fornecedor na forma de String
     * @param name Nome do fornecedor
     * @return a String com as faturas desse fornecedor
     * @throws NonExistantProviderException
     * @throws NonExistantBillException
     */
    public String billsFromProvider(String name) throws NonExistantProviderException, NonExistantBillException {
        Set<Bill> bills = this.getProviderBillsByID(name);

        if (bills.isEmpty()) throw new NonExistantBillException("ERROR: O fornecedor indicado não tem faturas emitidas.");

        Iterator<Bill> it = bills.iterator();
        StringBuilder sb = new StringBuilder("Faturas:");

        while(it.hasNext()){
            Bill b = it.next();

            sb.append(b).append('\n');
        }

        return sb.toString();
    }

    /**
     * Devove uma cópia da comunidade atua
     * @return a cópia
     */
    public Community clone(){
        return new Community(this);
    }

}
