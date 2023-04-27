package RacingManagerUI;

import java.util.Scanner;

public class PilotView {
    private Controller controller;
    private Scanner sc;

    public PilotView(Controller sc, Scanner scanner) {
        this.controller = sc;
        this.sc = scanner;
    }

    public void run () {
        String name = getName();
        String defaultValues = defaultValues();

        if (defaultValues.equals("s") || defaultValues.equals("S")) {
            try{
                this.controller.addPilot(name);
                System.out.println("\nPiloto registado com sucesso!");
            }
            catch (Exception e){
                System.out.println(e.getMessage());
            }
        }
        else if (defaultValues.equals("n") || defaultValues.equals("N")) {
            float cts = getCTS();
            float sva = getSVA();

            try{
                this.controller.addPilot(name, cts, sva);
                System.out.println("\nPiloto registado com sucesso!");
            }
            catch (Exception e){
                System.out.println(e.getMessage());
            }

        }
    }

    private String defaultValues() {
        System.out.print("Pretende utilizar os valores default para os níveis de perícia?(s/n) ");
        return sc.nextLine();
    }

    private String getName() {
        System.out.print("Indique o nome do piloto: ");
        return sc.nextLine();
    }

    private Float getCTS() {
        System.out.print("Indique o nível de perícia no critério Chuva vs Tempo Seco: ");
        float cts = sc.nextFloat(); sc.nextLine();
        return cts;
    }

    private Float getSVA() {
        System.out.print("Indique o nível de perícia no critério Segurança vs Agressividade: ");
        float sva = sc.nextFloat(); sc.nextLine();
        return sva;
    }
}
