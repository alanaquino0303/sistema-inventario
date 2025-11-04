#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_PRODUCTOS 100
#define MAX_NOMBRE 50
#define ARCHIVO_CSV "inventario.csv"

typedef struct {
    char nombre[MAX_NOMBRE];
    int cantidad;
    float precio;
} Producto;

Producto inventario[MAX_PRODUCTOS];
int totalProductos = 0;

// Función para limpiar buffer de entrada.
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Guardar inventario en archivo CSV.
void guardarInventario() {
    FILE *f = fopen(ARCHIVO_CSV, "w");
    if (!f) {
        printf("No se pudo guardar el archivo.\n");
        return;
    }

    for (int i = 0; i < totalProductos; i++) {
        fprintf(f, "%s,%d,%.2f\n",
                inventario[i].nombre,
                inventario[i].cantidad,
                inventario[i].precio);
    }

    fclose(f);
    printf("Inventario guardado en '%s'.\n", ARCHIVO_CSV);
}

// Cargar inventario desde CSV.
void cargarInventario() {
    FILE *f = fopen(ARCHIVO_CSV, "r");
    if (!f) {
        printf("No se encontró '%s'. Se creará uno nuevo.\n", ARCHIVO_CSV);
        return;
    }

    totalProductos = 0;
    while (fscanf(f, " %49[^,],%d,%f\n",
                  inventario[totalProductos].nombre,
                  &inventario[totalProductos].cantidad,
                  &inventario[totalProductos].precio) == 3) {
        totalProductos++;
        if (totalProductos >= MAX_PRODUCTOS) break;
    }

    fclose(f);
    printf("Inventario cargado (%d productos).\n", totalProductos);
}

// Agregar producto (con validación).
void agregarProducto() {
    if (totalProductos >= MAX_PRODUCTOS) {
        printf("\nInventario lleno.\n");
        return;
    }

    Producto nuevo;
    printf("\nAGREGAR PRODUCTO\n");

    do {
        printf("Nombre: ");
        scanf(" %[^\n]", nuevo.nombre);
        limpiarBuffer();
        if (strlen(nuevo.nombre) == 0) {
            printf("El nombre no puede estar vacío.\n");
        }
    } while (strlen(nuevo.nombre) == 0);

    do {
        printf("Cantidad: ");
        if (scanf("%d", &nuevo.cantidad) != 1 || nuevo.cantidad < 0) {
            printf("Ingrese una cantidad válida (entero positivo).\n");
            limpiarBuffer();
            nuevo.cantidad = -1;
        }
    } while (nuevo.cantidad < 0);

    do {
        printf("Precio: ");
        if (scanf("%f", &nuevo.precio) != 1 || nuevo.precio < 0) {
            printf("Ingrese un precio válido (número positivo).\n");
            limpiarBuffer();
            nuevo.precio = -1;
        }
    } while (nuevo.precio < 0);

    inventario[totalProductos++] = nuevo;
    guardarInventario();
    printf("\nProducto agregado y guardado correctamente.\n");
}

// Listar productos.
void listarProductos() {
    if (totalProductos == 0) {
        printf("\nNo hay productos en el inventario.\n");
        return;
    }

    printf("\nLISTA DE PRODUCTOS\n");
    printf("%-20s %-20s %-20s\n", "Nombre", "Cantidad", "Precio");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < totalProductos; i++) {
        printf("%-20s %-20d ₲%.2f\n",
               inventario[i].nombre,
               inventario[i].cantidad,
               inventario[i].precio);
    }
}

// Buscar producto.
void buscarProducto() {
    if (totalProductos == 0) {
        printf("\nNo hay productos en el inventario.\n");
        return;
    }

    char buscar[MAX_NOMBRE];
    printf("\nBUSCAR PRODUCTO\n");
    printf("Ingrese parte del nombre: ");
    scanf(" %[^\n]", buscar);
    limpiarBuffer();

    printf("\nResultados de búsqueda:\n");
    int encontrados = 0;

    for (int i = 0; i < totalProductos; i++) {
        if (strcasestr(inventario[i].nombre, buscar) != NULL) {
            printf("%-20s %-20d $%.2f\n",
                   inventario[i].nombre,
                   inventario[i].cantidad,
                   inventario[i].precio);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("No se encontraron productos con ese nombre.\n");
    }
}

// Modificar producto.
void modificarProducto() {
    if (totalProductos == 0) {
        printf("\nNo hay productos en el inventario.\n");
        return;
    }

    char buscar[MAX_NOMBRE];
    printf("\nMODIFICAR PRODUCTO\n");
    printf("Ingrese nombre exacto del producto: ");
    scanf(" %[^\n]", buscar);
    limpiarBuffer();

    int encontrado = -1;
    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(inventario[i].nombre, buscar) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    printf("Producto encontrado: %s (Cantidad: %d, Precio: %.2f)\n",
           inventario[encontrado].nombre,
           inventario[encontrado].cantidad,
           inventario[encontrado].precio);

    int nuevaCantidad;
    float nuevoPrecio;

    do {
        printf("Nueva cantidad: ");
        if (scanf("%d", &nuevaCantidad) != 1 || nuevaCantidad < 0) {
            printf("Ingrese una cantidad válida.\n");
            limpiarBuffer();
            nuevaCantidad = -1;
        }
    } while (nuevaCantidad < 0);

    do {
        printf("Nuevo precio: ");
        if (scanf("%f", &nuevoPrecio) != 1 || nuevoPrecio < 0) {
            printf("Ingrese un precio válido.\n");
            limpiarBuffer();
            nuevoPrecio = -1;
        }
    } while (nuevoPrecio < 0);

    inventario[encontrado].cantidad = nuevaCantidad;
    inventario[encontrado].precio = nuevoPrecio;

    guardarInventario();
    printf("Producto modificado y guardado.\n");
}

// Eliminar producto.
void eliminarProducto() {
    if (totalProductos == 0) {
        printf("\nNo hay productos en el inventario.\n");
        return;
    }

    char buscar[MAX_NOMBRE];
    printf("\nELIMINAR PRODUCTO\n");
    printf("Ingrese nombre exacto del producto: ");
    scanf(" %[^\n]", buscar);
    limpiarBuffer();

    int indice = -1;
    for (int i = 0; i < totalProductos; i++) {
        if (strcmp(inventario[i].nombre, buscar) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    for (int i = indice; i < totalProductos - 1; i++) {
        inventario[i] = inventario[i + 1];
    }
    totalProductos--;

    guardarInventario();
    printf("Producto eliminado y archivo actualizado.\n");
}

// Menú principal.
int main() {
    int opcion;

    cargarInventario();

    do {
        printf("\nSISTEMA DE INVENTARIO\n");
        printf("1. Agregar producto.\n");
        printf("2. Listar productos.\n");
        printf("3. Buscar producto.\n");
        printf("4. Modificar producto.\n");
        printf("5. Eliminar producto.\n");
        printf("6. Guardar inventario.\n");
        printf("7. Salir.\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion) {
            case 1: agregarProducto(); break;
            case 2: listarProductos(); break;
            case 3: buscarProducto(); break;
            case 4: modificarProducto(); break;
            case 5: eliminarProducto(); break;
            case 6: guardarInventario(); break;
            case 7:
                printf("\nSaliendo del programa...\n");
                guardarInventario();
                break;
            default:
                printf("\nOpción inválida.\n");
        }
    } while (opcion != 7);

    return 0;
}