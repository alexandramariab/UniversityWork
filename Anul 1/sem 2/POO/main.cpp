#include <iostream>
#include <memory>
#include <string>
#include<vector>
#include<algorithm>
using namespace std;
class Drum {
protected:
    string denumire;
    float lungime;
    int nrTronsoane;
public:
    Drum(const string &denumire, float lungime, int nr_tronsoane)
        : denumire(denumire),
          lungime(lungime),
          nrTronsoane(nr_tronsoane) {
        if (nrTronsoane<1)
            throw runtime_error("minim 1 tronson");
    }

    virtual ~Drum() = default;
    virtual float costContract()=0;
    int getNrTronsoane() const {
        return nrTronsoane;
    }
    string getDenumire() const {
        return denumire;
    }
    float getLungime() const {
        return lungime;
    }
    virtual void afisare() const {
        cout << "Drum: " << denumire << " | Lungime totala: " << lungime
             << " km | Nr. tronsoane: " << nrTronsoane;
    }
};

class DrumNational: public Drum {
private:
    int nrJudete;
public:
    DrumNational(const string &denumire, float lungime, int nr_tronsoane, int nr_judete)
        : Drum(denumire, lungime, nr_tronsoane),
          nrJudete(nr_judete) {
    }

    ~DrumNational() override = default;
    virtual float costContract() override {
        return 3000*(lungime/nrTronsoane);
    }
    void afisare() const override {
        Drum::afisare();
        cout << " [Tip: National | Judete: " << nrJudete << "]\n";
    }

};

class DrumEuropean: virtual public Drum {
protected:
    int nrTari;
public:
    DrumEuropean(const string &denumire, float lungime, int nr_tronsoane, int nr_tari)
        : Drum(denumire, lungime, nr_tronsoane),
          nrTari(nr_tari) {
    }

    ~DrumEuropean() override = default;
    virtual float costContract() override {
        return 3000*(lungime/nrTronsoane)+500*nrTari;
    }
    void afisare() const override {
        Drum::afisare();
        cout << " [Tip: European | Tari: " << nrTari << "]\n";
    }
};

class Autostrada: virtual public Drum {
protected:
    int nrBenzi;
public:
    Autostrada(const string &denumire, float lungime, int nr_tronsoane, int nr_benzi)
        : Drum(denumire, lungime, nr_tronsoane),
          nrBenzi(nr_benzi) {
        if (nrBenzi<2)
            throw runtime_error("trb minim 2 benzi");
    }

    ~Autostrada() override = default;
    virtual float costContract() override {
        return 2500*nrBenzi*(lungime/nrTronsoane);
    }
    void afisare() const override {
        Drum::afisare();
        cout << " [Tip: Autostrada | Benzi: " << nrBenzi << "]\n";
    }
};

class AutostradaEuropeana:public DrumEuropean, public Autostrada {
public:
    AutostradaEuropeana(const string &denumire, float lungime, int nr_tronsoane, int nr_benzi, int nr_tari)
        : Drum(denumire,lungime,nr_tronsoane),
            DrumEuropean(denumire, lungime, nr_tronsoane, nr_tari),
          Autostrada(denumire,lungime,nr_tronsoane,nr_benzi) {
    }
    virtual float costContract() override {
        return 2500*nrBenzi*(lungime/nrTronsoane)+500*nrTari;
    }
    void afisare() const override {
        Drum::afisare();
        cout << " [Tip: Autostrada Europeana | Benzi: " << nrBenzi << " | Tari: " << nrTari << "]\n";
    }
};

class Contract {
private:
    static int contor;
    int id;
    string nume;
    string cif;
    shared_ptr<Drum>drumAsociat;
    int tronson;
public:
    Contract(const string &nume, const string &cif, shared_ptr<Drum> drumAsociat, int tronson)
        : nume(nume),
          cif(cif) ,drumAsociat(drumAsociat), tronson(tronson){
        id=++contor;
        if (tronson < 1 || tronson > drumAsociat->getNrTronsoane()) {
            throw runtime_error("Tronsonul specificat nu exista pe acest drum!");
        }
    }

    ~Contract() = default;
    string getCif() const { return cif; }
    shared_ptr<Drum> getDrum() const { return drumAsociat; }
    int getTronson() const { return tronson; }

    void afisare() const {
        cout << "Contract ID: " << id << " | Firma: " << nume << " (CIF: " << cif
             << ") | Pe " << drumAsociat->getDenumire() << " [Tronsonul " << tronson
             << "] | Valoare contractata: " << drumAsociat->costContract() << " mii EUR\n";
    }
};
int Contract::contor=0;

class Meniu {
private:
    Meniu() = default;
    ~Meniu() = default;
    Meniu(const Meniu& m)=delete;
    Meniu& operator=(const Meniu& m)=delete;
    vector<shared_ptr<Drum>>drumuri;
    vector<shared_ptr<Contract>>contracte;
public:
    static Meniu& getInstance(){
        static Meniu instance;
        return instance;
    }

    void interactiuneAdaugareDrum(){
        string denumire;
        float lungime;
        int nrTronsoane, tip;

        cout << "Introdu denumire unic\203 drum (ex: A1, DN2): ";
        cin >> denumire;

        for (const auto& existent : drumuri) {
            if (existent->getDenumire() == denumire) {
                throw runtime_error("Eroare: Denumirea acestui drum exista deja!");
            }
        }

        cout << "Introdu lungimea (km): ";
        cin >> lungime;
        cout << "Introdu numarul de tronsoane: ";
        cin >> nrTronsoane;

        cout << "Alege tipul drumului:\n 1. Drum National\n 2. Drum European\n 3. Autostrada\n 4. Autostrada Europeana\nOptiune: ";
        cin >> tip;

        if (tip == 1) {
            int judete;
            cout << "Numar judete: "; cin >> judete;
            drumuri.push_back(make_shared<DrumNational>(denumire, lungime, nrTronsoane, judete));
        } else if (tip == 2) {
            int tari;
            cout << "Numar tari tranzitate: "; cin >> tari;
            drumuri.push_back(make_shared<DrumEuropean>(denumire, lungime, nrTronsoane, tari));
        } else if (tip == 3) {
            int benzi;
            cout << "Numar benzi: "; cin >> benzi;
            drumuri.push_back(make_shared<Autostrada>(denumire, lungime, nrTronsoane, benzi));
        } else if (tip == 4) {
            int benzi, tari;
            cout << "Numar benzi: "; cin >> benzi;
            cout << "Numar tari: "; cin >> tari;
            drumuri.push_back(make_shared<AutostradaEuropeana>(denumire, lungime, nrTronsoane, benzi, tari));
        } else {
            throw runtime_error("Eroare: Optiune de drum invalida!");
        }
        cout << "Drum inregistrat cu succes!\n";
    }
    void interactiuneAdaugareContract() {
        string numeFirma, cif, numeDrum;
        int tronson;

        cout << "Nume firma: "; cin >> numeFirma;
        cout << "CIF firma: "; cin >> cif;
        cout << "Denumirea drumului pe care se lucreaza: "; cin >> numeDrum;

        shared_ptr<Drum> drumGasit = nullptr;
        for (const auto& d : drumuri) {
            if (d->getDenumire() == numeDrum) {
                drumGasit = d;
                break;
            }
        }

        if (!drumGasit) {
            throw runtime_error("Eroare: Drumul specificat nu a fost gasit!");
        }

        cout << "Numar tronson (1 - " << drumGasit->getNrTronsoane() << "): ";
        cin >> tronson;

        // Verificare unicitate tronson
        for (const auto& c : contracte) {
            if (c->getDrum()->getDenumire() == numeDrum && c->getTronson() == tronson) {
                throw runtime_error("Eroare: Exista deja un contract semnat pe acest tronson!");
            }
        }

        contracte.push_back(make_shared<Contract>(numeFirma, cif, drumGasit, tronson));
        cout << "Contract adaugat cu succes!\n";
    }

    // Cerința a): Afișare inventar complet
    void afisareTot() const {
        cout << "\n=== INVENTAR DRUMURI RE\316EAA ===\n";
        for (const auto& d : drumuri) d->afisare();

        cout << "\n=== REGISTRU CONTRACTE ACTIVE ===\n";
        if (contracte.empty()) cout << "(Nu exista contracte inregistrate)\n";
        for (const auto& c : contracte) c->afisare();
        cout <<"=================================\n";
    }

    float lungimeTotala() {
        float lungime=0.0f;
        for (auto const&d: drumuri)
            lungime+=d->getLungime();
        return lungime;
    }

    float lungimeAutostrazi() {
        float lungime=0.0f;
        for (auto const&d: drumuri)
            if (dynamic_pointer_cast<Autostrada>(d))
            lungime+=d->getLungime();
        return lungime;
    }

    void stergeContracte() {
        string cif;
        cout<<"ciful firmei: ";
        cin>>cif;
        // Rezolvare robusta folosind Erase-Remove + Lambda, conform baremului
        contracte.erase(
            remove_if(contracte.begin(), contracte.end(), [&cif](const shared_ptr<Contract>& c) {
                return c->getCif() == cif;
            }),
            contracte.end()
        );
        cout << "Contractele firmei au fost eliminate din sistem.\n";
    }

};

int main() {
    Meniu& sistem = Meniu::getInstance();
    int optiune = -1;

    cout << "=== Sistem Centralizat de Gestiune CNAIR v2023 ===\n";

    while (optiune != 0) {
        try {
            cout << "\n---------------- M EN I U ----------------\n"
                 << "1. Adauga un drum in retea\n"
                 << "2. Inregistreaza un contract nou pe tronson\n"
                 << "3. Afiseaza toate drumurile si contractele\n"
                 << "4. Calculeaza lungimile totale (Retea vs Autostrazi)\n"
                 << "5. Reziliaza contractele unei firme (dupa CIF)\n"
                 << "6. Calculeaza costul total al contractelor unui drum\n"
                 << "0. Iesire program\n"
                 << "Alege actiunea: ";
            cin >> optiune;

            if (optiune == 1) sistem.interactiuneAdaugareDrum();
            else if (optiune == 2) sistem.interactiuneAdaugareContract();
            else if (optiune == 3) sistem.afisareTot();
            else if (optiune == 4) { sistem.lungimeAutostrazi(); sistem.lungimeTotala(); }
            else if (optiune == 5) sistem.stergeContracte();
            else if (optiune == 0) {
                cout << "Se inchide aplicatia. O zi buna!\n";
                break;
            }
            else {
                cout << "Optiune invalida! Incearca din nou.\n";
            }
        }
        catch (const exception& e) {
            // Tratarea excepțiilor aruncate în interiorul metodelor (propagare obligatorie pentru punctaj)
            cout << "\n>>> EXCEPtIE EVITAT\300: " << e.what() << "\n";
        }
    }
    return 0;
}