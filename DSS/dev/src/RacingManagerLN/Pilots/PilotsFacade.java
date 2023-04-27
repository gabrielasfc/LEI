package RacingManagerLN.Pilots;

import RacingManagerDL.PilotDAO;
import RacingManagerLN.Exceptions.AlreadyExistingPilotException;
import RacingManagerLN.Exceptions.InvalidCtsException;
import RacingManagerLN.Exceptions.InvalidSvaException;

import java.util.ArrayList;
import java.util.List;

public class PilotsFacade implements ISubPilots {
	private PilotDAO pilots;

	public PilotsFacade(){
		this.pilots = PilotDAO.getInstance();
	}

	public boolean addPilot(String name, float valueCTS, float valueSVA) throws InvalidCtsException, InvalidSvaException, AlreadyExistingPilotException {
		if (pilots.containsKey(name)) throw new AlreadyExistingPilotException("Já existe um piloto com o mesmo nome.");
		if (valueCTS<0 || valueCTS>1) throw new InvalidCtsException("CTS inválido, o valor deve estar entre 0 e 1.");
		if (valueSVA<0 || valueSVA>1) throw new InvalidSvaException("SVA inválido, o valor deve estar entre 0 e 1.");

		Pilot p = new Pilot(name, valueCTS, valueSVA);
		this.pilots.put(name,p);

		return true;
	}

	public boolean addPilot(String name) throws AlreadyExistingPilotException {
		if (pilots.containsKey(name)) throw new AlreadyExistingPilotException("Já existe um piloto com o mesmo nome!");
		Pilot p = new Pilot(name);
		this.pilots.put(name, p);

		return true;
	}

	public List<List<String>> showAllPilots() {
		List<List<String>> pilots = new ArrayList<>();

		for(Pilot pilot : this.pilots.values()){
			List<String> data = new ArrayList<>();

			data.add(pilot.getName());
			data.add(Float.toString(pilot.getCts()));
			data.add(Float.toString(pilot.getSva()));

			pilots.add(data);
		}

		return pilots;
	}

	public Pilot getPilot(String pilotName) {
		return this.pilots.get(pilotName).clone(); // clone ?
	}
}