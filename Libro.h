#ifndef LIBRO_H_INCLUDED
#define LIBRO_H_INCLUDED

class libro : public material
{
public:
    libro();
    libro(int, string);
    libro(int, string, int, string);
    void setNumPag(int nP){numPag=nP;};
    void setAutor(string a){autor=a;};
    int getNumPag(){return numPag;};
    string getAutor(){return autor;};
    void muestraDatos();
    int cantidadDiasPrestamo();
private:
    int numPag;
    string autor;
};

libro::libro()
{
    numPag=0;
    autor="N/A";
}

libro::libro(int nP, string a)
{
    numPag=nP;
    autor=a;
}

libro::libro(int id,string Tit, int nP, string a) : material(id,Tit)
{
    numPag=nP;
    autor=a;
}

void libro::muestraDatos()
{
    cout<<"Id: "<<idMaterial<<endl;
    cout<<"   Tipo: Libro"<<endl;
    cout<<"   Titulo: "<<titulo<<endl;
    cout<<"   Numero de Paginas: "<<numPag<<endl;
    cout<<"   Autor: "<<autor<<endl;
}

int libro::cantidadDiasPrestamo()
{
    return 7;
}


#endif // LIBRO_H_INCLUDED
