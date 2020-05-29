#include <iostream>
#include <string>
#include <fstream>
#include "Reserva.h"
#include <assert.h>
using namespace std;

ostream &operator << (ostream &os, fecha f)
{
    os << f.getDia();
    os << "/" << f.nombreMes() << "/" <<f.getAnio()<< endl;
    return os;
}

istream &operator >> (istream &os, fecha &f)
{
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
    char clave, resp;

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
    int contReservaTemp = contReserva-1;
    do
    {
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
            for(int i=0; i<contMaterial; i++)
            {
                cout<<"MATERIAL #"<<i+1<<endl;
                mat[i]->muestraDatos();
                cout<<endl;
            }
            cout<<"TOTAL DE MATERIALES:  "<<contMaterial<<endl;
            cout<<"---------------------------------------------------------------"<<endl;
            cout<<endl<<"Desea Realizar otra operacion?"<<endl;
            cin>>resp;

            break;
        }

        case 'b':
        {
            cout<<"----------------------LISTA DE RESERVAS----------------------"<<endl;
            for(int i=0; i<contReserva; i++)
            {
                cout<<"Reserva #"<<i+1<<":"<<endl;
                cout<<"   Fecha de Inicio:"<<res[i].getFechaReserva();
                for(int k=0; k<contMaterial; k++)
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
            cout<<endl<<"Desea Realizar otra operacion?"<<endl;
            cin>>resp;

            break;

        }
        case 'c':
        {
            cout<<"Ingrese el ID del material: "<<endl;
            cin>>idMaterial;
            cout<<endl;
            int x=1;
            cout<<"---------------------------------------------------------------"<<endl;
            for(int i=0; i<contReserva; i++)
            {
                if(idMaterial==res[i].getIdMaterial())
                {
                    cout<<"Reserva #"<<x<<" del material #"<<idMaterial<<":"<<endl;
                    cout<<"   Fecha de Inicio:"<<res[i].getFechaReserva();
                    for(int k=0; k<contMaterial; k++)
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
            cout<<"---------------------------------------------------------------"<<endl;

            cout<<endl<<"Desea Realizar otra operacion?"<<endl;
            cin>>resp;

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
            for(int i=0; i<contReserva; i++)
            {
                if(ftemp==res[i].getFechaReserva())
                {
                    cout<<"Reserva #"<<x<<" del material #"<<idMaterial<<":"<<endl;
                    cout<<"   Fecha de Inicio:"<<res[i].getFechaReserva();
                    for(int k=0; k<contMaterial; k++)
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
            cout<<endl<<"Desea Realizar otra operacion?"<<endl;
            cin>>resp;


            break;

        }
        case 'e':
        {
            int contMaterialTemp;
            bool fValido=false;
            bool verif= false;
            int reservatemp;
            cout<<"Ingrese el ID del material: "<<endl;
            cin>>idMaterial;
            for(int k=0; k<contMaterial; k++)            //Verificacion
                if(idMaterial==mat[k]->getIdMaterial())
                {
                    contMaterialTemp =k;
                }
            cout<<"Ingrese el Id del cliente: "<<endl;
            cin>>idClient;
            cout<<"Ingrese el dia: "<<endl;
            cin>>dia;
            cout<<"Ingrese el mes: "<<endl;
            cin>>mes;
            cout<<"Ingrese el anio: "<<endl;
            cin>>anio;
            fecha ftemp(anio,mes,dia);
            reserva reservaN(idMaterial,idClient,ftemp);

            for(int i=0; i<contReserva; i++)
            {
                if(res[i].getIdMaterial()==mat[contMaterialTemp]->getIdMaterial())
                {
                    verif=true;
                    reservatemp=i;
                }
            }
            fecha temp2= ftemp;
            ftemp+mat[contMaterialTemp]->cantidadDiasPrestamo();
            if(verif==true)
            {
                fecha inicio;
                fecha termino;
                inicio =res[reservatemp].getFechaReserva();
                termino=res[reservatemp].calculaFechaFinReserva(mat[contMaterialTemp]->cantidadDiasPrestamo());

                if((temp2>=inicio && temp2<=termino)||(ftemp>=inicio && ftemp<=termino))
                    fValido=false;
                else
                    fValido=true;
            }
            if(verif==false)
                fValido=true;
            if(fValido==false)
                cout<<"FECHA NO DISPONIBLE"<<endl;
            if(fValido==true)
            {
                contReservaTemp++;
                res[contReservaTemp]= reservaN;
                cout<<"RESERVA AGREGADA AL SISTEMA:"<<endl;
                cout<<"Reserva #"<<contReservaTemp<<endl;
                cout<<"   Fecha de Inicio:"<<reservaN.getFechaReserva();
                cout<<"   Fecha de Termino:"<<reservaN.calculaFechaFinReserva(mat[contMaterialTemp]->cantidadDiasPrestamo());
                cout<<"   Nombre de Material:"<<mat[contMaterialTemp]->getTitulo()<<endl;
                cout<<"   Id del Cliente:"<<reservaN.getIdCliente()<<endl;


            }
            cout<<endl<<"Desea Realizar otra operacion?"<<endl;
            cin>>resp;
            break;

        }
        case 'f':
        {
            ofstream arSalida;
            arSalida.open("Reserva.txt");
            for(int i=0; i<=contReservaTemp; i++)
            {
                arSalida<<res[i].getFechaReserva().getDia()<<" ";
                arSalida<<res[i].getFechaReserva().getMes()<<" ";
                arSalida<<res[i].getFechaReserva().getAnio()<<" ";
                arSalida<<res[i].getIdMaterial()<<" ";
                arSalida<<res[i].getIdCliente()<<endl;
            }
        }
        }
        if(resp=='n')
        {
            ofstream arSalida;
            arSalida.open("Reserva.txt");
            for(int i=0; i<=contReservaTemp; i++)
            {
                arSalida<<res[i].getFechaReserva().getDia()<<" ";
                arSalida<<res[i].getFechaReserva().getMes()<<" ";
                arSalida<<res[i].getFechaReserva().getAnio()<<" ";
                arSalida<<res[i].getIdMaterial()<<" ";
                arSalida<<res[i].getIdCliente()<<endl;
            }
        }

    }
    while(resp=='s');

}
