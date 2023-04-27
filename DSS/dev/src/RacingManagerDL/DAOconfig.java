package RacingManagerDL;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

public class DAOconfig {
    public static final String USERNAME = "admin";                       // Actualizar
    public static final String PASSWORD = "admin123";                       // Actualizar
    private static final String DATABASE = "RacingManager";          // Actualizar
    private static final String DRIVER = "jdbc:mariadb";        // Usar para MariaDB
    //private static final String DRIVER = "jdbc:mysql";        // Usar para MySQL
    public static final String URL = DRIVER+"://localhost/"+DATABASE;

    public static void createDB(){
        try {
            Connection c = DriverManager.getConnection(DRIVER+"://localhost/", DAOconfig.USERNAME, DAOconfig.PASSWORD);
            String sql = "CREATE DATABASE IF NOT EXISTS RacingManager;";
            Statement st = c.createStatement();
            st.executeUpdate(sql);

            c = DriverManager.getConnection(DRIVER+"://localhost/" + DATABASE, DAOconfig.USERNAME, DAOconfig.PASSWORD);
            Statement st2 = c.createStatement();
            sql =  "CREATE TABLE IF NOT EXISTS Player (\n" +
                    "  playerUsername VARCHAR(75) NOT NULL,\n" +
                    "  playerPassword VARCHAR(75) NOT NULL,\n" +
                    "  points INT NOT NULL,\n" +
                    "  country VARCHAR(75) NOT NULL,\n" +
                    "  PRIMARY KEY (playerUsername)\n" +
                    ");\n";

            st2.executeUpdate(sql);
            sql =  "CREATE TABLE IF NOT EXISTS Pilot (\n" +
                    "\tpilotName VARCHAR(75) NOT NULL,\n" +
                    "    cts DECIMAL(3,2) NOT NULL,\n" +
                    "    sva DECIMAL(3,2) NOT NULL,\n" +
                    "    PRIMARY KEY(pilotName)\n" +
                    ");\n";
            st2.executeUpdate(sql);
            sql =   "CREATE TABLE IF NOT EXISTS Car(\n" +
                    "\tidCar INT NOT NULL AUTO_INCREMENT,\n" +
                    "    model VARCHAR(75) NOT NULL,\n" +
                    "    brand VARCHAR(75) NOT NULL,\n" +
                    "    pac DECIMAL(3,2) NOT NULL,\n" +
                    "    horsePower INT NOT NULL,\n" +
                    "    engineCapacity INT NOT NULL,\n" +
                    "    reliability DECIMAL (3,2) NOT NULL,\n" +
                    "    tireType INT NOT NULL DEFAULT 1, -- 0 - HARD, 1 - SOFT, 2 - RAIN\n" +
                    "    engineMode INT NOT NULL DEFAULT 0, -- 0 - NORMAL, 1 - AGGRESSIVE, 2 - CONSERVATIVE\n" +
                    "    carType INT NOT NULL, -- type of car (0 - C1, 1 - C2, 2 - GT, 3 - SC, 4 - ElectricC1, 5 - ElectricC2, 6 - ElectricGT),\n" +
                    "    tireState DECIMAL(5,2) NOT NULL DEFAULT 100.00,\n" +
                    "    PRIMARY KEY(idCar)\n" +
                    ");\n";
            st2.executeUpdate(sql);
            sql =   "CREATE TABLE IF NOT EXISTS ElectricCar(\n" +
                    "\tidCar INT NOT NULL,\n" +
                    "    electricPower INT NOT NULL,\n" +
                    "    PRIMARY KEY(idCar),\n" +
                    "    FOREIGN KEY(idCar) REFERENCES Car(idCar)\n" +
                    ");\n";
            st2.executeUpdate(sql);
            sql =   "CREATE TABLE IF NOT EXISTS Circuit (\n" +
                    "  circuitName VARCHAR(75) NOT NULL,\n" +
                    "  circuitLength FLOAT NOT NULL,\n" +
                    "  numLaps INT NOT NULL,\n" +
                    "  PRIMARY KEY (circuitName)\n" +
                    ");\n";
            st2.executeUpdate(sql);
            sql =   "CREATE TABLE IF NOT EXISTS Championship (\n" +
                    "  championshipName VARCHAR(75) NOT NULL,\n" +
                    "  maxPlayers INT NOT NULL,\n" +
                    "  PRIMARY KEY (championshipName)\n" +
                    ");\n";
            st2.executeUpdate(sql);
            sql =   "CREATE TABLE IF NOT EXISTS Sector (\n" +
                    "  sectorType INT NOT NULL, -- 0 - Curve, 1 - Straight, 2 - Chicane \n" +
                    "  gdu INT NOT NULL, -- 0 - POSSIBLE, 1 - HARD, 2 - IMPOSSIBLE\n" +
                    "  circuitName VARCHAR(75) NOT NULL,\n" +
                    "  numSector INT NOT NULL,\n" +
                    "  PRIMARY KEY (numSector, circuitName),\n" +
                    "  FOREIGN KEY (circuitName) REFERENCES Circuit(circuitName)\n" +
                    ");\n";
            st2.executeUpdate(sql);
            sql =   "CREATE TABLE IF NOT EXISTS Simulation (\n" +
                    "  simulationName VARCHAR(75) NOT NULL,\n" +
                    "  initialDate DATE NOT NULL,\n" +
                    "  endDate DATE,\n" +
                    "  maxPlayers INT NOT NULL,\n" +
                    "  championshipName VARCHAR(75) NOT NULL,\n" +
                    "  currentRace INT NOT NULL DEFAULT 0, \n" +
                    "  PRIMARY KEY (simulationName),\n" +
                    "  FOREIGN KEY (championshipName) \n" +
                    "  REFERENCES Championship(championshipName)\n" +
                    ");\n";
            st2.executeUpdate(sql);
            sql =   "CREATE TABLE IF NOT EXISTS ChampionshipCircuit (\n" +
                    "  championshipName VARCHAR(75) NOT NULL,\n" +
                    "  circuitName VARCHAR(75) NOT NULL,\n" +
                    "  PRIMARY KEY (championshipName, circuitName),\n" +
                    "  FOREIGN KEY (championshipName) \n" +
                    "  REFERENCES Championship(championshipName),\n" +
                    "  FOREIGN KEY (circuitName) \n" +
                    "  REFERENCES Circuit(circuitName)\n" +
                    ");\n";
            st2.executeUpdate(sql);
            sql =   "CREATE TABLE IF NOT EXISTS Record (\n" +
                    "\tplayerUsername VARCHAR(75) NOT NULL,\n" +
                    "\tscore INT NOT NULL,\n" +
                    "\tnumAdjAvailable INT NOT NULL,\n" +
                    "\tidCar INT NOT NULL,\n" +
                    "\tpilotName VARCHAR(75) NOT NULL,\n" +
                    "\tsimulationName VARCHAR(75) NOT NULL,\n" +
                    "\tPRIMARY KEY (playerUsername, simulationName),\n" +
                    "\tFOREIGN KEY (playerUsername) \n" +
                    "    REFERENCES Player(playerUsername),\n" +
                    "    FOREIGN KEY (simulationName) \n" +
                    "    REFERENCES Simulation(simulationName),\n" +
                    "    FOREIGN KEY (idCar) \n" +
                    "    REFERENCES Car(idCar),\n" +
                    "    FOREIGN KEY (pilotName) \n" +
                    "    REFERENCES Pilot(pilotName)\n" +
                    ");\n";
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
