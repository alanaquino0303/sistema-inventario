# Sistema de Inventario en C

Aplicación de consola desarrollada en C para la gestión de inventarios. Permite agregar, listar, buscar, modificar y eliminar productos de manera sencilla. Los datos se almacenan en un archivo CSV (`inventario.csv`) para mantener la persistencia entre ejecuciones. Este proyecto sirve como práctica para el manejo de estructuras, archivos y menús interactivos en C.

---

## Características principales
- Menú interactivo y fácil de usar.
- Estructura `Producto` con nombre, cantidad y precio.
- Persistencia automática de datos en archivo CSV.
- Validación de entradas del usuario.
- Funciones modulares para cada operación: Agregar, listar, buscar, modificar y eliminar productos.
- Compatible con Linux, macO y Windows.
- Configuración mediante macros (`MAX_PRODUCTOS`, `MAX_NOMBRE`).

---

## Estructura del proyecto
```
/ sistema-inventario
├─ sistema_inventario.c     # Código fuente principal.
└─ README.md                # Documentación del proyecto.
```

---

## Requisitos
- Compilador C (GCC o Clang).
- Sistema operativo compatible con consola (Linux, macOS o Windows).
- Permisos de lectura y escritura en el directorio actual (para generar `inventario.csv`).

---

## Ejecución

### Compilar el programa

#### En Linux o macOS:

   ```bash
   gcc -o sistema_inventario sistema_inventario.c
   ```

#### En Windows:

   ```bash
   gcc -o sistema_inventario.exe sistema_inventario.c
   ```

---

### Ejecutar el programa

#### En Linux o macOS:

   ```bash
   ./sistema_inventario
   ```

#### En Windows:

   ```bash
   sistema_inventario.exe
   ```

---

### Archivo de datos
El archivo `inventario.csv` se crea automáticamente al agregar productos y se actualiza cada vez que se modifica el inventario. Su formato es el siguiente:
   ```
   nombre_producto,cantidad,precio
   Ejemplo,10,25.50
   ```

---

## Autor

Alan Aquino.
