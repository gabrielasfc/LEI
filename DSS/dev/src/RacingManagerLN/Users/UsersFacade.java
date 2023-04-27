package RacingManagerLN.Users;

import RacingManagerLN.Exceptions.NonExistentUsernameException;
import RacingManagerDL.PlayerDAO;

import java.util.*;

public class UsersFacade implements ISubUsers {
	private PlayerDAO players;
	private Admin admin;

	public UsersFacade(){
		this.players = PlayerDAO.getInstance();
		this.admin = new Admin();
	}

	public boolean existsUser(String username) {
		return this.players.get(username) != null;
	}

	public void loginUser(String username, String password) throws NonExistentUsernameException {
		Player p = this.players.get(username);

		if (p == null) throw new NonExistentUsernameException("O user " + username + " não existe!");
		if (!p.getPassword().equals(password)) throw new NonExistentUsernameException("A password não coincide!");
	}

	public void setAdmin(String username, String password) {
		this.admin = new Admin(username,password);
	}

	public boolean addPlayer(String username, String password, String country) throws NonExistentUsernameException {
		if(this.players.containsKey(username)) throw new NonExistentUsernameException("User já registado!");

		Player player = new Player(username, password, country);
		this.players.put(username, player);

		return true;
	}

	public List<List<String>> getGlobalClassification() {
		List<List<String>> classification = new ArrayList<>();

		Set<Player> players = new TreeSet<>((p1,p2) -> (p2.getPoints()-p1.getPoints())*1000 + p1.getUsername().compareTo(p2.getUsername()));
		players.addAll(this.players.values());

		for (Player player : players) {
			List<String> data = new ArrayList<>();

			data.add(player.getUsername());
			data.add(Integer.toString(player.getPoints()));

			classification.add(data);
		}

		return classification;
	}

	public List<List<String>> getGlobalClassification(String country) {
		Set<Player> players = new TreeSet<>((Player p1, Player p2) -> (p2.getPoints()-p1.getPoints())*1000 + p1.getUsername().compareTo(p2.getUsername()));
		for (Player player : this.players.values()) {
			if (player.getCountry().equals(country)) {
				players.add(player);
			}
		}

		List<List<String>> classification = new ArrayList<>();

		for (Player player : players){
			List<String> data = new ArrayList<>();

			data.add(player.getUsername());
			data.add(Integer.toString(player.getPoints()));

			classification.add(data);
		}

		return classification;
	}

	/**
	 * Updates user scores given their scores in a simulation
	 * @param scoresByUsername
	 */
	public void updateScore(Map<String, Integer> scoresByUsername) {
		for (String username : scoresByUsername.keySet()) {
			Player p = this.players.get(username);
			p.setPoints(p.getPoints() + scoresByUsername.get(username));
			this.players.put(username, p);
		}
	}
}