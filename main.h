#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#define WINDOWS 0
#define LINUX 1

#ifdef _WIN32
	// Windows-specific code
	#define OS_CODE WINDOWS
#elif __linux__
	// Linux-specific code
	#define OS_CODE LINUX
#endif

using namespace std;

typedef struct {
	int cvor;
	double tezina;
} Edge;

class Graf {
private:
	vector<string> cvorovi;
	vector<vector<Edge>> grane;
	istream *is = nullptr;
	ostream *os = nullptr;
	bool hasNegative;

	bool check_streams();
	vector<vector<double>> listToMatrix();
public:
	Graf(vector<string> cvorovi, vector<vector<Edge>> grane);
	Graf();
	void clear();
	bool is_valid_index(int in);
// I/O Functions
	void unos_cvorova();
	void unos_grana();
	void ispis_grafa_lista();
	void ispis_grafa_matrica();
	void set_streams(istream *is = &cin, ostream *os = &cout);
// Algoritmi
	bool is_directed();
	int broj_komponenti();
	vector<double> dajkstra(int cvor_id);
	vector<double> belman_ford(int cvor_id);
	Graf kruskal();
};