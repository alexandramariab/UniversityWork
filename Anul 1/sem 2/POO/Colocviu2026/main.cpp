#include <iostream>
#include<vector>
#include<string>
#include<memory>
#include<algorithm>
#include <cmath>
using namespace std;

class EroareAplicatie : public std::runtime_error {
public:
    explicit EroareAplicatie(const string& mesaj) : std::runtime_error(mesaj) {}
};

class EroareDate : public EroareAplicatie {
public:
    explicit EroareDate(const string& mesaj) : EroareAplicatie(mesaj) {}
};

class Echipament {
protected:
    string nume;
    static int contor;
    int id;
    float pret;


public:
    Echipament(const string &nume, float pret)
        : nume(nume),
          pret(pret) {
        id=++contor;
    }

    Echipament() = default;

    virtual ~Echipament() = default;
    virtual float consum()=0;
    virtual void citire(istream& in) {
        cout << "nume: "; in >> nume;
        cout << "pret: "; in >> pret;
    }
    virtual void afisare(ostream& out) const {
        out << "nume: " << nume << " | pret: " << pret;

    }
};


istream& operator>>(istream& in, Echipament& v) {
    v.citire(in);
    return in;
}

ostream& operator<<(ostream& out, const Echipament& v) {
    v.afisare(out);
    return out;
}


int Echipament::contor=0;

class Problema {
protected:
    string nume;
    int timpInceput;
    string prioritate;
public:
    Problema(const string &nume, int timp, const string &prioritate="scazuta")
        : nume(nume),
          timpInceput(timp),
          prioritate(prioritate) {
    }

    Problema() = default;

    virtual ~Problema() = default;
    string getNume() const { return nume; }
    string getPrioritate() const { return prioritate; }
    int getTimpInceput() const { return timpInceput; }

    virtual int impact(int timp_curent)=0;
    int getDurata(int timp_curent) const { return timp_curent - timpInceput; }
    virtual void citire(istream& in) {
        cout << "timp: "; in >> timpInceput;
        cout << "prio: "; in >> prioritate;
    }
    virtual void afisare(ostream& out) const {
        out << "timp: " << timpInceput << " | prio: " << prioritate;

    }
};

istream& operator>>(istream& in, Problema& v) {
    v.citire(in);
    return in;
}

ostream& operator<<(ostream& out, const Problema& v) {
    v.afisare(out);
    return out;
}

class IncalzireCentrala: public Problema {
private:
    vector<int>etajeAfectate;

public:
    IncalzireCentrala() = default;

    IncalzireCentrala(const string &nume, int timp, const string &prioritate, const vector<int> &etaje_afectate)
        : Problema(nume, timp, "medie"),
          etajeAfectate(etaje_afectate) {
    }

    ~IncalzireCentrala() override = default;

    virtual int impact(int timp_curent) override;
    virtual void citire(istream& in) {
        cout << "nr etaje: ";int n; in >> n;
        for (int i=1;i<=n;i++) {
            cout<<"etaj: "; int etaj; in>>etaj;
            etajeAfectate.push_back(etaj);
        }
    }
    virtual void afisare(ostream& out) const {
        out << "etaje: ";
        for (int i: etajeAfectate)
            out<< i;

    }
};

int IncalzireCentrala::impact(int timp_curent) {
    int s=0;
    int durata=getDurata(timp_curent);
    for (int i=0;i<etajeAfectate.size();i++)
        s+=etajeAfectate[i]*(durata- etajeAfectate[etajeAfectate.size()-i-1]);
    return s;

}

class ApaCalda: public Problema {
private:
    int mc;
public:
    ApaCalda() = default;

    ApaCalda(const string &nume, int timp, const string &prioritate, int mc)
        : Problema(nume, timp, "scazuta"),
          mc(mc) {
    }

    ~ApaCalda() override = default;
    virtual int impact(int timp_curent) override;
    virtual void citire(istream& in) {
        cout << "mc: "; in >> mc;
    }
    virtual void afisare(ostream& out) const {
        out << "mc: " << mc;

    }
};

int ApaCalda::impact(int timp_curent) {
    return pow(mc,getDurata(timp_curent));
}


class CalitateAer: public Problema {
private:
    int nrParticule;
    float nivelDioxid;
public:
    CalitateAer() = default;

    CalitateAer(const string &nume, int timp, const string &prioritate, int nr_particule, float nivel_dioxid)
        : Problema(nume, timp, getPrioritate()),
          nrParticule(nr_particule),
          nivelDioxid(nivel_dioxid) {
        if (nivelDioxid<400)
            throw EroareDate("peste 400");
    }

    ~CalitateAer() override = default;
    virtual int impact(int timp_curent) override;
    string getPrioritate() {
        if (nrParticule > 30 || nivelDioxid > 2000)
            return "ridicata";
        if (nrParticule > 10 || nivelDioxid > 1000)
            return "medie";
        return "scazuta";

    }
};

int CalitateAer::impact(int timp_curent) {
    int scor=1;
    if (nrParticule>30)
        scor+=70;
    else if (nrParticule>10)
        scor+=16;
    if (nivelDioxid>2000)
        scor+=30;
    else if (nivelDioxid>1000)
        scor+=10;
    return scor*getDurata(timp_curent);
}


class IncalzirePard:public Echipament {
private:
    int suprafata;
public:
    IncalzirePard(const string &nume, float pret, int suprafata)
        : Echipament(nume, pret),
          suprafata(suprafata) {
    }

    ~IncalzirePard() override = default;
    virtual float consum() override {
        return suprafata*pret;
    }


};



class PopmpaCaldura:public Echipament {
private:
    int intervalMetrou;

public:
    PopmpaCaldura(const string &nume, float pret, int interval_metrou)
        : Echipament(nume, pret),
          intervalMetrou(interval_metrou) {
        if (intervalMetrou == 0) throw EroareDate("Intervalul de metrou nu poate fi 0!");
    }

    ~PopmpaCaldura() override = default;
    virtual float consum() override {
        return 1000/intervalMetrou;
    }
};

class PurificatorSare :public Echipament {
private:

public:
    PurificatorSare(string nume = "", float pret = 0.0)
        : Echipament(nume, pret) {}

    float consum() override {
        // În 1/7 cazuri consumul generează o eroare (diviziune la zero sau eroare hardware)
        if (rand() % 7 == 0) {
            throw EroareDate("Eroare Critica Hardware: Diviziune cu 0 la Purificatorul de Sare!");
        }
        return 100.0f; // consum = 100
    }
};


class Program {
private:
    Program() : timpSimulat(0) { srand(time(nullptr)); }
    ~Program() = default;
    Program(const Program&) = delete;
    Program& operator=(const Program&) = delete;

    vector<shared_ptr<Echipament>> echipamente;
    vector<shared_ptr<Problema>> problemeActive;
    int timpSimulat;

public:
    static Program& getInstance() {
        static Program instance;
        return instance;
    }

    void adaugaEchipament() {
        echipamente.push_back(make_shared<IncalzirePard>("IncalzireParter", 45.5, 150));
        echipamente.push_back(make_shared<PopmpaCaldura>("PompaGeotermala", 120.0, 5));
        echipamente.push_back(make_shared<PurificatorSare>("PurificatorHihimala", 35.0));
        cout << "[SISTEM] Echipamentele implicite au fost pornite in clădirea Picnic Tower.\n";

    }
    void adaugareProblema() {
        cout<<"alege tip problema: ";
        cout<<"1,2,3";
        int tip;
        cin>>tip;
        shared_ptr<Problema> p;
        if (tip==1) p=make_shared<IncalzireCentrala>();
        else
            if (tip==2) p=make_shared<ApaCalda>();
        else
            if (tip==3) p=make_shared<CalitateAer>();
        if (p!=nullptr) {
            cin>>*p;
            problemeActive.push_back(p);
        }
    }

};





int main() {
    Program& app = Program::getInstance();
    app.adaugaEchipament();

    int optiune = -1;
    while (optiune != 0) {
        try{
            cout << "\n--- MANAGEMENT MONOTEHNICA PICNIC TOWER ---\n";
            cout << "1. Declansare / Simulare problema noua\n";
            cout << "2. Avansare timp simulare\n";
            cout << "3. Afisare rapoarte, consum si impact curent\n";
            cout << "0. Iesire aplicatie\n";
            cout << "Alegere: "; cin >> optiune;

            if (optiune == 1) app.adaugareProblema();
        }
        catch (const EroareDate& e)
        {cout <<" [HARDWARE CRASH]: " << e.what() << "\n";}
    }


    return 0;
}