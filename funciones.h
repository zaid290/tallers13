#include <stdio.h>

//ESTRUCTURAS

typedef struct {
    int id;
    char tipo[20];
    char marca[20];
    char condicion[10];
    float precio;
    int disponible;
} Vehiculo;

typedef struct {
    int id;
    char nombre[50];
    int edad;
    float presupuesto;
} Cliente;

typedef struct {
    int idVenta;
    int idVehiculo;
    int idCliente;
} Venta;



void registrarVehiculo();
void listarVehiculos();
void buscarVehiculo();
void registrarCliente();
void listarClientes();     
void registrarVenta();



int existeVehiculo(int id);
int existeCliente(int id);
int vehiculoDisponible(int id);

