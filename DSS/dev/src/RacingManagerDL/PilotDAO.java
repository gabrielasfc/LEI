package RacingManagerDL;

import RacingManagerLN.Pilots.Pilot;

import java.sql.*;
import java.util.*;
import java.util.stream.Collectors;

public class PilotDAO implements Map<String, Pilot> {
    private static PilotDAO singleton = null;
    private PilotDAO(){

    }

    public static PilotDAO getInstance(){
        if (PilotDAO.singleton == null){
            PilotDAO.singleton = new PilotDAO();
        }
        return PilotDAO.singleton;
    }


    @Override
    public int size() {
        int size = 0;

        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("SELECT COUNT(*) FROM Pilot")) {

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
             PreparedStatement st = c.prepareStatement("SELECT pilotName FROM Pilot WHERE pilotName=?;")) {

            st.setString(1, key.toString());
            ResultSet rs = st.executeQuery();
            found = rs.next();

        } catch (SQLException e) {
            // Error establishing connection
            throw new RuntimeException(e);
        }

        return found;
    }

    @Override
    public boolean containsValue(Object value) {
        Pilot pilot = (Pilot) value;
        return this.containsKey(pilot.getName());
    }

    @Override
    public Pilot get(Object key) {
        Pilot pilot = null;

        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("SELECT * FROM Pilot WHERE pilotName=?;")) {

            st.setString(1, key.toString());
            ResultSet rs = st.executeQuery();
            if(rs.next()){
                pilot = new Pilot(rs.getString(1),
                                  rs.getFloat(2),
                                  rs.getFloat(3));
            }

        } catch (SQLException e) {
            // Error establishing connection
            throw new RuntimeException(e);
        }

        return pilot;
    }

    @Override
    public Pilot put(String key, Pilot value) {
        Pilot pilot = null;

        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("INSERT INTO Pilot (pilotName, cts, sva) VALUES(?,?,?)"
                                                         + "ON DUPLICATE KEY UPDATE cts=VALUES(cts),"
                                                                                 + "sva=VALUES(sva);")) {

            st.setString(1, value.getName());
            st.setFloat(2, value.getCts());
            st.setFloat(3, value.getSva());
            st.executeUpdate();

        } catch (SQLException e) {
            // Error establishing connection
            throw new RuntimeException(e);
        }

        return pilot;
    }

    @Override
    public Pilot remove(Object key) {
        Pilot pilot = this.get(key);

        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("DELETE FROM Pilot WHERE pilotName=?;")) {

            st.setString(1, key.toString());
            st.executeUpdate();

        } catch (SQLException e) {
            // Error establishing connection
            throw new RuntimeException(e);
        }

        return pilot;
    }

    @Override
    public void putAll(Map<? extends String, ? extends Pilot> pilots) {
        for(Pilot p : pilots.values()){
            this.put(p.getName(), p);
        }
    }

    @Override
    public void clear() {
        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("TRUNCATE Pilot;")) {

            st.executeUpdate();
        } catch (SQLException e) {
            // Error establishing connection
            throw new RuntimeException(e);
        }
    }

    @Override
    public Set<String> keySet() {
        Set<String> keys = new HashSet<String>();

        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("SELECT pilotName from PILOT;")) {

            ResultSet rs = st.executeQuery();

            while(rs.next()){
                keys.add(rs.getString(1));
            }

        } catch (SQLException e) {
            // Error establishing connection
            throw new RuntimeException(e);
        }

        return keys;
    }

    @Override
    public Collection<Pilot> values() {
        Collection<Pilot> pilots = new ArrayList<>();

        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("SELECT * FROM Pilot;")) {

            ResultSet rs = st.executeQuery();
            while(rs.next()){
                Pilot p = new Pilot(rs.getString(1), rs.getFloat(2), rs.getFloat(3));
                pilots.add(p);
            }

        } catch (SQLException e) {
            // Error establishing connection
            throw new RuntimeException(e);
        }

        return pilots;
    }

    @Override
    public Set<Entry<String, Pilot>> entrySet() {
        return this.values().stream().collect(Collectors.toMap(Pilot:: getName, x -> x)).entrySet();
    }
}