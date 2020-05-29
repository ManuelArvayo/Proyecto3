#include <iostream>
#include <string>
#include <fstream>
#include "Reserva.h"
#include <assert.h>
using namespace std;

ostream &operator << (ostream &os, fecha f)             //Sobrecarga de operador <<
{
    os << f.getDia();
    os << "/" << f.nombreMes() << "/" <<f.getAnio()<< endl;
    return os;
}

istream &operator >> (istream &os, fecha &f)            //Sobrecarga de operador >>
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
    software softwareTemp[30];      //Declaracion de todos los arreglos que se usaran
    disco discoTemp[30];
    reserva res[60];

    int idMaterial, atributoUno;
    string titulo, atributoDos;     //Declaracion de variables para Materiales


    char clave, resp;       // Clave: Si el material es L/D/S & la opcion del menu seleccionada ; Resp: si se haran mas operaciones

    int dia, mes, anio, idClient;       //Declaracion de variables para reservaciones

    ifstream arMaterial;
    arMaterial.open("Material.txt");        //Abrir el archivo de materiales

    int contMaterial=0;
    while(arMaterial>>idMaterial>>titulo>>clave>>atributoUno>>atributoDos)  //Importar los valores
    {
        clave=tolower(clave);
        switch (clave)
        {
        case 'l':                       // Libros
        {
            libro temp(idMaterial,titulo,atributoUno,atributoDos);
            libroTemp[contMaterial]= temp;
            *(mat+contMaterial) = &libroTemp[contMaterial];
            contMaterial++;
            break;
        }
        case 'd':                       //Discos
        {
            disco temp(idMaterial,titulo,atributoUno,atributoDos);
            discoTemp[contMaterial]= temp;
            *(mat+contMaterial)=&discoTemp[contMaterial];
            contMaterial++;
            break;
        }
        case 's':                       //Software
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
    arMaterial.close();     //Cerrar archivo

    ifstream arReserva;
    arReserva.open("Reserva.txt");      //Abrir archivo de Reservas
    int contReserva=0;
    while(arReserva>>dia>>mes>>anio>>idMaterial>>idClient) //Importar valores
    {
        fecha f1(anio,mes,dia);             // Fecha de la reservacion n
        reserva resTemp(idMaterial,idClient,f1);    //Declaracion de la reserva
        res[contReserva]=resTemp;             //Inclusion de la reserva en el arreglo
        contReserva++;                              //contador del numero de reservas
    }
    int contReservaTemp = contReserva-1; // Se guarda el numero de reservas para proxima modificacion
    do
    {
        cout<<"Ingrese A para Consultar la lista de Materiales"<<endl;
        cout<<"Ingrese B para Consultar la lista de reservaciones"<<endl;
        cout<<"Ingrese C para Consultar las reservaciones de un material dado"<<endl;       //MENU
        cout<<"Ingrese D para Consultar las reservaciones de una fecha dada"<<endl;
        cout<<"Ingrese E para Hacer una reservación"<<endl;
        cout<<"Ingrese F para Terminar"<<endl;
        cin>>clave;
        cout<<endl;

        clave=tolower(clave);
        switch (clave)
        {
        case 'a':           //Se imprimen los datos de todos los materiales
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
            cout<<endl<<"Desea Realizar otra operacion?"<<endl;                    //Pregunta al usuario para saber si terminar el ciclo
            cin>>resp;

            break;
        }

        case 'b':           //Se imprimen todos los datos de todas las reservas
        {
            cout<<"----------------------LISTA DE RESERVAS----------------------"<<endl;
            for(int i=0; i<contReserva; i++)
            {
                cout<<"Reserva #"<<i+1<<":"<<endl;
                cout<<"   Fecha de Inicio:"<<res[i].getFechaReserva();
                for(int k=0; k<contMaterial; k++)
                {
                    if(res[i].getIdMaterial()==mat[k]->getIdMaterial())             //Validacion de que material se reservo en cada reserva
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




            //FALTA VALIDACION




            cout<<endl;
            int x=1;        //numero de reservas encontradas con ese iD
            cout<<"---------------------------------------------------------------"<<endl;
            for(int i=0; i<contReserva; i++)
            {
                if(idMaterial==res[i].getIdMaterial())              //Encontrar que reserva coincide con la id de material dada por el usuario
                {
                    cout<<"Reserva #"<<x<<" del material #"<<idMaterial<<":"<<endl;
                    cout<<"   Fecha de Inicio:"<<res[i].getFechaReserva();
                    for(int k=0; k<contMaterial; k++)
                    {
                        if(res[i].getIdMaterial()==mat[k]->getIdMaterial())         //Encontrar cual material esta reservado
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
            cout<<"Ingrese el mes: "<<endl;     //Ingreso de datos de la fecha a buscar
            cin>>mes;
            cout<<"Ingrese el anio: "<<endl;
            cin>>anio;
            fecha ftemp(anio,mes,dia);
            int x=1;                            //Cantidad de reservas encontradas en esa fecha
            cout<<"---------------------------------------------------------------"<<endl;

            for(int i=0; i<contReserva; i++)
            {
                if(ftemp==res[i].getFechaReserva())     //Buscar que reservas coinciden con la fecha dada por el usuario
                {
                    cout<<"Reserva #"<<x<<" del material #"<<idMaterial<<":"<<endl;
                    cout<<"   Fecha de Inicio:"<<res[i].getFechaReserva();
                    for(int k=0; k<contMaterial; k++)
                    {
                        if(res[i].getIdMaterial()==mat[k]->getIdMaterial())         //Buscar el Material que se esta reservando
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
        case 'e':
        {
            int contMaterialTemp;           // guarda la el indice del materiales para usarlo despues
            bool fValido=false;             // Booleano que verifica si la fecha de la reserva ingresada es valida
            bool verif= false;              // Booleano que verifica si ya hay reservas del material
            int reservatemp;                //
            cout<<"Ingrese el ID del material: "<<endl;
            cin>>idMaterial;



            //FALTA VERIFICACION QUE SI LA ID EXISTE



            for(int k=0; k<contMaterial; k++)            //Verificacion de que material se esta reservando
                if(idMaterial==mat[k]->getIdMaterial())
                {
                    contMaterialTemp =k;
                }
            cout<<"Ingrese el Id del cliente: "<<endl;
            cin>>idClient;
            cout<<"Ingrese el dia: "<<endl;
            cin>>dia;
            cout<<"Ingrese el mes: "<<endl;             //Ingresar datos de la reserva a realizar
            cin>>mes;
            cout<<"Ingrese el anio: "<<endl;
            cin>>anio;
            fecha ftemp(anio,mes,dia);                  //Fecha de la nueva reserva
            reserva reservaN(idMaterial,idClient,ftemp);        //Nueva reserva

            for(int i=0; i<contReserva; i++)
            {
                if(res[i].getIdMaterial()==mat[contMaterialTemp]->getIdMaterial())      //Buscar si ya hay reservas con ese material dado
                {
                    verif=true;             //Verif: Si ya hay reservas es true
                    reservatemp=i;          //Se guarda el numero de reserva
                }
            }
            fecha temp2= ftemp;             //Se guarda la fecha inicial de la nueva reserva
            ftemp+mat[contMaterialTemp]->cantidadDiasPrestamo();        //Se calcula la fecha final de la nueva reserva
            if(verif==true)     //Si hay reservaciones con ese material hay que verificar si las fechas no se traslapan
            {
                fecha inicio;
                fecha termino;
                inicio =res[reservatemp].getFechaReserva();   //Fecha de inicio de la Reserva ya establecida
                termino=res[reservatemp].calculaFechaFinReserva(mat[contMaterialTemp]->cantidadDiasPrestamo());  //Fecha de termino de la Reserva ya establecida

                if((temp2>=inicio && temp2<=termino)||(ftemp>=inicio && ftemp<=termino))    //Verificar si las fechas de traslapan
                    fValido=false;      //Si se traslapan fValido es falso, la fecha NO ES valida
                else
                    fValido=true;       //Si no se traslapan, fValido es verdadero, la fecha ES valida
            }
            if(verif==false)        //Si no hay reservas con el material, la fecha dada es valida por defecto
                fValido=true;
            if(fValido==false)
                cout<<"FECHA NO DISPONIBLE"<<endl; //Si la fecha no es valida, se imprime
            if(fValido==true)
            {
                contReservaTemp++;      //Si la fecha es valida, se aumenta el numero de reservas
                res[contReservaTemp]= reservaN;         //Se agrega la nueva reserva al arreglo
                cout<<"RESERVA AGREGADA AL SISTEMA:"<<endl;
                cout<<"Reserva #"<<contReservaTemp<<endl;
                cout<<"   Fecha de Inicio:"<<reservaN.getFechaReserva();            //Se imprimen los datos para que el usuario cheque si estan correctos
                cout<<"   Fecha de Termino:"<<reservaN.calculaFechaFinReserva(mat[contMaterialTemp]->cantidadDiasPrestamo());
                cout<<"   Nombre de Material:"<<mat[contMaterialTemp]->getTitulo()<<endl;
                cout<<"   Id del Cliente:"<<reservaN.getIdCliente()<<endl;



                //FALTA PREGUNTAR SI LOS DATOS ESTAN BIEN, HACER UN DO WHILE.



            }
            cout<<endl<<"Desea Realizar otra operacion?"<<endl;
            cin>>resp;
            break;

        }
        case 'f':
        {
            ofstream arSalida;
            arSalida.open("Reserva.txt");       //Abrir el archivo de salida con el mismo nombre para que se reescriba el archivo de reservas
            for(int i=0; i<=contReservaTemp; i++)
            {
                arSalida<<res[i].getFechaReserva().getDia()<<" ";
                arSalida<<res[i].getFechaReserva().getMes()<<" ";       //Exportar los datos del arreglo de reservas
                arSalida<<res[i].getFechaReserva().getAnio()<<" ";
                arSalida<<res[i].getIdMaterial()<<" ";
                arSalida<<res[i].getIdCliente()<<endl;
            }
        }
        }
        if(resp=='n')       //En caso de que el usuario responda 'n' a la pregunta "DESEA REALIZAR OTRA OPERACION?"
        {
            ofstream arSalida;
            arSalida.open("Reserva.txt");
            for(int i=0; i<=contReservaTemp; i++)
            {
                arSalida<<res[i].getFechaReserva().getDia()<<" ";
                arSalida<<res[i].getFechaReserva().getMes()<<" ";       //Hace lo mismo que el caso 'f' pero sin necesidad de
                arSalida<<res[i].getFechaReserva().getAnio()<<" ";      //volver a ver el menu
                arSalida<<res[i].getIdMaterial()<<" ";
                arSalida<<res[i].getIdCliente()<<endl;
            }
        }

    }
    while(resp=='s');

}
