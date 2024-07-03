#include "Wybor.h"
#include <iostream>
#include <cstring>

using namespace std;

#ifdef Kol_2

class Wlasciciel {

};

class Samochod {
protected:
	char numerRej[20];
	int licznik;
	bool stanDopuszczenia;
	Wlasciciel wlasciciel;
	static Samochod* wzorSamochod;
	double wartoscPoczatkowa;
public:
	void setLicznik(int nowyLicznik) {
		if (nowyLicznik >= 0)
		{
			licznik = nowyLicznik;
		}
		else {
			cerr << "Nie mozna ustawic ujemnej wartosci licznika!";
		}
	}

	int getLicznik() const {
		return licznik;
	}

	static void setWzorSamochodu(Samochod* wzor) {
		wzorSamochod = wzor;
	}

	Samochod(const char* numerRej, int licznik, bool stan, const Wlasciciel& wlas, double wartPocz){
		setNumerRej(numerRej);
		setLicznik(licznik);
		stanDopuszczenia = stan;
		wlasciciel = wlas;
		wartoscPoczatkowa = wartPocz;
	}

	void setNumerRej(const char* nrRej) {
		strncpy_s(numerRej, nrRej, sizeof(numerRej) - 1);
	}

	const char* getNumerRej() const {
		return numerRej;
	}

	Samochod() {
		if (wzorSamochod == nullptr) {
			throw runtime_error("Brak instancji wzorcowej");
		}
		setNumerRej(wzorSamochod->numerRej);
		licznik = wzorSamochod->licznik;
		stanDopuszczenia = wzorSamochod->stanDopuszczenia;
		wlasciciel = wzorSamochod->wlasciciel;
		wartoscPoczatkowa = wzorSamochod->wartoscPoczatkowa;
	}

	virtual int obliczZasieg() const {
		if (!stanDopuszczenia)
		{
			throw runtime_error("Samochod niedopuszczony do jazdy!");
		}
		return 800;
	}

	virtual double obliczWartosc() const {
		double WSP_SPARW = (stanDopuszczenia) ? 1.0: 0.2;
		double wartosc = (wartoscPoczatkowa - (0.2 * licznik)) * WSP_SPARW;
		if (wartosc<400)
		{
			wartosc = 400;
		}
		return wartosc;
	}

	bool operator!=(const Samochod& inny) const {
		if (abs(licznik - inny.licznik) > 20)
		{
			return true;
		};
		if (stanDopuszczenia != inny.stanDopuszczenia)
		{
			return true;
		};
		return false;
	}
};

class SamochodElektryczny : public Samochod{
protected: 
	int stanBaterii;
public:
	SamochodElektryczny(const Samochod& samochod, int bateria): Samochod(samochod), stanBaterii(bateria) {
		if (bateria < 0 || bateria>100)
		{
			throw invalid_argument("Stan baterii powinien byc w zakresie od 0 do 100!");
		};
	}

	virtual int obliczZasieg() const override {
		if (!stanDopuszczenia)
		{
			throw runtime_error("Samochod elektryczny niedopuszczony do jazdy!");
		}
		return 2.5 * stanBaterii;
	}
};



Samochod* Samochod::wzorSamochod = nullptr;

int main()
{
	
}

#endif
