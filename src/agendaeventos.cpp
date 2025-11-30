/**
 * @file agendaeventos.cpp
 * @brief Implementación del T.D.A. AgendaEventos
 * @author Daniel Martínez Infantes
 * @date 2025-12-28
 * @version 1.0
 */

#include "agendaeventos.h"
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

// =============== MÉTODOS PRIVADOS ======================

void AgendaEventos::reservar(int nueva_capacidad){
    if(nueva_capacidad <= capacidad){
        return;
    }

    if(nueva_capacidad < 1){
        nueva_capacidad = 1;
    }

    Evento *nuevo = new Evento[nueva_capacidad];

    for(int i = 0; i < n_eventos; ++i){
        nuevo[i] = datos[i];
    }
    delete [] datos;
    datos = nuevo;
    capacidad = nueva_capacidad;
}

bool AgendaEventos::haySolapamientoCon(const Evento &e) const{
    for(int i = 0; i < n_eventos; ++i) {
        if (datos[i].seSolapaCon(e)){
            return true;
        }
    }
    return false;
}

bool AgendaEventos::insertarOrdenado(const Evento &e, bool permitirSolape){
    if(!permitirSolape && haySolapamientoCon(e)){
        return false;
    }

    if(n_eventos == capacidad){
        reservar(capacidad == 0 ? 4 : 2 * capacidad);
    }

    // Busca posición donde insertar (orden por día y hora_inicio)
    int pos = n_eventos;
    for(int i = 0; i < n_eventos; ++i){
        if  (e.getDia() < datos[i].getDia() ||
            (e.getDia() == datos[i].getDia() &&
             e.getHoraInicio() < datos[i].getHoraInicio())){
            pos = i;
            break;
        }
    }

    // Desplaza hacia la derecha
    for(int j = n_eventos; j > pos; --j){
        datos[j] = datos[j-1];
    }

    datos[pos] = e;
    ++n_eventos;
    return true;
}

// =============== CONSTRUCTORES / DESTRUCTOR ============

AgendaEventos::AgendaEventos()
    : datos(nullptr), n_eventos(0), capacidad(0){}

AgendaEventos::AgendaEventos(const string &nombreFichero)
    : datos(nullptr), n_eventos(0), capacidad(0){

    ifstream fe(nombreFichero.c_str());
    if(!fe){
        cerr << "[ERROR] No se ha podido abrir el fichero: "
             << nombreFichero << endl;
        return;
    }

    string linea;
    int num_linea = 0;

    while(getline(fe, linea)){
        ++num_linea;
        if(linea.empty()){
            continue;
        }

        stringstream ss(linea);
        string nombre;
        string token_dia, token_hi, token_hf;

        // nombre (hasta primera coma)
        if(!getline(ss, nombre, ',')){
            cerr << "[ERROR] Línea " << num_linea
                 << ": formato incorrecto (nombre)." << endl;
            continue;
        }

        if(!getline(ss, token_dia, ',')){
            cerr << "[ERROR] Línea " << num_linea
                 << ": formato incorrecto (día)." << endl;
            continue;
        }

        if(!getline(ss, token_hi, ',')){
            cerr << "[ERROR] Línea " << num_linea
                 << ": formato incorrecto (hora inicio)." << endl;
            continue;
        }

        if(!getline(ss, token_hf, ',')){
            cerr << "[ERROR] Línea " << num_linea
                 << ": formato incorrecto (hora fin)." << endl;
            continue;
        }

        int dia = 0;
        double hi = 0.0, hf = 0.0;
        try{
            dia = stoi(token_dia);
            hi = stod(token_hi);
            hf = stod(token_hf);
        }catch(...){
            cerr << "[ERROR] Línea " << num_linea
                 << ": no se pueden convertir los datos numéricos."
                 << endl;
            continue;
        }

        Evento e(nombre, dia, hi, hf);

        if(!insertarOrdenado(e, false)){
            cerr << "[AVISO] Línea " << num_linea
                 << ": el evento \"" << nombre
                 << "\" solapa con otro y NO se inserta."
                 << endl;
        }
    }
}

AgendaEventos::AgendaEventos(const AgendaEventos &otra)
    : datos(nullptr), n_eventos(0), capacidad(0){

    reservar(otra.capacidad);
    n_eventos = otra.n_eventos;
    for(int i = 0; i < n_eventos; ++i){
        datos[i] = otra.datos[i];
    }
}

AgendaEventos & AgendaEventos::operator=(const AgendaEventos &otra){
    if(this != &otra){
        delete [] datos;
        datos = nullptr;
        n_eventos = 0;
        capacidad = 0;

        reservar(otra.capacidad);
        n_eventos = otra.n_eventos;
        for(int i = 0; i < n_eventos; ++i){
            datos[i] = otra.datos[i];
        }
    }
    return *this;
}

AgendaEventos::~AgendaEventos(){
    delete [] datos;
}

// ================== OPERACIONES FUNDAMENTALES ==========

int AgendaEventos::size() const{
    return n_eventos;
}

bool AgendaEventos::empty() const{
    return n_eventos == 0;
}

bool AgendaEventos::anadirEvento(const Evento &e, bool permitirSolape){
    bool ok = insertarOrdenado(e, permitirSolape);
    if(!ok && !permitirSolape){
        cerr << "[ERROR] No se puede insertar el evento \""
             << e.getNombre()
             << "\" porque se solapa con otro existente."
             << endl;
    }
    return ok;
}

bool AgendaEventos::eliminarEventoPorNombre(const string &nombre){
    for(int i = 0; i < n_eventos; ++i){
        if(datos[i].getNombre() == nombre){
            // Desplazar a la izquierda
            for(int j = i; j < n_eventos - 1; ++j){
                datos[j] = datos[j+1];
            }
            --n_eventos;
            return true;
        }
    }
    return false;
}

bool AgendaEventos::existeSolapamiento() const{
    for(int i = 0; i < n_eventos; ++i){
        for(int j = i+1; j < n_eventos; ++j){
            if(datos[i].seSolapaCon(datos[j])){
                return true;
            }
        }
    }
    return false;
}

void AgendaEventos::buscarPorNombre(const string &nombre,
                                    int *indices, int max_indices,
                                    int &num_encontrados) const{
    num_encontrados = 0;
    if(indices == nullptr || max_indices <= 0){
        return;
    }

    for(int i = 0; i < n_eventos && num_encontrados < max_indices; ++i){
        if(datos[i].getNombre() == nombre){
            indices[num_encontrados] = i;
            ++num_encontrados;
        }
    }
}

void AgendaEventos::buscarPorDia(int dia,
                                 int *indices, int max_indices,
                                 int &num_encontrados) const{
    num_encontrados = 0;
    if(indices == nullptr || max_indices <= 0){
        return;
    }

    for(int i = 0; i < n_eventos && num_encontrados < max_indices; ++i){
        if(datos[i].getDia() == dia){
            indices[num_encontrados] = i;
            ++num_encontrados;
        }
    }
}

void AgendaEventos::mostrar(ostream &os) const{
    if(n_eventos == 0){
        os << "[Agenda vacía]" << endl;
        return;
    }

    os << "=== Agenda de eventos (" << n_eventos << " eventos) ===" << endl;
    for(int i = 0; i < n_eventos; ++i){
        os << i << ") " << datos[i] << endl;
    }
}

// ================== NO FUNDAMENTALES ====================

void AgendaEventos::mostrarOrdenados(ostream &os) const{
    // Internamente ya está ordenada
    mostrar(os);
}

void AgendaEventos::mostrarHuecosLibresDia(int dia, ostream &os) const{
    if(dia < 1 || dia > 7){
        os << "[ERROR] Día inválido al consultar huecos libres." << endl;
        return;
    }

    // Recolecta índices del día dado
    const int MAX_DIA = 128; // límite razonable
    int indices[MAX_DIA];
    int num = 0;
    buscarPorDia(dia, indices, MAX_DIA, num);

    if(num == 0){
        os << "Día " << dia << ": libre desde 0.0 hasta 24.0" << endl;
        return;
    }

    os << "Huecos libres del día " << dia << ":" << endl;

    double inicio_jornada = 0.0;
    double fin_jornada = 24.0;

    // Como la agenda está globalmente ordenada, indices[] también lo estará por hora_inicio
    double cursor = inicio_jornada;

    for(int k = 0; k < num; ++k){
        const Evento &e = datos[indices[k]];
        if(e.getHoraInicio() > cursor){
            os << " - De " << cursor << " a " << e.getHoraInicio() << endl;
        }
        if(e.getHoraFin() > cursor)
            cursor = e.getHoraFin();
    }

    if(cursor < fin_jornada){
        os << " - De " << cursor << " a " << fin_jornada << endl;
    }
}

const Evento & AgendaEventos::getEvento(int i) const{
    assert(i >= 0 && i < n_eventos); // comprobación en tiempo de ejecución en depuración
    return datos[i];
}