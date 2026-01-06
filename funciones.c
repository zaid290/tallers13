#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"

// Definición de variables globales
Vehiculo inventario[MAX_VEHICULOS];
Cliente clientes[MAX_CLIENTES];
Venta ventas[MAX_VENTAS];
int num_vehiculos = 0;
int num_clientes = 0;
int num_ventas = 0;

// Limpiar buffer de entrada
void limpiar_buffer() {
 while(getchar() != '\n');
}

// Convertir string a minúsculas
void to_lowercase(char *str) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Cargar datos desde archivos
void cargar_datos() {
    FILE *f;
    
    // Cargar vehículos
    f = fopen("vehiculos.dat", "rb");
    if(f != NULL) {
        fread(&num_vehiculos, sizeof(int), 1, f);
        fread(inventario, sizeof(Vehiculo), num_vehiculos, f);
        fclose(f);
    }
    
    // Cargar clientes
    f = fopen("clientes.dat", "rb");
    if(f != NULL) {
        fread(&num_clientes, sizeof(int), 1, f);
        fread(clientes, sizeof(Cliente), num_clientes, f);
        fclose(f);
    }
    
    // Cargar ventas
    f = fopen("ventas.dat", "rb");
    if(f != NULL) {
        fread(&num_ventas, sizeof(int), 1, f);
        fread(ventas, sizeof(Venta), num_ventas, f);
        fclose(f);
    }
}

// Guardar datos en archivos
void guardar_datos() {
    FILE *f;
    
    // Guardar vehículos
    f = fopen("vehiculos.dat", "wb");
    if(f != NULL) {
        fwrite(&num_vehiculos, sizeof(int), 1, f);
        fwrite(inventario, sizeof(Vehiculo), num_vehiculos, f);
        fclose(f);
    }
    
    // Guardar clientes
    f = fopen("clientes.dat", "wb");
    if(f != NULL) {
        fwrite(&num_clientes, sizeof(int), 1, f);
        fwrite(clientes, sizeof(Cliente), num_clientes, f);
        fclose(f);
    }
    
    // Guardar ventas
    f = fopen("ventas.dat", "wb");
    if(f != NULL) {
        fwrite(&num_ventas, sizeof(int), 1, f);
        fwrite(ventas, sizeof(Venta), num_ventas, f);
        fclose(f);
    }
}

// Agregar vehículo al inventario
void agregar_vehiculo() {
    if(num_vehiculos >= MAX_VEHICULOS) {
        printf("\n¡Inventario lleno!\n");
        return;
    }
    
    Vehiculo v;
    v.id = num_vehiculos + 1;
    
    printf("\n--- AGREGAR VEHICULO ---\n");
    printf("Marca: ");
    fgets(v.marca, MAX_STRING, stdin);
    v.marca[strcspn(v.marca, "\n")] = 0;
    
    printf("Modelo: ");
    fgets(v.modelo, MAX_STRING, stdin);
    v.modelo[strcspn(v.modelo, "\n")] = 0;
    
    printf("Año: ");
    scanf("%d", &v.anio);
    limpiar_buffer();
    
    printf("Tipo (Sedan/SUV/Camioneta/Pickup/etc): ");
    fgets(v.tipo, MAX_STRING, stdin);
    v.tipo[strcspn(v.tipo, "\n")] = 0;
    
    printf("Condicion (Nuevo/Usado): ");
    fgets(v.condicion, MAX_STRING, stdin);
    v.condicion[strcspn(v.condicion, "\n")] = 0;
    
    printf("Precio: $");
    scanf("%f", &v.precio);
    limpiar_buffer();
    
    v.disponible = 1;
    
    inventario[num_vehiculos] = v;
    num_vehiculos++;
    
    printf("\nVehiculo agregado exitosamente! ID: %d\n", v.id);
}

// Listar todos los vehículos
void listar_vehiculos() {
    printf("\n--------------------------------------------------------------------\n");
    printf("                     INVENTARIO DE VEHICULOS                        \n");
    printf("--------------------------------------------------------------------\n");
    
    if(num_vehiculos == 0) {
        printf("No hay vehiculos registrados.\n");
        printf("--------------------------------------------------------------------\n");
        return;
    }
    
    for(int i = 0; i < num_vehiculos; i++) {
        printf("\n[ID: %d] %s %s %d - %s\n", 
               inventario[i].id,
               inventario[i].marca,
               inventario[i].modelo,
               inventario[i].anio,
               inventario[i].tipo);
        printf("Condicion: %s | Precio: $%.2f | Estado: %s\n",
               inventario[i].condicion,
               inventario[i].precio,
               inventario[i].disponible ? "DISPONIBLE" : "VENDIDO");
        printf("--------------------------------------------------------------------\n");
    }
}

// Buscar vehículos con filtros
void buscar_vehiculos_filtros() {
    char marca[MAX_STRING] = "";
    char tipo[MAX_STRING] = "";
    char condicion[MAX_STRING] = "";
    float precio_max = 0;
    int usar_marca = 0, usar_tipo = 0, usar_condicion = 0, usar_precio = 0;
    int opcion;
    
    printf("\n--- BUSQUEDA CON FILTROS ---\n");
    printf("Filtrar por marca? (1=Si, 0=No): ");
    scanf("%d", &opcion);
    limpiar_buffer();
    if(opcion == 1) {
        printf("Marca: ");
        fgets(marca, MAX_STRING, stdin);
        marca[strcspn(marca, "\n")] = 0;
        usar_marca = 1;
    }
    
    printf("Filtrar por tipo? (1=Si, 0=No): ");
    scanf("%d", &opcion);
    limpiar_buffer();
    if(opcion == 1) {
        printf("Tipo (Sedan/SUV/Camioneta/Pickup): ");
        fgets(tipo, MAX_STRING, stdin);
        tipo[strcspn(tipo, "\n")] = 0;
        usar_tipo = 1;
    }
    
    printf("Filtrar por condicion? (1=Si, 0=No): ");
    scanf("%d", &opcion);
    limpiar_buffer();
    if(opcion == 1) {
        printf("Condicion (Nuevo/Usado): ");
        fgets(condicion, MAX_STRING, stdin);
        condicion[strcspn(condicion, "\n")] = 0;
        usar_condicion = 1;
    }
    
    printf("Filtrar por precio maximo? (1=Si, 0=No): ");
    scanf("%d", &opcion);
    limpiar_buffer();
    if(opcion == 1) {
        printf("Precio maximo: $");
        scanf("%f", &precio_max);
        limpiar_buffer();
        usar_precio = 1;
    }
    
    // Realizar búsqueda
    printf("\n--------------------------------------------------------------------\n");
    printf("                    RESULTADOS DE BUSQUEDA                          \n");
    printf("--------------------------------------------------------------------\n");
    
    int encontrados = 0;
    for(int i = 0; i < num_vehiculos; i++) {
        if(!inventario[i].disponible) continue;
        
        int cumple = 1;
        
        // Comparaciones case-insensitive
        char marca_inv[MAX_STRING], tipo_inv[MAX_STRING], cond_inv[MAX_STRING];
        strcpy(marca_inv, inventario[i].marca);
        strcpy(tipo_inv, inventario[i].tipo);
        strcpy(cond_inv, inventario[i].condicion);
        to_lowercase(marca_inv);
        to_lowercase(tipo_inv);
        to_lowercase(cond_inv);
        
        char marca_buscar[MAX_STRING], tipo_buscar[MAX_STRING], cond_buscar[MAX_STRING];
        strcpy(marca_buscar, marca);
        strcpy(tipo_buscar, tipo);
        strcpy(cond_buscar, condicion);
        to_lowercase(marca_buscar);
        to_lowercase(tipo_buscar);
        to_lowercase(cond_buscar);
        
        if(usar_marca && strstr(marca_inv, marca_buscar) == NULL) cumple = 0;
        if(usar_tipo && strstr(tipo_inv, tipo_buscar) == NULL) cumple = 0;
        if(usar_condicion && strstr(cond_inv, cond_buscar) == NULL) cumple = 0;
        if(usar_precio && inventario[i].precio > precio_max) cumple = 0;
        
        if(cumple) {
            printf("\n[ID: %d] %s %s %d - %s\n", 
                   inventario[i].id,
                   inventario[i].marca,
                   inventario[i].modelo,
                   inventario[i].anio,
                   inventario[i].tipo);
            printf("Condicion: %s | Precio: $%.2f\n",
                   inventario[i].condicion,
                   inventario[i].precio);
            printf("--------------------------------------------------------------------\n");
            encontrados++;
        }
    }
    
    if(encontrados == 0) {
        printf("\nNo se encontraron vehiculos con esos criterios.\n");
    } else {
        printf("\nTotal encontrados: %d\n", encontrados);
    }
}

// Registrar cliente
void registrar_cliente() {
    if(num_clientes >= MAX_CLIENTES) {
        printf("\nBase de clientes llena!\n");
        return;
    }
    
    Cliente c;
    c.id = num_clientes + 1;
    
    printf("\n--- REGISTRAR CLIENTE ---\n");
    printf("Nombre completo: ");
    fgets(c.nombre, MAX_STRING, stdin);
    c.nombre[strcspn(c.nombre, "\n")] = 0;
    
    printf("Edad: ");
    scanf("%d", &c.edad);
    limpiar_buffer();
    
    printf("Telefono: ");
    fgets(c.telefono, MAX_STRING, stdin);
    c.telefono[strcspn(c.telefono, "\n")] = 0;
    
    clientes[num_clientes] = c;
    num_clientes++;
    
    printf("\nCliente registrado exitosamente! ID: %d\n", c.id);
}

// Registrar venta
void registrar_venta() {
    int id_cliente, id_vehiculo;
    
    printf("\n--- REGISTRAR VENTA ---\n");
    
    // Mostrar clientes
    printf("\nClientes disponibles:\n");
    for(int i = 0; i < num_clientes; i++) {
        printf("ID: %d - %s (Edad: %d)\n", clientes[i].id, clientes[i].nombre, clientes[i].edad);
    }
    
    if(num_clientes == 0) {
        printf("No hay clientes registrados. Por favor, registre un cliente primero.\n");
        return;
    }
    
    printf("\nID del cliente: ");
    scanf("%d", &id_cliente);
    limpiar_buffer();
    
    // Validar cliente
    int cliente_valido = 0;
    for(int i = 0; i < num_clientes; i++) {
        if(clientes[i].id == id_cliente) {
            cliente_valido = 1;
            break;
        }
    }
    
    if(!cliente_valido) {
        printf("\nCliente no encontrado!\n");
        return;
    }
    
    // Mostrar vehículos disponibles
    printf("\nVehiculos disponibles:\n");
    int hay_disponibles = 0;
    for(int i = 0; i < num_vehiculos; i++) {
        if(inventario[i].disponible) {
            printf("ID: %d - %s %s %d ($%.2f)\n", 
                   inventario[i].id,
                   inventario[i].marca,
                   inventario[i].modelo,
                   inventario[i].anio,
                   inventario[i].precio);
            hay_disponibles = 1;
        }
    }
    
    if(!hay_disponibles) {
        printf("No hay vehiculos disponibles para venta.\n");
        return;
    }
    
    printf("\nID del vehiculo: ");
    scanf("%d", &id_vehiculo);
    limpiar_buffer();
    
    // Validar vehículo
    int vehiculo_idx = -1;
    for(int i = 0; i < num_vehiculos; i++) {
        if(inventario[i].id == id_vehiculo && inventario[i].disponible) {
            vehiculo_idx = i;
            break;
        }
    }
    
    if(vehiculo_idx == -1) {
        printf("\nVehiculo no disponible!\n");
        return;
    }
    
    // Registrar venta
    Venta v;
    v.id = num_ventas + 1;
    v.id_cliente = id_cliente;
    v.id_vehiculo = id_vehiculo;
    v.precio_venta = inventario[vehiculo_idx].precio;
    
    printf("Fecha de venta (DD/MM/AAAA): ");
    fgets(v.fecha, MAX_STRING, stdin);
    v.fecha[strcspn(v.fecha, "\n")] = 0;
    
    // Marcar vehículo como vendido
    inventario[vehiculo_idx].disponible = 0;
    
    ventas[num_ventas] = v;
    num_ventas++;
    
    printf("\n--------------------------------------------------------------------\n");
    printf("                 VENTA REGISTRADA EXITOSAMENTE!                     \n");
    printf("--------------------------------------------------------------------\n");
    printf("Venta ID: %d\n", v.id);
    printf("Precio: $%.2f\n", v.precio_venta);
    printf("--------------------------------------------------------------------\n");
}

// Listar clientes
void listar_clientes() {
    printf("\n--------------------------------------------------------------------\n");
    printf("                        LISTA DE CLIENTES                           \n");
    printf("--------------------------------------------------------------------\n");
    
    if(num_clientes == 0) {
        printf("No hay clientes registrados.\n");
        printf("--------------------------------------------------------------------\n");
        return;
    }
    
    for(int i = 0; i < num_clientes; i++) {
        printf("\n[ID: %d] %s\n", clientes[i].id, clientes[i].nombre);
        printf("Edad: %d | Telefono: %s\n", clientes[i].edad, clientes[i].telefono);
        printf("--------------------------------------------------------------------\n");
    }
}

// Listar ventas
void listar_ventas() {
    printf("\n--------------------------------------------------------------------\n");
    printf("                       HISTORIAL DE VENTAS                          \n");
    printf("--------------------------------------------------------------------\n");
    
    if(num_ventas == 0) {
        printf("No hay ventas registradas.\n");
        printf("--------------------------------------------------------------------\n");
        return;
    }
    
    for(int i = 0; i < num_ventas; i++) {
        printf("\n[Venta ID: %d] Fecha: %s\n", ventas[i].id, ventas[i].fecha);
        
        // Buscar datos del cliente
        for(int j = 0; j < num_clientes; j++) {
            if(clientes[j].id == ventas[i].id_cliente) {
                printf("Cliente: %s (ID: %d)\n", clientes[j].nombre, clientes[j].id);
                break;
            }
        }
        
        // Buscar datos del vehículo
        for(int j = 0; j < num_vehiculos; j++) {
            if(inventario[j].id == ventas[i].id_vehiculo) {
                printf("Vehiculo: %s %s %d (ID: %d)\n", 
                       inventario[j].marca,
                       inventario[j].modelo,
                       inventario[j].anio,
                       inventario[j].id);
                break;
            }
        }
        
        printf("Precio de venta: $%.2f\n", ventas[i].precio_venta);
        printf("--------------------------------------------------------------------\n");
    }
}

// Menú principal
void menu_principal() {
    int opcion;
    
    do {
        printf("\n--------------------------------------------------------------------\n");
        printf("              CONCESIONARIA RUEDAS DE ORO - SGIC                   \n");
        printf("--------------------------------------------------------------------\n");
        printf(" 1. Agregar vehiculo al inventario\n");
        printf(" 2. Listar todos los vehiculos\n");
        printf(" 3. Buscar vehiculos (filtros)\n");
        printf(" 4. Registrar cliente\n");
        printf(" 5. Registrar venta\n");
        printf(" 6. Listar clientes\n");
        printf(" 7. Listar ventas\n");
        printf(" 8. Guardar y Salir\n");
        printf("--------------------------------------------------------------------\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        limpiar_buffer();
        
        switch(opcion) {
            case 1: agregar_vehiculo(); break;
            case 2: listar_vehiculos(); break;
            case 3: buscar_vehiculos_filtros(); break;
            case 4: registrar_cliente(); break;
            case 5: registrar_venta(); break;
            case 6: listar_clientes(); break;
            case 7: listar_ventas(); break;
            case 8: 
                guardar_datos();
                printf("\nDatos guardados! Hasta pronto.\n");
                break;
            default: printf("\nOpcion invalida.\n");
        }
    } while(opcion != 8);

}
