#include <main.h>
#include <algorithm>
#include <limits>
#include <cmath>

using namespace std;

void Graf::unos_cvorova()
{
	int n;

	if (!check_streams())
		return;

	*os << "Unesite broj cvorova:\t";
	*is >> n;

	*os << "Unesite imena cvorova:" << endl;
	string cvor;
	for (int i = 0; i < n; i++) {
		*is >> cvor;
		cvorovi.push_back(cvor);
	}
}

void Graf::unos_grana()
{
	string line, grana_str;
	vector<Edge> v;

	if (!check_streams())
		return;

	hasNegative = false;
	for (int i = 0; i < (int) cvorovi.size(); i++) {
Pocetak:
		*os << "Sa cime je sve povezan cvor " << i << "?" << endl;
		*os << "Unesite brojeve cvorova i tezine u jednom redu:" << endl;
		*os << "Format (razmaci se mogu koristiti umesto ,): C1,T1;C2,T2;C3,T3" << endl;

		do
			getline(*is, line);
		while (line == "\n" || line == "");
		istringstream unos(line);
		v.clear();

		while (getline(unos, grana_str, ';')) {
			if (grana_str == "" || grana_str == " ")
				continue;
			replace_if(grana_str.begin(), grana_str.end(), [](char c){
				return c == ',';
			}, ' ');
			istringstream unos_grane(grana_str);
			Edge grana = {-1, numeric_limits<double>::quiet_NaN()};
			unos_grane >> grana.cvor >> grana.tezina;

			if (!is_valid_index(grana.cvor) || isnan(grana.tezina) || !unos_grane.eof()) {
				if (is == &cin) {
					cerr << "*** Nepravilan unos! Indeksi datih cvorova idu od 0 do " << cvorovi.size() - 1 << " i morate uneti tezinu grane." << endl;
					cerr << "*** Molimo pokusajte ponovo." << endl;
					goto Pocetak;
				}
				else {
					cerr << "*** Fajl je ostecen! Prekidanje unosa!" << endl;
					clear();
					return; 
				}
			}
			if (grana.tezina < 0)
				hasNegative = true;
			v.push_back(grana);
		}
		grane.push_back(v);
	}
}

void Graf::ispis_grafa_lista()
{
	if (!check_streams())
		return;

	if (os == &cout)
		cerr << "Broj cvorova: ";
	*os << cvorovi.size() << endl;

	if (os == &cout)
		cerr << "Imena cvorova: " << endl;
	for (auto cvor : cvorovi)
		*os << cvor << endl;
    
	for (int i = 0; i < (int) grane.size(); i++) {
		if (os == &cout)
			cerr << "Cvor " << i << " je povezan sa cvorovima:" << endl;
		for (auto grana : grane[i])
			*os << grana.cvor << " " << grana.tezina << "; ";
		if (grane[i].size() == 0)
			*os << ";";
		*os << endl;
	}
}

void Graf::ispis_grafa_matrica()
{
	if (!check_streams())
		return;
	
	vector<vector<double>> matrix = listToMatrix();
	for (auto v : matrix) {
		for (auto k : v)
			*os << k << "\t";
		*os << endl;
	}
}