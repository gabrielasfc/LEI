package RacingManagerLN.Users;

import java.util.Objects;

public class Player extends User {
	private int points;
	private String country;

	public Player() {
		super();
		this.country = "";
		this.points = 0;
	}

	public Player(String username, String password, String country) {
		super(username, password);
		this.country = country;
		this.points = 0;
	}

	public Player(String username, String password, int points, String country) {
		super(username, password);
		this.points = points;
		this.country = country;
	}

	public void incrementScore(int score) {
		this.points += score;
	}

	public int getPoints() {
		return this.points;
	}

	public String getCountry() {
		return this.country;
	}

	public void setPoints(int points) {
		this.points = points;
	}

	public void setCountry(String country) {
		this.country = country;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (o == null || getClass() != o.getClass()) return false;
		Player that = (Player) o;
		return this.points == that.points && this.country.equals(that.country);
	}

	@Override
	public int hashCode() {
		return Objects.hash(this.points, this.country);
	}

	@Override
	public String toString() {
		final StringBuilder sb = new StringBuilder();
		sb.append(super.toString());
		sb.append(" | Points: ").append(this.points);
		sb.append(" | Country: ").append(this.country);

		return sb.toString();
	}
}