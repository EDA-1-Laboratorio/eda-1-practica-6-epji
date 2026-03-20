#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char titulo[100];
    char artista[100];
    int duracion; // en segundos
} Cancion;

void agregarCancion(Cancion c[], int *total) {
    printf("ID: ");
    scanf("%d", &c[*total].id);
    getchar(); // Limpiar buffer
    printf("Titulo: ");
    fgets(c[*total].titulo, 100, stdin);
    c[*total].titulo[strcspn(c[*total].titulo, "\n")] = 0; // Quitar salto de linea
    printf("Artista: ");
    fgets(c[*total].artista, 100, stdin);
    c[*total].artista[strcspn(c[*total].artista, "\n")] = 0;
    printf("Duracion (seg): ");
    scanf("%d", &c[*total].duracion);
    (*total)++;
}

void mostrarCatalogo(Cancion c[], int total) {
    printf("\n--- Catalogo de Canciones ---\n");
    for (int i = 0; i < total; i++) {
        printf("ID: %d | %s - %s (%d seg)\n", c[i].id, c[i].titulo, c[i].artista, c[i].duracion);
    }
}

void guardarCatalogo(Cancion c[], int total) {
    FILE *file = fopen("catalogo.dat", "wb");
    if (file != NULL) {
        fwrite(c, sizeof(Cancion), total, file);
        fclose(file);
        printf("Catalogo guardado.\n");
    }
}

int cargarCatalogo(Cancion c[]) {
    FILE *file = fopen("catalogo.dat", "rb");
    int total = 0;
    if (file != NULL) {
        total = fread(c, sizeof(Cancion), 100, file); // Lee hasta 100
        fclose(file);
    }
    return total;
}


int main() {
    Cancion catalogo[100];
    int total = cargarCatalogo(catalogo);
    int opcion;

    do {
        printf("\n1. Agregar cancion\n2. Mostrar catalogo\n3. Guardar y Salir\nOpcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: agregarCancion(catalogo, &total); break;
            case 2: mostrarCatalogo(catalogo, total); break;
            case 3: guardarCatalogo(catalogo, total); break;
        }
    } while (opcion != 3);

    return 0;
}
