--10. Crearea unei secvențe ce va fi utilizată în inserarea înregistrărilor în tabele (punctul 11) 

CREATE SEQUENCE CLIENT_SEQ START WITH 1;

CREATE SEQUENCE ANGAJAT_SEQ START WITH 1;

CREATE SEQUENCE ZONA_SALA_SEQ START WITH 1;

CREATE SEQUENCE TIP_SEDINTA_SEQ START WITH 1;

CREATE SEQUENCE REZERVA_SEQ START WITH 1;

CREATE SEQUENCE ECHIPAMENT_SEQ START WITH 1;

CREATE SEQUENCE MENTENANTA_SEQ START WITH 1;

CREATE SEQUENCE TIP_ABONAMENT_SEQ START WITH 1;

CREATE SEQUENCE DETINE_ABONAMENT_SEQ START WITH 1;

CREATE SEQUENCE VANZARE_SEQ START WITH 1;

CREATE SEQUENCE TIP_PRODUS_SEQ START WITH 1;

CREATE SEQUENCE BON_FISCAL_SEQ START WITH 1;

--11. Crearea tabelelor în SQL și inserarea de date coerente în fiecare dintre acestea

CREATE TABLE CLIENT (
    cod_client INT DEFAULT CLIENT_SEQ.NEXTVAL PRIMARY KEY,
    nume VARCHAR2(50),
    prenume VARCHAR2(50),
    email VARCHAR2(50),
    telefon VARCHAR2(10),
    data_nasterii DATE,
    data_inregistrare DATE
);

INSERT INTO CLIENT (nume, prenume, email, telefon, data_nasterii, data_inregistrare)
VALUES ('Popescu', 'Ana', 'ana@gmail.com', '0722354687', DATE '1999-04-12', DATE '2025-01-10');

INSERT INTO CLIENT (nume, prenume, email, telefon, data_nasterii, data_inregistrare)
VALUES ('Ionescu', 'Vlad', 'vlad@gmail.com', '0765437882', DATE '1998-07-21', DATE '2025-01-12');

INSERT INTO CLIENT (nume, prenume, email, telefon, data_nasterii, data_inregistrare)
VALUES ('Marin', 'Ioana', 'ioana@yahoo.com', '0722456782', DATE '2001-02-08', DATE '2025-01-15');

INSERT INTO CLIENT (nume, prenume, email, telefon, data_nasterii, data_inregistrare)
VALUES ('Dumitru', 'Andrei', 'andrei@gmail.com', '0755488765', DATE '1995-11-30', DATE '2025-02-01');

INSERT INTO CLIENT (nume, prenume, email, telefon, data_nasterii, data_inregistrare)
VALUES ('Georgescu', 'Elena', 'elena@yahoo.com', '0766211458', DATE '2000-09-17', DATE '2025-02-05');

INSERT INTO CLIENT (nume, prenume, email, telefon, data_nasterii, data_inregistrare)
VALUES ('Stan', 'Mihai', 'mihai@gmail.com', '0733523778', DATE '1997-06-19', DATE '2025-02-10');

INSERT INTO CLIENT (nume, prenume, email, telefon, data_nasterii, data_inregistrare)
VALUES ('Tudor', 'Irina', 'irina@yahoo.com', '0791234745', DATE '2002-01-25', DATE '2025-02-18');

INSERT INTO CLIENT (nume, prenume, email, telefon, data_nasterii, data_inregistrare)
VALUES ('Radu', 'Paul', 'paul@gmail.com', '0786452114', DATE '1996-03-14', DATE '2025-03-01');

INSERT INTO CLIENT (nume, prenume, email, telefon, data_nasterii, data_inregistrare)
VALUES ('Barbu', 'Cristina', 'cristina@gmail.com', '0722145668', DATE '1994-10-05', DATE '2025-03-06');

INSERT INTO CLIENT (nume, prenume, email, telefon, data_nasterii, data_inregistrare)
VALUES ('Enache', 'Robert', 'robert@yahoo.com', '0747556623', DATE '1993-12-20', DATE '2025-03-10');

SELECT *
FROM CLIENT
ORDER BY cod_client; 

CREATE TABLE ANGAJAT (
    cod_angajat INT DEFAULT ANGAJAT_SEQ.NEXTVAL PRIMARY KEY,
    nume VARCHAR2(50),
    prenume VARCHAR2(50),
    salariu NUMBER CHECK (salariu > 0)
);

INSERT INTO ANGAJAT (nume, prenume, salariu)
VALUES ('Vasilescu', 'Maria', 4200);

INSERT INTO ANGAJAT (nume, prenume, salariu)
VALUES ('Popa', 'Diana', 4300);

INSERT INTO ANGAJAT (nume, prenume, salariu)
VALUES ('Munteanu', 'Laura', 4100);

INSERT INTO ANGAJAT (nume, prenume, salariu)
VALUES ('Neagu', 'Alex', 4500);

INSERT INTO ANGAJAT (nume, prenume, salariu)
VALUES ('Dobre', 'Carmen', 4400);

INSERT INTO ANGAJAT (nume, prenume, salariu)
VALUES ('Ilie', 'Radu', 5000);

INSERT INTO ANGAJAT (nume, prenume, salariu)
VALUES ('Matei', 'Sorin', 5200);

INSERT INTO ANGAJAT (nume, prenume, salariu)
VALUES ('Nistor', 'Bogdan', 5100);

INSERT INTO ANGAJAT (nume, prenume, salariu)
VALUES ('Florea', 'Adrian', 5300);

INSERT INTO ANGAJAT (nume, prenume, salariu)
VALUES ('Petrescu', 'Dan', 5150);

INSERT INTO ANGAJAT (nume, prenume, salariu)
VALUES ('Avram', 'Vlad', 6500);

INSERT INTO ANGAJAT (nume, prenume, salariu)
VALUES ('Oprea', 'Bianca', 6300);

INSERT INTO ANGAJAT (nume, prenume, salariu)
VALUES ('Lazar', 'Tudor', 6400);

INSERT INTO ANGAJAT (nume, prenume, salariu)
VALUES ('Preda', 'Raluca', 6200);

INSERT INTO ANGAJAT (nume, prenume, salariu)
VALUES ('Serban', 'Marius', 6600);

SELECT *
FROM ANGAJAT
ORDER BY cod_angajat;

CREATE TABLE ZONA_SALA (
    cod_zona INT DEFAULT ZONA_SALA_SEQ.NEXTVAL PRIMARY KEY,
    nume_zona VARCHAR2(50),
    capacitate INT CHECK (capacitate > 0)
);

INSERT INTO ZONA_SALA (nume_zona, capacitate)
VALUES ('Fitness', 60);

INSERT INTO ZONA_SALA (nume_zona, capacitate)
VALUES ('Cardio', 40);

INSERT INTO ZONA_SALA (nume_zona, capacitate)
VALUES ('Pilates', 25);

SELECT *
FROM ZONA_SALA
ORDER BY cod_zona;

CREATE TABLE RECEPTIONER (
    cod_angajat INT PRIMARY KEY,
    limbi_straine VARCHAR2(100),
    FOREIGN KEY (cod_angajat) REFERENCES ANGAJAT(cod_angajat)
);

INSERT INTO RECEPTIONER (cod_angajat, limbi_straine)
VALUES (1, 'engleza, franceza');

INSERT INTO RECEPTIONER (cod_angajat, limbi_straine)
VALUES (2, 'engleza');

INSERT INTO RECEPTIONER (cod_angajat, limbi_straine)
VALUES (3, 'germana');

INSERT INTO RECEPTIONER (cod_angajat, limbi_straine)
VALUES (4, 'engleza, spaniola');

INSERT INTO RECEPTIONER (cod_angajat, limbi_straine)
VALUES (5, 'italiana');

SELECT *
FROM RECEPTIONER
ORDER BY cod_angajat;

CREATE TABLE TEHNICIAN (
    cod_angajat INT PRIMARY KEY,
    certificare VARCHAR2(50),
    FOREIGN KEY (cod_angajat) REFERENCES ANGAJAT(cod_angajat)
);

INSERT INTO TEHNICIAN (cod_angajat, certificare)
VALUES (6, 'Electrician autorizat');

INSERT INTO TEHNICIAN (cod_angajat, certificare)
VALUES (7, 'Mentenanta fitness');

INSERT INTO TEHNICIAN (cod_angajat, certificare)
VALUES (8, 'Mecanic echipamente');

INSERT INTO TEHNICIAN (cod_angajat, certificare)
VALUES (9, 'Service aparate cardio');

INSERT INTO TEHNICIAN (cod_angajat, certificare)
VALUES (10, 'Tehnician instalatii');

SELECT *
FROM TEHNICIAN
ORDER BY cod_angajat;


CREATE TABLE ANTRENOR (
    cod_angajat INT PRIMARY KEY,
    specializare VARCHAR2(50),
    cod_zona INT NOT NULL,
    FOREIGN KEY (cod_angajat) REFERENCES ANGAJAT(cod_angajat),
    FOREIGN KEY (cod_zona) REFERENCES ZONA_SALA(cod_zona)
);

INSERT INTO ANTRENOR (cod_angajat, specializare, cod_zona)
VALUES (11, 'Fitness', 1);

INSERT INTO ANTRENOR (cod_angajat, specializare, cod_zona)
VALUES (12, 'Cardio', 2);

INSERT INTO ANTRENOR (cod_angajat, specializare, cod_zona)
VALUES (13, 'Pilates', 3);

INSERT INTO ANTRENOR (cod_angajat, specializare, cod_zona)
VALUES (14, 'Fitness', 1);

INSERT INTO ANTRENOR (cod_angajat, specializare, cod_zona)
VALUES (15, 'Cardio', 2);

SELECT *
FROM ANTRENOR
ORDER BY cod_angajat;

CREATE TABLE TIP_SEDINTA_INDIVIDUALA (
    cod_tip_sedinta INT DEFAULT TIP_SEDINTA_SEQ.NEXTVAL PRIMARY KEY,
    pret_sedinta NUMBER CHECK (pret_sedinta > 0),
    durata INT CHECK (durata > 0),
    cod_zona INT NOT NULL,
    FOREIGN KEY (cod_zona) REFERENCES ZONA_SALA(cod_zona)
);

INSERT INTO TIP_SEDINTA_INDIVIDUALA (pret_sedinta, durata, cod_zona)
VALUES (120, 60, 1);

INSERT INTO TIP_SEDINTA_INDIVIDUALA (pret_sedinta, durata, cod_zona)
VALUES (130, 45, 2);

INSERT INTO TIP_SEDINTA_INDIVIDUALA (pret_sedinta, durata, cod_zona)
VALUES (150, 60, 3);

INSERT INTO TIP_SEDINTA_INDIVIDUALA (pret_sedinta, durata, cod_zona)
VALUES (180, 90, 1);

INSERT INTO TIP_SEDINTA_INDIVIDUALA (pret_sedinta, durata, cod_zona)
VALUES (160, 75, 2);

SELECT *
FROM TIP_SEDINTA_INDIVIDUALA
ORDER BY cod_tip_sedinta;

CREATE TABLE REZERVA (
    cod_rezervare INT DEFAULT REZERVA_SEQ.NEXTVAL PRIMARY KEY,
    cod_tip_sedinta INT NOT NULL,
    cod_client INT NOT NULL,
    cod_antrenor INT NOT NULL,
    data DATE,
    ora VARCHAR2(5),
    FOREIGN KEY (cod_tip_sedinta) REFERENCES TIP_SEDINTA_INDIVIDUALA(cod_tip_sedinta),
    FOREIGN KEY (cod_client) REFERENCES CLIENT(cod_client),
    FOREIGN KEY (cod_antrenor) REFERENCES ANTRENOR(cod_angajat)
);

INSERT INTO REZERVA (cod_tip_sedinta, cod_client, cod_antrenor, data, ora)
VALUES (1, 1, 11, DATE '2025-05-01', '10:00');

INSERT INTO REZERVA (cod_tip_sedinta, cod_client, cod_antrenor, data, ora)
VALUES (2, 2, 12, DATE '2025-05-01', '12:00');

INSERT INTO REZERVA (cod_tip_sedinta, cod_client, cod_antrenor, data, ora)
VALUES (3, 3, 13, DATE '2025-05-02', '09:00');

INSERT INTO REZERVA (cod_tip_sedinta, cod_client, cod_antrenor, data, ora)
VALUES (4, 4, 14, DATE '2025-05-02', '15:00');

INSERT INTO REZERVA (cod_tip_sedinta, cod_client, cod_antrenor, data, ora)
VALUES (5, 5, 15, DATE '2025-05-03', '11:00');

INSERT INTO REZERVA (cod_tip_sedinta, cod_client, cod_antrenor, data, ora)
VALUES (1, 6, 11, DATE '2025-05-04', '10:00');

INSERT INTO REZERVA (cod_tip_sedinta, cod_client, cod_antrenor, data, ora)
VALUES (2, 7, 12, DATE '2025-05-04', '13:00');

INSERT INTO REZERVA (cod_tip_sedinta, cod_client, cod_antrenor, data, ora)
VALUES (3, 8, 13, DATE '2025-05-05', '16:00');

INSERT INTO REZERVA (cod_tip_sedinta, cod_client, cod_antrenor, data, ora)
VALUES (4, 9, 14, DATE '2025-05-06', '18:00');

INSERT INTO REZERVA (cod_tip_sedinta, cod_client, cod_antrenor, data, ora)
VALUES (5, 10, 15, DATE '2025-05-07', '08:00');

SELECT *
FROM REZERVA
ORDER BY cod_rezervare;


CREATE TABLE ECHIPAMENT (
    cod_echipament INT DEFAULT ECHIPAMENT_SEQ.NEXTVAL PRIMARY KEY,
    denumire VARCHAR2(50),
    stare VARCHAR2(50),
    cod_zona INT NOT NULL,
    FOREIGN KEY (cod_zona) REFERENCES ZONA_SALA(cod_zona)
);

INSERT INTO ECHIPAMENT (denumire, stare, cod_zona)
VALUES ('Banca impins', 'functional', 1);

INSERT INTO ECHIPAMENT (denumire, stare, cod_zona)
VALUES ('Aparat presa picioare', 'functional', 1);

INSERT INTO ECHIPAMENT (denumire, stare, cod_zona)
VALUES ('Banda alergare', 'functional', 2);

INSERT INTO ECHIPAMENT (denumire, stare, cod_zona)
VALUES ('Bicicleta eliptica', 'in mentenanta', 2);

INSERT INTO ECHIPAMENT (denumire, stare, cod_zona)
VALUES ('Reformer Pilates', 'functional', 3);

INSERT INTO ECHIPAMENT (denumire, stare, cod_zona)
VALUES ('Gantere set', 'functional', 1);

INSERT INTO ECHIPAMENT (denumire, stare, cod_zona)
VALUES ('Stepper', 'defect', 2);

INSERT INTO ECHIPAMENT (denumire, stare, cod_zona)
VALUES ('Saltea Pilates', 'functional', 3);

INSERT INTO ECHIPAMENT (denumire, stare, cod_zona)
VALUES ('Aparat tractiuni', 'functional', 1);

INSERT INTO ECHIPAMENT (denumire, stare, cod_zona)
VALUES ('Bicicleta spinning', 'functional', 2);

SELECT *
FROM ECHIPAMENT
ORDER BY cod_echipament;

CREATE TABLE MENTENANTA (
    cod_mentenanta INT DEFAULT MENTENANTA_SEQ.NEXTVAL PRIMARY KEY,
    descriere VARCHAR2(255),
    cost_reparatie NUMBER CHECK (cost_reparatie >= 0),
    cod_angajat INT NOT NULL,
    cod_echipament INT NOT NULL,
    FOREIGN KEY (cod_angajat) REFERENCES TEHNICIAN(cod_angajat),
    FOREIGN KEY (cod_echipament) REFERENCES ECHIPAMENT(cod_echipament)
);

INSERT INTO MENTENANTA (descriere, cost_reparatie, cod_angajat, cod_echipament)
VALUES ('Schimbare cablu aparat', 250, 6, 1);

INSERT INTO MENTENANTA (descriere, cost_reparatie, cod_angajat, cod_echipament)
VALUES ('Verificare motor banda', 300, 9, 3);

INSERT INTO MENTENANTA (descriere, cost_reparatie, cod_angajat, cod_echipament)
VALUES ('Ungere mecanism', 120, 7, 2);

INSERT INTO MENTENANTA (descriere, cost_reparatie, cod_angajat, cod_echipament)
VALUES ('Inlocuire pedala', 180, 8, 4);

INSERT INTO MENTENANTA (descriere, cost_reparatie, cod_angajat, cod_echipament)
VALUES ('Revizie generala', 400, 10, 5);

INSERT INTO MENTENANTA (descriere, cost_reparatie, cod_angajat, cod_echipament)
VALUES ('Reparatie display', 220, 9, 7);

INSERT INTO MENTENANTA (descriere, cost_reparatie, cod_angajat, cod_echipament)
VALUES ('Schimbare suruburi', 90, 7, 6);

INSERT INTO MENTENANTA (descriere, cost_reparatie, cod_angajat, cod_echipament)
VALUES ('Verificare structura', 150, 6, 9);

INSERT INTO MENTENANTA (descriere, cost_reparatie, cod_angajat, cod_echipament)
VALUES ('Reglaj rezistenta', 130, 8, 10);

INSERT INTO MENTENANTA (descriere, cost_reparatie, cod_angajat, cod_echipament)
VALUES ('Curatare profesionala', 100, 10, 8);

SELECT *
FROM MENTENANTA
ORDER BY cod_mentenanta;

CREATE TABLE TIP_ABONAMENT (
    cod_tip_abonament INT DEFAULT TIP_ABONAMENT_SEQ.NEXTVAL PRIMARY KEY,
    denumire VARCHAR2(50),
    pret NUMBER CHECK (pret > 0)
);

INSERT INTO TIP_ABONAMENT (denumire, pret)
VALUES ('Standard', 120);

INSERT INTO TIP_ABONAMENT (denumire, pret)
VALUES ('Gold', 180);

INSERT INTO TIP_ABONAMENT (denumire, pret)
VALUES ('Diamond', 250);

SELECT *
FROM TIP_ABONAMENT
ORDER BY cod_tip_abonament;


CREATE TABLE ACCESEAZA (
    cod_tip_abonament INT,
    cod_zona INT,
    PRIMARY KEY (cod_tip_abonament, cod_zona),
    FOREIGN KEY (cod_tip_abonament) REFERENCES TIP_ABONAMENT(cod_tip_abonament),
    FOREIGN KEY (cod_zona) REFERENCES ZONA_SALA(cod_zona)
);

INSERT INTO ACCESEAZA (cod_tip_abonament, cod_zona)
VALUES (1, 1);

INSERT INTO ACCESEAZA (cod_tip_abonament, cod_zona)
VALUES (2, 1);

INSERT INTO ACCESEAZA (cod_tip_abonament, cod_zona)
VALUES (2, 2);

INSERT INTO ACCESEAZA (cod_tip_abonament, cod_zona)
VALUES (3, 1);

INSERT INTO ACCESEAZA (cod_tip_abonament, cod_zona)
VALUES (3, 2);

INSERT INTO ACCESEAZA (cod_tip_abonament, cod_zona)
VALUES (3, 3);

SELECT *
FROM ACCESEAZA
ORDER BY cod_tip_abonament, cod_zona;



CREATE TABLE DETINE_ABONAMENT_ACTIV (
    cod_abonament_activ INT DEFAULT DETINE_ABONAMENT_SEQ.NEXTVAL PRIMARY KEY,
    cod_tip_abonament INT NOT NULL,
    cod_client INT NOT NULL,
    data_inceput DATE NOT NULL,
    data_sfarsit DATE NOT NULL,
    CHECK (data_sfarsit > data_inceput),
    FOREIGN KEY (cod_tip_abonament) REFERENCES TIP_ABONAMENT(cod_tip_abonament),
    FOREIGN KEY (cod_client) REFERENCES CLIENT(cod_client)
);

INSERT INTO DETINE_ABONAMENT_ACTIV (cod_tip_abonament, cod_client, data_inceput, data_sfarsit) 
VALUES (1, 1, DATE '2025-05-06', DATE '2025-06-06');

INSERT INTO DETINE_ABONAMENT_ACTIV (cod_tip_abonament, cod_client, data_inceput, data_sfarsit) 
VALUES (2, 2, DATE '2025-05-06', DATE '2025-06-06');

INSERT INTO DETINE_ABONAMENT_ACTIV (cod_tip_abonament, cod_client, data_inceput, data_sfarsit) 
VALUES (3, 3, DATE '2025-05-07', DATE '2025-06-07');

INSERT INTO DETINE_ABONAMENT_ACTIV (cod_tip_abonament, cod_client, data_inceput, data_sfarsit) 
VALUES (1, 4, DATE '2025-05-07', DATE '2025-06-07');

INSERT INTO DETINE_ABONAMENT_ACTIV (cod_tip_abonament, cod_client, data_inceput, data_sfarsit) 
VALUES (2, 5, DATE '2025-05-08', DATE '2025-06-08');

INSERT INTO DETINE_ABONAMENT_ACTIV (cod_tip_abonament, cod_client, data_inceput, data_sfarsit) 
VALUES (3, 6, DATE '2025-05-08', DATE '2025-06-08');

INSERT INTO DETINE_ABONAMENT_ACTIV (cod_tip_abonament, cod_client, data_inceput, data_sfarsit) 
VALUES (1, 7, DATE '2025-05-09', DATE '2025-06-09');

INSERT INTO DETINE_ABONAMENT_ACTIV (cod_tip_abonament, cod_client, data_inceput, data_sfarsit) 
VALUES (2, 8, DATE '2025-05-09', DATE '2025-06-09');

INSERT INTO DETINE_ABONAMENT_ACTIV (cod_tip_abonament, cod_client, data_inceput, data_sfarsit) 
VALUES (3, 9, DATE '2025-05-10', DATE '2025-06-10');

INSERT INTO DETINE_ABONAMENT_ACTIV (cod_tip_abonament, cod_client, data_inceput, data_sfarsit) 
VALUES (1, 10, DATE '2025-05-10', DATE '2025-06-10');

SELECT * FROM DETINE_ABONAMENT_ACTIV 
ORDER BY cod_abonament_activ;


CREATE TABLE VANZARE (
    cod_vanzare INT DEFAULT VANZARE_SEQ.NEXTVAL PRIMARY KEY,
    data_vanzare DATE,
    metoda_plata VARCHAR2(10) CHECK (metoda_plata IN ('cash', 'card')),
    cod_angajat INT NOT NULL,
    cod_client INT NOT NULL,
    FOREIGN KEY (cod_angajat) REFERENCES RECEPTIONER(cod_angajat),
    FOREIGN KEY (cod_client) REFERENCES CLIENT(cod_client)
);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-01', 'card', 1, 1);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-01', 'cash', 2, 2);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-02', 'card', 3, 3);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-02', 'cash', 4, 4);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-03', 'card', 5, 5);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-03', 'cash', 1, 6);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-04', 'card', 2, 7);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-04', 'cash', 3, 8);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-05', 'card', 4, 9);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-05', 'cash', 5, 10);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-06', 'card', 1, 1);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-06', 'cash', 2, 2);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-07', 'card', 3, 3);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-07', 'cash', 4, 4);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-08', 'card', 5, 5);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-08', 'cash', 1, 6);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-09', 'card', 2, 7);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-09', 'cash', 3, 8);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-10', 'card', 4, 9);

INSERT INTO VANZARE (data_vanzare, metoda_plata, cod_angajat, cod_client) 
VALUES (DATE '2025-05-10', 'cash', 5, 10);

SELECT * FROM VANZARE ORDER BY cod_vanzare;



CREATE TABLE VANZARE_PRODUS (
    cod_vanzare INT PRIMARY KEY,
    FOREIGN KEY (cod_vanzare) REFERENCES VANZARE(cod_vanzare)
);

INSERT INTO VANZARE_PRODUS (cod_vanzare) 
VALUES (1);

INSERT INTO VANZARE_PRODUS (cod_vanzare) 
VALUES (2);

INSERT INTO VANZARE_PRODUS (cod_vanzare) 
VALUES (3);

INSERT INTO VANZARE_PRODUS (cod_vanzare) 
VALUES (4);

INSERT INTO VANZARE_PRODUS (cod_vanzare) 
VALUES (5);

INSERT INTO VANZARE_PRODUS (cod_vanzare) 
VALUES (6);

INSERT INTO VANZARE_PRODUS (cod_vanzare) 
VALUES (7);

INSERT INTO VANZARE_PRODUS (cod_vanzare) 
VALUES (8);

INSERT INTO VANZARE_PRODUS (cod_vanzare) 
VALUES (9);

INSERT INTO VANZARE_PRODUS (cod_vanzare) 
VALUES (10);

SELECT * FROM VANZARE_PRODUS ORDER BY cod_vanzare;



CREATE TABLE VANZARE_ABONAMENT (
    cod_vanzare INT PRIMARY KEY,
    data_inceput DATE NOT NULL,
    data_sfarsit DATE NOT NULL,
    cod_tip_abonament INT NOT NULL,
    CHECK (data_sfarsit > data_inceput),
    FOREIGN KEY (cod_vanzare) REFERENCES VANZARE(cod_vanzare),
    FOREIGN KEY (cod_tip_abonament) REFERENCES TIP_ABONAMENT(cod_tip_abonament)
);


INSERT INTO VANZARE_ABONAMENT (cod_vanzare, data_inceput, data_sfarsit, cod_tip_abonament) 
VALUES (11, DATE '2025-05-06', DATE '2025-06-06', 1);

INSERT INTO VANZARE_ABONAMENT (cod_vanzare, data_inceput, data_sfarsit, cod_tip_abonament) 
VALUES (12, DATE '2025-05-06', DATE '2025-06-06', 2);

INSERT INTO VANZARE_ABONAMENT (cod_vanzare, data_inceput, data_sfarsit, cod_tip_abonament) 
VALUES (13, DATE '2025-05-07', DATE '2025-06-07', 3);

INSERT INTO VANZARE_ABONAMENT (cod_vanzare, data_inceput, data_sfarsit, cod_tip_abonament) 
VALUES (14, DATE '2025-05-07', DATE '2025-06-07', 1);

INSERT INTO VANZARE_ABONAMENT (cod_vanzare, data_inceput, data_sfarsit, cod_tip_abonament) 
VALUES (15, DATE '2025-05-08', DATE '2025-06-08', 2);

INSERT INTO VANZARE_ABONAMENT (cod_vanzare, data_inceput, data_sfarsit, cod_tip_abonament) 
VALUES (16, DATE '2025-05-08', DATE '2025-06-08', 3);

INSERT INTO VANZARE_ABONAMENT (cod_vanzare, data_inceput, data_sfarsit, cod_tip_abonament) 
VALUES (17, DATE '2025-05-09', DATE '2025-06-09', 1);

INSERT INTO VANZARE_ABONAMENT (cod_vanzare, data_inceput, data_sfarsit, cod_tip_abonament) 
VALUES (18, DATE '2025-05-09', DATE '2025-06-09', 2);

INSERT INTO VANZARE_ABONAMENT (cod_vanzare, data_inceput, data_sfarsit, cod_tip_abonament) 
VALUES (19, DATE '2025-05-10', DATE '2025-06-10', 3);

INSERT INTO VANZARE_ABONAMENT (cod_vanzare, data_inceput, data_sfarsit, cod_tip_abonament) 
VALUES (20, DATE '2025-05-10', DATE '2025-06-10', 1);

SELECT * FROM VANZARE_ABONAMENT
ORDER BY cod_vanzare;


CREATE TABLE TIP_PRODUS (
    cod_tip INT DEFAULT TIP_PRODUS_SEQ.NEXTVAL PRIMARY KEY,
    denumire VARCHAR2(50) NOT NULL,
    producator VARCHAR2(50),
    pret NUMBER(8,2) CHECK (pret > 0)
);

INSERT INTO TIP_PRODUS (denumire, producator, pret) 
VALUES ('Apa plata', 'Dorna', 5);

INSERT INTO TIP_PRODUS (denumire, producator, pret) 
VALUES ('Baton proteic', 'Redis', 8);

INSERT INTO TIP_PRODUS (denumire, producator, pret) 
VALUES ('Shake proteic', 'GymBeam', 15);

INSERT INTO TIP_PRODUS (denumire, producator, pret) 
VALUES ('Tricou sport', 'Nike', 90);

INSERT INTO TIP_PRODUS (denumire, producator, pret) 
VALUES ('Manusi fitness', 'Adidas', 60);

INSERT INTO TIP_PRODUS (denumire, producator, pret) 
VALUES ('Energizant', 'RedBull', 9);

INSERT INTO TIP_PRODUS (denumire, producator, pret) 
VALUES ('Prosop sport', 'Decathlon', 35);

INSERT INTO TIP_PRODUS (denumire, producator, pret) 
VALUES ('Creatina', 'MyProtein', 110);

INSERT INTO TIP_PRODUS (denumire, producator, pret) 
VALUES ('Colanti sport', 'Puma', 120);

INSERT INTO TIP_PRODUS (denumire, producator, pret) 
VALUES ('Apa minerala', 'Borsec', 6);

SELECT * FROM TIP_PRODUS
ORDER BY cod_tip;


CREATE TABLE INCLUDE (
    cod_vanzare INT,
    cod_tip INT,
    cantitate INT CHECK (cantitate > 0),
    PRIMARY KEY (cod_vanzare, cod_tip),
    FOREIGN KEY (cod_vanzare) REFERENCES VANZARE_PRODUS(cod_vanzare),
    FOREIGN KEY (cod_tip) REFERENCES TIP_PRODUS(cod_tip)
);

INSERT INTO INCLUDE (cod_vanzare, cod_tip, cantitate) 
VALUES (1, 1, 2);

INSERT INTO INCLUDE (cod_vanzare, cod_tip, cantitate) 
VALUES (1, 2, 1);

INSERT INTO INCLUDE (cod_vanzare, cod_tip, cantitate) 
VALUES (2, 3, 1);

INSERT INTO INCLUDE (cod_vanzare, cod_tip, cantitate) 
VALUES (3, 4, 1);

INSERT INTO INCLUDE (cod_vanzare, cod_tip, cantitate) 
VALUES (4, 5, 1);

INSERT INTO INCLUDE (cod_vanzare, cod_tip, cantitate) 
VALUES (5, 6, 2);

INSERT INTO INCLUDE (cod_vanzare, cod_tip, cantitate) 
VALUES (6, 7, 1);

INSERT INTO INCLUDE (cod_vanzare, cod_tip, cantitate) 
VALUES (7, 8, 1);

INSERT INTO INCLUDE (cod_vanzare, cod_tip, cantitate) 
VALUES (8, 9, 1);

INSERT INTO INCLUDE (cod_vanzare, cod_tip, cantitate) 
VALUES (9, 10, 3);

INSERT INTO INCLUDE (cod_vanzare, cod_tip, cantitate) 
VALUES (10, 1, 1);

INSERT INTO INCLUDE (cod_vanzare, cod_tip, cantitate) 
VALUES (10, 2, 2);

SELECT * FROM INCLUDE 
ORDER BY cod_vanzare, cod_tip;


CREATE TABLE BON_FISCAL (
    cod_bon INT DEFAULT BON_FISCAL_SEQ.NEXTVAL PRIMARY KEY,
    data_emitere DATE,
    suma NUMBER(8,2) CHECK (suma > 0),
    cod_vanzare INT NOT NULL UNIQUE,
    FOREIGN KEY (cod_vanzare) REFERENCES VANZARE(cod_vanzare)
);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare) 
VALUES (DATE '2025-05-01', 18, 1);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare) 
VALUES (DATE '2025-05-01', 15, 2);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare) 
VALUES (DATE '2025-05-02', 90, 3);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare) 
VALUES (DATE '2025-05-02', 60, 4);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare) 
VALUES (DATE '2025-05-03', 18, 5);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare) 
VALUES (DATE '2025-05-03', 35, 6);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare)
VALUES (DATE '2025-05-04', 110, 7);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare) 
VALUES (DATE '2025-05-04', 120, 8);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare) 
VALUES (DATE '2025-05-05', 18, 9);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare)
VALUES (DATE '2025-05-05', 21, 10);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare)
VALUES (DATE '2025-05-06', 120, 11);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare)
VALUES (DATE '2025-05-06', 180, 12);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare)
VALUES (DATE '2025-05-07', 250, 13);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare)
VALUES (DATE '2025-05-07', 120, 14);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare)
VALUES (DATE '2025-05-08', 180, 15);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare)
VALUES (DATE '2025-05-08', 250, 16);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare)
VALUES (DATE '2025-05-09', 120, 17);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare)
VALUES (DATE '2025-05-09', 180, 18);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare) 
VALUES (DATE '2025-05-10', 250, 19);

INSERT INTO BON_FISCAL (data_emitere, suma, cod_vanzare) 
VALUES (DATE '2025-05-10', 120, 20);

SELECT * FROM BON_FISCAL 
ORDER BY cod_bon;

