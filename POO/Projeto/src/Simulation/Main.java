package src.Simulation;

import src.Community.Community;

import java.util.Scanner;

/**
 * Classe principal do programa - padrão MVC
 */
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Community community = new Community();
        CommunityController controller = new CommunityController(community);
        ClientView view = new ClientView(controller, sc);

        view.run();
    }
}
