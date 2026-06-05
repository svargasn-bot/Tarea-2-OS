#include "interfaz.hpp"

using namespace std;

void inicializarNcurses() {
    initscr();     
    noecho();      
    curs_set(0);    
    keypad(stdscr, TRUE);
}

int menuPrincipal(int &vueltas, int &ancho, int &numCaballos) {
    int opcion = 0;
    int yMax, xMax; 

    while(true) {
        getmaxyx(stdscr, yMax, xMax);
        clear(); 
        box(stdscr, 0, 0);

        attron(A_BOLD | A_REVERSE); 
        mvprintw(0, (xMax / 2) - 7, " HIPODROMO ");
        attroff(A_BOLD | A_REVERSE);

        // OPCIONES MENU
        string ops[5] = {
            "1. Iniciar Carrera", 
            "2. Vueltas: " + to_string(vueltas) + " (Limites: 1 a 4)", 
            "3. Largo Pista: " + to_string(ancho) + " (Limites: 30, 40, 50, 60)",
            "4. Nro Caballos: " + to_string(numCaballos) + " (Limites: 2 a 7)",
            "5. Salir"
        };

        for(int i = 0; i < 5; i++) {
            if(i == opcion) attron(A_REVERSE);
            // Centramos un poco más a la izquierda (-15) porque los textos son más largos
            mvprintw((yMax / 2) + i, (xMax / 2) - 15, "%s", ops[i].c_str());
            if(i == opcion) attroff(A_REVERSE);
        }

        int input = getch(); 
        
        // Navegación Arriba / Abajo adaptada para 5 opciones
        if(input == KEY_UP) {
            opcion--;
            if(opcion < 0) opcion = 4;
        }
        else if(input == KEY_DOWN) {
            opcion++;
            if(opcion > 4) opcion = 0;
        }
        // NUEVO: Navegación Izquierda / Derecha adaptado el menu
        else if(input == KEY_LEFT) {
            if(opcion == 1 && vueltas > 1) vueltas--; 
            if(opcion == 2 && ancho > 30) ancho -= 10; 
            if(opcion == 3 && numCaballos > 2) numCaballos--;
        }
        else if(input == KEY_RIGHT) {
            if(opcion == 1 && vueltas < 4) vueltas++;
            if(opcion == 2 && ancho < 60) ancho += 10; 
            if(opcion == 3 && numCaballos < 7) numCaballos++;
        }
        else if(input == '\n') {
            if(opcion == 0) return 1; // Retorna 1 para iniciar (igual que tu código original)
            if(opcion == 4) return 2; // Retorna 2 para salir
        }
    }
}

int menuFinal(int yBase) {
    int opcion = 0;
    string ops[2] = {" Volver ", " Salir "};
    int yMax, xMax;
    
    while(true) {
        getmaxyx(stdscr, yMax, xMax);
        mvprintw(yBase, (xMax / 2) - 14, "--- desea volver al menu? ---");
        for(int i = 0; i < 2; i++) {
            if(i == opcion) attron(A_REVERSE);
            mvprintw(yBase + 2, (xMax / 4) + (i * (xMax / 2.5)), "%s", ops[i].c_str());
            if(i == opcion) attroff(A_REVERSE); 
        }
        refresh();
        int input = getch();
        if(input == KEY_LEFT) opcion = 0;
        else if(input == KEY_RIGHT) opcion = 1;
        else if(input == '\n') return opcion;
    }
}