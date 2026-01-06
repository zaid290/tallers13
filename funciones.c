#include "funciones.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//VALIDACIONES

int existeVehiculo(int id) {
    FILE *f = fopen("vehiculos.dat", "rb");
    Vehiculo v;

    if (f == NULL) return 0;

    while (fread(&v, sizeof(Vehiculo), 1, f)) {
        if (v.id == id) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int existeCliente(int id) {
    FILE *f = fopen("clientes.dat", "rb");
    Cliente c;

    if (f == NULL) return 0;

    while (fread(&c, sizeof(Cliente), 1, f)) {
        if (c.id == id) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int vehiculoDisponible(int id) {
    FILE *f = fopen("vehiculos.dat", "rb");
    Vehiculo v;

    if (f == NULL) return 0;

    while (fread(&v, sizeof(Vehiculo), 1, f)) {
        if (v.id == id && v.disponible == 1) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

//VEHICULOS

void registrarVehiculo() {
    FILE *f = fopen("vehiculos.dat", "ab");
    Vehiculo v;

    if (f == NULL) {
        printf("Error al abrir archivo de vehiculos.\n");
        return;
    }

    printf("ID vehiculo: ");
    scanf("%d", &v.id);

    if (v.id <= 0 || existeVehiculo(v.id)) {
        printf("ID invalido o ya existente.\n");
        fclose(f);
        return;
    }

    printf("Tipo: ");
    scanf("%s", v.tipo);
    printf("Marca: ");
    scanf("%s", v.marca);
    printf("Condicion (nuevo/usado): ");
    scanf("%s", v.condicion);

    printf("Precio: ");
    scanf("%f", &v.precio);

    if (v.precio <= 0) {
        printf("Precio invalido.\n");
        fclose(f);
        return;
    }

    v.disponible = 1;
    fwrite(&v, sizeof(Vehiculo), 1, f);
    fclose(f);

    printf("Vehiculo registrado correctamente.\n");
}

void listarVehiculos() {
    FILE *f = fopen("vehiculos.dat", "rb");
    Vehiculo v;

    if (f == NULL) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    printf("\n--- VEHICULOS DISPONIBLES ---\n");
    while (fread(&v, sizeof(Vehiculo), 1, f)) {
        if (v.disponible == 1) {
            printf("ID:%d | %s | %s | %s | $%.2f\n",
                   v.id, v.tipo, v.marca, v.condicion, v.precio);
        }
    }
    fclose(f);
}

void buscarVehiculo() {
    FILE *f = fopen("vehiculos.dat", "rb");
    Vehiculo v;
    char tipo[20], marca[20];
    float presupuesto;

    if (f == NULL) {
        printf("No hay vehiculos registrados.\n");
        return;
    }

    printf("Tipo deseado: ");
    scanf("%s", tipo);
    printf("Marca deseada: ");
    scanf("%s", marca);
    printf("Presupuesto maximo: ");
    scanf("%f", &presupuesto);

    if (presupuesto <= 0) {
        printf("Presupuesto invalido.\n");
        fclose(f);
        return;
    }

    printf("\n--- RESULTADOS ---\n");
    while (fread(&v, sizeof(Vehiculo), 1, f)) {
        if (v.disponible == 1 &&
            strcmp(v.tipo, tipo) == 0 &&
            strcmp(v.marca, marca) == 0 &&
            v.precio <= presupuesto) {

            printf("ID:%d | %s | %s | %s | $%.2f\n",
                   v.id, v.tipo, v.marca, v.condicion, v.precio);
        }
    }
    fclose(f);
}

//CLIENTES

void registrarCliente() {
    FILE *f = fopen("clientes.dat", "ab");
    Cliente c;

    if (f == NULL) {
        printf("Error al abrir archivo de clientes.\n");
        return;
    }

    printf("ID cliente: ");
    scanf("%d", &c.id);

    if (c.id <= 0 || existeCliente(c.id)) {
        printf("ID invalido o ya existente.\n");
        fclose(f);
        return;
    }

    printf("Nombre: ");
    scanf("%s", c.nombre);

    printf("Edad: ");
    scanf("%d", &c.edad);
    if (c.edad <= 0) {
        printf("Edad invalida.\n");
        fclose(f);
        return;
    }

    printf("Presupuesto: ");
    scanf("%f", &c.presupuesto);
    if (c.presupuesto <= 0) {
        printf("Presupuesto invalido.\n");
        fclose(f);
        return;
    }

    fwrite(&c, sizeof(Cliente), 1, f);
    fclose(f);

    printf("Cliente registrado correctamente.\n");
}

void listarClientes() {
    FILE *f = fopen("clientes.dat", "rb");
    Cliente c;

    if (f == NULL) {
        printf("No hay clientes registrados.\n");
        return;
    }

    printf("\n--- LISTA DE CLIENTES ---\n");
    while (fread(&c, sizeof(Cliente), 1, f)) {
        printf("ID:%d | Nombre:%s | Edad:%d | Presupuesto:$%.2f\n",
               c.id, c.nombre, c.edad, c.presupuesto);
    }
    fclose(f);
}

//VENTAS

void registrarVenta() {
    FILE *fv = fopen("vehiculos.dat", "rb+");
    FILE *fventas = fopen("ventas.dat", "ab");
    Venta venta;
    Vehiculo v;
    int idVehiculo, idCliente;

    if (fv == NULL || fventas == NULL) {
        printf("Error al abrir archivos.\n");
        return;
    }

    printf("ID Vehiculo a vender: ");
    scanf("%d", &idVehiculo);

    if (!existeVehiculo(idVehiculo) || !vehiculoDisponible(idVehiculo)) {
        printf("Vehiculo no valido o no disponible.\n");
        fclose(fv);
        fclose(fventas);
        return;
    }

    printf("ID Cliente: ");
    scanf("%d", &idCliente);

    if (!existeCliente(idCliente)) {
        printf("Cliente no existe.\n");
        fclose(fv);
        fclose(fventas);
        return;
    }

    while (fread(&v, sizeof(Vehiculo), 1, fv)) {
        if (v.id == idVehiculo) {
            v.disponible = 0;
            fseek(fv, -sizeof(Vehiculo), SEEK_CUR);
            fwrite(&v, sizeof(Vehiculo), 1, fv);
            break;
        }
    }

    venta.idVenta = rand() % 10000;
    venta.idVehiculo = idVehiculo;
    venta.idCliente = idCliente;

    fwrite(&venta, sizeof(Venta), 1, fventas);

    fclose(fv);
    fclose(fventas);

    printf("Venta registrada exitosamente.\n");
}
