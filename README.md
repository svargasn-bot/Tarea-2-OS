# Tarea 2 OS
Comando de compilación :g++ main.cpp caballo.cpp hipodromo.cpp interfaz.cpp -o carrera -lncurses -pthread -o tarea2
Comando de ejecución: ./carrera

Integrantes de grupo:
- Vicente Arias
- Francisco Muñoz
- Sebastián Vargas

Esta Tarea utiliza la biblioteca <n.curses.h> si no se tiene esta biblioteca 
no se podrá compilar.


Este es un proyecto modularizado en **C++** que simula una carrera de caballos interactiva en la terminal utilizando la librería **NCurses**. 

El programa permite visualizar el avance aleatorio de los competidores sobre una pista geométrica y, a diferencia de las versiones estándar, la carrera no se detiene con el primer ganador; continúa hasta que **todos los caballos cruzan la meta** para desplegar una tabla de posiciones final de forma secuencial.

## Arquitectura del Proyecto

El código está estructurado bajo principios de ingeniería de software para mantener una alta cohesión y bajo acoplamiento, dividiéndose en los siguientes módulos:

* **Módulo Caballo (`caballo.hpp` / `caballo.cpp`):** Define la estructura de los competidores, su representación visual según la dirección del movimiento y la lógica para registrar el orden de llegada en el podio.
* **Módulo Hipódromo (`hipodromo.hpp` / `hipodromo.cpp`):** Maneja la geometría de la pista, el cálculo de las coordenadas del circuito (camino) y el renderizado de los elementos gráficos en pantalla.
* **Módulo Interfaz (`interfaz.hpp` / `interfaz.cpp`):** Encapsula la inicialización de la librería NCurses y gestiona las pantallas del menú principal y post-carrera.
* **Ejecucion Principal (`main.cpp`):** Coordina el flujo macro de la aplicación, los ciclos de la carrera y la actualización de los estados.

## Compilación y Ejecución (Linux / WSL)

Para compilar y ejecutar el proyecto en un entorno Linux con el compilador `g++`, asegúrate de tener instaladas las librerías de desarrollo de ncurses (`libncurses5-dev`) y ejecuta el siguiente comando en la terminal:

```bash
g++ main.cpp caballo.cpp hipodromo.cpp interfaz.cpp -o carrera -lncurses -pthread -o tarea2