#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

class material
{
    public:
        void muestraDatos();
        int cantidadDiasPrestamo();
    protected:
        int idMaterial;
        string titulo;
};

#endif // MATERIAL_H_INCLUDED
