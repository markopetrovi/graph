#include <main.h>
#include <limits>

using namespace std;

vector<double> Graf::dajkstra(int cvor_id)
{
    if (hasNegative) {
        cerr << "*** Ne mozete primeniti ovaj algoritam. Graf sadrzi grane sa negativnim tezinama." << endl;
        return vector<double>();
    }
    if (!is_valid_index(cvor_id)) {
        cerr << "*** Dat indeks cvora nije validan u ovom grafu." << endl;
        return vector<double>();
    }

    vector<double> put(cvorovi.size(), numeric_limits<double>::infinity());
    vector<bool> uradjeni(cvorovi.size(), false);
    put[cvor_id] = 0;

    auto find_next = [&](){
        int mini = -1;
        double minval = numeric_limits<double>::infinity();
        for (int i = 0; i < (int) cvorovi.size(); i++)
            if (put[i] < minval && !uradjeni[i]) {
                minval = put[i];
                mini = i;
            }
        return mini;
    };

    int current;
    while ((current = find_next()) != -1) {
        uradjeni[current] = true;
        for (Edge grana : grane[current])
            if (put[current] + grana.tezina < put[grana.cvor])
                put[grana.cvor] = put[current] + grana.tezina;
    }

    return put;
}