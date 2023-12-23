#include <main.h>
#include <limits>
#include <algorithm>

using namespace std;

typedef struct {
	Edge x;
	int poc;
} FullEdge;

Graf Graf::kruskal()
{
    if (is_directed()) {
		cerr << "*** Ovaj algoritam trenutno radi samo sa nepovezanim grafovima." << endl;
		return Graf();
	}

	vector<FullEdge> edges;
	for (int i = 0; i < (int) grane.size(); i++)
		for (Edge grana : grane[i])
			edges.push_back({grana, i});
	sort(edges.begin(), edges.end(), [](FullEdge a, FullEdge b){
		return a.x.tezina < b.x.tezina;
	});

	vector<int> komp(cvorovi.size(), 0);
	vector<vector<Edge>> nove_grane(cvorovi.size());
	int kp = 0;
	auto add_edge = [&](FullEdge grana){
		nove_grane[grana.x.cvor].push_back({grana.poc, grana.x.tezina});
		nove_grane[grana.poc].push_back(grana.x);
	};
	for (FullEdge grana : edges) {
		if (komp[grana.poc] == 0 && komp[grana.x.cvor] == 0) {
			komp[grana.x.cvor] = komp[grana.poc] = ++kp;
			add_edge(grana);
		}
		else if (komp[grana.poc] == 0 && komp[grana.x.cvor] != 0) {
			komp[grana.poc] = komp[grana.x.cvor];
			add_edge(grana);
		}
		else if (komp[grana.poc] != 0 && komp[grana.x.cvor] == 0) {
			komp[grana.x.cvor] = komp[grana.poc];
			add_edge(grana);
		}
		else if (komp[grana.poc] != 0 && komp[grana.x.cvor] != 0) {
			if (komp[grana.poc] != komp[grana.x.cvor]) {
				for (int i = 0; i < (int) komp.size(); i++)
					if (komp[i] == komp[grana.x.cvor])
						komp[i] = komp[grana.poc];
				add_edge(grana);
			}
		}
	}
    
    return Graf(cvorovi, nove_grane);
}
