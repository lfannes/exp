#include <iostream>
#include <string>

using namespace std;

class Persoon
{
public:
    Persoon(string name, int lengte) :name(name), lengte(lengte)
    {
    }

    operator int () const
    {
        return lengte;
    }
private:
    string name;
    int lengte;
};

int main()
{
    Persoon buurman("Simon" , 172);
    cout << static_cast<int>(buurman) << endl;
	return 0;
}
