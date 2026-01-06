#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main() {
    int opcion;

    do {
        printf("\n===== CONCESIONARIA RUEDAS DE ORO =====\n");
        printf("1. Registrar vehiculo\n");
        printf("2. Listar vehiculos disponibles\n");
        printf("3. Buscar vehiculo por preferencias\n");
        printf("4. Registrar cliente\n");
        printf("5. Listar clientes\n");   
        printf("6. Registrar venta\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: registrarVehiculo(); break;
            case 2: listarVehiculos(); break;
            case 3: buscarVehiculo(); break;
            case 4: registrarCliente(); break;
            case 5: listarClientes(); break;
            case 6: registrarVenta(); break;
            case 0: printf("Saliendo del sistema...\n"); break;
            default: printf("Opcion invalida.\n");
        }

    } while (opcion != 0);

    return 0;
}

//primero ctr + ñ
//gcc main.c funciones.c -o inventario.exe
//./inventario.exe

