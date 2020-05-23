#include <iostream>
#include "Fecha.h"
using namespace std;

ostream &operator << (ostream &os, fecha f) {
    os << f.getDia();
    os << "/" << f.nombreMes() << "/" <<f.getAnio()<< endl;
    return os;
}

istream &operator >> (istream &os, fecha &f) {
    int d,m,a;
    cout << "Dia: ";
    os >> f.dd;
    cout << "Mes: ";
    os >> f.mm;
    cout << "Anio: ";
    os >> f.aa;
    return os;
}

int main()
{

    fecha f1(1200,11,23);
    fecha f2(43,21,2);

    if(f1==f2)
        cout<<"";

    cout<<f1;
    cin>>f2;
    cout<<f2;

}
