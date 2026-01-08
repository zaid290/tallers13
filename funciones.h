#include <stdio.h>

//ESTRUCTURAS

typedef struct {
    int id;
    char nombre[50];       
    char tipo[20];         
    char marca[20];
    char condicion[10];    
    int anio;              
    float precio;
    int kilometraje;
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

//FUNCIONES

void registrarVehiculo();
void listarVehiculos();
void buscarVehiculo();
void registrarCliente();
void listarClientes();
void registrarVenta();

//VALIDACIONES

int existeVehiculo(int id);
int existeCliente(int id);
int vehiculoDisponible(int id);
