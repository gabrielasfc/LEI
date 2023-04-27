package RacingManagerDL;

import RacingManagerLN.Cars.*;

import java.sql.*;
import java.util.*;
import java.util.stream.Collectors;

public class CarDAO implements Map<Integer,Car> {
	private static CarDAO singleton = null;

	private CarDAO() {}

	public static CarDAO getInstance() {
		if (CarDAO.singleton == null) {
			CarDAO.singleton = new CarDAO();
		}
		return CarDAO.singleton;
	}

	@Override
	public int size() {
		int size = 0;

		try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 PreparedStatement st = c.prepareStatement("SELECT COUNT(*) FROM Car;")) {
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
		boolean found;
		int id = (int) key;

		try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 PreparedStatement st = c.prepareStatement("SELECT * from Car WHERE idCar=?;")) {

			st.setInt(1,(int) key);
			ResultSet rs = st.executeQuery();
			found = rs.next();

		} catch (SQLException e) {
			throw new RuntimeException(e);
		}

		return found;
	}

	@Override
	public boolean containsValue(Object value) {
		Car car = (Car) value;
		return car.equals(this.get(car.getCarId()));
	}

	@Override
	public Car get(Object key) {
		Car car = null;

		try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 PreparedStatement st1 = c.prepareStatement("SELECT * FROM Car WHERE idCar=?;")) {

			st1.setInt(1, (int) key);
			ResultSet rs1 = st1.executeQuery();

			if(rs1.next()){
				TireType tt = null;
				switch (rs1.getInt(8)) {
					case 0 -> tt = TireType.HARD;
					case 1 -> tt = TireType.SOFT;
					case 2 -> tt = TireType.RAIN;
				}

				EngineMode em = null;
				switch (rs1.getInt(9)) {
					case 0 -> em = EngineMode.NORMAL;
					case 1 -> em = EngineMode.AGGRESSIVE;
					case 2 -> em = EngineMode.CONSERVATIVE;
				}

				int type = rs1.getInt(10);
				if (type<4) {
					switch (type) {
						case 0 -> car = new C1(rs1.getInt(1),rs1.getString(3),rs1.getString(2),rs1.getInt(5),rs1.getInt(6),rs1.getFloat(7),rs1.getFloat(4),tt,em, rs1.getFloat(11));
						case 1 -> car = new C2(rs1.getInt(1),rs1.getString(3),rs1.getString(2),rs1.getInt(5),rs1.getInt(6),rs1.getFloat(7),rs1.getFloat(4),tt,em, rs1.getFloat(11));
						case 2 -> car = new GT(rs1.getInt(1),rs1.getString(3),rs1.getString(2),rs1.getInt(5),rs1.getInt(6),rs1.getFloat(7),rs1.getFloat(4),tt,em, rs1.getFloat(11));
						case 3 -> car = new SC(rs1.getInt(1),rs1.getString(3),rs1.getString(2),rs1.getInt(5),rs1.getFloat(7),rs1.getFloat(4),tt,em, rs1.getFloat(11));
					}
				} else {
					PreparedStatement st2 = c.prepareStatement("SELECT * FROM ElectricCar WHERE idCar=?;");
					st2.setInt(1, (int) key);
					ResultSet rs2 = st2.executeQuery();

					switch (type) {
						case 4 -> car = new HybridC1(rs1.getInt(1), rs1.getString(3), rs2.getString(2), rs1.getInt(5), rs1.getInt(6), rs1.getFloat(7), rs1.getFloat(4), tt, em, rs1.getFloat(11), rs2.getInt(2));
						case 5 -> car = new HybridC2(rs1.getInt(1), rs1.getString(3), rs2.getString(2), rs1.getInt(5), rs1.getInt(6), rs1.getFloat(7), rs1.getFloat(4), tt, em, rs1.getFloat(11), rs2.getInt(2));
						case 6 -> car = new HybridGT(rs1.getInt(1), rs1.getString(3), rs2.getString(2), rs1.getInt(5), rs1.getInt(6), rs1.getFloat(7), rs1.getFloat(4), tt, em, rs1.getFloat(11), rs2.getInt(2));
					}
				}
			}

		} catch (SQLException e) {
			// Error establishing connection
			throw new RuntimeException(e);
		}

		return car;
	}


	@Override
	public Car put(Integer key, Car value) {
		Car car = null;
		try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 PreparedStatement st1 = c.prepareStatement("INSERT INTO Car (model,brand,pac,horsePower,engineCapacity,reliability,tireType,engineMode,carType,tireState) VALUES (?,?,?,?,?,?,?,?,?,?);");
			 PreparedStatement st2 = c.prepareStatement("INSERT INTO ElectricCar(idCar,electricPower) VALUES (?,?);")) {

			st1.setString(1, value.getModel());
			st1.setString(2, value.getBrand());
			st1.setFloat(3,value.getPac());
			st1.setInt(4,value.getHorsePower());
			st1.setInt(5,value.getEngineCapacity());
			st1.setFloat(6,value.getReliability());
			st1.setFloat(10, value.getTireState());
			switch (value.getTireType()) {
				case HARD -> st1.setInt(7,0);
				case SOFT -> st1.setInt(7,1);
				case RAIN -> st1.setInt(7,2);
			}
			switch (value.getEngineMode()) {
				case NORMAL -> st1.setInt(8,0);
				case AGGRESSIVE -> st1.setInt(8,1);
				case CONSERVATIVE -> st1.setInt(8,2);
			}

			if (value instanceof C1) st1.setInt(9,0);
			else if (value instanceof C2) st1.setInt(9,1);
			else if (value instanceof GT) st1.setInt(9,2);
			else if	(value instanceof SC) st1.setInt(9,3);
			else if (value instanceof HybridC1) st1.setInt(9,4);
			else if (value instanceof HybridC2) st1.setInt(9,5);
			else if (value instanceof HybridGT) st1.setInt(9,6);

			st1.executeUpdate();

			int id = this.size();

			if (value instanceof HybridC1 || value instanceof HybridC2 || value instanceof HybridGT) {

				st2.setInt(1,id);
				if (value instanceof HybridC1) {
					HybridC1 c1 = (HybridC1) value;
					st2.setInt(2, c1.getEletricPower());
				} else if (value instanceof HybridC2) {
					HybridC2 c2 = (HybridC2) value;
					st2.setInt(2,c2.getEletricPower());
				} else {
					HybridGT gt = (HybridGT) value;
					st2.setInt(2,gt.getEletricPower());
				}

				st2.executeUpdate();

			}

			car = this.get(id);

		} catch (SQLException e) {
			// Error establishing connection
			throw new RuntimeException(e);
		}
		return car;
	}

	public Car update(Integer key, Car value) {
		try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 PreparedStatement st1 = c.prepareStatement("UPDATE Car SET model=?,brand=?,pac=?,horsePower=?,engineCapacity=?,reliability=?,tireType=?,engineMode=?,carType=?,tireState=? WHERE idCar=?;");
			 PreparedStatement st2 = c.prepareStatement("UPDATE ElectricCar SET electricPower=? WHERE idCar=?;")) {

			st1.setString(1,value.getModel());
			st1.setString(2,value.getBrand());
			st1.setFloat(3,value.getPac());
			st1.setInt(4,value.getHorsePower());
			st1.setInt(5,value.getEngineCapacity());
			st1.setFloat(6,value.getReliability());
			st1.setFloat(10, value.getTireState());
			switch (value.getTireType()) {
				case HARD -> st1.setInt(7,0);
				case SOFT -> st1.setInt(7,1);
				case RAIN -> st1.setInt(7,2);
			}
			switch (value.getEngineMode()) {
				case NORMAL -> st1.setInt(8,0);
				case AGGRESSIVE -> st1.setInt(8,1);
				case CONSERVATIVE -> st1.setInt(8,2);
			}

			String carClass = value.getClass().getName();
			switch (carClass) {
				case "C1" -> st1.setInt(9,0);
				case "C2" -> st1.setInt(9,1);
				case "GT" -> st1.setInt(9,2);
				case "SC" -> st1.setInt(9,3);
				case "HybridC1" -> st1.setInt(9,4);
				case "HybridC2" -> st1.setInt(9,5);
				case "HybridGT" -> st1.setInt(9,6);
			}

			st1.setInt(11,key);
			st1.executeUpdate();

			if (carClass.equals("HybridC1") || carClass.equals("HybridC2") || carClass.equals("HybridGT")) {

				st2.setInt(2,value.getCarId());

				if (carClass.equals("HybridC1")) {
					HybridC1 c1 = (HybridC1) value;
					st2.setInt(1,c1.getEletricPower());
				} else if (carClass.equals("HybridC2")) {
					HybridC2 c2 = (HybridC2) value;
					st2.setInt(1,c2.getEletricPower());
				} else {
					HybridGT gt = (HybridGT) value;
					st2.setInt(1,gt.getEletricPower());
				}

				st2.executeUpdate();
			}

		} catch (SQLException e) {
			// Error establishing connection
			throw new RuntimeException(e);
		}
		return value;
	}

	@Override
	public Car remove(Object key) {
		Car car = this.get(key);

		try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 PreparedStatement st = c.prepareStatement("DELETE FROM Car WHERE idCar=?;");
			 PreparedStatement st1 = c.prepareStatement("DELETE FROM ElectricCar WHERE idCar=?;")) {

			st.setInt(1, (int) key);
			st.executeUpdate();

			if (car instanceof HybridC1 || car instanceof HybridC2 || car instanceof HybridGT) {
				st1.setInt(1,(int) key);
				st1.executeUpdate();
			}

		} catch (SQLException e) {
			// Error establishing connection
			throw new RuntimeException(e);
		}

		return car;
	}

	@Override
	public void putAll(Map<? extends Integer, ? extends Car> cars) {
		for (Car c : cars.values()) {
			this.put(c.getCarId(),c);
		}
	}

	@Override
	public void clear() {
		try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 PreparedStatement st = c.prepareStatement("TRUNCATE Car;")) {

			ResultSet rs = st.executeQuery();

		} catch (SQLException e) {
			// Error establishing connection
			throw new RuntimeException(e);
		}
	}

	@Override
	public Set<Integer> keySet() {
		Set<Integer> keys = new HashSet<>();
		try (Connection c = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 PreparedStatement st = c.prepareStatement("SELECT idCar FROM Car;")) {

			ResultSet rs = st.executeQuery();
			while (rs.next()) {
				keys.add(rs.getInt(1));
			}

		} catch (SQLException e) {
			// Error establishing connection
			throw new RuntimeException(e);
		}

		return keys;
	}

	@Override
	public Collection<Car> values() {
		Collection<Car> cars = new ArrayList<>();

		Set<Integer> keys = this.keySet();
		for (int key : keys) {
			cars.add(this.get(key));
		}

		return cars;
	}

	@Override
	public Set<Entry<Integer, Car>> entrySet() {
		return this.values().stream().collect(Collectors.toMap(Car::getCarId, c -> c)).entrySet();
	}
}