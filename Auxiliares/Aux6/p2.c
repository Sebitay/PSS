#include "stdlib.h" // malloc, free
#include "stdio.h" // printf y todas las funnciones de archivos.
#include "string.h" // strcmp

typedef struct node {
    void *val;
    struct node *next;
} QueueNode;

typedef struct queue {
    QueueNode *first, **plast;
    int len;
} Queue;

Queue *makeQueue() {
    Queue *q = malloc(sizeof(Queue));
    q->first = NULL;
    q->plast = &q->first;
    q->len = 0;
    return q;
}

void put(Queue *q, void *ptr) {
    QueueNode *node = malloc(sizeof(QueueNode));
    node->val = ptr;
    node->next = NULL;
    *q->plast = node;
    q->plast = &node->next;
    q->len++;
}

void *get(Queue *q) {
    if (q->first == NULL) {
        return NULL;
    }
    void *val = q->first->val;
    QueueNode *next = q->first->next;
    free(q->first);
    q->first = next;
    if (next == NULL) {
        q->plast = &q->first;
    }
    q->len--;
    return val;
}

void *peek(Queue *q) {
    if (q->first == NULL) {
        return NULL;
    } else {
        return q->first->val;
    }
}

int emptyQueue(Queue *q) {
    return q->first == NULL;
}

int queueLength(Queue *q) {
    return q->len;
}

void destroyQueue(Queue *q) {
    QueueNode *node = q->first;
    while (node != NULL) {
        QueueNode *next = node->next;
        free(node);
        node = next;
    }
    free(q);
}

void quicksort(Queue *q, int (*cmp)(void *ptr1, void *ptr2)){
  if (emptyQueue(q)){ // Caso base, la cola entregada está vacía
    return;
  }
  // Estrategia de pivote, el primer elemento de la cola
  // Se crean dos colas, una para los elementos menores y otra para los mayores
  Queue *menor = makeQueue();
  Queue *mayor = makeQueue();
  void *pivote = get(q);
  while (!emptyQueue(q)){ // Se recorre la cola entregada
    void *elemento = get(q); // Se obtiene el elemento
    if (cmp(elemento, pivote) >=0){ // Se compara con el pivote
      put(mayor, elemento);
    } else {
      put(menor, elemento);
    }
  }
  // Se ordenan las colas menores y mayores recursivamente
  quicksort(mayor, cmp);
  quicksort(menor, cmp);
  // Se ponen los elementos en la cola original
  // Se ponen los elementos menores
  while (!emptyQueue(menor)){
    void *em = get(menor);
    put(q, em);
  }
  // Se pone el pivote
  put(q, pivote);
  // Se ponen los elementos mayores
  while (!emptyQueue(mayor)){
    void *em = get(mayor);
    put(q, em);
  }
  // Se destruyen las colas menores y mayores
  destroyQueue(menor);
  destroyQueue(mayor);
}

int cmp_strings(void *ptr1, void *ptr2) {
  return strcmp(ptr1, ptr2);
}

typedef struct persona{
  char *nombre;
  int edad;
} Persona;

int cmp_persona(void *ptr1, void *ptr2){
  Persona *p1 = (Persona *) ptr1;
  Persona *p2 = (Persona *) ptr2;
  return p1->edad - p2->edad;
}

int main() {
    char a[] = "pedro";
    char b[] = "juan";
    char c[] = "diego";
    char d[] = "pablo";
    Queue *q = makeQueue();

    put(q,a);
    put(q,b);
    put(q,c);
    put(q,d);

    quicksort(q, cmp_strings);

    while (!emptyQueue(q)){
      char *s = (char *) get(q);
      printf("%s\n",s);
    }

    printf("ahora con personas\n");

    Persona *p1 = malloc(sizeof(Persona));
    p1->nombre = "victoria";
    p1->edad = 20;
    Persona *p2 = malloc(sizeof(Persona));
    p2->nombre = "juanita";
    p2->edad = 30;
    Persona *p3 = malloc(sizeof(Persona));
    p3->nombre = "josefa";
    p3->edad = 10;
    Persona *p4 = malloc(sizeof(Persona));
    p4->nombre = "valentina";
    p4->edad = 40;

    put(q,p1);
    put(q,p2);
    put(q,p3);
    put(q,p4);

    quicksort(q, cmp_persona);

    while (!emptyQueue(q)){
      Persona *p = (Persona *) get(q);
      printf("%s\n",p->nombre);
    }
    return 0;
}