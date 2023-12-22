#include <iostream>
#include <main.h>
#include <unistd.h>

using namespace std;

inline void print_menu()
{
    cout << "Izaberite opciju:\n"
			"1) Unos grafa\n"
			"2) Ispis grafa u obliku liste\n"
			"3) Ispis grafa u obliku matrice\n"
			"4) Snimi graf\n"
			"5) Ucitaj graf\n\n"
			"6) Da li je graf usmeren?\n"
			"7) Broj komponenti povezanosti\n"
			"8) Najkraci putevi (Dajkstra)\n"
			"9) Najkraci putevi (Belman-Ford)\n"
			"10) Minimalno razapinjujuce stablo\n"
			"0) Izadji\n";
}

void clear_screen()
{
	if constexpr (OS_CODE == WINDOWS)
		system("cls");
	if constexpr (OS_CODE == LINUX)
		system("clear");
}

void wait_key_press()
{
	char c;
	cout << flush;
	cerr << flush;
	read(0, &c, 1);
}

int main()
{
	clear_screen();
	int n;
Pocetak:
	print_menu();
	cin >> n;

	if (n != 1 && n != 5 && n != 0) {
		cerr << "*** Morate prvo da unesete graf!" << endl;
		goto Pocetak;
	}
	Graf g;
	while (n != 0) {
		switch (n) {
			case 1:
				g.clear();
				g.set_streams();
				g.unos_cvorova();
				g.unos_grana();
				break;
			case 2:
				g.set_streams();
				g.ispis_grafa_lista();
				break;
			case 3:
				g.set_streams();
				g.ispis_grafa_matrica();
				break;
			case 4: {
				cout << "Unesite putanju do fajla:" << endl;
				string s;
				cin >> s;
				ofstream file(s);
				if (!file.good()) {
					cerr << "*** Taj fajl ne postoji ili se ne moze otvoriti!" << endl;
				}
				else {
					g.set_streams(&cin, &file);
					g.ispis_grafa_lista();
					file.close();
				}
				break;
			}
			case 5: {
				cout << "Unesite putanju do fajla:" << endl;
				string s;
				cin >> s;
				ifstream file(s);
				if (!file.good()) {
					cerr << "*** Taj fajl ne postoji ili se ne moze otvoriti!" << endl;
				}
				else {
					ofstream nullfile;
					if constexpr (OS_CODE == WINDOWS)
						nullfile.open("NUL");
					if constexpr (OS_CODE == LINUX)
						nullfile.open("/dev/null");
					g.clear();
					g.set_streams(&file, &nullfile);
					g.unos_cvorova();
					g.unos_grana();
				}
				break;
			}
			case 6:
				if (g.is_directed())
					cout << "Jeste usmeren!" << endl;
				else
					cout << "Nije usmeren!" << endl;
				break;
			case 7:
				cout << "Broj komponenti: " << g.broj_komponenti() << endl;
				break;
			case 8: {
				cout << "Unesite indeks pocetnog cvora: ";
				int in;
				cin >> in;
				vector<double> putevi = g.dajkstra(in);
				cout << "Najkraci putevi do svih cvorova od datog pocetnog cvora:" << endl;
				for (double put : putevi)
					cout << put << " ";
				cout << endl;
				break;
			}
			case 9: {
				cout << "Unesite indeks pocetnog cvora: ";
				int in;
				cin >> in;
				vector<double> putevi = g.belman_ford(in);
				cout << "Najkraci putevi do svih cvorova od datog pocetnog cvora:" << endl;
				for (double put : putevi)
					cout << put << " ";
				cout << endl;
				break;
			}
			case 10:
				Graf minS = g.kruskal();
				minS.set_streams();
				minS.ispis_grafa_matrica();
				break;
		}
		cout << endl << "Pritisnite Enter za nastavak...";
		wait_key_press();
		clear_screen();

		print_menu();
		cin >> n;
	}

	return 0;
}