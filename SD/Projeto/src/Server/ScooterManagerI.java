package Server;

import Exceptions.*;
import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;
import java.util.*;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class ScooterManagerI implements ScooterManager {
    private int R = 2;
    private int D = 5;
    private int N = 10; // dimensão do mapa
    private int S = 15; // número de scooters fixo
    private Scooter[] scooters; // coleção estática
    private Map<String, User> users;
    private ReentrantReadWriteLock.ReadLock usersReadLock;
    private ReentrantReadWriteLock.WriteLock usersWriteLock;
    private Map<Integer, Reservation> reservations;
    private ReentrantLock reservationsLock;
    private List<Reward> rewards;
    public ReentrantLock rewardsLock;
    private Condition rewardsCond;
    private Condition notificationsCond;
    private int lastActivate; // Para a condição da variável de condição
    private int lastPark;


    /**
     * Instantiates a scooter manager shared state
     * @param D radius of search
     * @param N size of the map
     * @param S number of scooters
     */
    public ScooterManagerI(int D, int N, int S){
        this.D = D;
        this.N = N;
        this.S = S;
        this.R = D;
        this.scooters = new Scooter[S];

        this.users = new HashMap<>();
        ReentrantReadWriteLock usersLock = new ReentrantReadWriteLock();
        this.usersReadLock = usersLock.readLock();
        this.usersWriteLock = usersLock.writeLock();

        this.rewards = new ArrayList<>();
        this.rewardsLock = new ReentrantLock();

        this.reservations = new HashMap<>();
        this.reservationsLock = new ReentrantLock();

        this.rewardsCond = this.rewardsLock.newCondition();
        this.notificationsCond = this.rewardsLock.newCondition();

        this.lastActivate = -1;
        this.lastPark = -1;

        this.randomizeScooterPositions();

        new Thread(() -> this.generateRewards()).start();
    }

    /**
     * Instantiates a scooter manager shared state
     * @param D radius of scooters search
     * @param N size of the map
     * @param S number of scooters
     * @param R radius of rewards search
     */
    public ScooterManagerI(int D, int N, int S, int R){
        this.D = D;
        this.N = N;
        this.S = S;
        this.R = R;
        this.scooters = new Scooter[S];

        this.users = new HashMap<>();
        ReentrantReadWriteLock usersLock = new ReentrantReadWriteLock();
        this.usersReadLock = usersLock.readLock();
        this.usersWriteLock = usersLock.writeLock();

        this.rewards = new ArrayList<>();
        this.rewardsLock = new ReentrantLock();

        this.reservations = new HashMap<>();
        this.reservationsLock = new ReentrantLock();

        this.rewardsCond = this.rewardsLock.newCondition();
        this.notificationsCond = this.rewardsLock.newCondition();

        this.lastActivate = -1;
        this.lastPark = -1;

        this.randomizeScooterPositions();

        new Thread(() -> this.generateRewards()).start();

        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Registers an user
     * @param username user's name
     * @param password user's password
     * @throws UsernameAlreadyExistsException Exception
     */
    public void register(String username, String password) throws UsernameAlreadyExistsException {
        try {
            this.usersWriteLock.lock(); // Total control of users collection

            if (this.users.containsKey(username)) { // Must be inside critial section, otherwise there can be two registers at the same time
                throw new UsernameAlreadyExistsException("O user " + username + " já existe!");
            }

            User newUser = new User(username, password);
            this.users.put(username, newUser);
        }
        finally {
            this.usersWriteLock.unlock();
        }
    }

    /**
     * Login in the app
     * @param username user's name
     * @param password user's password
     * @return returns user
     * @throws NonExistentUsernameException Exception
     * @throws WrongPasswordException Exception
     */
    public void login(String username, String password) throws NonExistentUsernameException, WrongPasswordException {
        try {
            this.usersReadLock.lock();

            if (!this.users.containsKey(username)) {
                throw new NonExistentUsernameException("O user " + username + " não existe!");
            }

            User user = this.users.get(username);

            if (!(user.getUsername().equals(username) && user.getPassword().equals(password))) {
                throw new WrongPasswordException("A password não coincide!");
            }
        }
        finally {
            this.usersReadLock.unlock();
        }
    }

    /**
     * Randomizes the scooters distribution in the map
     */
    private void randomizeScooterPositions(){
        Random random = new Random();
        for(int i=0; i<S; i++){
            int x = random.nextInt(N);
            int y = random.nextInt(N);
            this.scooters[i] = new Scooter(new Position(x, y));
        }
    }

    /**
     * Changes the notifications state of an user
     * @param username user's name
     * @param notificationsState state
     */
    public void changeNotificationsState(String username, boolean notificationsState) {
        User user = null;

        try {
            this.usersReadLock.lock();

            user = this.users.get(username);

            user.lock.lock();
        }
        finally {
            this.usersReadLock.unlock();
        }

        try {
            user.setNotificationsState(notificationsState);
        }
        finally {
            user.lock.unlock();
        }
    }

    /**
     * List the available scooters in a radius D (pre-configured) of p
     * @param p center of radius where scooters will be checked
     * @return a list of the positions of the free scooters
     */
    public List<Position> listFreeScooters(Position p){
        List<Position> freeScooters = new ArrayList<>();

        try{
            for(Scooter scooter: this.scooters){ // Iterate over scooters set
                scooter.lockScooter.lock();

                if(scooter.getIsFree()){
                    Position scooterPosition = scooter.getPosition();
                    if(scooterPosition.inRadius(p, D)){ // If scooterPosition in radius D of p
                        freeScooters.add(scooterPosition.clone());
                    }
                }
            }

            return freeScooters;
        }
        finally {
            for(Scooter scooter : this.scooters){
                scooter.lockScooter.unlock();
            }
        }
    }

    /**
     * List the rewards in a radius D (pre-configured) of p
     * @param p center of radius where rewards will be checked
     * @return a list of the positions of the rewards
     */
    public List<List<Position>> listRewards(Position p) {
        List<List<Position>> rewards = new ArrayList<>();

        try {
            this.rewardsLock.lock();

            for (Reward reward : this.rewards) {
                Position rewardPosition = reward.getInitialPosition(); // inicial ou final ?
                if (rewardPosition.inRadius(p, D)) {
                    List<Position> rewardPair = new ArrayList<>();
                    rewardPair.add(0, rewardPosition);
                    rewardPair.add(1, reward.getFinalPosition());
                    rewards.add(rewardPair);
                }
            }

            return rewards;
        }
      finally {
            this.rewardsLock.unlock();
        }
    }

    /**
     * Tries to activate a scooter the closest to a given position, limited by a radius D (pre-configured)
     * @param p center of radius where free scooters will be checked
     * @param username username of the client who activates the scooter
     * @return a reservation containing a reservation code and the position of the scooter found
     * @throws NoScootersAvailableException error if there are no available scooters
     */
    public Reservation activateScooter(Position p, String username) throws NoScootersAvailableException {
        Scooter nearScooter = null;

        for (Scooter scooter: this.scooters) { // Iterate over scooters set
            scooter.lockScooter.lock();
            Position scooterPosition = scooter.getPosition();
            if (scooter.getIsFree() && scooterPosition.inRadius(p, D)) { // If scooterPosition in radius D of p
                if (nearScooter == null) {
                    nearScooter = scooter;
                }
                else {
                    if (scooterPosition.distanceTo(p) < (nearScooter.getPosition().distanceTo(p))) {
                        nearScooter.lockScooter.unlock();
                        nearScooter = scooter;
                    }
                    else scooter.lockScooter.unlock();
                }
            }
            else scooter.lockScooter.unlock(); // ir libertando à medida
        }

        if (nearScooter == null) {
            throw new NoScootersAvailableException("Não há trotinetes livres num raio " + D + " de " + p.toString() + "!");
        }

        nearScooter.setIsFree(false);
        Reservation r = new Reservation(nearScooter, username);
        nearScooter.lockScooter.unlock();

        this.reservationsLock.lock();

        try {
            this.rewardsLock.lock();
            this.lastActivate = r.getReservationID(); // para a condição

            this.rewardsCond.signal();
            this.rewardsLock.unlock();

            this.reservations.put(r.getReservationID(), r);

            return r; 
        } finally {
            this.reservationsLock.unlock();
        }

    }

    /**
     * Calculates the cost of a reservation given the distance and duration
     * @param distance covered distance
     * @param duration duration of the reservation
     * @return the cost of the reservation
     */
    public static double calculateCost(double distance, double duration){
        double cost = 0;

        cost = 0.15 * distance + 0.15/60 * duration;// 15 centimos por minuto

        return - Math.round(cost * 100) / 100.0;  // Arredondar a 2 casas decimais
    }

    /**
     * Parks a scooter given the reservation code and the final position of the ride
     * @param reservationID reservation code
     * @param parkingPosition final position of the scooter
     * @return the cost of the ride or the reward (if applicable)
     */
    public double parkScooter(int reservationID, Position parkingPosition) throws InvalidReservationIDException{
        Scooter scooter = null;
        Reservation reservation = null;
        LocalDateTime parkTimestamp = LocalDateTime.now();

        try {
            this.reservationsLock.lock();

            if (this.reservations.containsKey(reservationID)){
                reservation = this.reservations.get(reservationID); // lançar exceção se for null
            }
            else{
                throw new InvalidReservationIDException("Invalid reservation id!");
            }

            this.reservations.remove(reservationID); // removemos do mapa?

            this.rewardsLock.lock();
        }
        finally {
            this.reservationsLock.unlock();
        }

        try {
            this.lastPark = reservation.getReservationID(); // para a condição

            scooter = reservation.getScooter();

            try {
                scooter.lockScooter.lock();
                scooter.setPosition(parkingPosition);
                scooter.setIsFree(true);
            }
            finally {
                scooter.lockScooter.unlock();
            }

            Position initialPosition = reservation.getInitialPosition();
            double distance = initialPosition.distanceTo(parkingPosition);
            double duration = ChronoUnit.SECONDS.between(parkTimestamp, reservation.getTimestamp()); // Segundos
            double cost = ScooterManagerI.calculateCost(distance, duration);

            for(Reward r: this.rewards){ // Verificar se é uma recompensa
                if (r.getInitialPosition().equals(reservation.getInitialPosition()) && r.getFinalPosition().equals(parkingPosition)){
                    cost = r.getValue();
                }
            }

            this.rewardsCond.signal(); // acordar a thread

            return cost;
        }
        finally {
            this.rewardsLock.unlock();
        }
    }

    /**
     * Generates all the rewards
     * The rewards will be generated on positions that have more than one scooter
     */
    public void generateRewards(){
        int lastActivate = -2;
        int lastPark = -2;

        while(true){ // Quando for estacionada
            try{
                this.rewardsLock.lock();

                while(this.lastActivate == lastActivate && this.lastPark == lastPark){
                    try{
                        this.rewardsCond.await();
                    }
                    catch (Exception ignored){ // mudar

                    }
                }

                List<Position> positions = new ArrayList<>();
                List<Scooter> toUnlock = new ArrayList<>();
                for(Scooter s : this.scooters){
                    s.lockScooter.lock();
                    if (s.getIsFree()) {
                        toUnlock.add(s);
                        positions.add(s.getPosition());
                    }
                    else s.lockScooter.unlock();
                }

                this.rewards.clear(); // Apagar as rewards que lá estavam

                List<Position> samePositions = this.scootersInSamePositions(positions);
                for(Position p1 : samePositions){
                    for (int i = 0; i < N; i++){
                        for (int j = 0; j < N; j++){
                            boolean bool = true;

                            for (Position p2 : positions){
                                if(p2.inRadius(i, j, R)){
                                    bool = false;
                                    break;
                                }
                            }

                            if(bool){
                                this.rewards.add(new Reward(p1, new Position(i, j)));
                            }
                        }
                    }
                }

                for (Scooter s : toUnlock){
                    s.lockScooter.unlock();
                }

                if (lastActivate == -2) lastActivate = -1; // Para executar uma primeira vez quando inicia
                if (lastPark == -2) lastPark = -1;

                lastPark = this.lastPark;
                lastActivate = this.lastActivate;

                this.notificationsCond.signalAll();
            }
            finally {
                this.rewardsLock.unlock();
            }
        }
    }

    /**
     * Gets the positions where rewards should be generated
     * @param positions List of positions
     * @return List of positions that have more than one scooter
     */
    public List<Position> scootersInSamePositions(List<Position> positions){
        List<Position> samePositions = new ArrayList<>();

        for(Position p : positions){
            if(Collections.frequency(positions, p) > 1 && !samePositions.contains(p))
                samePositions.add(p);
        }

        return samePositions;
    }

    /**
     * Gets the rewards on the radius of a given position
     * @param p Position
     * @return List of rewards
     */
    public List<Reward> getRewardsFromPosition(Position p){
        List<Reward> rewards = new ArrayList<>();

        for(Reward r : this.rewards){
            Position pos = r.getInitialPosition();

            if(pos.inRadius(p, D)){
                rewards.add(r);
            }
        }

        return rewards;
    }

    /**
     * Check if there are new rewards on the radius of a given position and waits for that otherwise
     * @param username User to check if its notifications are activated
     * @param p Position
     * @param lastRewards Stores the rewards from last notification (empty at the beginning)
     * @return List of rewards on the radius of a given position
     */
    public List<Reward> userNotifications(String username, Position p, List<Reward> lastRewards) throws NotificationsDisabledException{
        try{
            this.rewardsLock.lock();

            rewards = getRewardsFromPosition(p);
            while(getRewardsFromPosition(p) == null || (rewards.containsAll(lastRewards) && lastRewards.containsAll(rewards))){ // Condição : enquanto não houver recompensas no seu raio, adormece
                User u;
                try{
                    this.notificationsCond.await();

                    //verificar se as notificações estão desativadas
                    try {
                        this.usersReadLock.lock();

                        u = this.users.get(username);

                        u.lock.lock();
                    }
                    finally {
                        this.usersReadLock.unlock();
                    }

                    try {
                        if (!u.getNotificationsState()) {
                            throw new NotificationsDisabledException("As notificações estão desativadas!");
                        }
                    }
                    finally {
                        u.lock.unlock();
                    }

                    rewards = getRewardsFromPosition(p);
                }
                catch (Exception ignored){

                }
            }

            return rewards;
        }
        finally {
            this.rewardsLock.unlock();
        }
    }
}
