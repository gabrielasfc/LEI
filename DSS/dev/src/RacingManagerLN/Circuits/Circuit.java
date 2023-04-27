package RacingManagerLN.Circuits;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class Circuit {
	private String name;
	private float length;
	private int numLaps;
	private int numStraights;
	private int numChicanes;
	private int numCurves;
	private List<Sector> sectors;

	public Circuit(Circuit other){
		this.name = other.name;
		this.length = other.length;
		this.numLaps = other.numLaps;
		this.sectors = other.sectors;
	}

	private static int calculateStraights(float length, int numCurves, int numChicanes) {
		return numCurves + numChicanes;
	}

	public Circuit(String name, float length, int numLaps, List<Sector> sectors){
		this.name = name;
		this.length = length;
		this.numLaps = numLaps;
		this.numStraights = 0;
		this.numChicanes = 0;
		this.numCurves = 0;
		for (Sector s : sectors) {
			if (s instanceof Chicane) { this.numChicanes++; }
			else if (s instanceof Curve) { this.numCurves++; }
			else if (s instanceof Straight) { this.numStraights++; }
		}
		this.sectors = new ArrayList<>(sectors);
	}

	public Circuit(String name, float length, int numLaps, int numCurves, int numChicanes) {
		this.name = name;
		this.length = length;
		this.numLaps = numLaps;
		this.numCurves = numCurves;
		this.numChicanes = numChicanes;
		this.numStraights = Circuit.calculateStraights(length, numCurves, numChicanes);
		this.sectors = new ArrayList<>();
	}

	public void addSector(int gdu, int sectorType) {
		GDU g = switch (gdu) {
			case 1 -> GDU.POSSIBLE;
			case 2 -> GDU.HARD;
			case 3 -> GDU.IMPOSSIBLE;
			default -> null;
			// throw exception
		};

		switch (sectorType) {
			case 1 -> this.sectors.add(new Curve(g));
			case 2 -> this.sectors.add(new Straight(g));
			case 3 -> this.sectors.add(new Chicane(g));
			default -> {

			}
			// throw exception
		}
	}

	public List<String> showCircuitSectors() {
		List<String> ls = new ArrayList<>();
		for (Sector s : sectors) {
			ls.add(s.toString());
		}
		return ls;
	}

	public Circuit clone(){
		return new Circuit(this);
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public float getLength() {
		return length;
	}

	public void setLength(float length) {
		this.length = length;
	}

	public int getNumLaps() {
		return numLaps;
	}

	public void setNumLaps(int numLaps) {
		this.numLaps = numLaps;
	}

	public int getNumStraights() {
		return numStraights;
	}

	public void setNumStraights(int numStraights) {
		this.numStraights = numStraights;
	}

	public int getNumChicanes() {
		return numChicanes;
	}

	public void setNumChicanes(int numChicanes) {
		this.numChicanes = numChicanes;
	}

	public int getNumCurves() {
		return numCurves;
	}

	public void setNumCurves(int numCurves) {
		this.numCurves = numCurves;
	}

	public List<Sector> getSectors() {
		return sectors;
	}

	public void setSectors(List<Sector> sectors) {
		this.sectors = sectors;
	}
}