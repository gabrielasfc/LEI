package RacingManagerLN.Circuits;

public abstract class Sector {
	private GDU gdu;

	public Sector(GDU gdu) {
		this.gdu = gdu;
	}

	public GDU getGdu() {
		return gdu;
	}
}