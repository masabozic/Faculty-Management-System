#include <iostream>
#include <string>
#include <string.h>

using namespace std;

enum Pol{MUSKI,ZENSKI};
enum Zaposlece{ZAPOSLEN,OTPUSTEN};
enum VS{ISPITI, PREDAVANJA};
enum Finansiranje{BUDZET, SAMOFINANSIRANJE};

template <class T>
class List{
	private:
		struct listEl{
			T content;
			struct listEl* next;
		};
		listEl *head;
		listEl *tail;
		int noEl;

	public:
		List(){
			head=tail=NULL;
			noEl=0;
		}
		List(const List<T>&);

		List<T>& operator=(const List<T>&);

		virtual ~List();

		int size() const { return noEl; }

		bool empty() const { return head == NULL ? 1 : 0; }

		bool add(int, const T&);

		bool remove(int);

		bool read(int, T&)const;

		void clear();
};

template <class T>
ostream& operator<<(ostream& out, const List<T>& rl) {
	out << endl;
	out << "--------" << endl;
	for(int i = 1; i <= rl.size(); i++){
		if(i != 1) out << ", ";
		T res;
		rl.read(i, res);
		out << res;
	}
	out << endl << "--------" << endl;
	return out;
}

template <class T>
List<T>::List(const List<T>& rl) {
	head = NULL;
	tail = NULL;
	noEl = 0;

	for(int i = 1; i <= rl.noEl; i++){
		T res;
		if(rl.read(i, res))
			add(i, res);
	}
}

template <class T>
List<T>& List<T>::operator=(const List<T>& rl) {
	if(this != &rl) {
		clear();
		head = NULL;
		tail = NULL;
		noEl = 0;

		for(int i = 1; i <= rl.noEl; i++){
			T res;
			if(rl.read(i, res))
				add(i, res);
		}
	}
	return *this;
}

template <class T>
List<T>::~List() {
	while(!empty())
		remove(1);
}

template <class T>
bool List<T>::add(int n, const T& newContent) {
	if(n < 1 || n > noEl + 1)
		return false;
	else {
		listEl* newEl = new listEl;
		if(newEl == NULL)
			return false;
		else {
			newEl->content = newContent;
			if(n == 1) {
				newEl->next = head;
				head = newEl;
			} else if(n == noEl + 1) {
				newEl->next = NULL;
				tail->next = newEl;
			} else {
				listEl* temp = head;
				for(int i = 2; i < n; i++)
					temp = temp->next;
				newEl->next = temp->next;
				temp->next = newEl;
			}
			noEl++;
			if(newEl->next == NULL)
				tail = newEl;
			return true;
		}
	}
}

template <class T>
bool List<T>::remove(int n){
	if(n < 1 || n > noEl)
		return false;
	else {
		if(n == 1) {
			listEl* del = head;
			head = head->next;
			if(tail == del)
				tail = NULL;
			delete del;
			noEl--;
		} else {
			listEl* temp = head;
			for(int i = 2; i < n; i++)
				temp = temp->next;
			listEl* del = temp->next;
			temp->next = del->next;
			if(tail == del)
				tail = temp;
			delete del;
			noEl--;
		}
		return true;
	}
}

template <class T>
bool List<T>::read(int n,T& retVal) const {
	if(n < 1 || n > noEl)
		return false;
	else {
		if(n == 1)
			retVal = head->content;
		else if(n == noEl)
			retVal = tail->content;
		else {
			listEl* temp = head;
			for(int i = 1; i < n; i++)
				temp = temp->next;
			retVal = temp->content;
		}
		return true;
	}
}

template <class T>
void List<T>::clear() {
	while(!empty())
		remove(1);
}

class Ulica{
private:
    string ime;
    int broj;
public:
    Ulica(){
        ime="Episkopa Visariona";
        broj=3;
    }
    Ulica(string im, int br){
        ime=im;
        broj=br;
    }
    Ulica(const Ulica &u){
        ime=u.ime;
        broj=u.broj;
    }
    void setIme(string im){
        ime=im;
    }
    void setBroj(int br){
        broj=br;
    }
    string getIme(){
        return ime;
    }
    int getBroj(){
        return broj;
    }
    friend ostream &operator<<(ostream &izlaz, Ulica &u){
        izlaz << "Ime ulice: " << u.ime << endl;
        izlaz << "Broj: " << u.broj << endl;
    }
    friend istream &operator>>(istream &ulaz, Ulica &u){
        cout << "Unesite ime: " << endl;
        ulaz >> u.ime;
        cout << "Unesite broje: " << endl;
        ulaz >> u.broj;
    }
    void ispisUlice(){
        cout << "Ime ulice je: " << ime << endl;
        cout << "Broj je: " << broj << endl;
    }
};

class Mesto{
private:
    Ulica U;
    string grad;
public:
    Mesto(): U(){
        grad="Novi Sad";
    }
    Mesto(string im, int br, string g):U(im,br){
        grad=g;
    }
    Mesto(const Mesto &m):U(m.U){
        grad=m.grad;
    }
    void setGrad(string g){
        grad=g;
    }
    void setUlica(Ulica ul){
        U=ul;
    }
    string getGrad(){
        return grad;
    }
    Ulica getUlica(){
        return U;
    }
    friend ostream &operator<<(ostream &izlaz, Mesto &m){
        izlaz << "Ulica: " << m.U << endl;
        izlaz << "Grad: " << m.grad << endl;
    }
    friend istream &operator>>(istream &ulaz, Mesto &m){
        cout << "Unesite ulicu: " << endl;
        ulaz >> m.U;
        cout << "Unesite grad: " << endl;
        ulaz >> m.grad;
    }
    void ispisMesta(){
        cout << "Grad je: " << grad << endl;
        U.ispisUlice();
    }
};

class CallCentar{
private:
    Mesto M;
    string brTelefona;
public:
    CallCentar():M(){
        brTelefona="0621654862";
    }
    CallCentar(string im, int br, string g, string b):M(im,br,g){
        brTelefona=b;
    }
    CallCentar(const CallCentar &c):M(c.M){
        brTelefona=c.brTelefona;
    }
    void setMesto(Mesto m){
        M=m;
    }
    void setBrojTelefona(string brTel){
        brTelefona=brTel;
    }
    Mesto getMesto(){
        return M;
    }
    string getBrojTelefona(){
        return brTelefona;
    }
    friend ostream &operator<<(ostream &izlaz, CallCentar &c){
        izlaz << "Mesto: " << c.M << endl;
        izlaz << "Broj telefona: " << c.brTelefona << endl;
    }
    friend istream &operator>>(istream &ulaz, CallCentar &c){
        cout << "Unesite mesto: " << endl;
        ulaz >> c.M;
        cout << "Unesite broje telefona: " << endl;
        ulaz >> c.brTelefona;
    }
    void ispisCallCentra(){
        cout << "Broj telefona je: " << brTelefona << endl;
        M.ispisMesta();
    }
};

class Osoba{
public:
    string ime;
    string prezime;
    string kontakt;
    string datumRodjenja;
    Pol pol;
public:
    Osoba(){
        ime="Masa";
        prezime="Bozic";
        kontakt="0621654862";
        datumRodjenja="7.10.2004";
        pol=ZENSKI;
    }
    Osoba(string i, string p, string k, string d, Pol l){
        ime=i;
        prezime=p;
        kontakt=k;
        datumRodjenja=d;
        pol=l;
    }
    Osoba(const Osoba &o){
        ime=o.ime;
        prezime=o.prezime;
        kontakt=o.kontakt;
        datumRodjenja=o.datumRodjenja;
        pol=o.pol;
    }
    void setIme(string i){
        ime=i;
    }
    void setPrezime(string p){
        prezime=p;
    }
    void setKontakt(string k){
        kontakt=k;
    }
    void setDatumRodjenja(string d){
        datumRodjenja=d;
    }
    void setPol(Pol p){
        pol=p;
    }
    string getIme(){
        return ime;
    }
    string getPrezime(){
        return prezime;
    }
    string getKontakt(){
        return kontakt;
    }
    string getDatumRodjenja(){
        return datumRodjenja;
    }
    string getPol(){
        string temp;
        switch(pol){
        case MUSKI:
            temp="Muski";
            break;
        case ZENSKI:
            temp="Zenski";
            break;
        default:
            temp="Nije odredjen";
            break;
        }
        return temp;
    }
    void ispisOsobe(){
        cout << "Osoba se zove: " << ime << endl;
        cout << "Osoba se preziva: " << prezime << endl;
        cout << "Kontakt osobe je: " << kontakt << endl;
        cout << "Datum rodjenja osobe je: " << datumRodjenja << endl;
        string temp;
        switch(pol){
    case MUSKI:
        temp="Muski";
        break;
    case ZENSKI:
        temp="Zenski";
        break;
    default:
        temp="Nije odredjen";
        break;
        }
        cout << "Pol osobe je: " << pol << endl;
    }
    friend ostream &operator<<(ostream &izlaz, const Osoba &o){
        izlaz << "Ime: " << o.ime << endl;
        izlaz << "Prezime: " << o.prezime << endl;
        izlaz << "Kontakt: " << o.kontakt << endl;
        izlaz << "Datum rodjenja: " << o.datumRodjenja << endl;
        string temp;
        switch(o.pol){
    case MUSKI:
        temp="Muski";
        break;
    case ZENSKI:
        temp="Zenski";
        break;
    default:
        temp="Nije odredjeno";
        break;
        }
        cout << "Pol: " << temp << endl;
        return izlaz;
    }
    friend istream &operator>>(istream &ulaz, Osoba &o){
        cout << "Unesite ime: " << endl;
        ulaz >> o.ime;
        cout << "Unesite prezime: " << endl;
        ulaz >> o.prezime;
        cout << "Unesite kontakt: " << endl;
        ulaz >> o.kontakt;
        cout << "Unesite datum rodjenja: " << endl;
        ulaz >> o.datumRodjenja;
        cout << "Unesite pol(0-zenski, 1-muski): " << endl;
       int i,j;
       ulaz >> i;
        switch(i){
        case 0:
            o.pol=ZENSKI;
            break;
        case 1:
            o.pol=MUSKI;
            break;
      }
      return ulaz;
    }
};

class Finansiranjee{
public:
    int brIspita;
    int brKolokvijuma;
    Finansiranje fin;
public:
    Finansiranjee(){
        brIspita=1;
        brKolokvijuma=1;
        fin=BUDZET;
    }
    Finansiranjee(int bi, int bk, Finansiranje f){
        brIspita=bi;
        brKolokvijuma=bk;
        fin=f;
    }
    Finansiranjee(const Finansiranjee &f){
        brIspita=f.brIspita;
        brKolokvijuma=f.brKolokvijuma;
        fin=f.fin;
    }
    void setBrojIspita(int bi){
        brIspita=bi;
    }
    void setBrKolokvijuma(int bk){
        brKolokvijuma=bk;
    }
    void setFinansiranje(Finansiranje f){
        fin=f;
    }
    int getBrojIspita(){
        return brIspita;
    }
    int getBrojKolokvijuma(){
        return brKolokvijuma;
    }
     string getFinansiranje(){
        string temp;
        switch(fin){
        case BUDZET:
            temp="Budzet";
            break;
        case SAMOFINANSIRANJE:
            temp="Samofinansiranje";
            break;
        default:
            temp="Nije odredjeno";
            break;
        }
        return temp;
    }
    virtual double izracunajSumuNovca()=0;
};

class Student:public Osoba,public Finansiranjee{
public:
    int idStudenta;
    int godina;
    string fakultet;
public:
    Student(){
        Osoba:Osoba();
        idStudenta=1;
        godina=1;
        fakultet="PMF";
    }
    Student(string i, string p, string k, string d, Pol po, int id, int g, string f){
        Osoba:Osoba(i,p,k,d,po);
        idStudenta=id;
        godina=g;
        fakultet=f;
    }
    Student(const Student &s){
        Osoba:Osoba(s.ime, s.prezime, s.kontakt, s.datumRodjenja, s.pol);
        idStudenta=s.idStudenta;
        godina=s.godina;
        fakultet=s.fakultet;
    }
    void setIdStudenta(int i){
        idStudenta=i;
    }
    void setGodina(int g){
        godina=g;
    }
    void setFakultet(string f){
        fakultet=f;
    }
    int getIdStudenta(){
        return idStudenta;
    }
    int getGodina(){
        return godina;
    }
    string getFakultet(){
        return fakultet;
    }
    double izracunajSumuNovca(){
        int i;
        double sum;
        cout << "Izaberite opciju(0-budzet,1-samofinansiranje): " << endl;
        cin >> i;
        if(i==0){
            sum=0;
        }else if(i==1){
            sum=brIspita*2000+brKolokvijuma*1500;
        }
        return sum;
    }
    friend ostream& operator<<(ostream& izlaz, Student &s){
        izlaz << "Ime: " << s.ime << endl;
        izlaz << "Prezime: " << s.prezime << endl;
        izlaz << "Kontakt: " << s.kontakt << endl;
        izlaz << "Datum rodjenja: " << s.datumRodjenja << endl;
        string temp;
    switch(s.pol){
        case MUSKI:
            temp = "Muski";
            break;
        case ZENSKI:
            temp = "Zenski";
            break;
            default:
            temp = "Nije odredjen";
            break;
            }
        izlaz << "Pol: " << temp << endl;
        izlaz << "Broj ispita: " << s.brIspita << endl;
        izlaz << "Broj kolokvijuma: " << s.brKolokvijuma << endl;
        izlaz << "Id studenta: " << s.idStudenta << endl;
        izlaz << "Godina studiranja: " << s.godina << endl;
        izlaz << "Fakultet: " << s.fakultet << endl;
        string temp1;
    switch(s.fin){
        case BUDZET:
            temp1 = "Budzet";
            break;
        case SAMOFINANSIRANJE:
            temp1 = "Samofinansiranje";
            break;
            default:
            temp1 = "Nije odredjen";
            break;
            }
        izlaz << "Finansiranje: " << temp1 << endl;
    }
    friend istream &operator>>(istream &ulaz, Student &s){
        cout << "Unesite ime: " << endl;
        ulaz >> s.ime;
        cout << "Unesite prezime: " << endl;
        ulaz >> s.prezime;
        cout << "Unesite kontakt: " << endl;
        ulaz >> s.kontakt;
        cout << "Unesite datum rodjenja: " << endl;
        ulaz >> s.datumRodjenja;
        cout << "Unesite pol(0-zenski, 1-muski): " << endl;
       int i;
       ulaz >> i;
        switch(i){
        case 0:
            s.pol=ZENSKI;
            break;
        case 1:
            s.pol=MUSKI;
            break;
      }
      cout << "Unesite broj ispita: " << endl;
      ulaz >> s.brIspita;
      cout << "Unesite broj kolokvijuma: " << endl;
      ulaz >> s.brKolokvijuma;
      cout << "Unesite id studenta: " << endl;
      ulaz >> s.idStudenta;
      cout << "Unesite godinu studiranja: " << endl;
      ulaz >> s.godina;
      cout << "Unesite fakultet: " << endl;
      ulaz >> s.fakultet;
      cout << "Unesite finansiranje(0-budzet, 1-samofinansiranje): " << endl;
       int k;
       ulaz >> k;
        switch(k){
        case 0:
            s.fin=BUDZET;
            break;
        case 1:
            s.fin=SAMOFINANSIRANJE;
            break;
      }
    }
    void ispisStudenta(){
        Osoba::ispisOsobe();
        cout << "Broj ispita je: " << brIspita << endl;
        cout << "Broj kolokvijuma je: " << brKolokvijuma << endl;
        cout << "Id studenta je: " << idStudenta << endl;
        cout << "Student je: " << godina << "godina" << endl;
        cout << "Fakultet na koji ide student je: " << fakultet << endl;
        string temp;
        switch(fin){
    case BUDZET:
        temp="Budzet";
        break;
    case SAMOFINANSIRANJE:
        temp="Samofinansiranje";
        break;
    default:
        temp="Nije odredjen";
        break;
        }
        cout << "Finansiranje: " << fin << endl;
    }
};

class Profesor:public Osoba{
public:
    int idProfesora;
    string radnoVreme;
    int plata;
    Zaposlece zaposlece;
    string fakultet;
public:
    Profesor(){
        Osoba:Osoba();
        idProfesora=1;
        radnoVreme="od 8:00 do 18:00";
        plata=50000;
        zaposlece=ZAPOSLEN;
        fakultet="PMF";
    }
    Profesor(string i, string p, string k, string d, Pol l, int id, string rv, int pl, Zaposlece z, string f){
        Osoba:Osoba(i,p,k,d,l);
        idProfesora=id;
        radnoVreme=rv;
        plata=pl;
        zaposlece=z;
        fakultet=f;
    }
    Profesor(const Profesor &p){
        Osoba(p.ime, p.prezime, p.kontakt, p.datumRodjenja, p.pol);
        idProfesora=p.idProfesora;
        radnoVreme=p.radnoVreme;
        plata=p.plata;
        zaposlece=p.zaposlece;
        fakultet=p.fakultet;
    }
    void setIdProfesora(int id){
        idProfesora=id;
    }
    void setRadnoVreme(string r){
        radnoVreme=r;
    }
    void setPlata(int p){
        plata=p;
    }
    void setZaposlece(Zaposlece zap){
        zaposlece=zap;
    }
    void setFakultet(string f){
        fakultet=f;
    }
    int getIdProfesora(){
        return idProfesora;
    }
    string getradnoVreme(){
        return radnoVreme;
    }
    int getPlata(){
        return plata;
    }
    string getZaposlece(){
        string temp;
        switch(zaposlece){
        case ZAPOSLEN:
            temp="Zaposlen";
            break;
        case OTPUSTEN:
            temp="Otpusten";
            break;
        default:
            temp="Nije odredjeno";
            break;
        }
        return temp;
    }
    string getFakultet(){
        return fakultet;
    }
    void ispisProfesora(){
        Osoba::ispisOsobe();
        cout << "Id profesora je: " << idProfesora << endl;
        cout << "Radno vreme profesora je: " << radnoVreme << endl;
        cout << "Plata profesora je: " << plata << endl;
          string temp;
        switch(zaposlece){
    case ZAPOSLEN:
        temp="Zaposlen";
        break;
    case OTPUSTEN:
        temp="Otpusten";
        break;
    default:
        temp="Nije odredjen";
        break;
        }
        cout << "Profesor je: " << zaposlece << endl;
        cout << "Fakultet na kom profesor radi je: " << fakultet << endl;
    }
    friend ostream& operator<<(ostream& izlaz, Profesor &p){
        izlaz << "Ime: " << p.ime << endl;
        izlaz << "Prezime: " << p.prezime << endl;
        izlaz << "Kontakt: " << p.kontakt << endl;
        izlaz << "Datum rodjenja: " << p.datumRodjenja << endl;
        string temp;
    switch(p.pol){
        case MUSKI:
            temp = "Muski";
            break;
        case ZENSKI:
            temp = "Zenski";
            break;
            default:
            temp = "Nije odredjen";
            break;
            }
            izlaz << "Pol: " << temp << endl;
        izlaz << "Id profesora: " << p.idProfesora << endl;
        izlaz << "Radno vreme profesora: " << p.radnoVreme << endl;
        izlaz << "Plata: " << p.plata << endl;
        string temp1;
    switch(p.zaposlece){
        case ZAPOSLEN:
            temp1 = "Zaposlen";
            break;
        case OTPUSTEN:
            temp1 = "Otpusten";
            break;
            default:
            temp1 = "Nije odredjen";
            break;
            }
            izlaz << "Zaposlece: " << temp1 << endl;
            izlaz << "Fakultet: " << p.fakultet << endl;
    }
    friend istream &operator>>(istream &ulaz, Profesor &p){
        cout << "Unesite ime: " << endl;
        ulaz >> p.ime;
        cout << "Unesite prezime: " << endl;
        ulaz >> p.prezime;
        cout << "Unesite kontakt: " << endl;
        ulaz >> p.kontakt;
        cout << "Unesite datum rodjenja: " << endl;
        ulaz >> p.datumRodjenja;
        cout << "Unesite pol(0-zenski, 1-muski): " << endl;
       int i;
       ulaz >> i;
        switch(i){
        case 0:
            p.pol=ZENSKI;
            break;
        case 1:
            p.pol=MUSKI;
            break;
      }
      cout << "Unesite id: " << endl;
      ulaz >> p.idProfesora;
      cout << "Unesite radno vreme profesora: " << endl;
      ulaz >> p.radnoVreme;
      cout << "Unesite platu profesora: " << endl;
      ulaz >> p.plata;
      cout << "Unesite zaposlece(0-otpusten, 1-zaposlen): " << endl;
       int j;
       ulaz >> j;
        switch(j){
        case 0:
            p.zaposlece=OTPUSTEN;
            break;
        case 1:
            p.zaposlece=ZAPOSLEN;
            break;
      }
      cout << "Unesite fakultet: " << endl;
      ulaz >> p.fakultet;
    }
};

class Predmet{
private:
    Profesor profesor;
    string naziv;
public:
    Predmet():profesor(){
        naziv="Programiranje";
    }
    Predmet(Profesor prof, string ime):profesor(prof){
        naziv=ime;
    }
    Predmet(const Predmet &p):profesor(p.profesor){
        naziv=p.naziv;
    }
    void setProfesor(Profesor prof){
        profesor=prof;
    }
    void setNaziv(string ime){
        naziv=ime;
    }
    Profesor getProfesor(){
        return profesor;
    }
    string getNaziv(){
        return naziv;
    }
    void ispisPredmeta(){
        cout << "Naziv predmeta je: " << naziv << endl;
        profesor.ispisProfesora();
    }
};

class Osoblje:public Osoba{
public:
    int idOsoblja;
    string radnoVreme;
    int plata;
    Zaposlece zaposlece;
public:
    Osoblje(){
        Osoba:Osoba();
        idOsoblja=1;
        radnoVreme="od 8:00 do 18:00";
        plata=30000;
        zaposlece=ZAPOSLEN;
    }
    Osoblje(string i, string p, string d, string k, Pol pol, int id, string r, int pl, Zaposlece z){
        Osoba:Osoba(i,p,d,k,pol);
        idOsoblja=id;
        radnoVreme=r;
        plata=pl;
        zaposlece=z;
    }
    Osoblje(const Osoblje &o){
        Osoba:Osoba(o.ime, o.prezime, o.datumRodjenja, o.kontakt, o.pol);
        idOsoblja=o.idOsoblja;
        radnoVreme=o.radnoVreme;
        plata=o.plata;
        zaposlece=o.zaposlece;
    }
    void setIdOsoblja(int id){
        idOsoblja=id;
    }
    void setRadnoVreme(string rv){
        radnoVreme=rv;
    }
    void setPlata(int p){
        plata=p;
    }
    void setZaposlece(Zaposlece z){
        zaposlece=z;
    }
    int getIdOsoblja(){
        return idOsoblja;
    }
    string getRadnoVreme(){
        return radnoVreme;
    }
    int getPlata(){
        return plata;
    }
    string getZaposlece(){
        string temp;
        switch(zaposlece){
            case ZAPOSLEN:
            temp="Zaposlen";
            break;
        case OTPUSTEN:
            temp="Otpusten";
            break;
        default:
            temp="Nije odredjeno";
            break;
        }
        return temp;
    }
    void ispisOsoblja(){
        Osoba::ispisOsobe();
        cout << "Id osoblja je: " << idOsoblja << endl;
        cout << "Radno vreme osoblja je: " << radnoVreme << endl;
        cout << "Plata osoblja je: " << plata << endl;
          string temp;
        switch(zaposlece){
    case ZAPOSLEN:
        temp="Zaposlen";
        break;
    case OTPUSTEN:
        temp="Otpusten";
        break;
    default:
        temp="Nije odredjen";
        break;
        }
        cout << "Osoblje je: " << zaposlece << endl;
    }
    friend ostream& operator<<(ostream& izlaz, Osoblje &o){
        izlaz << "Ime: " << o.ime << endl;
        izlaz << "Prezime: " << o.prezime << endl;
        izlaz << "Kontakt: " << o.kontakt << endl;
        izlaz << "Datum rodjenja: " << o.datumRodjenja << endl;
        string temp;
    switch(o.pol){
        case MUSKI:
            temp = "Muski";
            break;
        case ZENSKI:
            temp = "Zenski";
            break;
            default:
            temp = "Nije odredjen";
            break;
            }
            izlaz << "Pol: " << temp << endl;
        izlaz << "Id osoblja: " << o.idOsoblja << endl;
        izlaz << "Radno vreme osoblja: " << o.radnoVreme << endl;
        izlaz << "Plata: " << o.plata << endl;
        string temp1;
    switch(o.zaposlece){
        case ZAPOSLEN:
            temp1 = "Zaposlen";
            break;
        case OTPUSTEN:
            temp1 = "Otpusten";
            break;
            default:
            temp1 = "Nije odredjen";
            break;
            }
            izlaz << "Zaposlece: " << temp1 << endl;
    }
    friend istream &operator>>(istream &ulaz, Osoblje &o){
        cout << "Unesite ime: " << endl;
        ulaz >> o.ime;
        cout << "Unesite prezime: " << endl;
        ulaz >> o.prezime;
        cout << "Unesite kontakt: " << endl;
        ulaz >> o.kontakt;
        cout << "Unesite datum rodjenja: " << endl;
        ulaz >> o.datumRodjenja;
        cout << "Unesite pol(0-zenski, 1-muski): " << endl;
       int i;
       ulaz >> i;
        switch(i){
        case 0:
            o.pol=ZENSKI;
            break;
        case 1:
            o.pol=MUSKI;
            break;
      }
      cout << "Unesite id: " << endl;
      ulaz >> o.idOsoblja;
      cout << "Unesite radno vreme osoblja: " << endl;
      ulaz >> o.radnoVreme;
      cout << "Unesite platu osoblja: " << endl;
      ulaz >> o.plata;
      cout << "Unesite zaposlece(0-otpusten, 1-zaposlen): " << endl;
       int j;
       ulaz >> j;
        switch(j){
        case 0:
            o.zaposlece=OTPUSTEN;
            break;
        case 1:
            o.zaposlece=ZAPOSLEN;
            break;
      }
    }
};

class InfoIspiti{
private:
    string vreme;
    Predmet predmet;
    float maxBodovi;
    float bodoviZaProlaz;
public:
    InfoIspiti():predmet(){
        vreme="8:10";
        maxBodovi=100;
        bodoviZaProlaz=60;
    }
    InfoIspiti(Predmet p, string v, float mb, float bzp):predmet(p){
        vreme=v;
        maxBodovi=mb;
        bodoviZaProlaz=bzp;
    }
    InfoIspiti(const InfoIspiti &m):predmet(m.predmet){
        vreme=m.vreme;
        maxBodovi=m.maxBodovi;
        bodoviZaProlaz=m.bodoviZaProlaz;
    }
    void setVreme(string v){
        vreme=v;
    }
    void setPredmet(Predmet p){
        predmet=p;
    }
    void setMaxBodovi(float mb){
        maxBodovi=mb;
    }
    void setBodoviZaProlaz(float bzp){
        bodoviZaProlaz=bzp;
    }
    string getVreme(){
        return vreme;
    }
    Predmet getPredmet(){
        return predmet;
    }
    float getMaxBodovi(){
        return maxBodovi;
    }
    float getBodoviZaProlaz(){
        return bodoviZaProlaz;
    }
    void ispisInfoIspiti(){
        cout << "Vreme održavanja ispita je: " << vreme << endl;
        cout << "Maksimalan broj bodova koje mozete osvojiti na ispitu je: " << maxBodovi << endl;
        cout << "Bodovi koji su vam potrebni da biste položili ispit su: " << bodoviZaProlaz << endl;
        predmet.ispisPredmeta();
    }
};

class Index{
private:
    List<int>ocena;
    Predmet predmet;
    Student student;
public:
    Index():predmet(),student(),ocena(){
    }
    Index(List<int>oc, Predmet p1, Student s1):predmet(p1),student(s1),ocena(oc){
    }
    Index(const Index &o):predmet(o.predmet),student(o.student),ocena(o.ocena){
    }
    void setOcena(List<int>o){
        ocena=o;
    }
    void setPredmet(Predmet p){
        predmet=p;
    }
    void setStudent(Student s){
        student=s;
    }
    List<int> getOcena(){
        return ocena;
    }
    Predmet getPredmet(){
        return predmet;
    }
    Student getStudent(){
        return student;
    }
    Index& operator+=(int k){
        ocena.add(ocena.size()+1,k);
        return *this;
    }
    void ispisOcena(){
        if(ocena.size()==0){
            cout << "Nema ocena" << endl;
        }else{
            int j;
            int l;
            for(j=1;j<ocena.size();j++){
                ocena.read(j,l);
                cout << l;
            }
        }
    }
    void ispisIndeksa(){
        predmet.ispisPredmeta();
        student.ispisStudenta();
        ispisOcena();
    }
};

class Zaposleni{
private:
    List<Profesor*> prof;
    List<Osoblje*> osoblje;
public:
    Zaposleni():prof(), osoblje(){}
    Zaposleni(List<Profesor*> p, List<Osoblje*> o):prof(p), osoblje(o){}
    Zaposleni(const Zaposleni &z):prof(z.prof), osoblje(z.osoblje){}
    void setProfesor(List<Profesor*> p){
        prof=p;
    }
    void setOsoblje(List<Osoblje*> o){
        osoblje=o;
    }
    List<Profesor*> getProfesor(){
        return prof;
    }
    List<Osoblje*> getOsoblje(){
        return osoblje;
    }
    Zaposleni& operator+=(Profesor& profesor){
        if(profesor.getZaposlece()=="ZAPOSLEN"){
            prof.add(prof.size()+1, &profesor);
        }
        return *this;
    }
    Zaposleni& operator+=(Osoblje& osob){
        if(osob.getZaposlece()=="ZAPOSLEN"){
            osoblje.add(osoblje.size()+1, &osob);
        }
        return *this;
    }
    void ispisProfesora(){
        if(prof.size()==0){
            cout << "Nema zaposlenih profesora" << endl;
        }else{
            Profesor* p;
            cout << "Profesori su: " << endl;
            int i;
            for(i=1;i<=prof.size();i++){
                prof.read(i,p);
            }
        }
    }
    void ispisOsoblja(){
        if(osoblje.size()==0){
            cout << "Nema zaposlenog osoblja" << endl;
        }else{
            Osoblje* o;
            cout << "Osoblje je: " << endl;
            int i;
            for(i=1;i<osoblje.size();i++){
                osoblje.read(i,o);
            }
        }
    }
    void ispisZaposlenih(){
        ispisProfesora();
        ispisOsoblja();
    }
};

class Prostorija{
public:
    double visina;
    double sirina;
public:
    Prostorija(){
        visina=1;
        sirina=1;
    }
    Prostorija(double v, double s){
        visina=v;
        sirina=s;
    }
    Prostorija(const Prostorija &p){
        visina=p.visina;
        sirina=p.sirina;
    }
   void setSirina(double s){
        if(s>0)
            sirina=s;
        else
            cout << "Nije uneta validna vrednost" << endl;
    }
    void setVisina(double v){
    if(v>0)
        visina=v;
    else
        cout << "Nije uneta validna vrednost" << endl;
    }
    double getVisina(){
        return visina;
    }
    double getSirina(){
        return sirina;
    }
    virtual double izracunajPovrsinu()=0;
};
class Sala:public Prostorija{
public:
    List<int>brSlobodnihSala;
    List<int>brZauzetihSala;
    int brojSpratova;
public:
    Sala():brSlobodnihSala(), brZauzetihSala(){
        brojSpratova=1;
    }
    Sala(List<int>S, List<int>Z, int bs):brSlobodnihSala(S), brZauzetihSala(Z){
        brojSpratova=bs;
    }
    Sala(Sala &s):brSlobodnihSala(s.brSlobodnihSala), brZauzetihSala(s.brZauzetihSala){
        brojSpratova=s.brojSpratova;
    }
    void setBrSlobodnihSala(List<int>S){
        brSlobodnihSala=S;
    }
    void setBrZauzetihSala(List<int>Z){
        brZauzetihSala=Z;
    }
    void setBrojSpratova(int brS){
        brojSpratova=brS;
    }
    List<int> getBrSlobodnihSala(){
        return brSlobodnihSala;
    }
    List<int> getBrZauzetihSala(){
        return brZauzetihSala;
    }
    int getBrojSpratova(){
        return brojSpratova;
    }
    double izracunajPovrsinu(){
        return (sirina*visina);
    }
    Sala& operator+=(int i){
        brSlobodnihSala.add(brSlobodnihSala.size()+1,i);
        return *this;
    }
    void ispisBrSlobodnihSala(){
        if(brSlobodnihSala.size()==0){
            cout << "Nema slobodnih sala" << endl;
        }else{
            int i;
            int s;
            for(i=1;i<brSlobodnihSala.size();i++){
                    brSlobodnihSala.read(i,s);
                    cout << s;
            }
        }
    }
    void ispisBrZauzetihSala(){
        if(brZauzetihSala.size()==0){
            cout << "Nema zauzetih sala" << endl;
        }else{
            int i;
            int z;
            for(i=1;i<brZauzetihSala.size();i++){
                    brZauzetihSala.read(i,z);
                    cout << z;
            }
        }
    }
    void ispisSale(){
        ispisBrSlobodnihSala();
        ispisBrZauzetihSala();
        cout << "Broj spratova je: " << brojSpratova << endl;
    }
};

class Fakultet{
public:
    Mesto m;
    CallCentar call;
    int brSala;
    int brSpratova;
    string imeFakulteta;
    Zaposleni zaposleni;
public:
    Fakultet():m(),call(),zaposleni(){
        brSala=500;
        brSpratova=5;
        imeFakulteta="Fakultet";
    }
    Fakultet(Mesto me, CallCentar c,Zaposleni zap, int b, int s, string i):m(me),call(c),zaposleni(zap){
        brSala=b;
        brSpratova=s;
        imeFakulteta=i;
    }
    Fakultet(const Fakultet &f):m(f.m),call(f.call),zaposleni(f.zaposleni){
        brSala=f.brSala;
        brSpratova=f.brSpratova;
        imeFakulteta=f.imeFakulteta;
    }
    void setMesto(Mesto me){
        m=me;
    }
    void satCallCentar(CallCentar c){
        call=c;
    }
    void setBrSala(int s){
        brSala=s;
    }
    void setBrSpratova(int b){
        brSpratova=b;
    }
    void setImeFakulteta(string ime){
        imeFakulteta=ime;
    }
    void setZaposleni(Zaposleni zap){
        zaposleni=zap;
    }
    Mesto getMesto(){
        return m;
    }
    CallCentar getCallCentar(){
        return call;
    }
    int getBrSala(){
        return brSala;
    }
    int getBrSpratova(){
        return brSpratova;
    }
    string getImeFakulteta(){
        return imeFakulteta;
    }
    Zaposleni getZaposleni(){
        return zaposleni;
    }
    friend ostream &operator<<(ostream &izlaz, Fakultet &f){
        izlaz << "Ime fakulteta: " << f.imeFakulteta << endl;
        izlaz << "Broj spratova: " << f.brSpratova << endl;
        izlaz << "Broj sala: " << f.brSala << endl;
        izlaz << "Call centar: " << f.call << endl;
        izlaz << "Mesto: " << f.m << endl;
    }
    friend istream &operator>>(istream &ulaz, Fakultet &f){
        cout << "Unesite ime: " << endl;
        ulaz >> f.imeFakulteta;
        cout << "Unesite broje spratova: " << endl;
        ulaz >> f.brSpratova;
        cout << "Unesite broj sala: " << endl;
        ulaz >> f.brSala;
    }
    void ispisFakulteta(Mesto mesto, CallCentar c, Zaposleni z){
        mesto.ispisMesta();
        c.ispisCallCentra();
        z.ispisZaposlenih();
        cout << "Broj sala koje fakultet ima je: " << brSala << endl;
        cout << "Broj spratova fakulteta je: " << brSpratova << endl;
        cout << "Ime fakulteta je: " << imeFakulteta << endl;
    }
};

int main()
{
    return 0;
}
