#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// Definimos el tipo de dato y el tamaño máximo
typedef int data;
#define MAX 10

// Estructura de la cola
typedef struct {
    data items[MAX];
    int front, rear, count;
} queue;

// --- Implementación de funciones de la cola ---
void initialize(queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

bool full(queue *q) { return q->count == MAX; }
bool empty(queue *q) { return q->count == 0; }

void enqueue(data d, queue *q) {
    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = d;
    q->count++;
}

data dequeue(queue *q) {
    data d = q->items[q->front];
    q->front = (q->front + 1) % MAX;
    q->count--;
    return d;
}

data front(queue *q) { return q->items[q->front]; }
data back(queue *q) { return q->items[q->rear]; }

// --- Bloque Principal  ---
int main(void) {
    int c;
    data pid;   
    queue a;    

    initialize(&a);

    printf("--- SISTEMA DE COMANDAS (Basado en queue.c) ---\n");
    printf("Comandos:\n 'a' + [num]: Recibir Comanda\n 's': Servir Platillo\n 'v': Ver Próximo\n 'u': Ver Último\n\n");

    /* Estructura original solicitada */
    while ((c = getchar()) != EOF) {
        switch (c) {
            case 'a':   // RECIBIR COMANDA (Enqueue)
                
                if (scanf("%u", &pid) == 1) { 
                    if (!full(&a)) {
                        enqueue(pid, &a);
                        printf(">> Platillo %u anotado.\n", pid);
                    } else {
                        printf(">> Cola llena.\n");
                    }
                }
                break;

            case 's':   // SERVIR PLATILLO (Dequeue)
                if (!empty(&a)) {
                    pid = dequeue(&a);
                    printf(">> Platillo %u servido.\n", pid);
                } else {
                    printf(">> No hay comandas.\n");
                }
                break;

            case 'v':   // CONSULTAR PRÓXIMO (Front)
                if (!empty(&a)) {
                    printf(">> El próximo a servir es: %u\n", front(&a));
                }
                break;

            case 'u':   // CONSULTAR ÚLTIMO (Back)
                if (!empty(&a)) {
                    printf(">> El último anotado fue: %u\n", back(&a));
                }
                break;
        }    
    }

    return 0;
}
