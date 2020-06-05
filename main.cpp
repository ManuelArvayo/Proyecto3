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
    do{
    cout << "Dia: ";
    os >> f.dd;
    }while(f.dd>31 || f.dd<0);
    do{
    cout << "Mes: ";
    os >> f.mm;
    }while(f.mm>12||(f.dd>30 && (f.mm==4 ||f.mm==6||f.mm==9||f.mm==11))||(f.dd>31 && (f.mm==1 ||f.mm==3||f.mm==5||f.mm==7||f.mm==8||f.mm==10||f.mm==12))|| (f.dd>28 && f.mm==2));
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
                    if(res[i].getIdMaterial()== mat[k]->getIdMaterial())             //Validacion de que material se reservo en cada reserva
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
            bool verif;
            do
            {
                cout<<"Ingrese el ID del material: "<<endl;
                cin>>idMaterial;
                int i=0;
                do
                {
                    if(idMaterial==mat[i]->getIdMaterial())             //Verificacion de la id del material
                        verif=true;
                    else
                        verif=false;
                    i++;
                }
                while(verif==false && i<contMaterial);
                if(verif==false)
                    cout<<"ID NO RECONOCIDA, INTENTELO DE NUEVO:"<<endl;
            }
            while(verif==false);

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
            fecha ftemp(anio,mes,dia);     //Ingreso de datos de la fecha a buscar
            cin>>ftemp;
            int x=1;                            //Cantidad de reservas encontradas en esa fecha
            cout<<"---------------------------------------------------------------"<<endl;

            for(int i=0; i<contReserva; i++)
            {
                for(int k=0;k<contMaterial;k++)
                {
                    if(res[i].getIdMaterial()==mat[k]->getIdMaterial())
                        if(ftemp>=res[i].getFechaReserva() && ftemp<=res[i].calculaFechaFinReserva(mat[k]->cantidadDiasPrestamo()))
                        {
                            cout<<"Reserva #"<<x<<"   Material #"<<res[i].getIdMaterial()<<":"<<endl;
                            cout<<"   Fecha de Inicio:"<<res[i].getFechaReserva();
                            cout<<"   Fecha de Termino:"<<res[i].calculaFechaFinReserva(mat[k]->cantidadDiasPrestamo());
                            cout<<"   Nombre de Material:"<<mat[k]->getTitulo()<<endl;
                            cout<<"   Id del Cliente:"<<res[i].getIdCliente()<<endl;
                            cout<<endl;
                        }

                }
//                if(ftemp==res[i].getFechaReserva())     //Buscar que reservas coinciden con la fecha dada por el usuario
//                {
//                    cout<<"Reserva #"<<x<<" del material #"<<idMaterial<<":"<<endl;
//                    cout<<"   Fecha de Inicio:"<<res[i].getFechaReserva();
//                    for(int k=0; k<contMaterial; k++)
//                    {
//                        if(res[i].getIdMaterial()==mat[k]->getIdMaterial())         //Buscar el Material que se esta reservando
//                        {
//                            cout<<"   Fecha de Termino:"<<res[i].calculaFechaFinReserva(mat[k]->cantidadDiasPrestamo());
//                            cout<<"   Nombre de Material:"<<mat[k]->getTitulo()<<endl;
//                        }
//                    }
//                    cout<<"   Id del Cliente:"<<res[i].getIdCliente()<<endl;
//                    cout<<endl;
                    x++;
                }

            cout<<"---------------------------------------------------------------"<<endl;

            cout<<endl<<"Desea Realizar otra operacion?"<<endl;
            cin>>resp;


            break;

        }
        case 'e':
        {
            reserva reservaN;
            int contMaterialTemp;           // guarda la el indice del materiales para usarlo despues
            bool fValido=false;             // Booleano que verifica si la fecha de la reserva ingresada es valida
            bool verif= false;
            bool verifmaterial;              // Booleano que verifica si ya hay reservas del material
            int reservatemp;
            do             //
            {
                cout<<"Ingrese el ID del material: "<<endl;
                cin>>idMaterial;
                int i=0;
                do
                {
                    if(idMaterial==mat[i]->getIdMaterial())             //Verificacion de la id del material
                        verifmaterial=true;
                    else
                        verifmaterial=false;
                    i++;
                }
                while(verifmaterial==false && i<contMaterial);
                if(verifmaterial==false)
                    cout<<"ID NO RECONOCIDA, INTENTELO DE NUEVO:"<<endl;
            }
            while(verifmaterial==false);

            for(int k=0; k<contMaterial; k++)            //Verificacion de que material se esta reservando
                if(idMaterial==mat[k]->getIdMaterial())
                {
                    contMaterialTemp =k;
                }
            cout<<"Ingrese el Id del cliente: "<<endl;
            cin>>idClient;
                fecha ftemp(anio,mes,dia);
            cin>>ftemp;                 //Fecha de la nueva reserva
            reserva Temporal(idMaterial,idClient,ftemp);        //Nueva reserva
            reservaN = Temporal;
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

                cout<<"-------------RESERVACION AGREGADA AL SISTEMA-----------"<<endl;
                cout<<"Reservacion #"<<contReserva+1<<endl;
                cout<<"   Fecha de Inicio:"<<reservaN.getFechaReserva();            //Se imprimen los datos para que el usuario cheque si estan correctos
                cout<<"   Fecha de Termino:"<<reservaN.calculaFechaFinReserva(mat[contMaterialTemp]->cantidadDiasPrestamo());
                cout<<"   Nombre de Material:"<<mat[contMaterialTemp]->getTitulo()<<endl;
                cout<<"   Id del Cliente:"<<reservaN.getIdCliente()<<endl;
                cout<<"---------------------------------------------------"<<endl;
                res[contReserva]= reservaN;         //Se agrega la nueva reserva al arreglo
                contReserva++;      //Si la fecha es valida, se aumenta el numero de reservas

            }
            cout<<endl<<"Desea Realizar otra operacion?"<<endl;
            cin>>resp;
            break;

        }
        case 'f':
        {
            ofstream arSalida;
            arSalida.open("Reserva.txt");       //Abrir el archivo de salida con el mismo nombre para que se reescriba el archivo de reservas
            for(int i=0; i<=contReserva-1; i++)
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
            for(int i=0; i<=contReserva-1; i++)
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
