/**
 * @file agendaeventos.h
 * @brief Declaración del T.D.A. AgendaEventos
 *        Gestión dinámica y ordenada de eventos sin solapamientos.
 * @author Daniel Martínez Infantes
 * @date 2025-12-28
 * @version 1.0
 */

#ifndef AGENDAEVENTOS_H
#define AGENDAEVENTOS_H

#include <string>
#include <iostream>
#include "evento.h"

using namespace std;

/**
 * @brief T.D.A. AgendaEventos
 *
 * Un objeto de la clase AgendaEventos representa una colección
 * de eventos académicos almacenados en un array dinámico y
 * mantenidos SIEMPRE en orden por (día, hora_inicio).
 *
 * Por defecto la agenda NO permite solapamientos, aunque se puede
 * insertar explícitamente con solapamiento si el usuario así lo indica
 * (por ejemplo, para pruebas).
 *
 * ----------------------------------------------
 *  FUNCIÓN DE ABSTRACCIÓN (FA)
 * ----------------------------------------------
 *     Un objeto físico:
 *          datos[0], datos[1], ..., datos[n_eventos-1]
 *
 *     Representa el conjunto abstracto:
 *          { datos[i] | 0 ≤ i < n_eventos }
 *
 * ----------------------------------------------
 *  INVARIANTE DE REPRESENTACIÓN (IR)
 * ----------------------------------------------
 *  - 0 ≤ n_eventos ≤ capacidad
 *  - datos apunta a un array dinámico válido de tamaño "capacidad"
 *    (o es nullptr si capacidad = 0)
 *  - Para todo par i < j:
 *        datos[i].dia < datos[j].dia  OR
 *        (datos[i].dia == datos[j].dia
 *         AND datos[i].hora_inicio ≤ datos[j].hora_inicio)
 *  - No existen solapamientos si los eventos se han insertado
 *    siempre con permitirSolape = false.
 *
 */
class AgendaEventos{

private:
    Evento *datos;      ///< Array dinámico de eventos
    int n_eventos;      ///< Número actual de eventos almacenados
    int capacidad;      ///< Tamaño del array dinámico reservado

    /**
     * @brief Reserva un nuevo tamaño de almacenamiento.
     * @param nueva_capacidad tamaño mínimo deseado.
     * @post Preserva los eventos existentes, realocando memoria.
     */
    void reservar(int nueva_capacidad);

    /**
     * @brief Inserta un evento manteniendo orden por (día, hora_inicio).
     *
     * @param e Evento a insertar.
     * @param permitirSolape Si es false, se comprueba solapamiento global.
     * @return true si el evento ha sido insertado, false si hay solapamiento
     *         y no está permitido.
     */
    bool insertarOrdenado(const Evento &e, bool permitirSolape);

    /**
     * @brief Comprueba si un evento se solapa con alguno ya almacenado.
     * @param e evento a comprobar
     * @return true si existe un solapamiento
     */
    bool haySolapamientoCon(const Evento &e) const;

public:

    // ============================================================
    //               CONSTRUCTORES / ASIGNACIÓN / DESTRUCTOR
    // ============================================================

    /// @brief Constructor por defecto: agenda vacía
    AgendaEventos();

    /**
     * @brief Constructor desde fichero
     *
     * Lee un fichero donde cada línea posee:
     *       nombre, día, hora_inicio, hora_fin
     *
     * Inserta cada evento si es válido y no solapa.
     * Si una línea da error o el evento solapa, el evento se ignora
     * y se imprime un mensaje explicativo.
     *
     * @param nombreFichero ruta del fichero de entrada
     */
    AgendaEventos(const string &nombreFichero);

    /// Constructor de copia
    AgendaEventos(const AgendaEventos &otra);

    /// Operador de asignación
    AgendaEventos &operator=(const AgendaEventos &otra);

    /// Destructor
    ~AgendaEventos();


    // ============================================================
    //                    OPERACIONES FUNDAMENTALES
    // ============================================================

    /// @return número de eventos almacenados
    int size() const;

    /// @return true si la agenda carece de eventos
    bool empty() const;

    /**
     * @brief Añade un evento a la agenda.
     *
     * @param e evento a insertar
     * @param permitirSolape true si se desea insertar aunque solape
     * @return true si se inserta correctamente
     */
    bool anadirEvento(const Evento &e, bool permitirSolape = false);

    /**
     * @brief Elimina el primer evento cuyo nombre coincide exactamente.
     *
     * @param nombre nombre a eliminar
     * @return true si se eliminó algún evento
     */
    bool eliminarEventoPorNombre(const string &nombre);

    /**
     * @brief Comprueba si existe algún solapamiento en toda la agenda.
     *
     * @return true si hay al menos un par de eventos solapados
     */
    bool existeSolapamiento() const;

    /**
     * @brief Búsqueda exacta por nombre.
     *
     * @param nombre nombre exacto a buscar
     * @param indices array donde guardar posiciones encontradas
     * @param max_indices tamaño del array indices
     * @param num_encontrados número de resultados válidos
     */
    void buscarPorNombre(const string &nombre,
                         int *indices, int max_indices,
                         int &num_encontrados) const;

    /**
     * @brief Búsqueda por día de la semana.
     *
     * @param dia día (1-7)
     * @param indices array donde guardar posiciones encontradas
     * @param max_indices tamaño del array indices
     * @param num_encontrados número de resultados válidos
     */
    void buscarPorDia(int dia,
                      int *indices, int max_indices,
                      int &num_encontrados) const;


    // ============================================================
    //                    OPERACIONES NO FUNDAMENTALES
    // ============================================================

    /**
     * @brief Muestra todos los eventos almacenados.
     * @param os flujo de salida
     */
    void mostrar(ostream &os) const;

    /**
     * @brief Muestra los eventos en orden (ya están ordenados internamente).
     */
    void mostrarOrdenados(ostream &os) const;

    /**
     * @brief Muestra las franjas horarias libres de un día.
     *
     * @param dia día de la semana (1-7)
     * @param os flujo de salida
     */
    void mostrarHuecosLibresDia(int dia, ostream &os) const;

    /**
     * @brief Acceso de solo lectura al evento i-ésimo.
     *
     * Esta operación es NO fundamental, pero es necesaria para:
     *  - imprimir los resultados de las búsquedas desde main
     *  - mantener encapsulación: no se expone el array interno
     *
     * @pre 0 ≤ i < size()
     *
     * @return referencia constante al evento en esa posición
     */
    const Evento & getEvento(int i) const;
};

#endif // AGENDAEVENTOS_H