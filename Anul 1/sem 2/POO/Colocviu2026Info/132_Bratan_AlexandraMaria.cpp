/*Bratan Alexandra-Maria
 *Grupa 132
 *CLion
 *g++.exe (GCC) 13.1.0
 *Obreja Camelia */

#include <iostream>
#include <string>
#include<vector>
#include <memory>
#include <algorithm>
using namespace std;


class EroareAplicatie: public runtime_error {
public:
    explicit EroareAplicatie(const string& mesaj): runtime_error(mesaj){}
};

class EroareDate: public EroareAplicatie {
public:
    explicit EroareDate(const string& mesaj): EroareAplicatie(mesaj){}
};

class Abonament {
protected:
    string denumire;
    static int contor;
    int id;
    float pretBaza;
    int durata;
public:
    Abonament(){id=++contor;}

    Abonament(const string &denumire, float pret_baza, int durata)
        : denumire(denumire),
          pretBaza(pret_baza),
          durata(durata) {
        id=++contor;
    }

    virtual ~Abonament() = default;
    virtual float calcPret()=0;
    virtual float pretRedus()=0;

    virtual void citire(istream& in) {
        cout<<"denumire: ";
        in>>denumire;
        cout<<"durata: ";
        in>>durata;
        cout<<"pret de baza: ";
        in>>pretBaza;
    }
    virtual void afisare(ostream& out) const {
        out<<"denumire: "<<denumire<<" id: "<<id<<"durata: "<<durata;
    }
};

istream& operator>>(istream&in, Abonament& a) {
    a.citire(in);
    return in;
}

ostream& operator<<(ostream& out, const Abonament& a) {
    a.afisare(out);
    return out;
}

class Standard: public Abonament {
private:
    int nrMaxAccesari;
    bool includeEvaluare;
public:
    Standard() = default;

    Standard(const string &denumire, float pret_baza, int durata, int nr_max_accesari, bool include_evaluare)
        : Abonament(denumire, pret_baza, durata),
          nrMaxAccesari(nr_max_accesari),
          includeEvaluare(include_evaluare) {
        if (durata<2)
            throw EroareDate("Standard are durata minima de 2 luni!");
    }

    ~Standard() override = default;

    virtual float calcPret() override {
        return pretBaza*durata;
    }
    virtual float pretRedus() override {
        return  pretBaza*durata;
    }

    void citire(istream &in) override {
        Abonament::citire(in);
        cout<<"nr max accesari: ";
        in>>nrMaxAccesari;
        cout<<"unclude evaluare? true/false";
        in>>includeEvaluare;
    }

    virtual void afisare(ostream& out) const{
        Abonament::afisare(out);
        out<<"nr max accesari: "<<nrMaxAccesari<<"unclude evaluare? true/false: "<<includeEvaluare;
    }
};

class Premium: public Abonament {
private:
    int nrInvitatii;
    bool oferaAcces;
public:
    Premium() = default;

    Premium(const string &denumire, float pret_baza, int durata, int nr_invitatii, bool ofera_acces)
        : Abonament(denumire, pret_baza, durata),
          nrInvitatii(nr_invitatii),
          oferaAcces(ofera_acces) {
    }

    ~Premium() override = default;
    virtual float calcPret() override {
        return pretBaza*durata+30*nrInvitatii;
    }
    virtual float pretRedus() override {
        if (durata>=6)
            return 12/100*calcPret();
    }
    void citire(istream &in) override {
        Abonament::citire(in);
        cout<<"nr invitatii: ";
        in>>nrInvitatii;
        cout<<"ofera acces? true/false";
        in>>oferaAcces;
    }

    virtual void afisare(ostream& out) const{
        Abonament::afisare(out);
        out<<"nr invitatii: "<<nrInvitatii<<"ofera acces? "<<oferaAcces;
    }


};

class Corporate: public Abonament {
private:
    int nrPersoaneIncluse;
    float procentNegociat;
public:
    Corporate() = default;

    Corporate(const string &denumire, float pret_baza, int durata, int nr_persoane_incluse, float procent_negociat)
        : Abonament(denumire, pret_baza, durata),
          nrPersoaneIncluse(nr_persoane_incluse),
          procentNegociat(procent_negociat) {
        if (nrPersoaneIncluse<5)
            throw EroareDate("minim 5 persoane!");


    }

    ~Corporate() override = default;
    virtual float calcPret() override {
        return pretBaza*durata*nrPersoaneIncluse;
    }
    virtual float pretRedus() override {
        return procentNegociat*calcPret();

    }
};

int Abonament::contor=0;


class Contract {
private:
    static int contor;
    int id;
    string tipClient;
    string numeTitular;
    string numeCompanie;
    vector<shared_ptr<Abonament>> abonamente;
public:
    Contract() = default;

    Contract(const string &tip_client, const string &nume_titular,
        const vector<shared_ptr<Abonament>> &abonamente, const string &nume_companie="")
        : tipClient(tip_client),
          numeTitular(nume_titular),
          numeCompanie(nume_companie),
          abonamente(abonamente) {
        if (tipClient!="persoana fizica" && tipClient!="persoana juridica")
            throw EroareDate("tip de persoana invalid");

    }

    ~Contract() = default;
    virtual void citire(istream& in) {
        cout<<"tip client: ";
        in>>tipClient;
        cout<<"nume titular: ";
        in>>numeTitular;
        if (tipClient=="persoana juridica") {
            cout<<"nume companie: ";
            in>>numeCompanie;
        }


    }
    virtual void afisare(ostream& out) const {
        out<<"tip client:: "<<tipClient<<" id: "<<id<<"nume titular:: "<<numeTitular;
        out<<"nume companie: "<<numeCompanie;
    }

};
istream& operator>>(istream&in, Contract& a) {
    a.citire(in);
    return in;
}

ostream& operator<<(ostream& out, const Contract& a) {
    a.afisare(out);
    return out;
}

int Contract::contor=0;


class Program {
private:
    Program() = default;

    ~Program() = default;
    Program(const Program& m)=delete;
    Program& operator=(const Program& m)=delete;
    vector<shared_ptr<Abonament>> abonamente;
    vector<shared_ptr<Contract>> contracte;

public:
    static Program& getInstance() {
        static Program instance;
        return instance;
    }

    void adaugareAbonament() {
        cout<<"tip: ";
        string tip;
        cin>>tip;
        shared_ptr<Abonament> a=nullptr;
        if (tip=="standard")
            a=make_shared<Standard>();
        else
            if (tip=="premium")
                a=make_shared<Premium>();
        else
            if (tip=="corporate")
                a=make_shared<Corporate>();
        if (a!=nullptr) {
            cin>>*a;
            abonamente.push_back(a);
        }

    }

    void afisareAbonamente() {
        for (auto const& a:abonamente)
            cout<<*a;
    }

    void filtrareAbonamente() {
        cout<<" tip: ";
        string tip;
        cin>>tip;
        for (auto const&a: abonamente) {
            if (tip=="standard")
                if (dynamic_pointer_cast<Standard>(a))
                    cout<<*a;
            else
                if (tip=="premium")
                    if (dynamic_pointer_cast<Premium>(a))
                        cout<<*a;
                else
                    if (tip=="corporate")
                        if (dynamic_pointer_cast<Corporate>(a))
                            cout<<*a;
        }
    }

    void adaugareContract() {
        cout<<"tip client: ";
        string tipClient;
        cin>>tipClient;
        cout<<"nume titular: ";
        string numeTitular;
        cin>>numeTitular;
        string numeCompanie;
        if (tipClient=="persoana juridica") {
            cout<<"nume companie: ";
            cin>>numeCompanie;
        }
        //nu am mai apucat sa adaug si abonament
        /*cout<<"nr abonamente: ";
        int nr;
        cin>>nr;
        if (nr<1)
            throw EroareDate("minim 1");
        for (int i=1;i<=nr;i++) {
            adaugareAbonament();
        }
        contracte.push_back(tipClient,numeTitular,numeCompanie);*/
    }



};

int main() {

    Program &s= Program::getInstance();
    int opt=-1;
    while (opt!=0) {
        try {
            cout<<"1. adaugare abonament";
            cout<<"2.afisare toate abonamente";
            cout<<"3. filtrare abonamente dupa tip";
            cout<<"4. adaugare contract nou";
            cin>>opt;
            if (opt==1)
                s.adaugareAbonament();
            else
                if (opt==2)
                    s.afisareAbonamente();
            else
                if (opt==3)
                    s.filtrareAbonamente();
            else
                if (opt==4)
                    s.adaugareContract();
            else
                if (opt==0)
                    break;

        }
        catch (const EroareDate& e) {
            cout<<"exceptie: "<<e.what()<<"\n";
        }
    }

    return 0;
}