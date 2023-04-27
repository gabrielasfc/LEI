package Tests;

import Server.Position;
import Server.Reservation;
import Server.ScooterManagerI;

import java.util.Random;

public class RandomizeRequest {
    ScooterManagerI sm;

    public RandomizeRequest(ScooterManagerI sm){
        this.sm = sm;
    }
    public void doStuff(){
        Random r = new Random();
        int x = r.nextInt(5);

        switch(x){
            case 0: // Login
                System.out.println(Thread.currentThread().getName() + " log in");
                try {
                    sm.login(Thread.currentThread().getName(), "password123");
                } catch (Exception e) {
                    // Ignore
                }
                break;
            case 1: // Register
                System.out.println(Thread.currentThread().getName() + " register");
                try {
                    sm.register(Thread.currentThread().getName(), "password123");
                } catch (Exception e) {
                    // Ignore
                }
                break;
            case 2: // Show rewards
                System.out.println(Thread.currentThread().getName() + " show rewards");
                try {
                    sm.register(Thread.currentThread().getName(), "password123");
                    sm.login(Thread.currentThread().getName(), "password123");
                } catch (Exception e) {
                    // Ignore
                }
                sm.listRewards(new Position(3,3));
                break;
            case 3: // Show scooters
                System.out.println(Thread.currentThread().getName() + " show scooters");
                try {
                    sm.register(Thread.currentThread().getName(), "password123");
                    sm.login(Thread.currentThread().getName(), "password123");
                } catch (Exception e) {
                    // Ignore
                }
                try {
                    sm.listFreeScooters(new Position(3,3));
                } catch (Exception e) {
                    // Ignore
                }
                break;
            case 4: // Activate scooter
                System.out.println(Thread.currentThread().getName() + " activate scooter");
                try {
                    sm.register(Thread.currentThread().getName(), "password123");
                    sm.login(Thread.currentThread().getName(), "password123");
                } catch (Exception e) {
                    // Ignore
                }
                try {
                    Reservation res = sm.activateScooter(new Position(3,3), Thread.currentThread().getName());
                    //Thread.sleep(1000);
                    sm.parkScooter(res.getReservationID(), new Position(5,5));
                } catch (Exception e) {
                    // Ignore
                }
                break;
            default:
                break;
            /*case 5: // Park scooter
                try {
                    sm.register(Thread.currentThread().getName(), "password123");
                    sm.login(Thread.currentThread().getName(), "password123");
                } catch (Exception e) {
                    // Ignore
                }

                break;*/

        }
        System.out.println(Thread.currentThread().getName() + " terminou! " + x);
    }
}
