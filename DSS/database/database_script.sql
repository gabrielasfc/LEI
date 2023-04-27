CREATE DATABASE IF NOT EXISTS RacingManager;
USE RacingManager;

-- DROP DATABASE RacingManager;

CREATE TABLE IF NOT EXISTS Player (
  playerUsername VARCHAR(75) NOT NULL,
  playerPassword VARCHAR(75) NOT NULL,
  points INT NOT NULL,
  country VARCHAR(75) NOT NULL,
  PRIMARY KEY (playerUsername)
);

CREATE TABLE IF NOT EXISTS Pilot (
	pilotName VARCHAR(75) NOT NULL,
    cts DECIMAL(3,2) NOT NULL,
    sva DECIMAL(3,2) NOT NULL,
    PRIMARY KEY(pilotName)
);

CREATE TABLE IF NOT EXISTS Car(
	idCar INT NOT NULL AUTO_INCREMENT,
    model VARCHAR(75) NOT NULL,
    brand VARCHAR(75) NOT NULL,
    pac DECIMAL(3,2) NOT NULL,
    horsePower INT NOT NULL,
    engineCapacity INT NOT NULL,
    reliability DECIMAL (3,2) NOT NULL,
    tireType INT NOT NULL DEFAULT 1, -- 0 - HARD, 1 - SOFT, 2 - RAIN
    engineMode INT NOT NULL DEFAULT 0, -- 0 - NORMAL, 1 - AGGRESSIVE, 2 - CONSERVATIVE
    carType INT NOT NULL, -- type of car (0 - C1, 1 - C2, 2 - GT, 3 - SC, 4 - ElectricC1, 5 - ElectricC2, 6 - ElectricGT),
    tireState DECIMAL(5,2) NOT NULL DEFAULT 100.00,
    PRIMARY KEY(idCar)
);

CREATE TABLE IF NOT EXISTS ElectricCar(
	idCar INT NOT NULL,
    electricPower INT NOT NULL,
    PRIMARY KEY(idCar),
    FOREIGN KEY(idCar) REFERENCES Car(idCar)
);

CREATE TABLE IF NOT EXISTS Circuit (
  circuitName VARCHAR(75) NOT NULL,
  circuitLength FLOAT NOT NULL,
  numLaps INT NOT NULL,
  PRIMARY KEY (circuitName)
);

CREATE TABLE IF NOT EXISTS Championship (
  championshipName VARCHAR(75) NOT NULL,
  maxPlayers INT NOT NULL,
  PRIMARY KEY (championshipName)
);

CREATE TABLE IF NOT EXISTS Sector (
  sectorType INT NOT NULL, -- 0 - Curve, 1 - Straight, 2 - Chicane 
  gdu INT NOT NULL, -- 0 - POSSIBLE, 1 - HARD, 2 - IMPOSSIBLE
  circuitName VARCHAR(75) NOT NULL,
  numSector INT NOT NULL,
  PRIMARY KEY (numSector, circuitName),
  FOREIGN KEY (circuitName) REFERENCES Circuit(circuitName)
);

CREATE TABLE IF NOT EXISTS Simulation (
  simulationName VARCHAR(75) NOT NULL,
  initialDate DATE NOT NULL,
  endDate DATE,
  maxPlayers INT NOT NULL,
  championshipName VARCHAR(75) NOT NULL,
  currentRace INT NOT NULL DEFAULT 0, 
  PRIMARY KEY (simulationName),
  FOREIGN KEY (championshipName) 
  REFERENCES Championship(championshipName)
);

CREATE TABLE IF NOT EXISTS ChampionshipCircuit (
  championshipName VARCHAR(75) NOT NULL,
  circuitName VARCHAR(75) NOT NULL,
  PRIMARY KEY (championshipName, circuitName),
  FOREIGN KEY (championshipName) 
  REFERENCES Championship(championshipName),
  FOREIGN KEY (circuitName) 
  REFERENCES Circuit(circuitName)
);

CREATE TABLE IF NOT EXISTS Record (
	playerUsername VARCHAR(75) NOT NULL,
	score INT NOT NULL,
	numAdjAvailable INT NOT NULL,
	idCar INT NOT NULL,
	pilotName VARCHAR(75) NOT NULL,
	simulationName VARCHAR(75) NOT NULL,
	PRIMARY KEY (playerUsername, simulationName),
	FOREIGN KEY (playerUsername) 
    REFERENCES Player(playerUsername),
    FOREIGN KEY (simulationName) 
    REFERENCES Simulation(simulationName),
    FOREIGN KEY (idCar) 
    REFERENCES Car(idCar),
    FOREIGN KEY (pilotName) 
    REFERENCES Pilot(pilotName)
);

CREATE USER 'admin'@localhost IDENTIFIED BY 'admin123';
grant all privileges on *.* to 'admin'@localhost;
flush privileges;
