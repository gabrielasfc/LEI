package RacingManagerLN.Simulations;

public class Position {
	private long time;
	private boolean stillRunning;
	private Record record;

	/**
	 * Constructor for Position records
	 * @param rec base record for that player
	 */
	public Position(Record rec) {
		this.record = rec;
		this.stillRunning = true;
		this.time = 0; // For premium
	}

	public long getTime() {
		return time;
	}

	public boolean isStillRunning() {
		return stillRunning;
	}

	public Record getRecord(){
		return this.record;
	}

	public void setTime(long time) {
		this.time = time;
	}

	public void setStillRunning(boolean stillRunning) {
		this.stillRunning = stillRunning;
	}

	/**
	 * Return the string representation from the position object
	 * @return the string representation of the position
	 */
	@Override
	public String toString() {
		String aux;
		if (this.stillRunning){
			aux = "Still Running";
		}
		else aux = "Broken Down";
		return this.record.toString() + aux + "\n";
	}

	/**
	 * Updates the current time of the player
	 * @param time
	 */
	public void addTime(long time) {
		this.time += time;
	}

	public void updatePosition(int position) {
		throw new UnsupportedOperationException();
	}

	public String toStringPremium(){
		String aux;
		if (this.stillRunning){
			aux = "Still Running";
		}
		else aux = "Broken Down";
		return this.record.toString() + aux + "\n" + "Tempo: " + this.time + "\n";
	}
}