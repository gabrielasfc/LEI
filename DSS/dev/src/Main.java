import RacingManagerLN.*;
import RacingManagerUI.Controller;
import RacingManagerUI.MainView;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        IRacingManagerLN facade = new RacingManagerLN();
        Controller controller = new Controller(facade);

        MainView view = new MainView(controller, sc);
        view.run();
    }
}
