#include "Fecha.h"
#ifndef RESERVA_H_INCLUDED
#define RESERVA_H_INCLUDED

class reserva
{
public:
    reserva();
    reserva(int, int, fecha);
    void setIdMaterial (int iM){idMaterial=iM;};
    void setIdCliente (int  iC){idCliente=iC;};
    void setFechaReservacion (fecha fR){fechaReservacion=fR;};
    int getIdMaterial(){return idMaterial;};
    int getIdCliente(){return idCliente;};
    fecha getFechaReserva(){return fechaReservacion;};
    fecha calculaFechaFinReserva(int);
private:
    int idMaterial, idCliente;
    fecha fechaReservacion;
};

reserva::reserva()
{
    idMaterial=0;
    idCliente=0;
    fecha fDefault;
    fechaReservacion=fDefault;
}

reserva::reserva(int idMat, int idClie, fecha fecReser)
{
    idMaterial=idMat;
    idCliente=idClie;
    fechaReservacion=fecReser;
}

fecha reserva::calculaFechaFinReserva(int cantDias)
{

}


#endif // RESERVA_H_INCLUDED
