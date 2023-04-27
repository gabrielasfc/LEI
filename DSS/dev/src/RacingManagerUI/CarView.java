package RacingManagerUI;

import RacingManagerLN.Exceptions.InvalidPacException;

import java.util.Scanner;

public class CarView {
    private Controller controller;
    private Scanner sc;

    public CarView(Controller sc, Scanner scanner) {
        this.controller = sc;
        this.sc = scanner;
    }

    public void run () {
        showCars();
        int type = getCarType();

        switch (type) {
            case 1:
                createC1();
                System.out.println("\nCarro registado com sucesso!");
                break;

            case 2:
                createC2();
                System.out.println("\nCarro registado com sucesso!");
                break;

            case 3:
                createSC();
                System.out.println("\nCarro registado com sucesso!");
                break;

            case 4:
                createGT();
                System.out.println("\nCarro registado com sucesso!");
                break;

            default:
                break;
        }

    }

    private void showCars() {
        System.out.println("------------------------");
        System.out.println("1... C1\n2... C2\n3... SC\n4... GT");
        System.out.println("------------------------");
    }

    private int getCarType() {
        System.out.print("Indique o número do tipo de carro que pretende criar: ");
        int car = sc.nextInt(); sc.nextLine();
        return car;
    }

    private String getBrand() {
        System.out.print("Indique a marca do carro: ");
        return sc.nextLine();
    }

    private String getModel() {
        System.out.print("Indique o modelo do carro: ");
        return sc.nextLine();
    }

    private int getPower() {
        System.out.print("Indique a potência do carro: ");
        int power = sc.nextInt(); sc.nextLine();
        return power;
    }

    private float getReliability() {
        System.out.print("Indique a fiabilidade do carro: ");
        float reliability = sc.nextFloat(); sc.nextLine();
        return reliability;
    }

    private int getElectricPower() {
        System.out.print("Indique a potência do motor elétrico do carro: ");
        int electricPower = sc.nextInt(); sc.nextLine();
        return electricPower;
    }

    private int getHybrid() {
        int electricPower = 0;

        System.out.print("Pretende que o carro seja híbrido?(s/n)");
        String hybrid = sc.nextLine();

        if (hybrid.equals("s") || hybrid.equals("S")) {
            electricPower = getElectricPower();
        }

        return electricPower;
    }

    private float getPAC() {
        System.out.print("Indique o PAC do carro: ");
        float pac = sc.nextFloat(); sc.nextLine();
        return pac;
    }

    private int getEngineCapacity() {
        System.out.print("Indique a cilindrada do carro: ");
        int engineCapacity = sc.nextInt(); sc.nextLine();
        return engineCapacity;
    }

    private void createC1() {
        String brand = getBrand();
        String model = getModel();
        int power = getPower();
        float reliability = getReliability();
        int electricPower = getHybrid();
        float pac = getPAC();

        try{
            this.controller.addC1(brand, model, power, reliability, pac, electricPower);
        }
        catch (Exception e){
            System.out.println(e.getMessage());
        }

    }

    private void createC2() {
        String brand = getBrand();
        String model = getModel();
        int engineCapacity = getEngineCapacity();
        int power = getPower();
        int electricPower = getHybrid();
        float pac = getPAC();

        try{
            this.controller.addC2(brand, model, power, engineCapacity, pac, electricPower);
        }
        catch (Exception e){
            System.out.println(e.getMessage());
        }
    }

    private void createSC() {
        String brand = getBrand();
        String model = getModel();
        int power = getPower();
        float pac = getPAC();

        try{
            this.controller.addSC(brand, model, power, pac);
        }
        catch (Exception e){
            System.out.println(e.getMessage());
        }
    }

    private void createGT() {
        String brand = getBrand();
        String model = getModel();
        int engineCapacity = getEngineCapacity();
        int power = getPower();
        int electricPower = getHybrid();
        float pac = getPAC();

        try{
            this.controller.addGT(brand, model, power, engineCapacity, pac, electricPower);
        }
        catch (Exception e){
            System.out.println(e.getMessage());
        }
    }

}
