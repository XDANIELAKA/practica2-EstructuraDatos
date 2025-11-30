/**
 * @file evento.cpp
 * @brief Implementación del T.D.A. Evento
 * @version 1.0
 */

#include "evento.h"

using namespace std;

// ============================================================
//                     CONSTRUCTORES
// ============================================================

Evento::Evento()
    : nombre(""), dia(1), hora_inicio(0.0), hora_fin(1.0){
    // Evento: lunes de 0.0 a 1.0
}

Evento::Evento(const string &n, int d,
               double hi, double hf)
    : nombre(n), dia(1), hora_inicio(0.0), hora_fin(1.0){

    // Se usan los setters para respetar las precondiciones
    setDia(d);
    setFranjaHoraria(hi, hf);
}

// ============================================================
//                     OBSERVADORES
// ============================================================

string Evento::getNombre() const{
    return nombre;
}

int Evento::getDia() const{
    return dia;
}

double Evento::getHoraInicio() const{
    return hora_inicio;
}

double Evento::getHoraFin() const{
    return hora_fin;
}

// ============================================================
//                     MODIFICADORES
// ============================================================

void Evento::setNombre(const string &n){
    nombre = n;
}

bool Evento::setDia(int d){
    if(d >= 1 && d <= 7){
        dia = d;
        return true;
    }
    return false;
}

bool Evento::setFranjaHoraria(double inicio, double fin){
    if(inicio >= 0.0 && fin <= 24.0 && inicio < fin){
        hora_inicio = inicio;
        hora_fin = fin;
        return true;
    }
    return false;
}

// ============================================================
//                     LÓGICA DEL TDA
// ============================================================

bool Evento::seSolapaCon(const Evento &otro) const{
    // Si son de distintos días, no hay solapamiento
    if(dia != otro.dia){
        return false;
    }

    // Solapan si [ini1, fin1) intersecta [ini2, fin2)
    // Intervalos semiabiertos: [inicio, fin)
    return (hora_inicio < otro.hora_fin) &&
           (otro.hora_inicio < hora_fin);
}

int Evento::compararPorNombre(const Evento &otro) const{
    return nombre.compare(otro.nombre);
}

void Evento::escribir(ostream &os) const{
    static const char* nombres_dias[8] = {
        "", "Lunes", "Martes", "Miércoles", "Jueves",
        "Viernes", "Sábado", "Domingo"
    };

    os << "Evento: " << nombre
       << " | Día: " << nombres_dias[dia]
       << " (" << dia << ")"
       << " | Inicio: " << hora_inicio
       << " | Fin: " << hora_fin;
}

// ============================================================
//                     OPERADOR DE SALIDA
// ============================================================

ostream & operator<<(ostream &os, const Evento &e){
    e.escribir(os);
    return os;
}