#ifndef SOFTWARE_H_INCLUDED
#define SOFTWARE_H_INCLUDED

class software : private material
{
public:
    software();
    software(int, string);
    void setVersion(int v){version=v;};
    void setSO(string sO){this ->sO=sO;};
    int getVersion(){return version;};
    string getSO(){return sO;};
    void muestraDatos();
    int cantidadDiasPrestamo();
private:
    int version;
    string sO;
};

software::software()
{
    version=0;
    sO="N/A";
}

software::software(int version,string sO)
{
    this->version=version;
    this->sO=sO;
}

void software::muestraDatos()
{
    cout<<"Id: "<<idMaterial<<endl;
    cout<<"   Tipo: Software"<<endl;
    cout<<"   Titulo: "<<titulo<<endl;
    cout<<"   Version: "<<version<<endl;
    cout<<"   SO: "<<sO<<endl;
}

int software::cantidadDiasPrestamo()
{
    return 1;
}

#endif // SOFTWARE_H_INCLUDED
