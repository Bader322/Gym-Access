drop table WorkoutClasses;
drop table Rooms;
drop table Trainers;
drop table Members;


CREATE TABLE Members (
    mid CHAR(10) PRIMARY KEY,
    name VARCHAR(20) NOT NULL,
    phoneNumber CHAR(11) NOT NULL, 
    joinDate DATE,
    expireDate DATE
    );

CREATE TABLE Trainers (
     tid CHAR(5) PRIMARY KEY,
     name VARCHAR(20) NOT NULL,
     Tlevel CHAR(1) NOT NULL
	);
	
CREATE TABLE Rooms (
    rno CHAR(5) PRIMARY KEY,
    tid CHAR(5) REFERENCES Trainers
	);
	
CREATE TABLE WorkoutClasses (
    wcid CHAR(5) PRIMARY KEY,
    name VARCHAR(10),
    rno CHAR(5)REFERENCES Rooms,
    tid CHAR(5) REFERENCES Trainers,
    mid CHAR(10) REFERENCES Members
	);

