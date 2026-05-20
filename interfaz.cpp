#include "interfaz.hpp"

using namespace std;

void inicializarNcurses() {
    initscr();     
    noecho();      
    curs_set(0);    
    keypad(stdscr, TRUE);
}

int menuPrincipal() {
    int opcion = 0;
    string ops[2] = {"1. Iniciar Carrera", "2. Salir "};
    int yMax, xMax; 

    while(true) {
        getmaxyx(stdscr, yMax, xMax);
        clear(); 
        box(stdscr, 0, 0);

        attron(A_BOLD | A_REVERSE); 
        mvprintw(0, (xMax / 2) - 7, " HIPODROMO ");
        attroff(A_BOLD | A_REVERSE);

        for(int i = 0; i < 2; i++) {
            if(i == opcion) attron(A_REVERSE);
            mvprintw((yMax / 2) + i, (xMax / 2) - 10, "%s", ops[i].c_str());
            attroff(A_REVERSE);
        }

        int input = getch(); 
        if(input == KEY_UP) opcion = 0;
        else if(input == KEY_DOWN) opcion = 1;
        else if(input == '\n') return opcion; 
    }
}

int menuFinal(int yBase) {
    int opcion = 0;
    string ops[2] = {" Volver ", " Salir "};
    int yMax, xMax;
    
    while(true) {
        getmaxyx(stdscr, yMax, xMax);
        mvprintw(yBase, (xMax / 2) - 15, "--- ¿desea volver al menu? ---");
        for(int i = 0; i < 2; i++) {
            if(i == opcion) attron(A_REVERSE);
            mvprintw(yBase + 2, (xMax / 4) + (i * (xMax / 2.5)), "%s", ops[i].c_str());
            attroff(A_REVERSE);
        }
        refresh();
        int input = getch();
        if(input == KEY_LEFT) opcion = 0;
        else if(input == KEY_RIGHT) opcion = 1;
        else if(input == '\n') return opcion;
    }
}