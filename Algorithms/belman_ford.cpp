#include <main.h>
#include <limits>

using namespace std;

vector<double> Graf::belman_ford(int cvor_id)
{
    if (!is_valid_index(cvor_id)) {
        cerr << "*** Dat indeks cvora nije validan u ovom grafu." << endl;
        return vector<double>();
    }
    
    vector<double> put(cvorovi.size(), numeric_limits<double>::infinity());
    put[cvor_id] = 0;

    for (int iter = 0; iter < (int) cvorovi.size(); iter++) {
        bool update = false;
        for (int p = 0; p < (int) cvorovi.size(); p++)
            for (Edge grana : grane[p])
                if (put[p] + grana.tezina < put[grana.cvor]) {
                    put[grana.cvor] = put[p] + grana.tezina;
                    update = true;
                }
        if (!update)
            return put;
    }

    return vector<double>(cvorovi.size(), -numeric_limits<double>::infinity());
}