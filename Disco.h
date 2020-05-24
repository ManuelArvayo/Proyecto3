#ifndef DISCO_H_INCLUDED
#define DISCO_H_INCLUDED

class disco : private material
{
public:
    disco();
    disco(int, string);
    disco(int, string, int, string);
    void setDuracion(int d){duracion=d;};
    void setGenero(string g){genero=g;};
    int getDuracion(){return duracion;};
    string getGenero(){return genero;};
    void muestraDatos();
    int cantidadDiasPrestamo();
private:
    int duracion;
    string genero;

};

disco::disco()
{
    duracion=0;
    genero="N/A";
}

disco::disco(int duracion, string genero)
{
    this ->duracion=duracion;
    this->genero=genero;
}

disco::disco(int id,string Tit, int duracion, string genero) : material(id,Tit)
{
    this ->duracion=duracion;
    this->genero=genero;
}


void disco::muestraDatos()
{
    cout<<"Id: "<<idMaterial<<endl;
    cout<<"   Tipo: Disco"<<endl;
    cout<<"   Titulo: "<<titulo<<endl;
    cout<<"   Duracion: "<<duracion<<endl;
    cout<<"   Genero: "<<genero<<endl;
}

int disco::cantidadDiasPrestamo()
{
    return 2;
}

#endif // DISCO_H_INCLUDED
