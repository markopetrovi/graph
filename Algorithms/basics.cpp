#include <main.h>
#include <functional>
#include <limits>

using namespace std;

vector<vector<double>> Graf::listToMatrix()
{
	vector<vector<double>> matrix(cvorovi.size(), vector<double>(cvorovi.size(), numeric_limits<double>::infinity()));

	for (int i = 0; i < (int) grane.size(); i++)
		for (Edge grana : grane[i])
			matrix[i][grana.cvor] = grana.tezina;

	return matrix;
}

bool Graf::is_directed()
{
	vector<vector<double>> matrix = listToMatrix();
	bool directed = false;

	for (int i = 0; i < (int) cvorovi.size() - 1; i++) {
		if (matrix[i][i+1] != matrix[i+1][i]) {
			directed = true;
			break;
		}
	}

	return directed;
}

int Graf::broj_komponenti()
{
	vector<int> komponente(cvorovi.size(), 0);
	auto find_unmarked = [&](){
		for (int i = 0; i < (int) komponente.size(); i++)
			if (komponente[i] == 0)
				return i;
		return -1;
	};

	int k = 0;
	function<void(int)> traverse = [&](int cvor_id){
		komponente[cvor_id] = k;
		for (Edge cvor : grane[cvor_id])
			if (komponente[cvor.cvor] == 0)
				traverse(cvor.cvor);
	};
	
	int cvor_id;
	while ((cvor_id = find_unmarked()) != -1) {
		k++;
		traverse(cvor_id);
	}

	return k;
}