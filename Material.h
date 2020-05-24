#include <string>
#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

class material
{
    public:
        material();
        material(int, string);
        void setIdMaterial(int iM){idMaterial=iM;};
        void setTitulo(string Tit){titulo=Tit;};
        int getIdMaterial(){return idMaterial;};
        string getTitulo(){return titulo;};
        virtual void muestraDatos() = 0;
        virtual int cantidadDiasPrestamo() = 0;
    protected:
        int idMaterial;
        string titulo;
};

material::material()
{
    idMaterial=0;
    titulo="N/A";
}

material::material(int id,string Tit)
{
    idMaterial=id;
    titulo=Tit;
}

#endif // MATERIAL_H_INCLUDED
