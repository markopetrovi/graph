#include <main.h>
#include <limits>

using namespace std;

// TODO: Implementirati pracenje komponenti povezanosti
Graf Graf::kruskal()
{
    if (is_directed()) {
        cerr << "*** FIXME: Ovaj algoritam trenutno radi samo sa nepovezanim grafovima." << endl;
        return Graf();
    }

    vector<bool> ukljucen(cvorovi.size(), false);
    vector<vector<double>> matrix = listToMatrix();
    int i, j;
    auto find_min = [&](){
        double minval = numeric_limits<double>::infinity();
        int mini = -1, minj = -1;
        for (i = 0; i < (int) cvorovi.size(); i++)
            for (j = 0; j < (int) cvorovi.size(); j++)
                if (matrix[i][j] < minval && !ukljucen[i] && !ukljucen[j]) {
                    minval = matrix[i][j];
                    mini = i;
                    minj = j;
                }
        i = mini;
        j = minj;
        return minval;
    };

    vector<vector<Edge>> nove_grane(cvorovi.size());
    while (find_min() != numeric_limits<double>::infinity()) {
        ukljucen[i] = true;
        ukljucen[j] = true;
        Edge grana = {j, matrix[i][j]};
        nove_grane[i].push_back(grana);
        grana = {i, matrix[i][j]};
        nove_grane[j].push_back(grana);
    }
    return Graf(cvorovi, nove_grane);
}
