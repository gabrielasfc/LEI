package RacingManagerDL;

import RacingManagerLN.Cars.*;
import RacingManagerLN.Circuits.Circuit;
import RacingManagerLN.Pilots.Pilot;
import RacingManagerLN.Simulations.Record;
import RacingManagerLN.Simulations.Simulation;

import java.sql.*;
import java.time.LocalDate;
import java.util.*;
import java.sql.Date;

public class SimulationDAO implements Map<String, Simulation> {
    private static SimulationDAO singleton= null;

    private SimulationDAO() {

    }

    public static SimulationDAO getInstance() {
        if (SimulationDAO.singleton == null ) {
            SimulationDAO.singleton = new SimulationDAO();
        }
        return SimulationDAO.singleton;
    }


    @Override
    public int size() {
        int size = 0;
        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("SELECT COUNT(*) FROM Simulation")){

            ResultSet rs = st.executeQuery();
            if (rs.next()){
                size = rs.getInt(1);
            }

        } catch (SQLException e) {
            // Error establishing connection
            throw new RuntimeException(e);
        }

        return size;
    }

    @Override
    public boolean isEmpty() {
        return this.size() == 0;
    }

    @Override
    public boolean containsKey(Object key) {
        return this.get(key) != null;
    }

    @Override
    public boolean containsValue(Object value) {
        return false;
    }

    @Override
    public Simulation get(Object key) {
        Simulation sim = null;
        String simName = (String)key;
        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st1 = c.prepareStatement("SELECT * FROM Simulation WHERE simulationName=?;")){

            st1.setString(1, simName);
            ResultSet rs = st1.executeQuery();

            if (rs.next()){
                List<Record> records = new ArrayList<>();
                List<Circuit> circuits = new ArrayList<>();

                String name = rs.getString(1);
                LocalDate initialDate = rs.getDate(2).toLocalDate();
                LocalDate endDate = null;
                if (rs.getDate(3) != null){
                    endDate = rs.getDate(3).toLocalDate();
                }
                int maxPlayers = rs.getInt(4);
                String champName = rs.getString(5);
                int currentRace = rs.getInt(6);

                PreparedStatement st2 = c.prepareStatement("SELECT * FROM Record WHERE simulationName=?");
                st2.setString(1, simName);
                ResultSet rs2 = st2.executeQuery();

                while (rs2.next()){
                    String username = rs2.getString(1);
                    int score = rs2.getInt(2);
                    int numAdjAvailable = rs2.getInt(3);
                    int carId = rs2.getInt(4);
                    String pilotName = rs2.getString(5);
                    Car car = null;
                    Pilot pilot = null;

                    PreparedStatement st3 = c.prepareStatement("SELECT * FROM Car WHERE idCar=?");
                    st3.setInt(1, carId);
                    ResultSet rs3 = st3.executeQuery();

                    if (rs3.next()){
                        int idCar = rs3.getInt(1);
                        String model = rs3.getString(2);
                        String brand = rs3.getString(3);
                        float pac = rs3.getFloat(4);
                        int horsePower = rs3.getInt(5);
                        int engineCapacity = rs3.getInt(6);
                        float reliability = rs3.getFloat(7);
                        int type = rs3.getInt(10);
                        float tireState = rs3.getFloat(11);
                        int electricPower = -1;

                        TireType tType = null;
                        switch (rs3.getInt(8)){
                            case 0: tType = TireType.HARD;
                            case 1: tType = TireType.SOFT;
                            case 2: tType = TireType.RAIN;
                        }

                        EngineMode eMode = null;
                        switch (rs3.getInt(9)){
                            case 0: eMode = EngineMode.NORMAL;
                            case 1: eMode = EngineMode.AGGRESSIVE;
                            case 2: eMode = EngineMode.CONSERVATIVE;
                        }

                        if(type >= 4 && type <= 6){
                            PreparedStatement st4 = c.prepareStatement("SELECT * FROM ElectricCar WHERE idCar=?");
                            st4.setInt(1, idCar);

                            ResultSet rs4 = st4.executeQuery();

                            if(rs4.next()){
                                electricPower = rs4.getInt(2);
                            }
                        }

                        switch(type){
                            case 0:
                                car = new C1(idCar, brand, model, horsePower, engineCapacity, reliability, pac, tType, eMode, tireState);
                            case 1:
                                car = new C2(idCar, brand, model, horsePower, engineCapacity, reliability, pac, tType, eMode, tireState);
                            case 2:
                                car = new GT(idCar, brand, model, horsePower, engineCapacity, reliability, pac, tType, eMode, tireState);
                            case 3:
                                car = new SC(idCar, brand, model, horsePower, reliability, pac, tType, eMode, tireState);
                            case 4:
                                car = new HybridC1(idCar, brand, model, horsePower, engineCapacity, reliability,
                                        pac, tType, eMode, tireState, electricPower);
                            case 5:
                                car = new HybridC2(idCar, brand, model, horsePower, engineCapacity, reliability,
                                        pac, tType, eMode, tireState, electricPower);
                            case 6:
                                car = new HybridGT(idCar, brand, model, horsePower, engineCapacity, reliability,
                                        pac, tType, eMode, tireState, electricPower);

                        }
                    }

                    PreparedStatement st5 = c.prepareStatement("SELECT * FROM Pilot WHERE pilotName=?");
                    st5.setString(1, pilotName);
                    ResultSet rs5 = st5.executeQuery();

                    if (rs5.next()){ // name, cts, sva
                        String namePilot = rs5.getString(1);
                        float cts = rs5.getFloat(2);
                        float sva = rs5.getFloat(3);
                        pilot = new Pilot(namePilot, cts, sva);
                    }

                    records.add(new Record(car, pilot, username, numAdjAvailable, score));
                }

                PreparedStatement st6 = c.prepareStatement("SELECT * FROM ChampionshipCircuit WHERE championshipName=?");
                st6.setString(1, champName);
                ResultSet rs6 = st6.executeQuery();

                while (rs6.next()){
                    String circName = rs6.getString(2);
                    CircuitDAO circuitDAO = CircuitDAO.getInstance();
                    Circuit circuit = circuitDAO.get(circName);
                    circuits.add(circuit);
                }

                sim = new Simulation(name, maxPlayers, initialDate, endDate, champName, circuits, records, currentRace);
            }

        } catch (SQLException e) {
            // Error establishing connection
            throw new RuntimeException(e);
        }

        return sim;
    }

    @Override
    public Simulation put(String key, Simulation value) {
        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("INSERT INTO Simulation (simulationName, initialDate, endDate, maxPlayers, championshipName, currentRace) VALUES (?,?,?,?,?,?) "
                                                         + "ON DUPLICATE KEY UPDATE simulationName=VALUES(simulationName), "
                                                                                 + "initialDate=VALUES(initialDate), "
                                                                                 + "endDate=VALUES(endDate), "
                                                                                 + "maxPlayers=VALUES(maxPlayers), "
                                                                                 + "championshipName=VALUES(championshipName), "
                                                                                 + "currentRace=VALUES(currentRace);")){

            st.setString(1, value.getName());
            st.setDate(2, Date.valueOf(value.getInitialDate()));
            if(value.getEndDate() != null){
                st.setDate(3, Date.valueOf(value.getEndDate()));
            } else {
                st.setDate(3, null);
            }
            st.setInt(4, value.getMaxPlayers());
            st.setString(5, value.getChampionshipName());
            st.setInt(6, value.getCurrentRace());

            st.executeUpdate();

            for(Record record : value.getRecords().values()){
                PreparedStatement st1 = c.prepareStatement("INSERT INTO Record (playerUsername, score, numAdjAvailable, idCar, pilotName, simulationName) VALUES (?,?,?,?,?,?) "
                                                             + "ON DUPLICATE KEY UPDATE playerUsername=VALUES(playerUsername), "
                                                                                     + "score=VALUES(score), "
                                                                                     + "numAdjAvailable=VALUES(numAdjAvailable), "
                                                                                     + "idCar=VALUES(idCar), "
                                                                                     + "pilotName=VALUES(pilotName), "
                                                                                     + "simulationName=VALUES(simulationName);");
                st1.setString(1, record.getUserName());
                st1.setInt(2, record.getScore());
                st1.setInt(3, record.getNumAdjAvailable());
                st1.setInt(4, record.getCar().getCarId());
                st1.setString(5, record.getPilot().getName());
                st1.setString(6, value.getName());

                st1.executeUpdate();
            }

            return value;
        } catch (SQLException e) {
            // Error establishing connection
            throw new RuntimeException(e);
        }
    }

    @Override
    public Simulation remove(Object key) {
        return null;
    }

    @Override
    public void putAll(Map<? extends String, ? extends Simulation> m) {

    }

    @Override
    public void clear() {

    }

    @Override
    public Set<String> keySet() {
        return null;
    }

    /**
     * Collects all the simulations stored in a collection
     * @return a collection of all the simulations stored
     */
    @Override
    public Collection<Simulation> values() {
        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD); Statement st = c.createStatement();){
            String sql = "SELECT simulationName FROM Simulation";
            ResultSet rs = st.executeQuery(sql);
            Collection<Simulation> simulations = new ArrayList<>();


            while (rs.next()){
                Simulation s = this.get(rs.getString("simulationName"));
                simulations.add(s);
            }

            return simulations;
        } catch (SQLException e) {
            // Error establishing connection
            throw new RuntimeException(e);
        }
    }

    @Override
    public Set<Entry<String, Simulation>> entrySet() {
        return null;
    }
}
