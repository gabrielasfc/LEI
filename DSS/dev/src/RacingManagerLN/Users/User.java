package RacingManagerLN.Users;

public class User {
	private String username;
	private String password;

	public User() {
		this.username = "";
		this.password = "";
	}

	public User(String username, String password) {
		this.username = username;
		this.password = password;
	}

	public String getUsername() {
		return this.username;
	}

	public String getPassword() {
		return this.password;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	@Override
	public String toString() {
		final StringBuilder sb = new StringBuilder("\nUser");
		sb.append(" | Username: ").append(this.username);
		sb.append(" | Password: ").append(this.password);

		return sb.toString();
	}
}