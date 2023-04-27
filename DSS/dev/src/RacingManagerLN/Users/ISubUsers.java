package RacingManagerLN.Users;

import RacingManagerLN.Exceptions.*;

import java.util.List;
import java.util.Map;

public interface ISubUsers {

	public void loginUser(String username, String password) throws NonExistentUsernameException;

	public void setAdmin(String username, String password);

	public boolean addPlayer(String username, String password, String nationality) throws NonExistentUsernameException;

	public boolean existsUser(String username);

	public List<List<String>> getGlobalClassification();

	public List<List<String>> getGlobalClassification(String country);

	public void updateScore(Map<String, Integer> scoresByUsername);
}