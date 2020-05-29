#include <iostream>
#include <string>
#include <fstream>
#include "Reserva.h"
using namespace std;

ostream &operator << (ostream &os, fecha f) {
    os << f.getDia();
    os << "/" << f.nombreMes() << "/" <<f.getAnio()<< endl;
    return os;
}

istream &operator >> (istream &os, fecha &f) {
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

material *mat[30];
libro libroTemp[30];
software softwareTemp[30];
disco discoTemp[30];
reserva res[60];

int idMaterial, atributoUno;
string titulo, atributoDos;
char clave;

int dia, mes, anio, idClient;

ifstream arMaterial;
arMaterial.open("Material.txt");

int contMaterial=0;
while(arMaterial>>idMaterial>>titulo>>clave>>atributoUno>>atributoDos)
{
    clave=tolower(clave);
    switch (clave)
    {
        case 'l':
            {
                libro temp(idMaterial,titulo,atributoUno,atributoDos);
                libroTemp[contMaterial]= temp;
                *(mat+contMaterial) = &libroTemp[contMaterial];
                contMaterial++;
                break;
            }
        case 'd':
            {
                disco temp(idMaterial,titulo,atributoUno,atributoDos);
                discoTemp[contMaterial]= temp;
                *(mat+contMaterial)=&discoTemp[contMaterial];
                contMaterial++;
                break;
            }
        case 's':
            {
                software temp(idMaterial,titulo,atributoUno,atributoDos);
                softwareTemp[contMaterial] = temp;
                *(mat+contMaterial)=&softwareTemp[contMaterial];
                contMaterial++;
                break;
            }
        default:
            cout<<"Error en la captura de Datos (MATERIAL)"<<endl;
    }
}
arMaterial.close();

ifstream arReserva;
arReserva.open("Reserva.txt");
int contReserva=0;
while(arReserva>>dia>>mes>>anio>>idMaterial>>idClient)
{
    fecha f1(anio,mes,dia);
    reserva resTemp(idMaterial,idClient,f1);
    res[contReserva]=resTemp;
    contReserva++;
}
int contReservaTemp = contReserva;
cout<<"Ingrese A para Consultar la lista de Materiales"<<endl;
cout<<"Ingrese B para Consultar la lista de reservaciones"<<endl;
cout<<"Ingrese C para Consultar las reservaciones de un material dado"<<endl;
cout<<"Ingrese D para Consultar las reservaciones de una fecha dada"<<endl;
cout<<"Ingrese E para Hacer una reservación"<<endl;
cout<<"Ingrese F para Terminar"<<endl;
cin>>clave;
cout<<endl;

clave=tolower(clave);
switch (clave)
    {
    case 'a':
        {
            cout<<"----------------------LISTA DE MATERIALES----------------------"<<endl;
            for(int i=0;i<contMaterial;i++)
            {
                cout<<"MATERIAL #"<<i+1<<endl;
                mat[i]->muestraDatos();
                cout<<endl;
            }
            cout<<"TOTAL DE MATERIALES:  "<<contMaterial<<endl;
            cout<<"---------------------------------------------------------------"<<endl;
            break;
        }

    case 'b':
        {
            cout<<"----------------------LISTA DE RESERVAS----------------------"<<endl;
            for(int i=0;i<contReserva;i++)
            {
            cout<<"Reserva #"<<i+1<<":"<<endl;
            cout<<"   Fecha de Inicio:"<<res[i].getFechaReserva();
                for(int k=0; k<contMaterial;k++)
                {
                    if(res[i].getIdMaterial()==mat[k]->getIdMaterial())
                    {
                        cout<<"   Fecha de Termino:"<<res[i].calculaFechaFinReserva(mat[k]->cantidadDiasPrestamo());
                        cout<<"   Nombre de Material:"<<mat[k]->getTitulo()<<endl;
                    }
                }
            cout<<"   Id del Cliente:"<<res[i].getIdCliente()<<endl;
            cout<<endl;
            }
            cout<<"TOTAL DE RESERVAS  :"<<contReserva<<endl;
            cout<<"---------------------------------------------------------------"<<endl;
            break;
        }
    case 'c':
        {
            cout<<"Ingrese el ID del material: "<<endl;
            cin>>idMaterial;
            int x=1;
            for(int i=0;i<contReserva;i++)
            {
                if(idMaterial==res[i].getIdMaterial())
                {
                    cout<<"Reserva #"<<x<<" del material #"<<idMaterial<<":"<<endl;
                     cout<<"   Fecha de Inicio:"<<res[i].getFechaReserva();
                    for(int k=0; k<contMaterial;k++)
                    {
                        if(res[i].getIdMaterial()==mat[k]->getIdMaterial())
                        {
                            cout<<"   Fecha de Termino:"<<res[i].calculaFechaFinReserva(mat[k]->cantidadDiasPrestamo());
                            cout<<"   Nombre de Material:"<<mat[k]->getTitulo()<<endl;
                        }
                    }
                    cout<<"   Id del Cliente:"<<res[i].getIdCliente()<<endl;
                    cout<<endl;
                    x++;
                }
            }
            break;
        }

    case 'd':
        {
            cout<<"Ingrese el dia: "<<endl;
            cin>>dia;
            cout<<"Ingrese el mes: "<<endl;
            cin>>mes;
            cout<<"Ingrese el anio: "<<endl;
            cin>>anio;
            fecha ftemp(anio,mes,dia);
            int x=1;
            for(int i=0;i<contReserva;i++)
            {
                if(ftemp==res[i].getFechaReserva())
                {
                    cout<<"Reserva #"<<x<<" del material #"<<idMaterial<<":"<<endl;
                     cout<<"   Fecha de Inicio:"<<res[i].getFechaReserva();
                    for(int k=0; k<contMaterial;k++)
                    {
                        if(res[i].getIdMaterial()==mat[k]->getIdMaterial())
                        {
                            cout<<"   Fecha de Termino:"<<res[i].calculaFechaFinReserva(mat[k]->cantidadDiasPrestamo());
                            cout<<"   Nombre de Material:"<<mat[k]->getTitulo()<<endl;
                        }
                    }
                    cout<<"   Id del Cliente:"<<res[i].getIdCliente()<<endl;
                    cout<<endl;
                    x++;
                }
            }
            break;
        }
    case 'e':
        {
            int contMaterialTemp;
            bool fValido;
            cout<<"Ingrese el ID del material: "<<endl;
            cin>>idMaterial;
            //Verificacion
            cout<<"Ingrese el Id del cliente: "<<endl;
            cin>>idClient;
            cout<<"Ingrese el dia: "<<endl;
            cin>>dia;
            cout<<"Ingrese el mes: "<<endl;
            cin>>mes;
            cout<<"Ingrese el anio: "<<endl;
            cin>>anio;
            fecha ftemp(anio,mes,dia);
            reserva r1(idMaterial,idClient,ftemp);
            for(int k=0; k<contMaterial;k++)
                if(idMaterial==mat[k]->getIdMaterial())
                {
                    contMaterialTemp =k;
                }
            int i=0;
            fecha temp2= ftemp;
            ftemp+mat[contMaterialTemp]->cantidadDiasPrestamo();
//            do{
                    int j=0;
                    do
                    {

                        fecha inicio;
                        fecha termino;
                        inicio =res[j].getFechaReserva();
                        termino=res[j].calculaFechaFinReserva(mat[contMaterialTemp]->cantidadDiasPrestamo());
                        if(res[j].getIdMaterial()==mat[contMaterialTemp]->getIdMaterial())
                        {
                        if((temp2>=inicio && temp2<=termino)||(ftemp>=inicio && ftemp<=termino))
                            fValido=false;
                        else
                            fValido=true;
                        }
                        j++;
                    }while(fValido==false && j<contReserva);

//                i++;
//                }while(fValido==true && i<contReserva);
            if(fValido==false)
                cout<<"FECHA NO DISPONIBLE"<<endl;
            if(fValido==true)
            {
                contReservaTemp++;
                res[contReservaTemp]= r1;
                cout<<"RESERVA AGREGADA AL SISTEMA:"<<endl;
                cout<<"Reserva #"<<contReservaTemp<<endl;
                cout<<"   Fecha de Inicio:"<<r1.getFechaReserva();
                cout<<"   Fecha de Termino:"<<r1.calculaFechaFinReserva(mat[contMaterialTemp]->cantidadDiasPrestamo());
                cout<<"   Nombre de Material:"<<mat[contMaterialTemp]->getTitulo()<<endl;
                cout<<"   Id del Cliente:"<<r1.getIdCliente()<<endl;


            }
        }

}

//
//                            {cout<<"MATERIAL NO DISPONIBLE"<<endl;}
//                    ftemp+mat[contMaterialTemp]->cantidadDiasPrestamo();
//
//
//                        else
//                        {

}
