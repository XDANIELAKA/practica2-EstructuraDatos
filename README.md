Gestor de Agenda de Eventos
Práctica 2 – Estructuras de Datos (TDA, representación dinámica, ordenada y sin solapamientos)

Este proyecto implementa dos Tipos de Datos Abstractos (TDA):

TDA Evento → representa un evento académico con nombre, día y franja horaria.

TDA AgendaEventos → gestiona un conjunto dinámico ordenado de eventos sin solapamientos.

El programa permite cargar eventos desde un fichero, añadir, eliminar, buscar, mostrar huecos libres y comprobar solapamientos mediante un menú interactivo.

---

# 1. Estructura del proyecto
```
.
├── include/  ├── evento.h
│   └── agendaeventos.h
├── src/
│   ├── evento.cpp
│   ├── agendaeventos.cpp
│   └── main.cpp
├── datos/
│   ├── agenda.txt
│   ├── agenda_solapamientos.txt
│   └── agenda_errores_formato.txt
├── build/
├── Makefile
└── README.md
```

--

# 2. Compilación y ejecución

### Compilar el programa

make

### Ejecutar

./programa

### Limpiar ficheros generados

make clean

### Generar documentación Doxygen
Desde la raiz del proyecto, ejecutamos:
  make doc

Para abrirlo,
Desde Linux:
  xdg-open doc/html/index.html
Desde Windows:
  start doc/html/index.html

// (es necesario tener doc/Doxyfile ya configurado) 

---

# 3. Formato del fichero de entrada
Cada línea del fichero representa un evento:
  nombre, día, hora_inicio, hora_fin

Ejemplo:
  Clase de Matemáticas,1,8.5,10.0

- El día es un entero entre el 1 y 7.
- Las horas se dan en formato decimal(ej: 10.5 = 10:30)
- La franja se interpreta como intervalo semiabierto: [inicio, fin. Esto implica que: un evento que acaba a las 11.0 NO solapa con uno que comienza a la misma hora.

---

# 4. Uso del programa interactivo
El menú ofrece:
1. Cargar agenda desde el fichero
2. Mostrar todos los eventos
3. Agregar un evento
4. Eliminar un evento por nombre
5. Buscar eventos por nombre
6. Buscar eventos por dia
7. Mostrar huecos libres en un dia
8. Comprobar solapamientos
9. Salir

Ejemplo:
  Introduzca el nombre del fichero: datos/agenda.txt
  Agenda cargada desde datos/agenda.txt

---

# 5. Ficheros de prueba
### agenda.txt
Sin solapamientos, para pruebas normales y funcionamiento correcto.

### agenda_solapamiento.txt
Con solapamientos, diseñado para mostrar:
  [AVISO] Línea 2: el evento "Tutoría con Ana" solapa con otro y NO se inserta.

### agenda_errores_formato.txt
Con errores graves para mostrar la robustez del programa ante:
- Falta de comas
- Día inválido
- Horas fuera de rango
- Texto donde deberían ir números

Ejemplo:
  [ERROR] Línea 4: formato incorrecto (hora inicio).
  [ERROR] Línea 6: no se pueden convertir los datos numéricos.

---

# 6. Retroalimentación del programa
### Archivos no encontrados
  [ERROR] No se ha podido abrir el fichero: datos/agenda.txt

### Formato incorrecto
  [ERROR] Línea 3: formato incorrecto (día).

### Solapamientos detectados
  [AVISO] Línea 7: el evento "Reunión solapada" solapa con otro y NO se inserta.

### Eliminación correcta
  Evento eliminado correctamente.

### Eliminación fallida
  No se encontró un evento con ese nombre.

---

# 7. TDA Evento
### Operaciones fundamentales
- Constructores
- getNombre()
- getDia()
- getHoraInicio()
- getHoraFin()
- setNombre()
- setDia()
- setFranjaHoraria()

### Operaciones no fundamentales
- seSolapaCon()
- compararPorNombre()
- escribir()
- operator<<>>

### Invariante del TDA Evento
- 1 ≤ dia ≤ 7
- 0.0 ≤ hora_inicio < hora_fin ≤ 24.0

---

# 8. TDA AgendaEventos
### Representación interna
- Array dinámico
- Orden por (dia, hora_inicio)
- Redimensionado automático
- Sin solapamientos por defecto

### Función de Abstracción (FA)
El array datos[0..n_eventos-1] representa el conjunto de eventos almacenados.

### Invariante de Representación (IR)
0 ≤ n_eventos ≤ capacidad
Los eventos están siempre ordenados
No hay solapamientos si permitirSolape = false

### Operaciones fundamentales
- aniadirEvento()
- eliminarEventoPorNombre()
- size()
- empty()

### Operaciones no fundamentales
- buscarPorNombre()
- buscarPorDia()
- mostrar()
- mostrarHuecosLibresDia()
- existeSolapamiento()
- getEvento(int i) const → acceso seguro para imprimir búsquedas
