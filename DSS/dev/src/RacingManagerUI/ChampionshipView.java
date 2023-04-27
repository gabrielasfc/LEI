package RacingManagerUI;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.ExecutionException;

public class ChampionshipView {
    private Controller controller;
    private Scanner sc;

    public ChampionshipView(Controller sc, Scanner scanner) {
        this.controller = sc;
        this.sc = scanner;
    }

    public void run() {
        List<List<String>> circuits = this.controller.showAllCircuits();

        String championship = getChampionshipName();
        showCircuits(circuits);

        int maxPlayers = getMaxPlayers();
        int mode = getMode();

        List<String> chosen = null;
        if (mode == 1){
            chosen = getCircuits(circuits);
        }
        else if (mode == 2) {
            int numCircuits = getNumCircuits();
            chosen = this.controller.generateCircuits(numCircuits);
        }

        try{
            this.controller.addChampionship(championship, chosen, maxPlayers);
            System.out.println("Campeonato criado com sucesso!");
        }
        catch (Exception e){
            System.out.println(e.getMessage());
        }

    }

    private String getChampionshipName() {
        System.out.print("Indique o nome do campeonato: ");
        return sc.nextLine();
    }

    private int getMaxPlayers(){
        System.out.print("Indique o número máximo de jogadores: ");
        int max = sc.nextInt(); sc.nextLine();
        return max;
    }

    private int getNumCircuits(){
        System.out.print("Indique o número de circuitos: ");
        int num = sc.nextInt(); sc.nextLine();
        return num;
    }

    private List<String> getCircuits(List<List<String>> circuits){
        List<String> chosen = new ArrayList<>();

        System.out.println("Escolha os circuitos: ");
        System.out.println("0... Guardar");

        int opt = -1;
        while(opt != 0){
            opt = sc.nextInt(); sc.nextLine();
            if (opt > 0){
                chosen.add(circuits.get(opt-1).get(0));
                System.out.println("Circuito " + circuits.get(opt-1).get(0) + " guardado com sucesso!");
            }
        }

        return chosen;
    }



    private int getMode(){
        System.out.println("\n-----------------------------------");
        System.out.println("1... Escolher ordenadamente");
        System.out.println("2... Escolher aleatorimente");
        System.out.println("-----------------------------------");

        int mode = sc.nextInt(); sc.nextLine();

        return mode;
    }

    public void showCircuits(List<List<String>> circuits){
        int i = 1;
        System.out.println("\n-----------------------------------");

        for (List<String> circuit : circuits){
            System.out.print(i + "... ");
            System.out.print(circuit.get(0) + " | Voltas : ");
            System.out.print(circuit.get(1) + " | Tamanho : ");
            System.out.print(circuit.get(2) + " km | Retas : ");
            System.out.print(circuit.get(3) + " | Curvas : ");
            System.out.print(circuit.get(4) + " | Chicanes : ");
            System.out.println(circuit.get(5));

            i++;
        }

        System.out.println("\n-----------------------------------");
    }
}
