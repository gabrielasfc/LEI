USE RacingManager;

INSERT INTO Pilot (pilotName, cts, sva)
VALUES ('Lewis Hamilton', 0.35, 0.4),
	   ('Max Verstappen', 0.5, 0.8),
       ('Charles Leclerc', 0.6, 0.7),
       ('Lando Norris', 0.7, 0.5),
       ('Nicholas Latifi', 0.6, 0.3);

INSERT INTO Player (playerUsername, playerPassword, points, country)
VALUES ('varelzzz', '12345', 0, 'Portugal'),
	   ('gabs', 'ola123', 0, 'Portugal'),
       ('tonegamer', '123ole', 0, 'França'),
       ('mikeb', 'abcd', 0, 'Portugal'),
       ('tunes', '987654321', 0, 'Marrocos');
       
INSERT INTO Circuit (circuitName, circuitLength, numLaps)
VALUES ('Monaco', 3.3, 5),
       ('Gualtar Campus', 3, 7);
INSERT INTO Championship (championshipName, maxPlayers)
VALUES ('DSS Lovers', 10);
       
INSERT INTO Sector (sectorType, gdu, circuitName, numSector)
VALUES (0, 1, 'Monaco', 0),
	   (1, 0, 'Monaco', 1),
       (2, 1, 'Monaco', 2),
       (0, 1, 'Gualtar Campus', 0),
	   (1, 0, 'Gualtar Campus', 1),
       (2, 2, 'Gualtar Campus', 2),
       (0, 1, 'Gualtar Campus', 3),
	   (1, 0, 'Gualtar Campus', 4),
       (0, 1, 'Gualtar Campus', 5);
       
INSERT INTO Car (model, brand, pac, horsePower, engineCapacity, reliability, tireType, engineMode, carType)
VALUES	('W13','Mercedes', 0.97, 1070, 6000, 0.96, 1, 0, 1),
		('RB18','RedBull', 0.94, 1080, 6000, 0.95, 1, 0, 1),
		('F1-75','Ferrari', 0.93, 1075, 6000, 0.94, 1, 0, 1),
		('MCL36','McLaren', 0.93, 1065, 6000, 0.94, 1, 0, 1),
		('A522','Alpine', 0.95, 1065, 6000, 0.94, 1, 0, 1);
        
INSERT INTO ChampionshipCircuit(championshipName, circuitName)
VALUES 	('DSS Lovers', 'Monaco'),
        ('DSS Lovers', 'Gualtar Campus');
        
INSERT INTO Simulation (simulationName, initialDate, endDate, maxPlayers, championshipName)
VALUES ('UMinho', '2022-12-17', NULL, 4, 'DSS Lovers');
        
INSERT INTO Record (playerUsername, score, numAdjAvailable, idCar, pilotName, simulationName)
VALUES  ('mikeb', 0, 2, 1, 'Max Verstappen', 'UMinho'),
        ('tunes', 0, 2, 2, 'Max Verstappen', 'UMinho'),
		('varelzzz', 0, 2, 3, 'Nicholas Latifi', 'UMinho'),
        ('gabs', 0, 2, 4, 'Charles Leclerc', 'UMinho'),
        ('tonegamer', 0, 2, 5, 'Lando Norris', 'UMinho');
        

