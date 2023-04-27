package RacingManagerDL;

import RacingManagerLN.Championships.Championship;
import RacingManagerLN.Circuits.*;

import java.sql.*;
import java.util.*;
import java.util.stream.Collectors;

public class ChampionshipDAO implements Map<String, Championship> {
    private static ChampionshipDAO singleton = null;

    private ChampionshipDAO() {}

    public static ChampionshipDAO getInstance() {
        if (ChampionshipDAO.singleton == null) {
            ChampionshipDAO.singleton = new ChampionshipDAO();
        }

        return ChampionshipDAO.singleton;
    }

    @Override
    public int size() {
        int size = 0;

        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("SELECT COUNT(*) FROM Championship;")) {
            ResultSet rs = st.executeQuery();
            if (rs.next()) {
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
        boolean found = false;

        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("SELECT championshipName from Championship WHERE championshipName=?;")) {

            st.setString(1, key.toString());
            ResultSet rs = st.executeQuery();
            found = rs.next();

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return found;
    }

    @Override
    public boolean containsValue(Object value) {
        Championship c = (Championship) value;
        return c.equals(get(c.getName()));
    }

    /**
     *
     * @param key the key whose associated value is to be returned
     * @return
     */
    @Override
    public Championship get(Object key) {
        String champName = (String)key;
        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st1 = c.prepareStatement("SELECT * FROM Championship WHERE championshipName=?;");
             PreparedStatement st2 = c.prepareStatement("SELECT circuitName FROM ChampionshipCircuit WHERE championshipName=?;")){

             st1.setString(1, champName);
             st2.setString(1, champName);
             ResultSet rs = st1.executeQuery();
             Championship champ = null;
             CircuitDAO circDAO = CircuitDAO.getInstance();
             List<Circuit> circuits = new ArrayList<>();
             int maxPlayers=0;
             if (rs.next()){
                 maxPlayers = rs.getInt(2);
                 ResultSet rs2 = st2.executeQuery();

                 while(rs2.next()){
                     String circuitName = rs2.getString(1);
                     Circuit circuit = circDAO.get(circuitName);
                     circuits.add(circuit);
                 }
             }
            champ = new Championship(maxPlayers, (String)key, circuits);
            return champ;
        } catch (SQLException e) {
            // Error establishing connection
            throw new RuntimeException(e);
        }
    }

    @Override
    public Championship put(String key, Championship value) {
        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("INSERT INTO Championship (championshipName, maxPlayers) VALUES (?,?);");
             PreparedStatement st1 = c.prepareStatement("INSERT INTO ChampionshipCircuit (championshipName,circuitName) VALUES (?,?);")) {

            st.setString(1, key);
            st.setInt(2, value.getMaxPlayers());
            st.executeUpdate();

            for (Circuit circuit : value.getCircuits()) {
                st1.setString(1,key);
                st1.setString(2,circuit.getName());
                st1.executeUpdate();
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return value;
    }

    @Override
    public Championship remove(Object key) {
        Championship champ = this.get(key);

        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("DELETE FROM Championship WHERE championshipName=?;")) {

            st.setString(1, key.toString());
            st.executeUpdate();

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return champ;
    }

    @Override
    public void putAll(Map<? extends String, ? extends Championship> championships) {
        for (Championship c : championships.values()) {
            this.put(c.getName(), c);
        }
    }

    @Override
    public void clear() {
        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("TRUNCATE Championship;")) {

            st.executeUpdate();

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Set<String> keySet() {
        Set<String> keys = new HashSet<String>();

        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("SELECT championshipName FROM Championship;")) {

            ResultSet rs = st.executeQuery();
            while (rs.next()) {
                keys.add(rs.getString(1));
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return keys;
    }

    @Override
    public Collection<Championship> values() {
        Collection<Championship> championships = new ArrayList<>();

        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("SELECT * FROM Championship;")) {

            ResultSet rs = st.executeQuery();

            while (rs.next()){
                Championship champ = new Championship(rs.getInt(2), rs.getString(1));
                championships.add(champ);
            }

        } catch (SQLException e) {
            // Error establishing connection
            throw new RuntimeException(e);
        }

        return championships;
    }

    @Override
    public Set<Entry<String, Championship>> entrySet() {
        return this.values().stream().collect(Collectors.toMap(Championship :: getName, x -> x)).entrySet();
    }
}