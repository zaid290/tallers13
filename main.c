#include <stdio.h>
#include "funciones.h"

int main() {
    printf("\n--------------------------------------------------------------------\n");
    printf("              SISTEMA DE GESTION DE INVENTARIO                      \n");
    printf("                 CONCESIONARIA RUEDAS DE ORO                        \n");
    printf("--------------------------------------------------------------------\n");
    
    cargar_datos();
    printf("\nDatos cargados correctamente.\n");
    
    menu_principal();
    
    return 0;
}
//primero ctr + ñ
//gcc main.c funciones.c -o examen.exe
//./examen.exe