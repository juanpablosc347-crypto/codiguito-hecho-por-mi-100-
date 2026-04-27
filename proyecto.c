#include <stdio.h>
#include <string.h>

// Estructura del registro con 5 atributos
struct Videojuego {
    int id;
    char nombre[50];
    char genero[30];
    int anio;
    float precio;
};

// Funcion para agregar un registro
void agregar() {
    struct Videojuego v;
    FILE *archivo = fopen("videojuegos.bin", "ab");

    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }

    printf("ID: ");
    scanf("%d", &v.id);
    getchar(); // limpia el enter

    printf("Nombre: ");
    scanf("%[^\n]", v.nombre);
    getchar();

    printf("Genero: ");
    scanf("%[^\n]", v.genero);
    getchar();

    printf("Anio de lanzamiento: ");
    scanf("%d", &v.anio);

    printf("Precio: ");
    scanf("%f", &v.precio);

    fwrite(&v, sizeof(struct Videojuego), 1, archivo);
    fclose(archivo);

    printf("Registro agregado correctamente\n\n");
}

// Funcion para mostrar todos los registros
void consultarTodos() {
    struct Videojuego v;
    FILE *archivo = fopen("videojuegos.bin", "rb");

    if (archivo == NULL) {
        printf("No hay registros guardados\n\n");
        return;
    }

    printf("\n--- Lista de videojuegos ---\n");
    for (; fread(&v, sizeof(struct Videojuego), 1, archivo) == 1;) {
        printf("ID: %d | Nombre: %s | Genero: %s | Anio: %d | Precio: %.2f\n",
               v.id, v.nombre, v.genero, v.anio, v.precio);
    }
    printf("\n");

    fclose(archivo);
}

// Funcion para buscar por ID
void buscarPorID() {
    struct Videojuego v;
    int buscar, encontrado = 0;

    FILE *archivo = fopen("videojuegos.bin", "rb");

    if (archivo == NULL) {
        printf("No hay registros guardados\n\n");
        return;
    }

    printf("ID a buscar: ");
    scanf("%d", &buscar);

    for (; fread(&v, sizeof(struct Videojuego), 1, archivo) == 1;) {
        if (v.id == buscar) {
            printf("ID: %d | Nombre: %s | Genero: %s | Anio: %d | Precio: %.2f\n",
                   v.id, v.nombre, v.genero, v.anio, v.precio);
            encontrado = 1;
        }
    }

    if (encontrado == 0) {
        printf("No se encontro el registro\n");
    }
    printf("\n");

    fclose(archivo);
}

// Funcion para eliminar un registro
void eliminar() {
    struct Videojuego v;
    int buscar, encontrado = 0;

    FILE *archivo = fopen("videojuegos.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");

    if (archivo == NULL) {
        printf("No hay registros guardados\n\n");
        return;
    }

    printf("ID a eliminar: ");
    scanf("%d", &buscar);

    // copia todos menos el que quieres borrar
    for (; fread(&v, sizeof(struct Videojuego), 1, archivo) == 1;) {
        if (v.id != buscar) {
            fwrite(&v, sizeof(struct Videojuego), 1, temp);
        } else {
            encontrado = 1;
        }
    }

    fclose(archivo);
    fclose(temp);

    remove("videojuegos.bin");
    rename("temp.bin", "videojuegos.bin");

    if (encontrado) {
        printf("Registro eliminado\n\n");
    } else {
        printf("No se encontro el ID\n\n");
    }
}

// Funcion para modificar un registro
void modificar() {
    struct Videojuego v;
    int buscar, encontrado = 0;

    FILE *archivo = fopen("videojuegos.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");

    if (archivo == NULL) {
        printf("No hay registros guardados\n\n");
        return;
    }

    printf("ID a modificar: ");
    scanf("%d", &buscar);

    for (; fread(&v, sizeof(struct Videojuego), 1, archivo) == 1;) {
        if (v.id == buscar) {
            encontrado = 1;
            printf("Datos nuevos:\n");
            getchar();

            printf("Nombre: ");
            scanf("%[^\n]", v.nombre);
            getchar();

            printf("Genero: ");
            scanf("%[^\n]", v.genero);
            getchar();

            printf("Anio de lanzamiento: ");
            scanf("%d", &v.anio);

            printf("Precio: ");
            scanf("%f", &v.precio);
        }
        fwrite(&v, sizeof(struct Videojuego), 1, temp);
    }

    fclose(archivo);
    fclose(temp);

    remove("videojuegos.bin");
    rename("temp.bin", "videojuegos.bin");

    if (encontrado) {
        printf("Registro modificado\n\n");
    } else {
        printf("No se encontro el ID\n\n");
    }
}

int main() {
    int opcion;

    do {
        printf("=== SISTEMA DE VIDEOJUEGOS ===\n");
        printf("1. Agregar\n");
        printf("2. Eliminar\n");
        printf("3. Modificar\n");
        printf("4. Consultar todos\n");
        printf("5. Buscar por ID\n");
        printf("6. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        printf("\n");

        switch (opcion) {
            case 1: agregar(); break;
            case 2: eliminar(); break;
            case 3: modificar(); break;
            case 4: consultarTodos(); break;
            case 5: buscarPorID(); break;
            case 6: printf("Saliendo...\n"); break;
            default: printf("Opcion no valida\n\n");
        }
    } while (opcion != 6);

    return 0;
}