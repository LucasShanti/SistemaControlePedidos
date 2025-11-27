#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "interface.h"



int main()
{
    initscr();
    mostrarMenuPrincipal();
    endwin();
    return 0;
}