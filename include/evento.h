/**
 * @file evento.h
 * @brief Declaración del T.D.A. Evento
 *        Representa un evento académico con nombre, día y franja horaria.
 *
 * Este TDA sigue la teoría enseñada en la asignatura:
 * - dominio claro,
 * - operaciones fundamentales,
 * - encapsulación,
 * - invariantes,
 * - documentación Doxygen.
 *
 * @version 1.0
 */

#ifndef EVENTO_H
#define EVENTO_H

#include <string>
#include <iostream>

using namespace std;

/**
 * @brief T.D.A. Evento
 *
 * Un objeto de la clase @b Evento representa una actividad programada
 * en un día y una franja horaria concreta.
 *
 * ---------------------------------------------------
 *   DOMINIO VÁLIDO
 * ---------------------------------------------------
 *  - Día ∈ [1..7] (1=lunes, 7=domingo)
 *  - 0.0 ≤ hora_inicio < hora_fin ≤ 24.0
 *
 * ---------------------------------------------------
 *   INTERPRETACIÓN DE LA FRANJA HORARIA
 * ---------------------------------------------------
 * La franja se interpreta como un intervalo semiabierto:
 *
 *           [hora_inicio , hora_fin)
 *
 * Esto significa que:
 *   - un evento que termina a las 11.0 NO solapa con otro que comienza a las 11.0
 *   - pero sí solapa con uno que comienza en 10.9, 10.5, etc.
 *
 */
class Evento{

private:
    string nombre;       ///< Nombre del evento
    int dia;             ///< Día de la semana (1=lunes ... 7=domingo)
    double hora_inicio;  ///< Hora de inicio (en formato decimal)
    double hora_fin;     ///< Hora de fin (en formato decimal)

public:

    // ============================================================
    //                     CONSTRUCTORES / DESTRUCTOR
    // ============================================================

    /**
     * @brief Constructor por defecto
     *
     * Genera un evento neutro pero válido:
     *   - día = 1
     *   - franja = [0.0 , 1.0)
     */
    Evento();

    /**
     * @brief Constructor por parámetros
     *
     * @param nombre nombre del evento
     * @param dia día de la semana (1-7)
     * @param hora_inicio inicio en formato decimal
     * @param hora_fin fin en formato decimal
     *
     * @pre 1 ≤ dia ≤ 7
     * @pre 0.0 ≤ hora_inicio < hora_fin ≤ 24.0
     */
    Evento(const string &nombre, int dia,
           double hora_inicio, double hora_fin);

    /// Constructor de copia (generado automáticamente)
    Evento(const Evento &otro) = default;

    /// Operador de asignación (generado automáticamente)
    Evento & operator=(const Evento &otro) = default;

    /// Destructor
    ~Evento() = default;


    // ============================================================
    //                     OPERACIONES FUNDAMENTALES
    // ============================================================

    /// @return nombre del evento
    string getNombre() const;

    /// @return día del evento (1-7)
    int getDia() const;

    /// @return hora de inicio del evento
    double getHoraInicio() const;

    /// @return hora de fin del evento
    double getHoraFin() const;

    /// Cambia el nombre del evento
    void setNombre(const string &n);

    /**
     * @brief Establece un nuevo día para el evento
     * @param d día de la semana (1-7)
     * @return true si se asignó correctamente
     */
    bool setDia(int d);

    /**
     * @brief Cambia la franja horaria del evento
     * @param inicio nueva hora de inicio
     * @param fin nueva hora de fin
     * @pre 0.0 ≤ inicio < fin ≤ 24.0
     * @return true si es válida y se asigna correctamente
     */
    bool setFranjaHoraria(double inicio, double fin);


    // ============================================================
    //                     LÓGICA DEL TDA (NO FUNDAMENTALES)
    // ============================================================

    /**
     * @brief Comprueba si dos eventos se solapan.
     *
     * Reglas:
     *  - Deben ser del MISMO día.
     *  - Sus intervalos [ini, fin) deben intersecarse.
     *
     * @param otro evento con el que se compara
     * @return true si hay solapamiento
     */
    bool seSolapaCon(const Evento &otro) const;

    /**
     * @brief Comparación lexicográfica por nombre
     *
     * @return <0 si this < otro,
     *          0 si iguales,
     *         >0 si this > otro.
     */
    int compararPorNombre(const Evento &otro) const;

    /**
     * @brief Escribe toda la información del evento en un flujo
     */
    void escribir(ostream &os) const;
};

/**
 * @brief Operador de salida para imprimir un evento
 */
ostream & operator<<(ostream &os, const Evento &e);

#endif // EVENTO_H