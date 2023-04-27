package RacingManagerDL;

import RacingManagerLN.Users.Player;

import java.sql.*;
import java.util.*;
import java.util.stream.Collectors;

public class PlayerDAO implements Map<String, Player> {
    private static PlayerDAO singleton = null;

    private PlayerDAO() {}

    public static PlayerDAO getInstance() {
        if (PlayerDAO.singleton == null) {
            PlayerDAO.singleton = new PlayerDAO();
        }

        return PlayerDAO.singleton;
    }

    @Override
    public int size() {
        int size = 0;

        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("SELECT COUNT(*) FROM Player;")) {

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
             PreparedStatement st = c.prepareStatement("SELECT playerUsername FROM Player WHERE playerUsername=?;")) {

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
        Player p = (Player) value;
        return p.equals(get(p.getUsername()));
    }

    @Override
    public Player get(Object key) {
        Player p = null;

        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("SELECT * FROM Player WHERE playerUsername=?;")) {

            st.setString(1, key.toString());
            ResultSet rs = st.executeQuery();
            if (rs.next()) {
                p = new Player(rs.getString(1),
                               rs.getString(2),
                                  rs.getInt(3),
                               rs.getString(4));
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return p;
    }

    @Override
    public Player put(String key, Player p) {
        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("INSERT INTO Player (playerUsername, playerPassword, points, country) VALUES(?,?,?,?)"
                                                         + "ON DUPLICATE KEY UPDATE playerPassword=VALUES(playerPassword),"
                                                                                 + "points=VALUES(points),"
                                                                                 + "country=VALUES(country);")) {

            st.setString(1, p.getUsername());
            st.setString(2, p.getPassword());
            st.setInt(3, p.getPoints());
            st.setString(4, p.getCountry());
            st.executeUpdate();

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return p;
    }

    @Override
    public Player remove(Object key) {
        Player p = this.get(key);

        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("DELETE FROM Player WHERE playerUsername=?;")) {

            st.setString(1, key.toString());
            st.executeUpdate();

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return p;
    }

    @Override
    public void putAll(Map<? extends String, ? extends Player> players) {
        for (Player p : players.values()) {
            this.put(p.getUsername(), p);
        }
    }

    @Override
    public void clear() {
        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("TRUNCATE Player;")) {

            st.executeUpdate();

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Set<String> keySet() {
        Set<String> keys = new HashSet<String>();

        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("SELECT playerUsername FROM Player;")) {

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
    public Collection<Player> values() {
        Collection<Player> players = new ArrayList<>();

        try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement st = c.prepareStatement("SELECT * FROM Player;")) {

            ResultSet rs = st.executeQuery();
            while (rs.next()) {
                Player p = new Player(rs.getString(1), rs.getString(2), rs.getInt(3), rs.getString(4));
                players.add(p);
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        return players;
    }

    @Override
    public Set<Entry<String, Player>> entrySet() {
        return this.values().stream().collect(Collectors.toMap(Player :: getUsername, x -> x)).entrySet();
    }
}