#include <iostream>
#include<string>
#include <vector>
#include<memory>
#include <algorithm>
using namespace std;
class Candidat {
protected:
    static int contor; // Pentru ID unic cerut în barem
    int id;
    string nume;
    string prenume;
    string dataNastere;

public:
    Candidat(const string &nume, const string &prenume, const string &dataNastere)
        : nume(nume), prenume(prenume), dataNastere(dataNastere) {
        id = ++contor; // Incrementare automată
    }

    virtual ~Candidat() = default; // DESTRUCTOR VIRTUAL OBLIGATORIU

    // Funcție virtuală pură pentru calculul polimorfic
    virtual float estimare_valoare() const = 0;

    virtual void print() const {
        cout << "ID: " << id << " | " << nume << " " << prenume
             << " (" << dataNastere << ") | Scor: " << estimare_valoare() << " puncte";
    }
};
int Candidat::contor = 0;

class CandidatSprint : public Candidat {
private:
    float timpSecunde; // float pentru a evita trunchierea zecimalelor
public:
    CandidatSprint(const string &n, const string &p, const string &d, float timp)
        : Candidat(n, p, d), timpSecunde(timp) {
        if (timp <= 0) throw invalid_argument("Timpul trebuie sa fie pozitiv!");
    }

    float estimare_valoare() const override {
        if (timpSecunde < 10) return 10.0f;
        return 90.0f / timpSecunde;
    }

    void print() const override {
        Candidat::print();
        cout << " [Proba: Sprint | Rezultat: " << timpSecunde << "s]\n";
    }
};

class CandidatCros : public Candidat {
private:
    float timpMinute;
public:
    CandidatCros(const string &n, const string &p, const string &d, float timp)
        : Candidat(n, p, d), timpMinute(timp) {
        if (timp <= 0) throw invalid_argument("Timpul trebuie sa fie pozitiv!");
    }

    float estimare_valoare() const override {
        if (timpMinute < 30) return 10.0f;
        return 120.0f / timpMinute;
    }

    void print() const override {
        Candidat::print();
        cout << " [Proba: Cros | Rezultat: " << timpMinute << " min]\n";
    }
};

class CandidatLungime : public Candidat {
private:
    string tipProba; // "SemiMaraton" sau "Maraton"
    float distantaKm;
public:
    CandidatLungime(const string &n, const string &p, const string &d, const string& tip, float distanta)
        : Candidat(n, p, d), tipProba(tip), distantaKm(distanta) {
        if (distanta < 0) throw invalid_argument("Distanta nu poate fi negativa!");
    }

    float estimare_valoare() const override {
        if (distantaKm > 50) return 10.0f;
        return distantaKm / 5.0f;
    }

    void print() const override {
        Candidat::print();
        cout << " [Proba: " << tipProba << " | Rezultat: " << distantaKm << " km]\n";
    }
};
class Inscriere {
private:
    Inscriere(){};
    ~Inscriere() = default;
    Inscriere( const Inscriere&o)=delete;
    Inscriere &operator=(const Inscriere& o)=delete;
    vector<shared_ptr<Candidat>>candidati;
    const string codAdminSecret = "Bucuresti2024";
public:
    static Inscriere& getInstance() {
        static Inscriere inscriere;
        return inscriere;
    }

    void inscriereCandidat() {
        string nume, prenume, dataNastere, tipProba;
        int rezultat;
        cout<<"introdu numele: "<<"\n";
        cin>>nume;
        cout<<"introdu prenumele: "<<"\n";
        cin>>prenume;
        cout<<"introdu data nasterii: "<<"\n";
        cin>>dataNastere;
        cout<<"introdu tipul probei: "<<"\n";
        cin>>tipProba;
        cout<<"introdu rezultatul tau pentru proba: "<<"\n";
        cin>>rezultat;

        if (tipProba == "Sprint") {
            candidati.push_back(make_shared<CandidatSprint>(nume, prenume, dataNastere, rezultat));
        } else if (tipProba == "Cros") {
            candidati.push_back(make_shared<CandidatCros>(nume, prenume, dataNastere, rezultat));
        } else if (tipProba == "SemiMaraton" || tipProba == "Maraton") {
            candidati.push_back(make_shared<CandidatLungime>(nume, prenume, dataNastere, tipProba, rezultat));
        } else {
            throw invalid_argument("Tip de proba necunoscut!");
        }
        cout << "Inscriere realizata cu succes!\n\n";

    }

    void StopInscriere() {
        string cod;
        cout<<"introdu codul: ";
        cin>>cod;
        if (cod!=codAdminSecret)
            throw runtime_error("Acces restrictionat! Cod incorect.");
        sort(candidati.begin(), candidati.end(), [](const shared_ptr<Candidat>&a, const shared_ptr<Candidat>&b) {
            return a->estimare_valoare()>b->estimare_valoare();
        });
        if (candidati.size() > 500) {
            candidati.resize(500);
        }

        cout<<"candidati acceptati: "<<"\n";
        for (const auto& c : candidati) {
            c->print();
        }

    }

};

int main() {
    Inscriere& i=Inscriere::getInstance();
    int conditie=-1;
    while (conditie!=0) {
        try {
            cout<<"alege actiune: 1.inscriere candidat   2.afisare lista candidati acceptati  0. exit"<<"\n";
            cin>>conditie;
            if (conditie==1)
                i.inscriereCandidat();
            else
                if (conditie==2)
                    i.StopInscriere();
            else
                if (conditie==0)
                    break;
        }
        catch (const exception&e) {
            cout<<"Eroare: "<<e.what();
        }
    }
    return 0;
}