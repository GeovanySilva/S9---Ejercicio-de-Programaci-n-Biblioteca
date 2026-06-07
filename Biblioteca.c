#include <stdio.h>
#include <string.h>

#define MAX_LIBROS 10

struct Libro {
    int id;
    char titulo[100];
    char autor[50];
    int anio;
    char estado[15];
};

struct Libro libros[MAX_LIBROS];
int cantidad = 0;

// Buscar libro por ID
int buscarPorID(int id) {
    for(int i = 0; i < cantidad; i++) {
        if(libros[i].id == id)
            return i;
    }
    return -1;
}

// Registrar libro
void registrarLibro() {
    if(cantidad >= MAX_LIBROS) {
        printf("\nNo se pueden agregar más libros.\n");
        return;
    }

    int id;

    printf("\nIngrese ID del libro: ");
    scanf("%d", &id);

    if(buscarPorID(id) != -1) {
        printf("Error: El ID ya existe.\n");
        return;
    }

    libros[cantidad].id = id;

    getchar();

    printf("Ingrese titulo: ");
    fgets(libros[cantidad].titulo, 100, stdin);
    libros[cantidad].titulo[strcspn(libros[cantidad].titulo, "\n")] = '\0';

    printf("Ingrese autor: ");
    fgets(libros[cantidad].autor, 50, stdin);
    libros[cantidad].autor[strcspn(libros[cantidad].autor, "\n")] = '\0';

    printf("Ingrese año de publicacion: ");
    scanf("%d", &libros[cantidad].anio);

    strcpy(libros[cantidad].estado, "Disponible");

    cantidad++;

    printf("Libro registrado correctamente.\n");
}

// Mostrar libros
void mostrarLibros() {
    if(cantidad == 0) {
        printf("\nNo hay libros registrados.\n");
        return;
    }

    printf("\n=======================================================================\n");
    printf("%-5s %-25s %-20s %-10s %-12s\n",
           "ID", "Titulo", "Autor", "Año", "Estado");
    printf("=======================================================================\n");

    for(int i = 0; i < cantidad; i++) {
        printf("%-5d %-25s %-20s %-10d %-12s\n",
               libros[i].id,
               libros[i].titulo,
               libros[i].autor,
               libros[i].anio,
               libros[i].estado);
    }
}

// Buscar libro
void buscarLibro() {
    int opcion;

    printf("\n1. Buscar por ID\n");
    printf("2. Buscar por titulo\n");
    printf("Seleccione opcion: ");
    scanf("%d", &opcion);

    if(opcion == 1) {
        int id;
        printf("Ingrese ID: ");
        scanf("%d", &id);

        int pos = buscarPorID(id);

        if(pos != -1) {
            printf("\nID: %d\n", libros[pos].id);
            printf("Titulo: %s\n", libros[pos].titulo);
            printf("Autor: %s\n", libros[pos].autor);
            printf("Año: %d\n", libros[pos].anio);
            printf("Estado: %s\n", libros[pos].estado);
        } else {
            printf("Libro no encontrado.\n");
        }
    }
    else if(opcion == 2) {
        char titulo[100];

        getchar();

        printf("Ingrese titulo: ");
        fgets(titulo, 100, stdin);
        titulo[strcspn(titulo, "\n")] = '\0';

        int encontrado = 0;

        for(int i = 0; i < cantidad; i++) {
            if(strcmp(libros[i].titulo, titulo) == 0) {
                printf("\nID: %d\n", libros[i].id);
                printf("Titulo: %s\n", libros[i].titulo);
                printf("Autor: %s\n", libros[i].autor);
                printf("Año: %d\n", libros[i].anio);
                printf("Estado: %s\n", libros[i].estado);
                encontrado = 1;
                break;
            }
        }

        if(!encontrado)
            printf("Libro no encontrado.\n");
    }
}

// Actualizar estado
void actualizarEstado() {
    int id;

    printf("\nIngrese ID del libro: ");
    scanf("%d", &id);

    int pos = buscarPorID(id);

    if(pos == -1) {
        printf("Libro no encontrado.\n");
        return;
    }

    if(strcmp(libros[pos].estado, "Disponible") == 0)
        strcpy(libros[pos].estado, "Prestado");
    else
        strcpy(libros[pos].estado, "Disponible");

    printf("Estado actualizado correctamente.\n");
}

// Eliminar libro
void eliminarLibro() {
    int id;

    printf("\nIngrese ID del libro a eliminar: ");
    scanf("%d", &id);

    int pos = buscarPorID(id);

    if(pos == -1) {
        printf("Libro no encontrado.\n");
        return;
    }

    for(int i = pos; i < cantidad - 1; i++) {
        libros[i] = libros[i + 1];
    }

    cantidad--;

    printf("Libro eliminado correctamente.\n");
}

int main() {

    int opcion;

    do {
        printf("\n===== SISTEMA DE BIBLIOTECA =====\n");
        printf("1. Registrar libro\n");
        printf("2. Mostrar libros\n");
        printf("3. Buscar libro\n");
        printf("4. Actualizar estado\n");
        printf("5. Eliminar libro\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                registrarLibro();
                break;
            case 2:
                mostrarLibros();
                break;
            case 3:
                buscarLibro();
                break;
            case 4:
                actualizarEstado();
                break;
            case 5:
                eliminarLibro();
                break;
            case 6:
                printf("Programa finalizado.\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }

    } while(opcion != 6);

    return 0;
}
