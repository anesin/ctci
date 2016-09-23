
PRAGMA auto_vacuum = 1;


CREATE TABLE Tenants
(
	TenantID               INTEGER NOT NULL ,
	TenantName             TEXT NOT NULL ,
 PRIMARY KEY (TenantID)
);

CREATE  INDEX IdxTenantID ON Tenants
(TenantID   ASC);

INSERT INTO Tenants VALUES ( 1, 'Anesin');
INSERT INTO Tenants VALUES ( 2, 'Whistler');
INSERT INTO Tenants VALUES ( 3, 'Azur');
INSERT INTO Tenants VALUES ( 4, 'Jarvis');
INSERT INTO Tenants VALUES ( 5, 'Ethan');
INSERT INTO Tenants VALUES ( 6, 'Larry');
INSERT INTO Tenants VALUES ( 7, 'Rian');
INSERT INTO Tenants VALUES ( 8, 'Freddy');
INSERT INTO Tenants VALUES ( 9, 'Ryan');
INSERT INTO Tenants VALUES (10, 'Jack');
INSERT INTO Tenants VALUES (11, 'Jayden');
INSERT INTO Tenants VALUES (12, 'Anderson');
INSERT INTO Tenants VALUES (13, 'Arthur');
INSERT INTO Tenants VALUES (14, 'Bill');
INSERT INTO Tenants VALUES (15, 'Boris');
INSERT INTO Tenants VALUES (16, 'Brad');
INSERT INTO Tenants VALUES (17, 'Bryant');
INSERT INTO Tenants VALUES (18, 'Colin');
INSERT INTO Tenants VALUES (19, 'Eddy');
INSERT INTO Tenants VALUES (20, 'Reese');
INSERT INTO Tenants VALUES (21, 'Pablo');
INSERT INTO Tenants VALUES (22, 'Lily');
INSERT INTO Tenants VALUES (23, 'Jessie');
INSERT INTO Tenants VALUES (24, 'Jennifer');
INSERT INTO Tenants VALUES (25, 'Regina');
INSERT INTO Tenants VALUES (26, 'Jenna');
INSERT INTO Tenants VALUES (27, 'Chloe');
INSERT INTO Tenants VALUES (28, 'Sophie');
INSERT INTO Tenants VALUES (29, 'Marcia');
INSERT INTO Tenants VALUES (30, 'Serena');
INSERT INTO Tenants VALUES (31, 'Dew');
INSERT INTO Tenants VALUES (32, 'Anna');
INSERT INTO Tenants VALUES (33, 'Leah');
INSERT INTO Tenants VALUES (34, 'Lia');
INSERT INTO Tenants VALUES (35, 'Lucia');
INSERT INTO Tenants VALUES (36, 'Nicole');
INSERT INTO Tenants VALUES (37, 'Mia');
INSERT INTO Tenants VALUES (38, 'Betty');
INSERT INTO Tenants VALUES (39, 'Joy');
INSERT INTO Tenants VALUES (40, 'Charlize');



CREATE TABLE Complexes
(
	ComplexID              INTEGER NOT NULL ,
	ComplexName            TEXT NOT NULL ,
 PRIMARY KEY (ComplexID)
);

CREATE  INDEX IdxComplexID ON Complexes
(ComplexID   ASC);

INSERT INTO Complexes VALUES (1000, 'Sobit Maeul');
INSERT INTO Complexes VALUES (2000, 'Daeun Maeul');
INSERT INTO Complexes VALUES (3000, 'Naru Maeul');



CREATE TABLE Buildings
(
	BuildingID             INTEGER NOT NULL ,
	ComplexID              INTEGER NOT NULL ,
	BuildingName           TEXT NOT NULL ,
	Address                TEXT NOT NULL ,
 PRIMARY KEY (BuildingID),
FOREIGN KEY (ComplexID) REFERENCES Complexes (ComplexID)
);

CREATE  INDEX IdxBuildingID ON Buildings
(BuildingID   ASC);

INSERT INTO Buildings VALUES ( 1, 1000, 'SeoheaGrangbl',         'Bansong-dong, Hwaseong-si, Gyeonggi-do, Korea, 445-758');
INSERT INTO Buildings VALUES ( 2, 2000, 'Dasoop Castle',         'Bansong-dong, Hwaseong-si, Gyeonggi-do, Korea, 445-723');
INSERT INTO Buildings VALUES ( 3, 3000, 'BoraVill',              'Bansong-dong, Hwaseong-si, Gyeonggi-do, Korea, 445-753');
INSERT INTO Buildings VALUES ( 4, 1000, 'Sindo Branew',          'Bansong-dong, Hwaseong-si, Gyeonggi-do, Korea, 445-729');
INSERT INTO Buildings VALUES ( 5, 2000, 'Raemian',               'Bansong-dong, Hwaseong-si, Gyeonggi-do, Korea, 445-732');
INSERT INTO Buildings VALUES ( 6, 3000, 'Urim Rumi',             'Bansong-dong, Hwaseong-si, Gyeonggi-do, Korea, 445-755');
INSERT INTO Buildings VALUES ( 7, 1000, 'Gyeongnam honorsville', 'Bansong-dong, Hwaseong-si, Gyeonggi-do, Korea, 445-740');
INSERT INTO Buildings VALUES ( 8, 2000, 'Unam Firstvill',        'Bansong-dong, Hwaseong-si, Gyeonggi-do, Korea, 445-734');
INSERT INTO Buildings VALUES ( 9, 3000, 'Ggumegreen',            'Bansong-dong, Hwaseong-si, Gyeonggi-do, Korea, 445-757');
INSERT INTO Buildings VALUES (10, 2000, 'World Meridian',        'Bansong-dong, Hwaseong-si, Gyeonggi-do, Korea, 445-736');
INSERT INTO Buildings VALUES (11, 3000, 'Humansia',              'Bansong-dong, Hwaseong-si, Gyeonggi-do, Korea, 445-817');
INSERT INTO Buildings VALUES (12, 3000, 'Metapolis',             'Bansong-dong, Hwaseong-si, Gyeonggi-do, Korea, 445-700');



CREATE TABLE Apartments
(
	AptID                  INTEGER NOT NULL ,
	UnitNumber             TEXT NOT NULL ,
	BuildingID             INTEGER NOT NULL ,
 PRIMARY KEY (AptID),
FOREIGN KEY (BuildingID) REFERENCES Buildings (BuildingID)
);

CREATE  INDEX IdxAptID ON Apartments
(AptID   ASC);

INSERT INTO Apartments VALUES (100, '101-100',  1);
INSERT INTO Apartments VALUES (110, '202-110',  2);
INSERT INTO Apartments VALUES (120, '303-120',  3);
INSERT INTO Apartments VALUES (130, '104-130',  4);
INSERT INTO Apartments VALUES (140, '205-140',  5);
INSERT INTO Apartments VALUES (150, '306-150',  6);
INSERT INTO Apartments VALUES (160, '107-160',  7);
INSERT INTO Apartments VALUES (170, '208-170',  8);
INSERT INTO Apartments VALUES (180, '309-180',  9);
INSERT INTO Apartments VALUES (190, '210-190', 10);
INSERT INTO Apartments VALUES (200, '311-200', 11);
INSERT INTO Apartments VALUES (210, '312-210', 12);
INSERT INTO Apartments VALUES (220, '101-220',  1);
INSERT INTO Apartments VALUES (230, '202-230',  2);
INSERT INTO Apartments VALUES (240, '303-240',  3);
INSERT INTO Apartments VALUES (250, '104-250',  4);
INSERT INTO Apartments VALUES (260, '205-260',  5);
INSERT INTO Apartments VALUES (270, '306-270',  6);
INSERT INTO Apartments VALUES (280, '107-280',  7);
INSERT INTO Apartments VALUES (290, '208-290',  8);
INSERT INTO Apartments VALUES (300, '309-300',  9);
INSERT INTO Apartments VALUES (310, '210-310', 10);
INSERT INTO Apartments VALUES (320, '311-320', 11);
INSERT INTO Apartments VALUES (330, '312-330', 12);



CREATE TABLE AptTenants
(
	TenantID               INTEGER NOT NULL ,
	AptID                  INTEGER NOT NULL ,
 PRIMARY KEY (TenantID,AptID),
FOREIGN KEY (TenantID) REFERENCES Tenants (TenantID),
FOREIGN KEY (AptID) REFERENCES Apartments (AptID)
);

CREATE UNIQUE INDEX IdxTenantIDAptID ON AptTenants
(TenantID   ASC,AptID   ASC);

INSERT INTO AptTenants VALUES ( 1, 100);
INSERT INTO AptTenants VALUES ( 2, 110);
INSERT INTO AptTenants VALUES ( 3, 120);
INSERT INTO AptTenants VALUES ( 4, 130);
INSERT INTO AptTenants VALUES ( 5, 140);
INSERT INTO AptTenants VALUES ( 6, 150);
INSERT INTO AptTenants VALUES ( 7, 160);
INSERT INTO AptTenants VALUES ( 8, 170);
INSERT INTO AptTenants VALUES ( 9, 180);
INSERT INTO AptTenants VALUES (10, 190);
INSERT INTO AptTenants VALUES (11, 200);
INSERT INTO AptTenants VALUES (12, 210);
INSERT INTO AptTenants VALUES (13, 220);
INSERT INTO AptTenants VALUES (14, 230);
INSERT INTO AptTenants VALUES (15, 240);
INSERT INTO AptTenants VALUES (16, 250);
INSERT INTO AptTenants VALUES (17, 260);
INSERT INTO AptTenants VALUES (18, 270);
INSERT INTO AptTenants VALUES (19, 280);
INSERT INTO AptTenants VALUES (20, 290);
INSERT INTO AptTenants VALUES (21, 300);
INSERT INTO AptTenants VALUES (22, 310);
INSERT INTO AptTenants VALUES (23, 320);
INSERT INTO AptTenants VALUES (24, 330);
INSERT INTO AptTenants VALUES (25, 100);
INSERT INTO AptTenants VALUES (26, 110);
INSERT INTO AptTenants VALUES (27, 120);
INSERT INTO AptTenants VALUES (28, 130);
INSERT INTO AptTenants VALUES (29, 140);
INSERT INTO AptTenants VALUES (30, 150);
INSERT INTO AptTenants VALUES (31, 160);
INSERT INTO AptTenants VALUES (32, 170);
INSERT INTO AptTenants VALUES (33, 180);
INSERT INTO AptTenants VALUES (34, 190);
INSERT INTO AptTenants VALUES (35, 200);
INSERT INTO AptTenants VALUES (36, 210);
INSERT INTO AptTenants VALUES (37, 220);
INSERT INTO AptTenants VALUES (38, 230);
INSERT INTO AptTenants VALUES (39, 240);
INSERT INTO AptTenants VALUES (40, 250);
INSERT INTO AptTenants VALUES ( 1, 260);
INSERT INTO AptTenants VALUES ( 3, 270);
INSERT INTO AptTenants VALUES ( 5, 280);
INSERT INTO AptTenants VALUES ( 7, 290);
INSERT INTO AptTenants VALUES ( 9, 300);
INSERT INTO AptTenants VALUES (11, 310);
INSERT INTO AptTenants VALUES (13, 320);
INSERT INTO AptTenants VALUES (15, 330);
INSERT INTO AptTenants VALUES (17, 100);
INSERT INTO AptTenants VALUES (19, 110);
INSERT INTO AptTenants VALUES (21, 120);
INSERT INTO AptTenants VALUES (23, 130);
INSERT INTO AptTenants VALUES (25, 140);
INSERT INTO AptTenants VALUES (27, 150);
INSERT INTO AptTenants VALUES (29, 160);
INSERT INTO AptTenants VALUES (31, 170);
INSERT INTO AptTenants VALUES (33, 260);
INSERT INTO AptTenants VALUES (35, 190);
INSERT INTO AptTenants VALUES (37, 200);
INSERT INTO AptTenants VALUES (39, 210);
INSERT INTO AptTenants VALUES ( 1, 220);
INSERT INTO AptTenants VALUES ( 5, 230);
INSERT INTO AptTenants VALUES ( 9, 240);
INSERT INTO AptTenants VALUES (13, 250);
INSERT INTO AptTenants VALUES (17, 180);
INSERT INTO AptTenants VALUES (21, 270);
INSERT INTO AptTenants VALUES (25, 280);
INSERT INTO AptTenants VALUES (29, 290);
INSERT INTO AptTenants VALUES (33, 300);
INSERT INTO AptTenants VALUES (37, 310);
INSERT INTO AptTenants VALUES ( 1, 320);
INSERT INTO AptTenants VALUES ( 9, 330);
INSERT INTO AptTenants VALUES (17, 330);
INSERT INTO AptTenants VALUES (25, 110);
INSERT INTO AptTenants VALUES (33, 120);
INSERT INTO AptTenants VALUES ( 1, 130);
INSERT INTO AptTenants VALUES (17, 140);
INSERT INTO AptTenants VALUES (33, 150);



CREATE TABLE Requests
(
	RequestID              INTEGER NOT NULL ,
	Status                 TEXT NOT NULL  CHECK (Status IN ('Open', 'Close')),
	AptID                  INTEGER NOT NULL ,
	Description            TEXT NULL ,
 PRIMARY KEY (RequestID),
FOREIGN KEY (AptID) REFERENCES Apartments (AptID)
);

CREATE  INDEX IdxRequestID ON Requests
(RequestID   ASC);

INSERT INTO Requests VALUES ( 1, 'Open',  100, NULL);
INSERT INTO Requests VALUES ( 2, 'Close', 110, NULL);
INSERT INTO Requests VALUES ( 3, 'Open',  120, NULL);
INSERT INTO Requests VALUES ( 4, 'Close', 130, NULL);
INSERT INTO Requests VALUES ( 5, 'Open',  140, NULL);
INSERT INTO Requests VALUES ( 6, 'Close', 150, NULL);
INSERT INTO Requests VALUES ( 7, 'Open',  160, NULL);
INSERT INTO Requests VALUES ( 8, 'Close', 170, NULL);
INSERT INTO Requests VALUES ( 9, 'Close', 180, NULL);
INSERT INTO Requests VALUES (10, 'Open',  190, NULL);
INSERT INTO Requests VALUES (11, 'Close', 200, NULL);
INSERT INTO Requests VALUES (12, 'Close', 210, NULL);
INSERT INTO Requests VALUES (13, 'Close', 220, NULL);
INSERT INTO Requests VALUES (14, 'Open',  230, NULL);
INSERT INTO Requests VALUES (15, 'Close', 240, NULL);
INSERT INTO Requests VALUES (16, 'Close', 250, NULL);
INSERT INTO Requests VALUES (17, 'Close', 260, NULL);
INSERT INTO Requests VALUES (18, 'Close', 270, NULL);
INSERT INTO Requests VALUES (19, 'Open',  280, NULL);
INSERT INTO Requests VALUES (20, 'Close', 290, NULL);
INSERT INTO Requests VALUES (21, 'Close', 300, NULL);
INSERT INTO Requests VALUES (22, 'Open',  310, NULL);
INSERT INTO Requests VALUES (23, 'Open',  320, NULL);
INSERT INTO Requests VALUES (24, 'Close', 330, NULL);


