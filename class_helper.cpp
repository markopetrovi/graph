#include <main.h>

using namespace std;

void Graf::clear()
{
	cvorovi.clear();
	grane.clear();
}

bool Graf::check_streams()
{
	if (!is || !os) {
		cerr << "You have to setup stdio/stdout streams first." << endl;
		return false;
	}
	return true;
}

void Graf::set_streams(istream *is, ostream *os)
{
	this->is = is;
	this->os = os;
}

bool Graf::is_valid_index(int in)
{
	return !(in < 0 || in >= (int) cvorovi.size());
}

Graf::Graf() {}
Graf::Graf(vector<string> cvorovi, vector<vector<Edge>> grane)
{
	this->cvorovi = cvorovi;
	this->grane = grane;
}