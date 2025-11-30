/**
 * @file main.cpp
 * @brief Programa principal para probar el T.D.A. AgendaEventos
 */

#include <iostream>
#include <limits>
#include "agendaeventos.h"

using namespace std;

void mostrarMenu(){
    cout << "\n================= GESTOR DE AGENDA =================\n";
    cout << "1. Cargar agenda desde fichero\n";
    cout << "2. Mostrar todos los eventos\n";
    cout << "3. Agregar un evento\n";
    cout << "4. Eliminar un evento por nombre\n";
    cout << "5. Buscar eventos por nombre\n";
    cout << "6. Buscar eventos por dia\n";
    cout << "7. Mostrar huecos libres en un dia\n";
    cout << "8. Comprobar si hay solapamientos\n";
    cout << "9. Salir\n";
    cout << "Seleccione una opcion: ";
}

void limpiarEntrada(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main(){
    AgendaEventos agenda;  
    bool salir = false;

    while(!salir){
        mostrarMenu();
        int opcion;
        if(!(cin >> opcion)){
            limpiarEntrada();
            cout << "Opción no válida.\n";
            continue;
        }
        limpiarEntrada();  // limpia salto de línea

        switch(opcion){

        case 1: { // Carga desde fichero
            cout << "Introduzca el nombre del fichero (por ejemplo datos/agenda.txt): ";
            string nombre_fichero;
            getline(cin, nombre_fichero);

            AgendaEventos nuevaAgenda(nombre_fichero);
            agenda = nuevaAgenda;

            cout << "Agenda cargada desde " << nombre_fichero << ".\n";
            break;
        }

        case 2: { // Mostrar
            agenda.mostrar(cout);
            break;
        }

        case 3: { // Añadir evento
            string nombre;
            int dia;
            double hi, hf;
            char opcionSolape;

            cout << "Nombre del evento: ";
            getline(cin, nombre);

            cout << "Día (1=lunes ... 7=domingo): ";
            cin >> dia;

            cout << "Hora inicio (decimal ej. 9.0): ";
            cin >> hi;

            cout << "Hora fin (decimal ej. 11.5): ";
            cin >> hf;
            limpiarEntrada();

            cout << "¿Permitir solapamiento explícitamente? (s/n): ";
            cin >> opcionSolape;
            limpiarEntrada();

            bool permitirSolape = (opcionSolape == 's' || opcionSolape == 'S');

            Evento e(nombre, dia, hi, hf);
            if(agenda.anadirEvento(e, permitirSolape)){
                cout << "Evento agregado correctamente.\n";
            }else{
                cout << "No se ha podido agregar el evento.\n";
                if(!permitirSolape){
                    cout << "Motivo: el evento se solapa con otro ya existente.\n";
                }
            }
            break;
        }

        case 4: { // Eliminar por nombre
            string nombre;
            cout << "Nombre exacto del evento a eliminar: ";
            getline(cin, nombre);

            if(agenda.eliminarEventoPorNombre(nombre))
                cout << "Evento eliminado correctamente.\n";
            else
                cout << "No se encontró un evento con ese nombre.\n";

            break;
        }

        case 5: { // Buscar por nombre
            cout << "Nombre exacto a buscar: ";
            string nombre;
            getline(cin, nombre);

            const int MAX_RES = 64;
            int indices[MAX_RES];
            int num = 0;

            agenda.buscarPorNombre(nombre, indices, MAX_RES, num);

            if(num == 0){
                cout << "No se han encontrado eventos con ese nombre.\n";
            }else{
                cout << "Se han encontrado " << num << " evento(s):\n\n";
                for(int i = 0; i < num; ++i){
                    const Evento &ev = agenda.getEvento(indices[i]);
                    cout << "  -> " << ev << "\n";
                }
            }
            break;
        }

        case 6: { // Buscar por día
            cout << "Día de la semana (1-7): ";
            int dia;
            cin >> dia;
            limpiarEntrada();

            const int MAX_RES = 128;
            int indices[MAX_RES];
            int num = 0;

            agenda.buscarPorDia(dia, indices, MAX_RES, num);

            if(num == 0){
                cout << "No hay eventos ese día.\n";
            }else{
                cout << "Eventos del día " << dia << ":\n\n";
                for(int i = 0; i < num; ++i){
                    const Evento &ev = agenda.getEvento(indices[i]);
                    cout << "  -> " << ev << "\n";
                }
            }
            break;
        }

        case 7: { // Huecos libres
            cout << "Día (1-7): ";
            int dia;
            cin >> dia;
            limpiarEntrada();

            agenda.mostrarHuecosLibresDia(dia, cout);
            break;
        }

        case 8: { // Solapamientos
            if(agenda.existeSolapamiento())
                cout << "Hay solapamientos en la agenda.\n";
            else
                cout << "No hay solapamientos.\n";

            break;
        }

        case 9:
            salir = true;
            cout << "Saliendo del programa...\n";
            break;

        default:
            cout << "Opción no válida.\n";
        }
    }

    return 0;
}