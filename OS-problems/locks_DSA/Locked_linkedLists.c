#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *_node;
} Node;

typedef struct {
    pthread_mutex_t lock;
    Node *head;
} List;

//initialize list's head and initialize lock
void listInitialize(List *L){
    L->head = NULL;
    pthread_mutex_init(&L->lock, NULL);
}

int listInsert(List *L,int key){
    
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        perror("Error");
        return 1;
    }
    node->val = key;
    pthread_mutex_lock(&L->lock);
    node->_node = L->head;
    L->head = node;
    pthread_mutex_unlock(&L->lock);
    return 0;

}


Node *listLookup(List *L, int key){
    pthread_mutex_lock(&L->lock);
    Node *curr = L->head;
    do
    {
        if (curr->val == key) {
            break;
        }
        
    } while (curr = curr->_node);
    pthread_mutex_unlock(&L->lock);
    if (curr) return curr;
    curr = malloc(sizeof(Node));
    curr->val = 0;
    curr->_node = NULL;
    return curr;
    
}

void *worker(void *L) {
    listInsert(L,2);
    listInsert(L,3);
    listInsert(L,6);
    listInsert(L,9);
}

int main(){
    List *L;
    pthread_t t1;

    L = malloc(BUFSIZ);
    listInitialize(L);
    listInsert(L,2);


    if (pthread_create(&t1, NULL, worker, L)) {
        perror("Error");
    }

    pthread_join( t1, NULL);

    printf("%d \n", listLookup(L, 3)->val);
    free(L);
    return 0;
}