package RacingManagerLN.Pilots;

import java.util.Objects;

public class Pilot {
	private String name;
	private float cts;
	private float sva;

	public Pilot(String name, float cts, float sva) {
		this.name = name;
		this.cts = cts;
		this.sva = sva;
	}

	public Pilot(String name) {
		this.name = name;
		this.cts = (float)0.5; //valores default
		this.sva = (float)0.5; //valores default
	}

	public String getName() {
		return name;
	}

	public float getCts() {
		return cts;
	}

	public float getSva() {
		return sva;
	}

	public void setName(String name) {
		this.name = name;
	}

	public void setCts(float cts) {
		this.cts = cts;
	}

	public void setSva(float sva) {
		this.sva = sva;
	}

	public static boolean validateCTS(float value) {
		return value >= 0 && value <= 1;
	}

	public static boolean validateSVA(float value) {
		return value >= 0 && value <= 1;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (o == null || getClass() != o.getClass()) return false;
		Pilot pilot = (Pilot) o;
		return Float.compare(pilot.cts, cts) == 0 && Float.compare(pilot.sva, sva) == 0 &&
				pilot.name.equals(pilot.name);
	}

	@Override
	public int hashCode() {
		return Objects.hash(name, cts, sva);
	}

	public Pilot clone(){
		return new Pilot(this.name, this.cts, this.sva);
	}
}