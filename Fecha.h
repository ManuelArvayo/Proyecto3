#include <string>
using namespace std;
#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED


class fecha
{
public:
    fecha();
    fecha(int, int, int);
    int getDia(){return dd;};
    int getMes(){return mm;};
    int getAnio(){return aa;};
    void setFecha(int, int, int);
    void operator+(int);
    bool operator>=(fecha);
    bool operator<=(fecha);
    bool operator>(fecha);
    bool operator<(fecha);
    bool operator==(fecha);
    friend ostream &operator << (ostream &os, fecha f);
    friend istream &operator >> (istream &os, fecha &f);
    string nombreMes();


private:
    int dd, mm, aa;
};

fecha::fecha()
{
    aa=1;
    mm=1;
    dd=1;
}

fecha::fecha(int anio, int mes, int dia)
{
    aa=anio;
    mm=mes;
    dd=dia;
}

void fecha::setFecha(int anio, int mes, int dia)
{
    aa=anio;
    mm=mes;
    dd=dia;
}

void fecha:: operator+(int dias)
{
    dd+=dias;
}

bool fecha::operator>=(fecha f1)
{
    if(aa>=f1.aa)
        if(mm>=f1.mm)
            if(dd>=f1.dd)
                return true;
    return false;
}

bool fecha::operator<=(fecha f1)
{
    if(aa<=f1.aa)
        if(mm<=f1.mm)
            if(dd<=f1.dd)
                return true;
    return false;
}

bool fecha::operator>(fecha f1)
{
    if(aa>f1.aa)
        return true;
    if(aa<=f1.aa && mm>f1.mm)
        return true;
    if(aa<=f1.aa && mm<=f1.mm && dd>f1.dd)
        return true;
    return false;
}

bool fecha::operator<(fecha f1)
{
    if(aa<f1.aa)
        return true;
    if(aa>=f1.aa && mm<f1.mm)
        return true;
    if(aa>=f1.aa && mm>=f1.mm && dd<f1.dd)
        return true;
    return false;
}

bool fecha::operator==(fecha f1)
{
    if(aa==f1.aa)
        if(mm==f1.mm)
            if(dd==f1.dd)
                return true;
    return false;
}


string fecha::nombreMes()
{
if(mm==1)
{
    string mes="Ene";
    return mes;
}
if(mm==2)
{
    string mes="Feb";
    return mes;
}
if(mm==3)
{
    string mes="Mar";
    return mes;
}
if(mm==4)
{
    string mes="Abr";
    return mes;
}
if(mm==5)
{
    string mes="May";
    return mes;
}
if(mm==6)
{
    string mes="Jun";
    return mes;
}
if(mm==7)
{
    string mes="Jul";
    return mes;
}
if(mm==8)
{
    string mes="Ago";
    return mes;
}
if(mm==9)
{
    string mes="Sep";
    return mes;
}
if(mm==10)
{
    string mes="Oct";
    return mes;
}
if(mm==11)
{
    string mes="Nov";
    return mes;
}
if(mm==12)
{
    string mes="Dic";
    return mes;
}
return "ERROR";
}

#endif // FECHA_H_INCLUDED
