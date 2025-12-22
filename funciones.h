

#define MAX_VEHICULOS 100
#define MAX_CLIENTES 100
#define MAX_VENTAS 100
#define MAX_STRING 50

// Estructuras de datos
typedef struct {
    int id;
    char marca[MAX_STRING];
    char modelo[MAX_STRING];
    int anio;
    char tipo[MAX_STRING]; // Sedan, SUV, Camioneta, etc.
    char condicion[MAX_STRING]; // Nuevo, Usado
    float precio;
    int disponible; // 1 = disponible, 0 = vendido
} Vehiculo;

typedef struct {
    int id;
    char nombre[MAX_STRING];
    int edad;
    char telefono[MAX_STRING];
} Cliente;

typedef struct {
    int id;
    int id_cliente;
    int id_vehiculo;
    char fecha[MAX_STRING];
    float precio_venta;
} Venta;

// Variables globales externas
extern Vehiculo inventario[MAX_VEHICULOS];
extern Cliente clientes[MAX_CLIENTES];
extern Venta ventas[MAX_VENTAS];
extern int num_vehiculos;
extern int num_clientes;
extern int num_ventas;

// Prototipos de funciones
void menu_principal();
void cargar_datos();
void guardar_datos();
void agregar_vehiculo();
void listar_vehiculos();
void buscar_vehiculos_filtros();
void registrar_cliente();
void registrar_venta();
void listar_clientes();
void listar_ventas();
void limpiar_buffer();
void to_lowercase(char *str);
