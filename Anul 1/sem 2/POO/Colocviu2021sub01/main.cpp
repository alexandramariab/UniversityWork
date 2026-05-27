#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
class Malware {
protected:
    float ratingImpact;
    string dataInfectare;
    string nume;
    string metodaInfectare;
    vector<string>registriiModif;

public:
    Malware(float rating_impact, const string &data_infectare, const string &nume, vector<string>registrii_modif, const string &metoda_infectare="unknown")
        : ratingImpact(0.0),
          dataInfectare(data_infectare),
          nume(nume),
          metodaInfectare(metoda_infectare),
          registriiModif(registrii_modif) {
    }

    virtual ~Malware() = default;
    virtual void calcRatingImpact()=0;
    float getRatingFinal(){
        calcRatingImpact();
        float rezultat = ratingImpact;
        for (const string& reg : registriiModif) {
            if (reg == "HKLM-run" || reg == "HKCU-run") {
                rezultat += 20;
            }
        }
        return rezultat;
    }
};

class Rootkit:virtual public Malware {
protected:
    vector<string>listaImport;
    vector<string>stringuriSemnif;
public:
    Rootkit(float rating_impact, const string &data_infectare, const string &nume, const string &metoda_infectare,
        const vector<string> &registrii_modif, const vector<string> &lista_import,
        const vector<string> &stringuri_semnif)
        : Malware(rating_impact, data_infectare, nume, registrii_modif, metoda_infectare),
          listaImport(lista_import),
          stringuriSemnif(stringuri_semnif) {
    }

    ~Rootkit() override = default;
    virtual void calcRatingImpact() override {
        ratingImpact = 0;
        for (string s: stringuriSemnif)
            if (s=="System Service Descriptor Table" || s=="SSDT" || s=="NtCreateFile")
                ratingImpact+=100;
        for (string st: listaImport)
            if (st=="ntoskrnl.exe")
                ratingImpact=ratingImpact*2;
    }
};

class Keylogger: virtual public Malware {
protected:
    vector<string>functiiFolosite;
    vector<string>taste;

public:
    Keylogger(float rating_impact, const string &data_infectare, const string &nume, const string &metoda_infectare,
        const vector<string> &registrii_modif, const vector<string> &functii_folosite, const vector<string> &taste)
        : Malware(rating_impact, data_infectare, nume, registrii_modif, metoda_infectare),
          functiiFolosite(functii_folosite),
          taste(taste) {
    }

    ~Keylogger() override = default;

    virtual void calcRatingImpact() override {
        ratingImpact = 0;
        for (string t: taste)
            if (t=="[Up]" || t=="[Num Lock]" || t=="[Down]" || t=="[Right]" || t=="[UP]" || t=="[Left]" || t=="[PageDown]")
                ratingImpact+=10;
        for (string f: functiiFolosite)
            if (f=="CreateFileW" || f=="OpenProcess" || f=="ReadFile" || f=="WriteFile" || f=="RegisterHotKey" || f=="SetWindowsHookEx")
                ratingImpact+=30;
    }
};
class Kernel:public Rootkit, public Keylogger{
private:
    bool ascundeFisiere;
    bool ascundeReg;
public:
    Kernel(float rating_impact, const string &data_infectare, const string &nume, const string &metoda_infectare,
        const vector<string> &registrii_modif, const vector<string> &lista_import,
        const vector<string> &stringuri_semnif,const vector<string> &functii_folosite, const vector<string> &taste, bool ascunde_fisiere, bool ascunde_reg)
        : Malware(rating_impact,data_infectare,nume,registrii_modif,metoda_infectare), Rootkit(rating_impact,data_infectare,nume,metoda_infectare,registrii_modif,lista_import,stringuri_semnif),
          Keylogger(rating_impact,data_infectare,nume,metoda_infectare,registrii_modif,functii_folosite, taste),
          ascundeFisiere(ascunde_fisiere),
          ascundeReg(ascunde_reg) {
    }

    ~Kernel() override = default;
    virtual void calcRatingImpact() override {
        ratingImpact = 0;
        Rootkit::calcRatingImpact();   // OBLIGATORIU: trage calculele din Rootkit
        float tempRootkit = ratingImpact;

        Keylogger::calcRatingImpact(); // OBLIGATORIU: trage calculele din Keylogger
        float tempKeylogger = ratingImpact;

        ratingImpact = tempRootkit + tempKeylogger;
        if (ascundeFisiere==true)
            ratingImpact+=20;
        if (ascundeReg==true)
            ratingImpact+=30;
    }

};

class Ransomware: public Malware {
private:
    float ratingCriptare;
    float ratingObfuscare;
public:
    Ransomware(float rating_impact, const string &data_infectare, const string &nume, const string &metoda_infectare,
        const vector<string> &registrii_modif, float rating_criptare, float rating_obfuscare)
        : Malware(rating_impact, data_infectare, nume, registrii_modif, metoda_infectare),
          ratingCriptare(rating_criptare),
          ratingObfuscare(rating_obfuscare) {
    }

    ~Ransomware() override = default;
    virtual void calcRatingImpact() override {
        ratingImpact = 0;
        ratingImpact=ratingCriptare+ratingObfuscare;
    }

};

class Computer {
private:
    static int contor;
    int id;
    vector<shared_ptr<Malware>>malware;
public:
    Computer(const vector<shared_ptr<Malware>> &malware)
        :
          malware(malware){
        id=++contor;
    }

    ~Computer() = default;

    float calcRatingFinal() const {
        float total=0;
        for (auto const& m: malware)
            total+=m->getRatingFinal();
        return total;
    }
    void afisare() const {
        cout<<"computer cu id: "<<id<<" are rating final: "<<calcRatingFinal();
    }
};

class Meniu {
private:
    Meniu() = default;
    ~Meniu() = default;
    Meniu(const Meniu& m)=delete;
    Meniu& operator=(const Meniu& m)=delete;
    vector<shared_ptr<Computer>>computere;
public:
    static Meniu& getInstance(){
        static Meniu instance;
        return instance;
    }

    void afisareCalc() const {
        for (auto const& c: computere)
            c->afisare();
    }
    void afisareSort() {
        sort(computere.begin(), computere.end(), [](const shared_ptr<Computer>&a, const shared_ptr<Computer>&b) {
            return a->calcRatingFinal()>b->calcRatingFinal();
        });
        for (auto const& c: computere)
            c->afisare();
    }
    void primeleK() {
        int k;
        cout<<"introdu nr:";
        cin>>k;
        sort(computere.begin(), computere.end(), [](const shared_ptr<Computer>&a, const shared_ptr<Computer>&b) {
            return a->calcRatingFinal()>b->calcRatingFinal();
        });

        int limita = min(k, (int)computere.size());
        for (auto i = 0; i < limita; i++)
            computere[i]->afisare();
    }

    void procentInfectate() {
        int nr=0;
        for (auto const& c: computere)
            if (c->calcRatingFinal()!=0)
                nr++;
        cout<<"procentaj: "<<(nr*100)/computere.size();
    }
    void populareAutomata() {
        // Asigură-te că vectorul e gol înainte de populare
        computere.clear();

        // --- COMPUTER 1: Infectat cu Rootkit și Ransomware ---
        vector<shared_ptr<Malware>> malwaresPC1;

        // Rootkit-ul primește: rating, data, nume, metoda_infectare, registrii, dlls, stringuri
        malwaresPC1.push_back(make_shared<Rootkit>(
            0.0, "25.05.2026", "ZeusRoot", "WebScam",
            vector<string>{"HKLM-run", "Software-MyKey"},
            vector<string>{"ntoskrnl.exe", "user32.dll"},
            vector<string>{"SSDT", "NtCreateFile"}
        ));

        // Ransomware-ul primește: rating, data, nume, metoda_infectare, registrii, ratingCriptare, ratingObfuscare
        malwaresPC1.push_back(make_shared<Ransomware>(
            0.0, "26.05.2026", "WannaCryV2", "EmailSpam",
            vector<string>{"HKCU-run"},
            8.0, 45.5
        ));

        // Adăugăm primul calculator în sistem
        computere.push_back(make_shared<Computer>(malwaresPC1));


        // --- COMPUTER 2: Infectat cu un hibrid periculos Kernel-Keylogger ---
        vector<shared_ptr<Malware>> malwaresPC2;

        // Kernel-ul primește: rating, data, nume, metoda_infectare, registrii, dlls, stringuri, functii, taste, ascundeFisiere, ascundeReg
        malwaresPC2.push_back(make_shared<Kernel>(
            0.0, "27.05.2026", "DarkKernel", "USB-Drive",
            vector<string>{"NormalReg"},
            vector<string>{"ntoskrnl.exe"},
            vector<string>{"NtCreateFile"},
            vector<string>{"SetWindowsHookEx", "ReadFile"},
            vector<string>{"[Up]", "[Down]", "[Num Lock]"},
            true, true
        ));

        computere.push_back(make_shared<Computer>(malwaresPC2));


        // --- COMPUTER 3: Un calculator curat (fără malware) ---
        vector<shared_ptr<Malware>> malwaresPC3; // vector gol
        computere.push_back(make_shared<Computer>(malwaresPC3));

        cout << "\n>>> [INFO] Baza de date a fost populata automat cu " << computere.size() << " calculatoare.\n";
    }
};
int Computer::contor=0;
int main() {

    Meniu& sistem = Meniu::getInstance();
    sistem.populareAutomata();
    int optiune=-1;
    while (optiune!=0) {
        try{
            cout<<" alege optiune: 1. afisare info pt fiecare calc; "
                  "2. afis info pt fiecare calc ordonat dupa raating "
                  "3. afisare primele k calc dupa rating"
                  "4. afisare procent";
            cin>>optiune;
            if (optiune==1)
                sistem.afisareCalc();
            else
                if (optiune==2)
                    sistem.afisareSort();
            else
                if (optiune==3)
                    sistem.primeleK();
            else
                if (optiune==4)
                    sistem.procentInfectate();
            else
                if (optiune==0)
                    break;
            else
                throw runtime_error("optiune invalida");
        }
        catch (const exception& e) {
            // Tratarea excepțiilor aruncate în interiorul metodelor (propagare obligatorie pentru punctaj)
            cout << "\n>>> EXCEPtIE EVITAT\300: " << e.what() << "\n";
        }
    }

    return 0;
}