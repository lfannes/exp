#include <iostream>
#include <string>

using namespace std;

struct Pointer
{
	Pointer() :id(0), name("")
	{
		cout << "Default-constructor" << endl;
	}
	Pointer(int id) :id(id), name("")
	{
		cout << "Only id is filled" << endl;
	}
	Pointer(int id, string name) :id(id), name(name)
	{
		cout << "Everything is filled" << endl;
	}
	void print()
	{
		cout << name << " " << id << endl;
	}
	void setName(string x)
	{
		name = x;
	}
	void setPointer(int* x)
	{
		ptr = x;
		cout << *ptr << endl;
	}
	int id;
	string name;
	int* ptr = nullptr;
};

int main()
{
	int b = 5;
	int* loly = &b;
	Pointer* pointer;
	Pointer x(5);
	pointer = &x;
	pointer->setName("lolypop");
	x.print();
	pointer->setPointer(loly);
	return 0;
}