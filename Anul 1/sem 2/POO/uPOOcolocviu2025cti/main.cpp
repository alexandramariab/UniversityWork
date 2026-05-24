#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;
class Obiect {
protected:
    static int contor;
    int id;
    string nume;
    string data;
    int era;
    float pretListare;

public:
    Obiect(const string &nume, const string& data, int era, float pretListare ): nume(nume), data(data), era(era), pretListare(pretListare) {
        id=++contor;
    }

    virtual ~Obiect()=default;
    string getNume() const {
        return nume;
    }
    string getData() const {
        return data;
    }
    int getEra() const {
        return era;
    }
    float getPretListare() const {
        return pretListare;
    }
    int getId() const {
        return id;
    }


    virtual string colectibilitate() const = 0;
    virtual void afisare() const {
        cout << "ID: " << id << " | " << nume << " (" << data << ") | Pret curent: " << pretListare << " lei";
    }
};
int Obiect::contor = 0;

class ArtefactIstoric: public Obiect {
private:
    vector<string>persoaneRenumite;
public:
    ArtefactIstoric(const std::string &nume, const std::string &data, int era, float pretListare,std::vector<std::string>persoaneRenumite):
    Obiect(nume,data,era,pretListare), persoaneRenumite(persoaneRenumite){}
    virtual string colectibilitate() const override {
        if (persoaneRenumite.size()>3)
            return "ridicat";
        else
            return "scazut";
    }
    void afisare() const override {
        Obiect::afisare();
        cout << " [Istoric | Colectibilitate: " << colectibilitate() << "]";
    }
};


class ArtefactArtistic: public Obiect {
private:
    string tip;
    string material;
public:
    ArtefactArtistic(const std::string &nume, const std::string &data, int era, float pretListare,string tip, string material):
    Obiect(nume,data,era,pretListare), tip(tip), material(material) {
        if (material != "ulei" && material != "marmura" && material != "acrilic" && material != "lemn" && material != "piatra") {
            throw invalid_argument("Material necunoscut pentru un artefact artistic!");
        }
    }
    virtual string colectibilitate() const override {
        if (material=="ulei" || material=="marmura")
            return "ridicat";
        else
            return "scazut";
    }
    void afisare() const override {
        Obiect::afisare();
        cout << " [Artistic (" << tip << ") | Colectibilitate: " << colectibilitate() << "]";
    }

};


class ArtefactPretios: public Obiect {
private:
    string numeDesigner;
    float greutate;
public:
    ArtefactPretios(const std::string &nume, const std::string &data, int era, float pretListare,string numeDesigner, float greutate):
    Obiect(nume,data,era,pretListare), numeDesigner(numeDesigner), greutate(greutate){}
    virtual string colectibilitate() const override {
        if (greutate>250 && numeDesigner!="Necunoscut")
            return "ridicat";
        else
            return "scazut";
    }

    void afisare() const override {
        Obiect::afisare();
        cout << " [Pretios (" << numeDesigner << ") | Colectibilitate: " << colectibilitate() << "]";
    }
};



class Entitate {
protected:
    static int contor;
    int numar;
    float buget;
    int pasLicitare;
    int valoareConfort;
    shared_ptr<Obiect>tipPreferat;
    shared_ptr<Obiect>tipIgnorat;

public:
    Entitate(float buget, int pasLicitare, int valoareConfort,shared_ptr<Obiect>tipPreferat, shared_ptr<Obiect>tipIgnorat):
    buget(buget), pasLicitare(pasLicitare), valoareConfort(valoareConfort), tipPreferat(tipPreferat), tipIgnorat(tipIgnorat) {
        numar=++contor;
    }
    virtual ~Entitate()=default;

    virtual bool continuaLicitare(Obiect &o)=0;
    int getNumar() const { return numar; }
    float getBuget() const { return buget; }
    int getPasLicitare() const { return pasLicitare; }

    virtual void afisare() const = 0;

};

int Entitate::contor=0;

class PersoanaFizica: public Entitate {
private:
    string nume;
public:
    PersoanaFizica(float buget, int pasLicitare, int valoareConfort, std::shared_ptr<Obiect>tipPreferat, std::shared_ptr<Obiect>tipIgnorat, const std::string &nume):
    Entitate(buget,pasLicitare,valoareConfort,tipPreferat,tipIgnorat), nume(nume){}
    virtual bool continuaLicitare(Obiect& o) override {
        float pretViitor = o.getPretListare() + pasLicitare;

        // Constrângerea supremă: dacă n-are bani sau e obiectul ignorat, zice NU direct
        if (pretViitor > buget) return false;

        // Verificăm dacă este de tipul preferat (folosind dynamic_cast)
        bool estePreferat = (dynamic_cast<ArtefactIstoric*>(tipPreferat.get()) && dynamic_cast<ArtefactIstoric*>(&o)) ||
                            (dynamic_cast<ArtefactArtistic*>(tipPreferat.get()) && dynamic_cast<ArtefactArtistic*>(&o)) ||
                            (dynamic_cast<ArtefactPretios*>(tipPreferat.get()) && dynamic_cast<ArtefactPretios*>(&o));

        // Textul exact: continuă dacă se încadrează în buget ȘI este de tip preferat...
        if (estePreferat) {
            return true;
        }

        // ...sau dacă prețul încă nu a depășit pragul de confort pentru un obiect normal
        return (pretViitor <= valoareConfort);
    }

    void afisare() const override {
        cout << "PF #" << numar << " - " << nume << " | Buget: " << buget << " lei |";
    }
};

class PersoanaJuridica: public Entitate {
private:
    string numeOrg;
    vector<shared_ptr<PersoanaFizica>>persFizice;
public:
    PersoanaJuridica(float buget, int pasLicitare, int valoareConfort, std::shared_ptr<Obiect>tipPreferat, std::shared_ptr<Obiect>tipIgnorat, const std::string &numeOrg, vector<shared_ptr<PersoanaFizica>>persFizice):
    Entitate(buget,pasLicitare,valoareConfort,tipPreferat,tipIgnorat), numeOrg(numeOrg), persFizice(persFizice){}

    virtual bool continuaLicitare(Obiect& o) override {
        // A. ÎNTOTDEAUNA prima verificare: dacă firma o ignoră, returnează false direct!
        bool esteIgnoratDeFirma = (dynamic_cast<ArtefactIstoric*>(tipIgnorat.get()) && dynamic_cast<ArtefactIstoric*>(&o)) ||
                                  (dynamic_cast<ArtefactArtistic*>(tipIgnorat.get()) && dynamic_cast<ArtefactArtistic*>(&o)) ||
                                  (dynamic_cast<ArtefactPretios*>(tipIgnorat.get()) && dynamic_cast<ArtefactPretios*>(&o));
        if (esteIgnoratDeFirma) return false;

        // B. Numărarea voturilor
        int nr = 0;
        for (auto const& rep: persFizice)
            if (rep->continuaLicitare(o) == true)
                nr++;

        // C. Exact jumătate (folosind înmulțirea încrucișată sigură pentru numere întregi)
        if (2 * nr == persFizice.size())
            return true;

        // D. Regula preferinței + minim un reprezentant
        bool estePreferatDeFirma = (dynamic_cast<ArtefactIstoric*>(tipPreferat.get()) && dynamic_cast<ArtefactIstoric*>(&o)) ||
                                   (dynamic_cast<ArtefactArtistic*>(tipPreferat.get()) && dynamic_cast<ArtefactArtistic*>(&o)) ||
                                   (dynamic_cast<ArtefactPretios*>(tipPreferat.get()) && dynamic_cast<ArtefactPretios*>(&o));
        if (estePreferatDeFirma && nr >= 1) return true;

        return false;
    }

    void afisare() const override {
        cout << "PJ #" << numar << " - " << numeOrg << " (" << persFizice.size() << " rep) | Buget: " << buget << " lei |";
    }
};


class Licitatie {
private:
    Licitatie(){}
    ~Licitatie(){}
    vector<shared_ptr<Obiect>> inventar;
    vector<shared_ptr<Entitate>> participanti;
    Licitatie(const Licitatie&)=delete;
    Licitatie&operator=(const Licitatie&)=delete;

public:
    static Licitatie& getInstance() {
        static Licitatie licitatie;
        return licitatie;
    }

    void adaugaObiect(shared_ptr<Obiect> o){
       inventar.push_back(o);
    }
    void adaugaParticipant(shared_ptr<Entitate> e) {
        participanti.push_back(e);
    }

    void afisareParticipanti() const {
        for (auto const& p: participanti)
            p->afisare();
        cout<<"\n";
    }

    void afisareInventar() const {
        cout << "\n--- ARTICOLE DISPONIBILE LA LICITATIE ---\n";
        for (const auto& o : inventar) {
            o->afisare();
            cout << "\n";
        }
    }

    void afisareColectibilitate() const {
        for (const auto& o : inventar)
            cout<<o->colectibilitate()<<"\n";
    }

};
int main() {
    Licitatie& l=Licitatie::getInstance();
    auto sablonIstoric = make_shared<ArtefactIstoric>("", "", 0, 0, vector<string>{});
    auto sablonArtistic = make_shared<ArtefactArtistic>("", "", 0, 0, "", "");
    auto sablonPretios = make_shared<ArtefactPretios>("", "", 0, 0, "", 0);
    auto pf1 = make_shared<PersoanaFizica>(15000, 500, 7000, sablonIstoric, sablonPretios, "Alex");
    auto pf2 = make_shared<PersoanaFizica>(20000, 1000, 13000, sablonArtistic, sablonIstoric, "Maria");

    int optiune=-1;
    while (optiune!=0) {
        cout<<"alege o optiune din meniu: "
        <<"1. adauga participanti"<<"\n"
        <<"2. adauga artefacte"<<"\n"
        <<"3. afiseaza participanti"<<"\n"
        <<"4. afisare articole disponibile"<<"\n"
        <<"5. afisare grad colectibilitate"<<"\n";
        cin>>optiune;
        try {
            switch (optiune) {
                case 1: {
                    l.adaugaParticipant(pf1);
                    break;
                }
                case 2: {
                    l.adaugaObiect(sablonArtistic);
                    break;
                }
                case 3: {
                    l.afisareParticipanti();
                    break;
                }
                case 4: {

                    l.afisareInventar();
                    break;
                }
                case 5: {
                    l.afisareColectibilitate();
                    break;
                }
            }
        }
        catch (const exception &e) {
            cout<<"Eroare: "<<e.what();
        }
    }

        return 0;

}