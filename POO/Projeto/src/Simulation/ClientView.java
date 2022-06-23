package src.Simulation;

import src.Exceptions.*;

import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.*;

public class ClientView {
    private CommunityController controller; // Para mandar os pedidos ao modelo
    private Scanner sc; // Para termos apenas uma instância do Scanner do stdin

    /**
     * Construtor que cria uma nova Vista com o controlador (interface com a comunidade) e o Scanner
     * @param c Controlador da comunidade
     * @param sc Scanner que lê do Standard Input
     */
    public ClientView(CommunityController c, Scanner sc){
        this.controller = c;
        this.sc = sc;
    }

    /**
     * Método que corre a simulação do programa nos vários modos
     */
    public void run() {
        // Carregamento dos dados //
        int option = showSetUpMenu();

        boolean success = this.loadState(option);
        if (!success) return;

        // Simulação //
        option = this.showSimulationMenu();
        this.sc.nextLine();

        // Simulação por menu //
        if (option == 1){
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH");

            LocalDateTime initialDate = LocalDateTime.now();

            System.out.println("\nData inicial da simulação: \n1... Data atual\n2... Data à escolha");
            option = sc.nextInt();
            sc.nextLine();

            if (option == 2) {
                System.out.println("\nInsira a data inicial da simulação: ");
                String dataInicial = sc.nextLine();

                try{
                    initialDate = LocalDateTime.parse(dataInicial, formatter);
                } catch(DateTimeParseException e){
                    System.out.println("Formato da data inválido");
                    return;
                }
            }

            //
            this.controller.startSimulation(initialDate);

            while (option != 0) {
                option = showRunningMenu();

                switch (option) {
                    case 0:
                        break;
                    case 1:
                        showTurnOnMenu();
                        break;
                    case 2:
                        showTurnOffMenu();
                        break;
                    case 3:
                        showAdvanceMenu();
                        showChangeProviderMenu();
                        break;
                    case 4:
                        showChangeProviderValuesMenu();
                        break;
                    case 5:
                        showBillsMenu();
                        break;
                    case 6:
                        showProvidersMenu();
                        break;
                    case 7:
                        showHousesMenu();
                        break;
                    case 8:
                        showQueriesMenu();
                        break;
                    case 9:
                        try{
                            this.controller.storeState(showStoreStateMenu());
                        } catch(IOException e){
                            System.out.println(e.getMessage());
                        }
                    default:
                        System.out.println("Opção não disponível!");
                }
            }
            // No final guardamos o estado do programa
            System.out.println("===================================");
            System.out.println("Quer guardar o estado do programa? \n1... Sim\n2... Não");
            option = sc.nextInt();
            sc.nextLine();
            if (option == 1){
                try{
                    this.controller.storeState(showStoreStateMenu());
                } catch(IOException e){
                    System.out.println(e.getMessage());
                }
            }
        }
        else {
            // Simulação por ficheiro de automatização
            System.out.println("Qual o nome do ficheiro de simulação? ");
            String nomeFich = "Files/Automation.txt"; //this.sc.next();
            ParserAutomation pA = new ParserAutomation(this.controller.getCommunity(), nomeFich);
            pA.parse();
        }


    }

    /**
     * Menu que mostra os diferentes modos de carregar os dados do programa
     * @return Inteiro que representa a opção escolhida
     */
    private int showSetUpMenu(){
        System.out.println("===================================================");
        System.out.println("Como pretende carregar a informação da comunidade?");
        System.out.println("1... Ficheiro de texto\n2... Ficheiro binário\n3... Menu");
        System.out.println("===================================================");

        return sc.nextInt();
    }

    /**
     * Menu que pergunta onde o utilizador quer guardar o estado do programa
     * @return String com o PATH do ficheiro onde se vai guardar o estado
     */
    private String showStoreStateMenu(){
        System.out.println("\nQual o nome do ficheiro para guardar o estado? ");
        String fileName = "Files/" + sc.nextLine();

        return fileName;
    }

    /**
     * Menu que mostra as diferentes formas de simular o programa
     * @return Inteiro que representa a opção escolhida
     */
    private int showSimulationMenu(){
        System.out.println("\n=========================================");
        System.out.println("Como pretende simular o avanço do tempo?\n1... Menu\n2... Automatização");
        System.out.println("=========================================");

        return sc.nextInt();
    }

    /**
     * Carrega o estado do programa
     * @param option Opção que indica qual o modo de carregar o estado
     * @return true, se a operação foi bem sucedidade, false caso contrário
     */
    private boolean loadState(int option) {
        String fileName;
        switch(option){
            case 1:
                System.out.println("\nNome do Ficheiro: ");
                fileName = "Files/" + this.sc.next();
                this.controller.setUpReadFromTextFile(fileName); // A exceção já é apanhada no parser
                break;
            case 2:
                System.out.println("\nNome do Ficheiro: ");
                fileName = "Files/" + this.sc.next();

                try {
                    this.controller.setUpReadFromBinaryFile(fileName);
                }
                catch (IOException | ClassNotFoundException e){
                    System.out.println("O ficheiro indicado não existe.");
                    return false;
                }

                break;
            case 3:
                do{
                    System.out.println("\n==========================");
                    System.out.println("0... Terminar");
                    System.out.println("1... Adicionar casa");
                    System.out.println("2... Adicionar fornecedor");
                    System.out.println("==========================");

                    option = sc.nextInt();
                    sc.nextLine();

                    switch(option){
                        case 0:
                            System.out.println("\nConstrução terminada!");
                            break;
                        case 1:
                            showHouseMenu();
                            break;
                        case 2:
                            showProviderMenu();
                            break;
                        default:
                            System.out.println("Opção inválida!");
                    }
                } while(option != 0);
                break;
        }
        return true;
    }

    /**
     * Menu que promove a simulação
     * @return Inteiro que representa a opção escolhida
     */
    private int showRunningMenu(){
        System.out.println("\n=========================================");
        System.out.println("Escolha uma opção:");
        System.out.println("0... Sair");
        System.out.println("1... Ligar dispositivo");
        System.out.println("2... Desligar dispositivo");
        System.out.println("3... Avançar tempo");
        System.out.println("4... Alterar fornecedor");
        System.out.println("5... Mostrar faturas");
        System.out.println("6... Mostrar fornecedores");
        System.out.println("7... Mostrar casas");
        System.out.println("8... Queries");
        System.out.println("9... Guardar o estado atual em ficheiro");
        System.out.println("========================================");

        int option = sc.nextInt();
        sc.nextLine();

        return option;
    }

    ///////////////////////////////////////////////////////////////////////////////
    //                      Construção do estado por menu                        //
    ///////////////////////////////////////////////////////////////////////////////

    /**
     * Menu para adicionar casa
     */
    private void showHouseMenu(){
        System.out.println("========== ADICIONAR CASA ==========");
        System.out.println("Indique a morada:");
        String address = sc.nextLine();

        System.out.println("Indique o nome do proprietário:");
        String prop = sc.nextLine();

        System.out.println("Indique o NIF do proprietário:");

        int nif = sc.nextInt();
        sc.nextLine(); // Para ler o '\n'

        System.out.println("Qual o nome do fornecedor: ");
        String provider = sc.nextLine();

        int id;

        try{
            // View não conhece a estrutura casa nem a estrutura fornecedor
            id = this.controller.addHouse(address, prop, nif, provider);
        } catch (NonExistantProviderException e){
            System.out.println(e.getMessage());
            return;
        }

        showLocationMenu(id);

        System.out.println("\nA casa foi adicionada com sucesso.\n");
    }

    /**
     * Menu para adicionar fornecedor
     */
    private void showProviderMenu(){
        System.out.println("========== ADICIONAR FORNECEDOR ==========");

        System.out.println("Indique o nome: ");
        String name = sc.nextLine();

        try{
            System.out.println("Indique o preço base (por kWh): ");
            double baseValue = sc.nextDouble();

            System.out.println("Indique o valor do imposto: ");
            double tax = sc.nextDouble();

            sc.nextLine();

            System.out.println("Qual a fórmula para o cálculo do preço: ");
            System.out.println("// t - imposto, c - consumo (kwh), b - valor base //");
            String formula = sc.nextLine();

            this.controller.addProvider(name, baseValue, tax, formula);
        }
        catch (InputMismatchException e){
            sc.nextLine();
            System.out.println("ERROR: Formato de double inválido.");
        }
    }

    /**
     * Menu para adicionar divisões e dispositivos a uma dada casa
     * @param houseId Id da casa onde vamos adicionar
     */
    private void showLocationMenu(int houseId){
        boolean moreLocations = true;

        System.out.println("========== ADICIONAR DIVISÃO ==========");
        while (moreLocations == true){
            System.out.println("Indique o nome da divisão: ");
            String nameLocation = sc.nextLine();

            boolean moreDevices = true;
            while (moreDevices == true){
                showDeviceMenu(nameLocation, houseId);
                System.out.println("0... Voltar\n1... Adicionar mais dispositivos a esta divisão");
                int choice = sc.nextInt();
                if (choice == 0) moreDevices = false;
            }

            System.out.println("0... Nova casa\n1... Nova divisão");
            int choice = sc.nextInt();
            if (choice == 0) moreLocations = false;
        }

    }

    /**
     * Menu para adicionar dispositivos a uma dada divisão de uma dada casa
     * @param location String com a divisão da casa
     * @param houseId Id da casa
     */
    private void showDeviceMenu(String location, int houseId){
        int choice;

        System.out.println("========== ADICIONAR DISPOSITIVO ==========");
        System.out.println("0... SmartBulb\n1... Smart Camera\n 2... Smart Speaker");
        System.out.println("===========================================");
        choice = sc.nextInt();

        switch(choice){
            case 0:
                showSmartBulbMenu(location, houseId);
                break;
            case 1:
                showSmartCameraMenu(location, houseId);
                break;
            case 2:
                showSmartSpeakerMenu(location, houseId);
                break;
        }

    }

    /**
     * Menu para adicionar uma nova SmartBulb
     * @param location Divisão da casa onde vai ser inserida
     * @param houseId Id da casa
     */
    private void showSmartBulbMenu(String location, int houseId){
        System.out.println("========== ADICIONAR SMART BULB ==========");
        System.out.println("Indique o mode:\n0... COLD\n1... NEUTRAL\n2... WARM\n");
        int tone = sc.nextInt();

        System.out.println("Indique o tamanho (em cms):");
        int size = sc.nextInt();
        System.out.println("==========================================");


        this.controller.addSmartBulb(tone, size, location, houseId); // A view não conhece a classe SmartBulb
    }

    /**
     * Menu para adicionar uma nova SmartCamera
     * @param location Divisão da casa onde vai ser inserida
     * @param houseId Id da casa
     */
    private void showSmartCameraMenu(String location, int houseId){
        int dimX, dimY;

        System.out.println("========== ADICIONAR SMART CAMERA ==========");
        System.out.println("Indique a resolução (px * px):\n");
        dimX = sc.nextInt(); dimY = sc.nextInt();

        System.out.println("Indique o tamanho do ficheiro (em MB):"); //MB OU BYTES?
        int fileSize = sc.nextInt();
        System.out.println("============================================");

        this.controller.addSmartCamera(dimX, dimY, fileSize, location, houseId); // A view não conhece a classe SmartCamera

    }

    /**
     * Menu para adicionar uma nova SmartSpeaker
     * @param location Divisão da casa onde vai ser inserida
     * @param houseId Id da casa
     */
    private void showSmartSpeakerMenu(String location, int houseId){
        System.out.println("========== ADICIONAR SMART SPEAKER ==========");
        System.out.println("Indique o volume:\n");
        int volume = sc.nextInt();

        System.out.println("Indique o nome da estação de rádio:\n");
        String channel = sc.next();

        System.out.println("Indique a marca:\n");
        String brand = sc.next();
        System.out.println("=============================================");

        this.controller.addSmartSpeaker(volume, channel, brand, location, houseId); // A view não conhece a classe SmartSpeaker
    }

    ///////////////////////////////////////////////////////////////////////////////
    //                            Menus de simulação                             //
    ///////////////////////////////////////////////////////////////////////////////


    /**
     * Menu que permite ligar o dispositivo de uma casa
     */
    private void showTurnOnMenu(){
        System.out.println("========================================");
        System.out.println("Indique o ID da casa:");
        int idCasa = sc.nextInt();

        //showDevices - casa
        System.out.println(this.controller.showHouse(idCasa));

        System.out.println("\n================================================");
        System.out.println("Opções: \n1... Ligar todos os dispositivos \n2... Ligar os dispositivos de uma certa divisão \n3... Ligar um único dispositivo");
        System.out.println("================================================");
        int option = sc.nextInt();

        if (option == 1){
            try{
                this.controller.addTurnChangeToHouse(idCasa, 1); // Mudança em todos os disp
                System.out.println("\nTodos os dispositivos foram ligados com sucesso!");
            } catch (NonExistantHouseException e){
                System.out.println(e.getMessage());
            }
        }
        else if (option == 2){
            sc.nextLine();
            System.out.println("Qual a divisão? ");
            String location = sc.nextLine();
            try{
                this.controller.addTurnChangeToHouse(idCasa, location, 1); // Mudança de todos os dispositivos numa divisão
                System.out.println("\nTodos os dispositivos da divisão " + location + " foram ligados com sucesso!");
            } catch (NonExistantHouseException | NonExistantLocationException e){
                System.out.println(e.getMessage());
            }
        }
        else if (option == 3){
            System.out.println("Indique o ID do dispositivo:");
            int deviceId = sc.nextInt();

            try {
                this.controller.addTurnChangeToHouse(idCasa, deviceId, 1); // Mudança num dispositivo específico
                System.out.println("\nO dispositivo " + deviceId + " foi ligado com sucesso!");
            }
            catch (NonExistantDeviceException | NonExistantHouseException e){
                System.out.println(e.getMessage());
            }
        }
    }

    /**
     * Menu que permite desligar o dispositivo de uma casa
     */
    private void showTurnOffMenu(){
        System.out.println("========================================");
        System.out.println("Indique o ID da casa:");
        int idCasa = sc.nextInt();

        System.out.println("\n===================================================");
        System.out.println("Opções: \n1... Desligar todos os dispositivos \n2... Desligar os dispositivos de uma certa divisão \n3... Desligar um único dispositivo");
        System.out.println("===================================================");
        int option = sc.nextInt();

        if (option == 1){
            try{
                this.controller.addTurnChangeToHouse(idCasa, 0);
                System.out.println("\nTodos os dispositivos foram desligados com sucesso!");
            } catch (NonExistantHouseException e){
                System.out.println(e.getMessage());
            }
        }
        else if (option == 2){
            System.out.println("Qual a divisão? ");
            String location = sc.nextLine();
            try{
                this.controller.addTurnChangeToHouse(idCasa, location, 0);
                System.out.println("\nTodos os dispositivos da divisão " + location + " foram desligados com sucesso!");
            } catch (NonExistantHouseException | NonExistantLocationException e){
                System.out.println(e.getMessage());
            }
        }
        else if (option == 3){
            System.out.println("Indique o ID do dispositivo:");
            int deviceId = sc.nextInt();
            System.out.println("=======================================");

            try {
                this.controller.addTurnChangeToHouse(idCasa, deviceId, 0);
                System.out.println("\nO dispositivo " + deviceId + " foi desligado com sucesso!");
            }
            catch (NonExistantDeviceException | NonExistantHouseException e) {
                System.out.println(e.getMessage());
            }
        }

    }

    /**
     * Menu que permite avançar o tempo
     */
    private void showAdvanceMenu(){
        System.out.println("\n============================================");
        System.out.println("Indique o número de horas que quer avançar:");
        int hours = sc.nextInt();

        this.controller.advance(hours);
    }

    /**
     * Menu que mostra as fatura a um dado momento
     */
    private void showBillsMenu(){
        System.out.println("\n================ FATURAS ================");
        System.out.print(this.controller.showHouseBills());
        System.out.println("=========================================");
    }

    /**
     * Menu que mostra os fornecedores de uma comunidade
     */
    private void showProvidersMenu(){
        System.out.println("\n============================== FORNECEDORES ==============================");
        System.out.print(this.controller.showProviders());
        System.out.println("==========================================================================");
    }

    /**
     * Menu que mostra as casas de uma dada comunidade
     */
    private void showHousesMenu(){
        System.out.println("\nOpção: \n1... Todas as casas\n2... Uma casa em específico");
        int option = sc.nextInt();

        if (option == 1){
            System.out.println("========== CASAS ==========");
            System.out.print(this.controller.showHouses());
            System.out.println("===========================");
        }
        else {
            System.out.println("\nIndique o ID da casa:");
            option = sc.nextInt();
            System.out.println(this.controller.showHouse(option));
        }

    }

    /**
     * Menu que permite mudar o fornecedor de uma dada casa
     */
    private void showChangeProviderMenu(){
        boolean settingUp = true;

        while(settingUp){
            System.out.println("\nPretende fazer alterações nos fornecedores das casas?\n1... Sim\n2... Não");
            int option = sc.nextInt();
            switch(option){
                case 1 :
                    System.out.println(this.controller.showHouses()); // Mostrar as casas decentemente

                    System.out.println("Indique o ID da casa que pretende alterar:");
                    int idCasa = sc.nextInt();

                    System.out.println(this.controller.showProviders());

                    System.out.println("\nIndique o nome do novo fornecedor:");
                    String providerName = sc.next();

                    try {
                        this.controller.addChangeProviderToHouse(idCasa, providerName);
                        System.out.println("\nO fornecedor foi alterado com sucesso!");
                    }
                    catch (NonExistantHouseException | NonExistantProviderException e) {
                        System.out.println(e.getMessage());
                        break;
                    }
                    break;
                case 2 :
                    settingUp = false;
                    break;
                default :
                    System.out.println("Opção indisponível!");
            }
            System.out.println("======================================================");
        }
    }

    /**
     * Menu que permite fazer alterações nos fornecedores da comunidade
     */
    private void showChangeProviderValuesMenu(){
        System.out.println("Indique o nome do fornecedor:");
        String nameProvider = sc.nextLine();

        System.out.println("\nIndique o campo que pretende alterar:");
        System.out.println("1... Valor base\n2... Taxa\n3... Fórmula");
        int option = sc.nextInt();

        switch(option){
            case 1:
                System.out.println("\nNovo valor: ");
                double newValue = sc.nextDouble();
                try{
                    this.controller.addChangeProviderBaseValue(newValue, nameProvider);
                    System.out.print("\nO valor base do fornecedor " + nameProvider + " foi alterado com sucesso!");
                } catch (NonExistantProviderException e){
                    System.out.println(e.getMessage());
                }
                break;
            case 2:
                System.out.println("\nNova taxa: ");
                double newTax = sc.nextDouble();
                try{
                    this.controller.addChangeProviderTax(newTax, nameProvider);
                    System.out.print("\nA taxa do fornecedor " + nameProvider + " foi alterada com sucesso!");
                } catch(NonExistantProviderException e){
                    System.out.println(e.getMessage());
                }

                break;
            case 3:
                System.out.println("\nNova fórmula: ");
                System.out.println("// t - imposto, c - consumo (kwh), b - valor base //");
                String newFormula = sc.next();
                try{
                    this.controller.addChangeProviderFormula(newFormula, nameProvider);
                    System.out.print("\nA fórmula do fornecedor " + nameProvider + " foi alterada com sucesso!");
                } catch (NonExistantProviderException e){
                    System.out.println(e.getMessage());
                }
                break;
            default:
                break;
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    //                            Menus de queries                               //
    ///////////////////////////////////////////////////////////////////////////////

    /**
     * Menu que permite escolher a query a executar
     */
    private void showQueriesMenu() {
        System.out.println("\n============================= QUERIES =============================");
        System.out.println("0... Voltar");
        System.out.println("1... Casa que mais gastou no último período de simulação");
        System.out.println("2... Comercializador com maior volume de faturação até ao momento");
        System.out.println("3... Lista de faturas emitidas por um determinado comercializador");
        System.out.println("4... Maiores consumidores de energia durante um determinado período");
        System.out.println("===================================================================");

        int option = sc.nextInt();
        sc.nextLine();

        switch (option) {
            case 0:
                break;
            case 1:
                showQuery1Menu();
                break;
            case 2:
                showQuery2Menu();
                break;
            case 3:
                showQuery3Menu();
                break;
            case 4:
                showQuery4Menu();
                break;
            default:
                break;
        }
    }

    /**
     * Menu que mostra a query1 (Casa que mais gastou até ao momento)
     */
    private void showQuery1Menu() {
        try {
            System.out.println("\nCasa que mais gastou até ao momento:\n");
            System.out.println(this.controller.highestConsumption());
        }
        catch (NonExistantHouseException | NonExistantBillException e) {
            System.out.println(e.getMessage());
        }
    }

    /**
     * Menu que mostra a query2 (Comercializador com maior volume de faturação)
     */
    private void showQuery2Menu(){
        try {
            System.out.println("\nComercializador com maior volume de faturação:\n");
            System.out.println(this.controller.highestBill());
        }
        catch (NonExistantProviderException | NonExistantBillException e) {
            System.out.println(e.getMessage());
        }
    }

    /**
     * Menu que mostra a query3 (Faturas de um dado fornecedor)
     */
    private void showQuery3Menu(){
        System.out.println("\nIndique o nome do fornecedor:");
        String name = sc.nextLine();

        try {
            System.out.println(this.controller.billsFromProvider(name));
        }
        catch (NonExistantProviderException | NonExistantBillException e) {
            System.out.println(e.getMessage());
        }
    }

    /**
     * Menu que mostra a query 4 (Ordenação dos maiores consumidores de energia num dado intervalo de tempo)
     */
    private void showQuery4Menu(){
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH");
        System.out.println("\nInsira a data inicial (YYYY-MM-DD HH):");
        String startDate = sc.nextLine();

        System.out.println("\nInsira a data final (YYYY-MM-DD HH): ");
        String endDate = sc.nextLine();

        try {
            LocalDateTime start = LocalDateTime.parse(startDate, formatter);
            LocalDateTime end = LocalDateTime.parse(endDate, formatter);

            System.out.println("\nOrdenação dos maiores consumidores de energia:\n");

            System.out.println(this.controller.topConsumers(start, end));
        }
        catch (DateTimeParseException e) {
            System.out.println("ERROR: Data inserida incorretamente.");
        }
        catch (NonExistantHouseException e) {
            System.out.println(e.getMessage());
        }
    }
}
