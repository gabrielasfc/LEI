package RacingManagerLN.Pilots;

import RacingManagerLN.Exceptions.AlreadyExistingPilotException;
import RacingManagerLN.Exceptions.InvalidCtsException;
import RacingManagerLN.Exceptions.InvalidSvaException;

import java.util.List;

public interface ISubPilots {

	public boolean addPilot(String name, float valueCTS, float valueSVA) throws InvalidCtsException, InvalidSvaException, AlreadyExistingPilotException;

	public boolean addPilot(String name) throws AlreadyExistingPilotException;

	public List<List<String>> showAllPilots();

	public Pilot getPilot(String pilotName);
}