package RacingManagerLN.Users;

public class Admin extends User {
	private static Admin singleton = null;

	public Admin(){
		super();
	}

	public Admin(String username, String password) {
		super(username, password);
	}

	public static Admin getInstance(String username, String password) {
		if (Admin.singleton == null) {
			Admin.singleton = new Admin(username, password);
		}

		return Admin.singleton;
	}
}