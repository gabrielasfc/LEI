package RacingManagerUI;

import RacingManagerDL.DAOconfig;
import RacingManagerLN.Exceptions.NonExistentUsernameException;
import java.util.List;
import java.util.Scanner;

public class MainView {
    private Controller controller;
    private Scanner sc;

    public MainView(Controller controller, Scanner sc){
        this.sc = sc;
        this.controller = controller;
    }

    public void run(){
        int opt = loginMenu();
        int userMenu = -1;

        if(opt == 1){
            String username = getUsername();
            String password = getPassword();

            if (username.equals(DAOconfig.USERNAME)) {
                if (password.equals(DAOconfig.PASSWORD)) {
                    userMenu = 0;
                } else {
                    return;
                }
            } else {
                userMenu = 1;
                try {
                    this.controller.loginUser(username, password);
                    System.out.println("\nLogin efetuado com sucesso!");
                } catch (NonExistentUsernameException e) {
                    System.out.println("Username doesn't exist!");
                    return;
                }
            }
        }
        else if (opt == 2){
            String username = getUsername();
            String password = getPassword();
            String country = getNationality();

            try{
                this.controller.addPlayer(username, password, country);
                userMenu = 1;
                System.out.println("\nRegisto efetuado com sucesso!");
            }
            catch (NonExistentUsernameException e){
                System.out.println("Username already registered!");
                return;
            }
        }

        if (userMenu == 0) {
            opt = -1;
            while (opt != 5) {
                opt = showAdminMenu();
                switch (opt) {
                    case 1 -> new PilotView(controller, sc).run(); // piloto
                    case 2 -> new CarView(controller, sc).run(); // carro
                    case 3 -> new CircuitView(controller, sc).run();
                    case 4 -> new ChampionshipView(controller, sc).run(); // compeonato
                }
            }
        } else if (userMenu == 1) {
            opt = -1;

            while (opt !=3) {
                opt = showChooseMode();

                switch (opt) {
                    case 1:
                        int classification = chooseClassification();
                        switch (classification) {
                            case 1:
                                showGlobalClassification(this.controller.getGlobalClassification());
                                break;

                            case 2:
                                String country = getCountry();
                                showCountryClassification(country, this.controller.getGlobalClassification(country));
                                break;

                            case 3:
                                String initDate = getInitialDate();
                                String finalDate = getFinalDate();
                                showDatesClassification(initDate, finalDate, this.controller.getGlobalClassification(initDate, finalDate));
                                break;

                            default:
                                break;
                        }
                        break;

                    case 2:
                        SimulationView sim = new SimulationView(controller, sc);
                        sim.run();
                        break;

                    default:
                        break;
                }
            }
        }
    }

    private int loginMenu(){
        System.out.println("\n=================================");
        System.out.println("          RACING MANAGER         ");
        System.out.println("=================================");
        System.out.println("1... Login\n2... Registar");
        System.out.println("=================================");

        int opt = sc.nextInt(); sc.nextLine();
        return opt;
    }

    public String getUsername(){
        System.out.print("Indique o username: ");
        return sc.nextLine();
    }

    public String getPassword(){
        System.out.print("Indique a password: ");
        return sc.nextLine();
    }

    public String getNationality(){
        System.out.print("Indique o país: ");
        return sc.nextLine();
    }

    private int showChooseMode() {
        System.out.println("\n=======================");
        System.out.println("1... Ver classificações");
        System.out.println("2... Jogar");
        System.out.println("3... Sair");
        System.out.println("=======================");

        int opt = sc.nextInt(); sc.nextLine();
        return opt;
    }

    private int showAdminMenu() {
        System.out.println("\n=======================");
        System.out.println("1... Criar Piloto");
        System.out.println("2... Criar Carro");
        System.out.println("3... Criar Circuito");
        System.out.println("4... Criar Campeonato");
        System.out.println("5... Sair");
        System.out.println("=======================");

        int opt = sc.nextInt(); sc.nextLine();
        return opt;
    }

    private int chooseClassification() {
        System.out.println("\n----------------------------");
        System.out.println("1... Classificação global");
        System.out.println("2... Classificação por país");
        System.out.println("3... Classificação por datas");
        System.out.println("----------------------------");

        System.out.print("Indique o tipo de classificação que pretende: ");
        int opt = sc.nextInt(); sc.nextLine();
        return opt;
    }

    private void showGlobalClassification(List<List<String>> classification) {
        int i=1;

        for (List<String> player : classification) {
            System.out.print(i + ". ");
            System.out.print(player.get(0) + " | ");
            System.out.println("Points: " + player.get(1));

            i++;
        }
    }

    private void showCountryClassification(String country, List<List<String>> classification) {
        System.out.println("--------------------------");
        System.out.println("País: " + country);
        System.out.println("--------------------------");
        showGlobalClassification(classification);
    }

    private void showDatesClassification(String initialDate, String finalDate, List<List<String>> classification) {
        System.out.println("---------------------------------------");
        System.out.println("De: " + initialDate + " a " + finalDate);
        System.out.println("---------------------------------------");
        showGlobalClassification(classification);
    }

    private String getCountry() {
        System.out.print("Indique o país: ");
        return sc.nextLine();
    }

    private String getInitialDate() {
        System.out.print("Indique a data inicial(YYYY-MM-DD): ");
        return sc.nextLine();
    }

    private String getFinalDate() {
        System.out.print("Indique a data final(YYYY-MM-DD): ");
        return sc.nextLine();
    }
}
