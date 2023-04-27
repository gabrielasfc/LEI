package RacingManagerUI;

import RacingManagerLN.Exceptions.*;

import java.util.List;
import java.util.Scanner;

public class SimulationView {
    private Controller controller;
    private Scanner sc;

    public SimulationView(Controller sc, Scanner scanner) {
        this.controller = sc;
        this.sc = scanner;
    }

    public void run() {
        String simulationName = "";
        int opt = showMenu();
        if (opt == 1){
            opt = showChooseChamp();

            if (opt == 1) {
                simulationName = getSimulation();
                String car = getCar();
                String pilot = getPilot();
                String username = getUsername();
                try{
                    this.controller.addRecord(simulationName, Integer.parseInt(car), pilot, username);
                }
                catch (NonExistentCarException e){
                    System.out.println("O carro não existe!");
                }
                catch (NonExistentSimulationException e){
                    System.out.println("A simulação não existe!");
                }
                catch (NonExistentPilotException e){
                    System.out.println("O piloto não existe!");
                }
                catch (NonExistentUsernameException e){
                    System.out.println("O username não existe!");
                }

            }

            else if (opt == 2) {
                String champName = getChampionship();
                simulationName = getSimulationName();
                try {
                    this.controller.addSimulation(simulationName, champName);
                } catch (AlreadyExistingSimulationException e) {
                    System.out.println("A simulação já existe!");
                } catch (NonExistentChampionshipException e) {
                    System.out.println("O campeonato não existe!");
                }

                String car = getCar();
                String pilot = getPilot();
                String username = getUsername();
                try {
                    this.controller.addRecord(simulationName, Integer.parseInt(car), pilot, username);
                } catch (NonExistentCarException e) {
                    System.out.println("O carro não existe!");
                } catch (NonExistentSimulationException e) {
                    System.out.println("A simulação não existe!");
                } catch (NonExistentPilotException e) {
                    System.out.println("O piloto não existe!");
                } catch (NonExistentUsernameException e) {
                    System.out.println("O username não existe!");
                }
            }
        }
        else if (opt == 2){
            simulationName = getSimulation();
            if (simulationName.equals("0")) return;
            int nextSimulation = showNextSimulationMenu();
            boolean isSimulationOver = false;

            while (nextSimulation == 1 && !isSimulationOver) {
                showInitialGrid(simulationName);

                String weather = "";

                try{
                    weather = this.controller.getWeather();
                } catch(NonExistentSimulationException e){
                    System.out.println(e.getMessage());
                }
                showWeather(weather);

                int addAdjustment = -1;
                while (addAdjustment != 2) {
                    addAdjustment = showAdjustmentsMenu();
                    if (addAdjustment == 1) {
                        String username = getUsername();
                        adjustmentsHandler(username);
                    }
                }

                int tires = -1;
                while (tires != 2) {
                    tires = showTiresType();
                    if (tires == 1) {
                        String username = getUsername();
                        tiresHandler(username);
                    }
                }

                boolean isRaceOver = false;
                int i=1;

                while (!isRaceOver) {
                    try{
                        isRaceOver = this.controller.simulateLap();
                        showLapGrid(i);
                        i++;
                    } catch (NonExistentSimulationException e){
                        System.out.println(e.getMessage());
                    }

                }

                showRaceFinalGrid();

                try {
                    isSimulationOver = this.controller.finishSimulation();
                } catch (NonExistentSimulationException e){
                    System.out.println(e.getMessage());
                }

                if (!isSimulationOver) {
                    nextSimulation = showNextSimulationMenu();
                }
            }

            this.showChampionshipClassification();
        }
    }

    private String getSimulationName() {
        System.out.print("\nIndique o nome da simulação: ");
        return sc.nextLine();
    }

    private int showNextSimulationMenu(){
        System.out.println("\n=================================");
        System.out.println("Deseja simular a próxima corrida?");
        System.out.println("1... Sim\n2... Não");
        System.out.println("=================================");

        int x = sc.nextInt(); sc.nextLine();
        return x;
    }

    private void showInitialGrid(String simulationName) {
        System.out.println("\n---------------------------------");
        System.out.println("        GRELHA DE PARTIDA        ");
        showInitGrid(simulationName);
        System.out.println("---------------------------------");
    }

    private void showInitGrid(String simulationName) {
        try {
            List<List<String>> grid = this.controller.startSimulation(simulationName);

            for (List<String> p : grid) {
                System.out.print(p.get(0) + ". ");
                System.out.print("User: " + p.get(1) + " | ");
                System.out.print("Car: " + p.get(2) + " " + p.get(3) + " | ");
                System.out.print("Pilot: " + p.get(4) + " | ");
                System.out.print("Remaining adjustments: " + p.get(5) + " | ");
                System.out.println("Score: " + p.get(6));
            }
        } catch (NonExistentSimulationException e) {
            System.out.println(e.getMessage());
        }
    }

    private void showWeather(String weather) {
        System.out.println("TEMPO PREVISTO: " + weather);
        System.out.println("---------------------------------");
    }

    private int showAdjustmentsMenu() {
        System.out.println("\n========================================");
        System.out.println("Deseja efetuar alguma afinação no carro?");
        System.out.println("1... Sim\n2... Não");
        System.out.println("========================================");

        int x = sc.nextInt(); sc.nextLine(); // To read the \n
        return x;

    }

    private String getUsername() {
        System.out.print("Indique o username: ");
        String username = sc.nextLine();
        return username;
    }

    private float getDownforce() {
        System.out.print("\nIndique o novo valor de downforce: ");
        float x = sc.nextFloat(); sc.nextLine();
        return x;
    }

    private int showMenu(){
        System.out.println("\n=================================");
        System.out.println("1... Participar num campeonato\n2... Assistir corridas");
        System.out.println("=================================");

        int opt = sc.nextInt(); sc.nextLine();
        return opt;
    }

    private int getEngineType() {
        System.out.println("\n---------------------------");
        System.out.println("1... Normal");
        System.out.println("2... Agressivo");
        System.out.println("3... Conservativo");
        System.out.println("---------------------------");
        System.out.print("Indique o novo tipo de motor: ");

        int x = sc.nextInt(); sc.nextLine();
        return x;
    }

    private void adjustmentsHandler(String username) {
        float downforce = getDownforce();
        int engineType = getEngineType();

        try {
            this.controller.addAdjustment(username, downforce, engineType);
        } catch (NoAdjustementsLeftException | NonExistentRecordException | NonExistentSimulationException | InvalidDownforceException e){
            System.out.println(e.getMessage());
        }
    }

    private int showTiresType() {
        System.out.println("\n===============================");
        System.out.println("Deseja alterar o tipo de pneus?");
        System.out.println("1... Sim\n2... Não");
        System.out.println("===============================");

        int tiresType = sc.nextInt(); sc.nextLine();
        return tiresType;
    }

    private int getTiresType() {
        System.out.println("----------------------------");
        System.out.println("1... Duros");
        System.out.println("2... Macios");
        System.out.println("3... Chuva");
        System.out.println("----------------------------");
        System.out.print("Indique o novo tipo dos pneus: ");

        return sc.nextInt();
    }

    private void tiresHandler(String username){
        int tiresType = getTiresType();
        try {
            this.controller.setTiresType(username, tiresType);
        } catch (NonExistentRecordException | NonExistentSimulationException e){
            System.out.println(e.getMessage());
        }
    }

    private void showGrid() {
        try {
            List<List<String>> grid = this.controller.showGrid();

            for (List<String> p : grid) {
                System.out.print(p.get(0) + ". ");
                System.out.print("User: " + p.get(1) + " | ");
                System.out.print("Car: " + p.get(2) + " " + p.get(3) + " | ");
                System.out.print("Pilot: " + p.get(4) + " | ");
                System.out.print("Remaining adjustments: " + p.get(5) + " | ");
                System.out.print("Score: " + p.get(6) + " | ");
                System.out.println("Time: " + p.get(7));
            }
        } catch (NonExistentSimulationException e) {
            System.out.println(e.getMessage());
        }
    }

    private void showLapGrid(int i){
        System.out.println("\n-----------------------------------");
        System.out.println("      GRELHA ATUAL (Volta " + i + " )");
        showGrid();
        System.out.println("-----------------------------------");
    }

    private void showRaceFinalGrid(){
        System.out.println("\n=================================");
        System.out.println("       CORRIDA TERMINADA!        ");
        System.out.println("---------------------------------");
        System.out.println("           GRELHA FINAL          ");
        showGrid();
        System.out.println("=================================");
    }

    private void showChampionshipClassification(){
        System.out.println("\n===================================");
        System.out.println("        CAMPEONATO TERMINADO!      ");
        System.out.println("-----------------------------------");
        System.out.println("       RESULTADO DO CAMPEONATO     ");
        try{
            List<List<String>> scores = this.controller.getChampionshipClassification();
            int pos=1;

            for(List<String> playerScore: scores){
                System.out.print(pos + ". ");
                System.out.println(playerScore.get(0) + " | Score: " + playerScore.get(1));
                pos++;
            }
        } catch (NonExistentSimulationException e){
            System.out.println(e.getMessage());
        }
        System.out.println("=================================");
    }


    private int showChooseChamp() {
        System.out.println("\n=================================");
        System.out.println("1... Juntar-se a campeonato existente\n2... Começar campeonato");
        System.out.println("=================================");

        int opt = sc.nextInt(); sc.nextLine();
        return opt;
    }

    private String getSimulation() {
        List<List<String>> simulations = this.controller.showSimulations();
        showExistentSimulations(simulations);
        System.out.print("Indique o número da simulação que pretende escolher: ");

        int sim = sc.nextInt(); sc.nextLine();
        if (sim==0) return "0";

        return simulations.get(sim-1).get(0);
    }

    private void showExistentSimulations(List<List<String>> simulations) {
        int i=1;

        System.out.println("\n-----------------------------------");
        System.out.println("0... Voltar");

        for (List<String> simulation : simulations) {
            System.out.print(i + "... ");
            System.out.print(simulation.get(0) + " | ");
            System.out.print("Número máximo de jogadores: " + simulation.get(1) + " | ");
            System.out.print("Criado a: " + simulation.get(2) + " | ");
            System.out.println("Campeonato: " + simulation.get(3));

            i++;
        }

        System.out.println("-----------------------------------");
    }

    private String getChampionship() {
        List<List<String>> championships = this.controller.showChampionships();
        showExistentChampionships(championships);
        System.out.print("Indique o número do campeonato base que pretende escolher: ");

        int champ = sc.nextInt(); sc.nextLine();
        return championships.get(champ-1).get(0);
    }

    private void showExistentChampionships(List<List<String>> championships) {
        int i=1;

        System.out.println("\n-----------------------------------");

        for (List<String> champ : championships) {
            System.out.print(i + "... ");
            System.out.print(champ.get(0) + " | ");
            System.out.println("Número máximo de jogadores: " + champ.get(1));

            i++;
        }

        System.out.println("-----------------------------------");
    }

    private void showCars(List<List<String>> cars) {
        int i=1;

        for (List<String> car : cars) {
            System.out.print(i + "... ");
            System.out.print(car.get(1) + " " + car.get(2) + " | ");
            System.out.print("Horse Power: " + car.get(3) + " | ");
            System.out.print("Engine Capacity: " + car.get(4) + " | ");
            System.out.print("PAC: " + car.get(5));

            if (car.size() > 6) {
                System.out.println(" | Electric Power: " + car.get(6));
            } else System.out.println();

            i++;
        }
    }

    private String getCar() {
        List<List<String>> cars = this.controller.showAllCars();
        System.out.println("\n-----------------------------------");
        showCars(cars);
        System.out.println("-----------------------------------");
        System.out.print("Indique o número do carro que pretende escolher: ");

        int car = sc.nextInt(); sc.nextLine();
        return cars.get(car-1).get(0);
    }

    private void showPilots(List<List<String>> pilots) {
        int i=1;

        for (List<String> pilot : pilots) {
            System.out.print(i + "... ");
            System.out.print(pilot.get(0) + " | ");
            System.out.print("Chuva vs Tempo Seco: " + pilot.get(1) + " | ");
            System.out.println("Segurança vs Agressividade: " + pilot.get(2));

            i++;
        }
    }

    private String getPilot() {
        List<List<String>> pilots = this.controller.showAllPilots();
        System.out.println("\n-----------------------------------");
        showPilots(pilots);
        System.out.println("-----------------------------------");
        System.out.print("Indique o número do piloto que pretende escolher: ");

        int pilot = sc.nextInt(); sc.nextLine();
        return pilots.get(pilot-1).get(0);
    }
}
