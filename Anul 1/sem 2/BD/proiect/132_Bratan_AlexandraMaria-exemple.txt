--12. Formularea în limbaj natural și implementarea a 5 cereri SQL complexe ce vor utiliza, în ansamblul lor, următoarele elemente
     --a) subcereri sincronizate în care intervin cel puțin 3 tabele: Această cerere utilizează subcereri sincronizate în care intervin cel puțin 3 tabele: CLIENT, REZERVA, TIP_SEDINTA_INDIVIDUALA și ZONA_SALA. 
--1. Formulare în limbaj natural:
--Afișați clienții care au rezervat ședințe individuale în zona Fitness, au efectuat cel puțin o rezervare, iar suma totală a prețurilor ședințelor rezervate de ei este mai mare decât media sumelor totale pe client (calculată pentru toți clienții cu rezervări). Pentru fiecare client se vor afișa: numele complet, numărul de rezervări, suma totală plătită pentru ședințe și data ultimei rezervări.



SELECT 
    c.nume || ' ' || c.prenume AS nume_client,
    COUNT(r.cod_rezervare) AS nr_rezervari,
    SUM(ts.pret_sedinta) AS suma_totala_sedinte,
    MAX(r.data) AS data_ultima_rezervare
FROM CLIENT c
JOIN REZERVA r ON c.cod_client = r.cod_client
JOIN TIP_SEDINTA_INDIVIDUALA ts ON r.cod_tip_sedinta = ts.cod_tip_sedinta
WHERE EXISTS (
    SELECT 1
    FROM REZERVA r2
    JOIN TIP_SEDINTA_INDIVIDUALA ts2 ON r2.cod_tip_sedinta = ts2.cod_tip_sedinta
    JOIN ZONA_SALA z ON ts2.cod_zona = z.cod_zona
    WHERE r2.cod_client = c.cod_client
      AND z.nume_zona = 'Fitness'
)
GROUP BY c.cod_client, c.nume, c.prenume
HAVING COUNT(r.cod_rezervare) >= 1
   AND SUM(ts.pret_sedinta) > (
        SELECT AVG(total_per_client)
        FROM (
            SELECT SUM(ts3.pret_sedinta) AS total_per_client
            FROM CLIENT c2
            JOIN REZERVA r3 ON c2.cod_client = r3.cod_client
            JOIN TIP_SEDINTA_INDIVIDUALA ts3 ON r3.cod_tip_sedinta = ts3.cod_tip_sedinta
            GROUP BY c2.cod_client
        )
    )
ORDER BY suma_totala_sedinte DESC;

--2. Formulare în limbaj natural:
--Pentru fiecare tip de produs, afișați denumirea, producătorul, prețul unitar, cantitatea totală vândută și venitul total generat.

--b) subcereri nesincronizate în clauza FROM

SELECT 
    p.denumire,
    p.producator,
    p.pret,
    v.cantitate_totala,
    v.valoare_totala
FROM (
    SELECT cod_tip, denumire, producator, pret
    FROM TIP_PRODUS
) p
JOIN (
    SELECT 
        i.cod_tip,
        SUM(i.cantitate) AS cantitate_totala,
        SUM(i.cantitate * tp.pret) AS valoare_totala
    FROM INCLUDE i
    JOIN VANZARE_PRODUS vp ON i.cod_vanzare = vp.cod_vanzare
    JOIN TIP_PRODUS tp ON i.cod_tip = tp.cod_tip
    GROUP BY i.cod_tip
) v ON p.cod_tip = v.cod_tip
ORDER BY v.valoare_totala DESC;


--3. Formulare în limbaj natural:
--Afișați recepționerii care au operat vânzări cu suma totală a bonurilor fiscale mai mare decât media sumelor totale pe recepționer. Se va afișa numele complet al recepționerului, numărul de vânzări, suma totală a bonurilor și media bonurilor emise de acesta.



--c) grupări de date, funcții grup, filtrare la nivel de grupuri cu subcereri 
--nesincronizate (în clauza de HAVING) în care intervin cel puțin 3 tabele
--(in cadrul aceleiași cereri): grupări (GROUP BY), funcții grup (COUNT, SUM, AVG), filtrare la nivel de grupuri cu subcerere nesincronizată în HAVING, iar în subcererea nesincronizată intervin cel puțin 3 tabele (ANGAJAT, RECEPTIONER, VANZARE, BON_FISCAL)

SELECT 
    a.nume || ' ' || a.prenume AS nume_receptioner,
    COUNT(v.cod_vanzare) AS nr_vanzari,
    SUM(b.suma) AS suma_totala,
    ROUND(AVG(b.suma), 2) AS media_bonurilor
FROM ANGAJAT a
JOIN RECEPTIONER r ON a.cod_angajat = r.cod_angajat
JOIN VANZARE v ON r.cod_angajat = v.cod_angajat
JOIN BON_FISCAL b ON v.cod_vanzare = b.cod_vanzare
GROUP BY a.cod_angajat, a.nume, a.prenume
HAVING SUM(b.suma) > (
    SELECT AVG(total_per_receptioner)
    FROM (
        SELECT SUM(b2.suma) AS total_per_receptioner
        FROM ANGAJAT a2
        JOIN RECEPTIONER r2 ON a2.cod_angajat = r2.cod_angajat
        JOIN VANZARE v2 ON r2.cod_angajat = v2.cod_angajat
        JOIN BON_FISCAL b2 ON v2.cod_vanzare = b2.cod_vanzare
        GROUP BY a2.cod_angajat
    )
)
ORDER BY suma_totala DESC;

--4. Formulare în limbaj natural:
--Afișați toate vânzările din sistem, împreună cu numele clientului, tipul vânzării, metoda de plată și suma bonului fiscal. Pentru valorile lipsă se vor folosi valori implicite. Ordonați rezultatele după tipul vânzării, apoi după sumă descrescător.



-- d) ordonări și utilizarea funcțiilor NVL și DECODE (în cadrul aceleiași cereri) : ordonări (ORDER BY), funcția NVL (de două ori), funcția DECODE (de două ori). Toate în aceeași cerere.

SELECT 
    v.cod_vanzare,
    NVL(c.nume || ' ' || c.prenume, 'Client necunoscut') AS nume_client,
    DECODE(vp.cod_vanzare, NULL, 'Vanzare abonament', 'Vanzare produs') AS tip_vanzare,
    DECODE(v.metoda_plata, 'cash', 'Plata numerar', 'card', 'Plata cu cardul', 'Metoda necunoscuta') AS metoda_plata,
    NVL(b.suma, 0) AS suma_bon
FROM VANZARE v
LEFT JOIN CLIENT c ON v.cod_client = c.cod_client
LEFT JOIN VANZARE_PRODUS vp ON v.cod_vanzare = vp.cod_vanzare
LEFT JOIN VANZARE_ABONAMENT va ON v.cod_vanzare = va.cod_vanzare
LEFT JOIN BON_FISCAL b ON v.cod_vanzare = b.cod_vanzare
ORDER BY tip_vanzare, suma_bon DESC, v.data_vanzare;




--5. Formulare în limbaj natural:
--Pentru fiecare client care deține sau a deținut abonamente, afișați numele clientului formatat, primele 10 caractere din numele complet scrise cu majuscule, data începutului și a sfârșitului abonamentului în format „DD-MON-YYYY”, vechimea abonamentului în luni (valoare absolută), statusul abonamentului („Activ” dacă data_sfârșit >= data curentă, altfel „Expirat”), și numărul total de abonamente deținute de client.


--e) două funcții diferite pe șiruri: INITCAP, UPPER, minim două funcții diferite pe date calendaristice: TO_CHAR, MONTHS_BETWEEN, TRUNC, o expresie CASE.
--f) clauza WITH.



WITH statistica_abonamente AS (
    SELECT 
        c.cod_client,
        c.nume,
        c.prenume,
        d.data_inceput,
        d.data_sfarsit,
        COUNT(d.cod_abonament_activ) OVER (PARTITION BY c.cod_client) AS nr_total_abonamente
    FROM CLIENT c
    JOIN DETINE_ABONAMENT_ACTIV d ON c.cod_client = d.cod_client
)
SELECT 
    INITCAP(stat.nume) || ' ' || INITCAP(stat.prenume) AS nume_formatat,
    UPPER(SUBSTR(stat.nume || ' ' || stat.prenume, 1, 10)) AS prefix_nume_majuscule,
    TO_CHAR(stat.data_inceput, 'DD-MON-YYYY') AS data_inceput_format,
    TO_CHAR(stat.data_sfarsit, 'DD-MON-YYYY') AS data_sfarsit_format,
    ROUND(ABS(MONTHS_BETWEEN(SYSDATE, stat.data_sfarsit)), 2) AS luni_de_la_expirare,
    CASE 
        WHEN stat.data_sfarsit >= TRUNC(SYSDATE) THEN 'Activ'
        ELSE 'Expirat'
    END AS status_abonament,
    stat.nr_total_abonamente
FROM statistica_abonamente stat
ORDER BY stat.data_sfarsit DESC;




--13. Implementarea a 3 operații de actualizare și de suprimare a datelor utilizând subcereri

--Actualizarea prețului ședințelor individuale prin creșterea cu 10% pentru
--tipurile de ședințe care au fost rezervate de de cel puțin două ori. 
UPDATE TIP_SEDINTA_INDIVIDUALA
SET pret_sedinta = pret_sedinta * 1.1
WHERE cod_tip_sedinta IN (
    SELECT r.cod_tip_sedinta
    FROM REZERVA r
    GROUP BY r.cod_tip_sedinta
    HAVING COUNT(*) > 1
);


--Ștergerea înregistrărilor din tabela MENTENANTA pentru echipamentele 
--care se află în stare funcțională, deoarece acestea nu mai 
--necesită evidența intervențiilor anterioare.
DELETE FROM MENTENANTA
WHERE cod_echipament IN (
    SELECT e.cod_echipament
    FROM ECHIPAMENT e
    WHERE e.stare = 'functional'
);


--Actualizarea salariului angajaților care sunt recepționeri și 
--au operat vânzări în valoare totală mai mare de 500 lei.
UPDATE ANGAJAT
SET salariu = salariu + 300
WHERE cod_angajat IN (
    SELECT v.cod_angajat
    FROM VANZARE v
    JOIN BON_FISCAL b ON v.cod_vanzare = b.cod_vanzare
    GROUP BY v.cod_angajat
    HAVING SUM(b.suma) > 500
);



--14. Crearea unei vizualizări complexe(un exemplu de operație LMD permisă pe vizualizarea respectivă și un exemplu de operație LMD nepermisă)

--Crearea vizualizării:
CREATE VIEW VIEW_VANZARI_COMPLEXE AS
SELECT
    v.cod_vanzare,
    v.data_vanzare,
    v.metoda_plata,
    c.nume || ' ' || c.prenume AS nume_client,
    a.nume || ' ' || a.prenume AS nume_receptioner,
    b.cod_bon,
    b.suma
FROM VANZARE v
JOIN CLIENT c ON v.cod_client = c.cod_client
JOIN ANGAJAT a ON v.cod_angajat = a.cod_angajat
JOIN RECEPTIONER r ON a.cod_angajat = r.cod_angajat
JOIN BON_FISCAL b ON v.cod_vanzare = b.cod_vanzare;

--Operație LMD permisă
--Actualizarea metodei de plată pentru o vânzare prin intermediul vizualizării:
UPDATE VIEW_VANZARI_COMPLEXE
SET metoda_plata = 'card'
WHERE cod_vanzare = 1;

--Această operație este permisă deoarece se modifică un atribut care provine direct din tabela VANZARE.


--Operație LMD nepermisă
--Inserarea unei înregistrări noi în vizualizarea complexă:
INSERT INTO VIEW_VANZARI_COMPLEXE
(cod_vanzare, data_vanzare, metoda_plata, nume_client, nume_receptioner, cod_bon, suma)
VALUES
(100, DATE '2025-05-10', 'cash', 'Test Client', 'Test Receptioner', 100, 200);



--15.Formularea în limbaj natural și implementarea în SQL: o cerere ce utilizează operația outer join pe minimum 4 tabele, o cerere ce utilizează operația division și o cerere care implementează analiza top-n

--a) Outer join pe minimum 4 tabele:
--Formulare în limbaj natural: Afișați toți clienții, împreună cu rezervările lor, tipurile de ședințe, zonele în care au loc și antrenorii asociați, chiar dacă unele informații lipsesc.

SELECT
    c.nume || ' ' || c.prenume AS nume_client,
    r.data,
    r.ora,
    ts.pret_sedinta,
    z.nume_zona,
    a.nume || ' ' || a.prenume AS nume_antrenor
FROM CLIENT c
LEFT OUTER JOIN REZERVA r ON c.cod_client = r.cod_client
LEFT OUTER JOIN TIP_SEDINTA_INDIVIDUALA ts ON r.cod_tip_sedinta = ts.cod_tip_sedinta
LEFT OUTER JOIN ZONA_SALA z ON ts.cod_zona = z.cod_zona
LEFT OUTER JOIN ANGAJAT a ON r.cod_antrenor = a.cod_angajat
ORDER BY c.nume, r.data;


--b) Operația division:
--Formulare în limbaj natural: Găsiți clienții care au avut acces, prin abonamentele lor, la toate zonele sălii.
SELECT c.nume || ' ' || c.prenume AS nume_client
FROM CLIENT c
WHERE NOT EXISTS (
    SELECT z.cod_zona
    FROM ZONA_SALA z
    WHERE NOT EXISTS (
        SELECT 1
        FROM DETINE_ABONAMENT_ACTIV da
        JOIN ACCESEAZA ac ON da.cod_tip_abonament = ac.cod_tip_abonament
        WHERE da.cod_client = c.cod_client
        AND ac.cod_zona = z.cod_zona
    )
);


--c) Analiza top-n:
--Formulare în limbaj natural: Afișați top 5 clienți în funcție de suma totală plătită pentru vânzările realizate în sală.

SELECT *
FROM (
    SELECT
        c.nume || ' ' || c.prenume AS nume_client,
        SUM(b.suma) AS total_platit,
        COUNT(v.cod_vanzare) AS nr_vanzari
    FROM CLIENT c
    JOIN VANZARE v ON c.cod_client = v.cod_client
    JOIN BON_FISCAL b ON v.cod_vanzare = b.cod_vanzare
    GROUP BY c.cod_client, c.nume, c.prenume
    ORDER BY total_platit DESC
)
WHERE ROWNUM <= 5;

--16. Optimizarea unei cereri, aplicând regulile de optimizare ce derivă din proprietățile operatorilor algebrei relaționale. Cererea va fi exprimată prin expresie algebrică, arbore algebric și limbaj (SQL), atât anterior cât și ulterior optimizării


--Cererea inițială (neoptimizată):

--Afișați numele complet al clientului, data rezervării, prețul ședinței individuale și numele antrenorului pentru rezervările care au prețul mai mare de 150 lei și care au fost făcute pentru zona „Fitness”.

--SQL inițial:

SELECT c.nume, c.prenume, r.data, ts.pret_sedinta, a.nume, a.prenume
FROM CLIENT c, REZERVA r, TIP_SEDINTA_INDIVIDUALA ts, ANTRENOR ant, ZONA_SALA z, ANGAJAT a
WHERE c.cod_client = r.cod_client
  AND r.cod_tip_sedinta = ts.cod_tip_sedinta
  AND r.cod_antrenor = ant.cod_angajat
  AND ant.cod_angajat = a.cod_angajat
  AND ts.cod_zona = z.cod_zona
  AND ts.pret_sedinta > 150
  AND z.nume_zona = 'Fitness';


--SQL optimizat:

SELECT c.nume, c.prenume, r.data, ts.pret_sedinta, a.nume, a.prenume
FROM CLIENT c
JOIN REZERVA r ON c.cod_client = r.cod_client
JOIN TIP_SEDINTA_INDIVIDUALA ts ON r.cod_tip_sedinta = ts.cod_tip_sedinta AND ts.pret_sedinta > 150
JOIN ZONA_SALA z ON ts.cod_zona = z.cod_zona AND z.nume_zona = 'Fitness'
JOIN ANTRENOR ant ON r.cod_antrenor = ant.cod_angajat
JOIN ANGAJAT a ON ant.cod_angajat = a.cod_angajat;



--17. b)Aplicarea denormalizării
--Interogare frecventă: "Afișați toate rezervările cu numele clientului, numele antrenorului, zona în care se desfășoară și prețul ședinței."
--În schema normalizată, această interogare necesită join-uri între 6 tabele: REZERVA, CLIENT, ANTRENOR, ANGAJAT și TIP_SEDINTA_INDIVIDUALA, ZONA_SALA. Pentru a optimiza performanța acestei interogări frecvente, putem denormaliza aceste tabele.

--SQL:
SELECT r.cod_rezervare, r.data, r.ora, ts.pret_sedinta, ts.durata,
       c.nume AS nume_client, c.prenume AS prenume_client,
       ang.nume AS nume_antrenor, ang.prenume AS prenume_antrenor,
       z.nume_zona AS zona
FROM REZERVA r
JOIN CLIENT c ON r.cod_client = c.cod_client
JOIN TIP_SEDINTA_INDIVIDUALA ts ON r.cod_tip_sedinta = ts.cod_tip_sedinta
JOIN ANTRENOR ant ON r.cod_antrenor = ant.cod_angajat
JOIN ANGAJAT ang ON ant.cod_angajat = ang.cod_angajat
JOIN ZONA_SALA z ON ts.cod_zona = z.cod_zona;







