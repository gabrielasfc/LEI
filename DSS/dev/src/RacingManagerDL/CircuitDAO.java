package RacingManagerDL;

import RacingManagerLN.Circuits.*;

import java.sql.*;
import java.util.*;
import java.util.stream.Collectors;

public class CircuitDAO implements Map<String, Circuit> {
	public static CircuitDAO singleton = null;

	public static CircuitDAO getInstance() {
		if (CircuitDAO.singleton == null) {
			CircuitDAO.singleton = new CircuitDAO();
		}
		return CircuitDAO.singleton;
	}

	private CircuitDAO(){

	}

	@Override
	public int size() {
		int size = 0;

		try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 PreparedStatement st = c.prepareStatement("SELECT COUNT(*) FROM Circuit")) {

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
		return this.size()==0;
	}

	@Override
	public boolean containsKey(Object key) {
		boolean found = false;

		try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 PreparedStatement st = c.prepareStatement("SELECT circuitName FROM Circuit WHERE circuitName=?;")) {

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
		Circuit circuit = (Circuit) value;
		return circuit.equals(get(circuit.getName()));
	}

	@Override
	public Circuit get(Object key) {
		Circuit circuit = null;

		try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 PreparedStatement st1 = c.prepareStatement("SELECT * FROM Circuit WHERE circuitName=?;");
			 PreparedStatement st2 = c.prepareStatement("SELECT * FROM Sector WHERE circuitName=?;")) {

			st1.setString(1, key.toString());
			ResultSet rs1 = st1.executeQuery();
			st2.setString(1, key.toString());
			ResultSet rs2 = st2.executeQuery();

			List<Sector> sectors = new ArrayList<>();
			while (rs2.next()) {
				int sectorType = rs2.getInt(1);
				int gdu = rs2.getInt(2);
				GDU g = switch (gdu) {
					case 0 -> GDU.POSSIBLE;
					case 1 -> GDU.HARD;
					case 2 -> GDU.IMPOSSIBLE;
					default -> null;
					// throw exception
				};

				switch (sectorType) {
					case 0 -> sectors.add(new Curve(g));
					case 1 -> sectors.add(new Straight(g));
					case 2 -> sectors.add(new Chicane(g));
				}

			}

			if(rs1.next()){
				circuit = new Circuit(rs1.getString(1), rs1.getFloat(2), rs1.getInt(3),sectors);
			}

		} catch (SQLException e) {
			// Error establishing connection
			throw new RuntimeException(e);
		}

		return circuit;
	}

	@Override
	public Circuit put(String s, Circuit value) {
		Circuit circuit = null;

		try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 PreparedStatement st1 = c.prepareStatement("INSERT INTO Circuit (circuitName, circuitLength, numLaps) VALUES (?,?,?)"
			 											 + "ON DUPLICATE KEY UPDATE circuitLength=VALUES(circuitLength),"
					 															 + "numLaps=VALUES(numLaps);");
			 PreparedStatement st2 = c.prepareStatement("INSERT INTO Sector (sectorType, gdu, circuitName, numSector) VALUES (?,?,?,?)"
			 											 + "ON DUPLICATE KEY UPDATE sectorType=VALUES(sectorType),"
					 													  		 + "gdu=VALUES(gdu);")) {

			st1.setString(1, value.getName());
			st1.setFloat(2, value.getLength());
			st1.setInt(3, value.getNumLaps());
			st1.executeUpdate();

		} catch (SQLException e) {
			// Error establishing connection
			throw new RuntimeException(e);
		}


		return circuit;
	}

	public void putSector (String circuitName,int sectorType, int gdu) {
		try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 PreparedStatement st2 = c.prepareStatement("INSERT INTO Sector (sectorType, gdu, circuitName, numSector) VALUES (?,?,?,?);");
			 PreparedStatement st1 = c.prepareStatement("SELECT COUNT(*) FROM Sector WHERE circuitName=?;")) {

			st1.setString(1,circuitName);
			ResultSet rs1 = st1.executeQuery();
			rs1.next();
			int numSector = rs1.getInt(1);

			st2.setInt(1,sectorType);
			st2.setInt(2,gdu);
			st2.setString(3,circuitName);
			st2.setInt(4,numSector);
			st2.executeUpdate();

		} catch (SQLException e) {
			// Error establishing connection
			throw new RuntimeException(e);
		}

	}

	@Override
	public Circuit remove(Object key) {
		Circuit circuit = this.get(key);

		try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 PreparedStatement st1 = c.prepareStatement("DELETE FROM Circuit WHERE circuitName=?;");
			 PreparedStatement st2 = c.prepareStatement("DELETE FROM Sector WHERE circuitName=?;")) {

			st1.setString(1, key.toString());
			st1.executeUpdate();
			st2.setString(1, key.toString());
			st2.executeUpdate();

		} catch (SQLException e) {
			// Error establishing connection
			throw new RuntimeException(e);
		}

		return circuit;
	}

	@Override
	public void putAll(Map<? extends String, ? extends Circuit> circuits) {
		for(Circuit c : circuits.values()){
			this.put(c.getName(), c);
		}
	}

	@Override
	public void clear() {
		try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 PreparedStatement st = c.prepareStatement("TRUNCATE Circuit;")) {

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
			 PreparedStatement st = c.prepareStatement("SELECT circuitName FROM Circuit;")) {

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
	public Collection<Circuit> values() {
		Collection<Circuit> circuits = new ArrayList<>();

		Set<String> keys = keySet();
		for(String key : keys){
			circuits.add(this.get(key));
		}

		return circuits;
	}

	@Override
	public Set<Entry<String, Circuit>> entrySet() {
		return values().stream().collect(Collectors.toMap(Circuit::getName, x -> x)).entrySet();
	}
}