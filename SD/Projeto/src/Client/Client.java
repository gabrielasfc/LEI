package Client;

import Server.Position;
import Server.Reservation;
import Server.Reward;

import java.io.IOException;
import java.util.List;
import java.util.Scanner;
import static java.lang.Math.abs;

public class Client {
    public static void main(String[] args) throws IOException, InterruptedException {
        ScooterManager client = new ScooterManagerStub();

        Scanner sc = new Scanner(System.in);

        Client.loginMenu(sc, client);
        Client.showMenu(sc, client);

        client.close();
    }

    private static void showMenu(Scanner sc, ScooterManager c) throws IOException, InterruptedException {
        while (true){
            System.out.println("\n===================================");
            System.out.println("1... Mostrar trotinetes disponíveis");
            System.out.println("2... Mostrar recompensas");
            System.out.println("3... Reservar trotinete");
            System.out.println("4... Estacionar trotinete");
            System.out.println("5... Ativar notificações");
            System.out.println("6... Desativar notificações");
            System.out.println("===================================");

            int opt = sc.nextInt();

            switch (opt){
                case 1:
                    showScootersMenu(sc, c);
                    break;

                case 2:
                    showRewardsMenu(sc, c);
                    break;

                case 3:
                    activateScooterMenu(sc, c);
                    break;

                case 4:
                    parkScooterMenu(sc, c);
                    break;

                case 5:
                    turnOnNotificationsMenu(sc, c);
                    System.out.println("\nNotificações ativadas com sucesso!");
                    break;

                case 6:
                    c.turnOnOffNotifications(false, null);
                    System.out.println("\nNotificações desativadas com sucesso!");
                    break;

                default:
                    break;

            }
        }
    }

    private static boolean signUpMenu(Scanner sc, ScooterManager c) throws IOException, InterruptedException {
        System.out.print("Introduza o username: ");
        String username = sc.next();
        System.out.print("Introduza a password: ");
        String password = sc.next();

        boolean success = c.register(username, password);
        if (success == true){
            c.login(username, password);
            System.out.println("\nRegisto efetuado com sucesso!");
        }
        else {
            System.out.println("\nRegisto não efetuado!");
        }
        return success;
    }

    private static boolean signInMenu(Scanner sc, ScooterManager c) throws IOException, InterruptedException {
        System.out.print("Introduza o username: ");
        String username = sc.next();
        System.out.print("Introduza a password: ");
        String password = sc.next();

        boolean success = c.login(username, password);
        if (success == true){
            System.out.println("\nLogin efetuado com sucesso!");
        }
        else {
            System.out.println("\nLogin inválido!\n");
        }
        return success;
    }

    private static void loginMenu(Scanner sc, ScooterManager c) throws IOException, InterruptedException {
        boolean registered = false;
        boolean loggedIn = false;

        while (!registered && !loggedIn){
            System.out.println("===============");
            System.out.println("1... Registar");
            System.out.println("2... Autenticar");
            System.out.println("===============");

            int opt = sc.nextInt();

            if (opt == 1){
                registered = signUpMenu(sc, c);
            }

            if (opt == 2){
                loggedIn = signInMenu(sc, c);
            }
        }

    }

    private static void showScootersMenu(Scanner sc, ScooterManager c) throws IOException, InterruptedException {
        System.out.println("Indique a sua posição atual");
        System.out.print("x: ");
        int x = sc.nextInt();
        System.out.print("y: ");
        int y = sc.nextInt();

        Position p = new Position(x, y);
        List<Position> availScooters = c.listFreeScooters(p);

        System.out.println();
        if (availScooters.size() == 0){
            System.out.println("Nenhuma trotinete livre perto da posição " + p.toString());
        }
        for(Position pos: availScooters){
            System.out.println("Trotinete livre na posição " + pos.toString());
        }
    }

    private static void showRewardsMenu(Scanner sc, ScooterManager c) throws IOException, InterruptedException {
        System.out.println("Indique a sua posição atual");
        System.out.print("x: ");
        int x = sc.nextInt();
        System.out.print("y: ");
        int y = sc.nextInt();

        Position p = new Position(x, y);
        List<List<Position>> rewards = c.listRewards(p);

        if (rewards.size() == 0){
            System.out.print("\nNão há recompensas perto da posição " + p.toString());
        }

        System.out.println();
        for(List<Position> reward: rewards){
            System.out.println("Recompensa disponível de " + reward.get(0).toString() + " para " + reward.get(1).toString());
        }
    }

    private static int activateScooterMenu(Scanner sc, ScooterManager c) throws IOException, InterruptedException {
        System.out.println("Indique a sua posição atual");
        System.out.print("x: ");
        int x = sc.nextInt();
        System.out.print("y: ");
        int y = sc.nextInt();

        Position p = new Position(x, y);
        Reservation r = c.activateScooter(p);
        if (r != null){
            System.out.println("\nTrotinete na posição " + r.getInitialPosition().toString() + " reservada com sucesso!");
            System.out.println("Código de reserva atribuído: " + r.getReservationID());
            return r.getReservationID();
        }
        else{
            System.out.print("\nNão há trotinetes disponíveis perto da posição " + p.toString());
            return -1;
        }

    }

    private static void parkScooterMenu(Scanner sc, ScooterManager c) throws IOException, InterruptedException {
        System.out.print("Indique o código de reserva: ");
        int reservation = sc.nextInt();

        System.out.println("Indique a sua posição atual");
        System.out.print("x: ");
        int x = sc.nextInt();
        System.out.print("y: ");
        int y = sc.nextInt();

        double cost = c.parkScooter(new Position(x, y), reservation);

        if (cost > 0){
            System.out.println("\nPrémio da recompensa: " + cost + "€");
        }
        else if (cost < 0){
            System.out.println("\nCusto da viagem: " + abs(cost) + "€");
        }
    }

    private static void turnOnNotificationsMenu(Scanner sc, ScooterManager c){
        System.out.println("Indique a sua posição atual");
        System.out.print("x: ");
        int x = sc.nextInt();
        System.out.print("y: ");
        int y = sc.nextInt();

        c.turnOnOffNotifications(true, new Position(x, y));
        Thread t = new Thread(() -> {
            while(true){
                List<Reward> rewards = c.waitForNotifications();

                if (rewards == null)
                    break;

                System.out.println("\n--------------------------------------------");
                System.out.println("        Novas notificações recebidas        ");
                System.out.println("--------------------------------------------");

                for(int i=0; i<rewards.size(); i++){
                    String initPos = rewards.get(i).getInitialPosition().toString();
                    String finalPos = rewards.get(i).getFinalPosition().toString();
                    System.out.println("Recompensa disponível de " + initPos + " para " + finalPos);
                }
                System.out.println("--------------------------------------------\n");
            }
        });
        t.start();
    }
}