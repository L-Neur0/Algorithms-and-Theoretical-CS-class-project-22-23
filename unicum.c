#include <stddef.h>
#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#define MAX_AUTONOMIE 100
#define MARKER -1


struct Node {
    int key;
    int num_auto;
    int autonomie[MAX_AUTONOMIE];
    struct Node* left;
    struct Node* right;
    struct Node* p;
};


struct Node* crea_nodo(int key, int num_auto, int auton[]) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        printf("Errore nell'allocazione di memoria.\n");
        return NULL;
    }

    node->key = key;
    node->num_auto = num_auto;
    int i;
    for (i = 0; i < num_auto; i++) {
        node->autonomie[i] = auton[i];  // Copia i valori di autonomie
    }
    node->left = NULL;
    node->right = NULL;
    node->p = NULL;
    return node;
}

struct Node* tree_search(struct Node* x, int k){
    if ((x==NULL)||(x->key==k)){
        return x;
    }
    if (x->key < k){
        return tree_search(x->right, k);
        }else{return tree_search(x->left, k);}
}


struct Node* tree_insert(struct Node* root, struct Node* z){
    struct Node* y;
    struct Node* x;
    y=NULL;
    x=root;
    while(x!=NULL){
        y=x;
        if (z->key<x->key){
            x=x->left;
        }else{ x=x->right;}
    }
    z->p=y;
    if(y==NULL){
        root=z;  
        return root;  // albero era vuoto
    }else if(z->key<y->key){
        y->left=z;
        return root;
    }else if (z->key>y->key){
        y->right = z;
    }

    return root;}

struct Node* aggiungi_stazione(int dist, int num_auto, int autonomie[], struct Node* root) {
    struct Node* stazione=crea_nodo(dist, num_auto, autonomie);
    struct Node* temp;
    temp=NULL;
    temp=tree_search(root, dist);
    if(temp!=NULL){
        printf("non aggiunta\n");
        return root;
        }else{
        root=tree_insert(root, stazione);
        printf("aggiunta\n");}

    return root;
}


struct Node* tree_minimum(struct Node* x){
    while (x->left!=NULL){
        x=x->left;
    }
    return x;
}

struct Node* tree_successor(struct Node* node) {
    if (node->right != NULL) {
        return tree_minimum(node->right);
    }

    struct Node* parent = node->p;
    while (parent != NULL && node == parent->right) {
        node = parent;
        parent = parent->p;
    }
    return parent;
}
struct Node* delete_node(struct Node* root, int key) {
    if (root == NULL) {
        printf("non demolita\n");
        root=NULL;
        return root;
    }

    if (key < root->key) {
        root->left = delete_node(root->left, key);
    } else if (key > root->key) {
        root->right = delete_node(root->right, key);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            if (temp != NULL) {
                temp->p = root->p;
            }
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            if (temp != NULL) {
                temp->p = root->p;
            }
            free(root);
            return temp;
        }

        // Node with two children, find in-order successor
        struct Node* successor = tree_successor(root);
        root->key = successor->key;
        root->right = delete_node(root->right, successor->key);
    }
    return root;
}

void aggiungiauto(struct Node* root, int dist, int autonomia){
    struct Node* stazione;
    stazione=NULL;
    stazione=tree_search(root, dist);
    if(stazione!=NULL){
        stazione->num_auto++;
        stazione->autonomie[stazione->num_auto-1]=autonomia;
        printf("aggiunta\n");
        //printf("auto a stazione a distanza: %d \n", dist);
    }else{ printf("non aggiunta\n");
           // printf("commento: non esiste stazione a distanza determinata\n");}

    }
}



void  rimuoviauto(struct Node* root, int dist, int autonomia){
    struct Node* stazione;
    stazione=NULL;
    int i, j, trovato, posizione;
    trovato=0;
    posizione=0;
    stazione=tree_search(root, dist);
    for(i=0; i<stazione->num_auto; i++){
            if(stazione->autonomie[i]==autonomia){
                printf("%d \n", stazione->autonomie[i]);
                posizione=i;
                trovato=1;
                break;
        }
    }

    if(trovato==1){
        for (j = posizione; j < stazione->num_auto; j++) {
                    stazione->autonomie[j] = stazione->autonomie[j + 1];
                }
            stazione->num_auto--;
            printf("rottamata:");
            // printf(" auto con autonomia %d a stazione a distanza: %d \n", autonomia, dist);
        }else{ printf("non rottamata:");
              // printf("auto con autonomia:%d NON trovata nella stazione a distanza %d.\n", autonomia, stazione->key);}
        
    }
}

struct Node* findNearestNode(struct Node* root, int dist) {
    struct Node* nearest = NULL;
    struct Node* current = root;

    while (current != NULL) {
        if (current->key == dist) {
            // Trovato un nodo con la distanza esatta
            return current;} else {

            if (nearest == NULL || abs(current->key - dist) < abs(nearest->key - dist)) {
                nearest = current;
            }

            if (current->key > dist) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
    }

    return nearest;
}


///////////////////////////////QUICKSORT////////////////////////////////

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Funzione per mettere l'elemento pivot nella posizione corretta e restituire l'indice del pivot.
int partition(int arr[], int low, int high){
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++){
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

//  Quicksort function

void quicksort(int arr[], int low, int high){
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quicksort(arr, low, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, high);
    }
}

// Recursive function for forward path.

void ric_plan(struct Node* root, struct Node* staz, struct Node* staz_end, int dist){
    int max=0;
    if(staz->key==staz_end->key){
        printf("%d ", staz->key);
        return;
    }
    
    printf("%d ", staz->key);
    quicksort(staz->autonomie, 0, staz->num_auto-1);
    max = staz->autonomie[staz->num_auto-1];
    dist = dist + max;
    struct Node* next_staz = findNearestNode(root, dist);
    if (next_staz != NULL && dist <= next_staz->key) {
        ric_plan(root, next_staz, staz_end, dist);
    } else {
        // Non è possibile raggiungere la prossima stazione con l'autonomia attuale
        printf("nessun percorso\n");
    }
}

// Recursive function for reverse path.

void reverse_ric_plan(struct Node* root, struct Node* staz, struct Node* staz_end, int dist) {
    if (staz->key == staz_end->key) {
        printf("%d ", staz->key);
        return;
    }

    printf("%d ", staz->key);
    quicksort(staz->autonomie, 0, staz->num_auto - 1);
    int max = staz->autonomie[staz->num_auto - 1];
    dist = dist - max;  // Sottrai la massima autonomia invece di aggiungerla
    struct Node* next_staz = findNearestNode(root, dist);
    if (next_staz != NULL && dist >= next_staz->key) {
        reverse_ric_plan(root, next_staz, staz_end, dist);
    } else {
        // Non è possibile raggiungere la prossima stazione con l'autonomia attuale
        printf("nessun percorso\n");
    }
}



//casi ambigui.

void pianifica_percorso(struct Node* root, int partenza, int arrivo){
    struct Node* staz_start;
    struct Node* staz_end;
    int dist=0;
    staz_start=tree_search(root, partenza);
    if(staz_start==NULL){
        // printf("Non esiste percorso DA %d \n", partenza);
        printf("nessun percorso\n");
        return;
    }
    staz_end=tree_search(root, arrivo);
    if(staz_end==NULL){
        // printf("Non esiste percorso A %d \n", arrivo);
        printf("nessun percorso\n");
        return;
    }
    
    if (staz_start->key==staz_end->key){
        // printf("PARTENZA UGUALE AD ARRIVO");
        printf("nessun percorso\n");
        return;
    }
    dist=staz_start->key;
    if((staz_end->key - staz_start->key)>0){
        ric_plan(root, staz_start, staz_end, dist);
        // printf("\nsenso andata");
    }else{
        reverse_ric_plan(root, staz_start, staz_end, dist);
        // printf("\nsenso ritorno");
    }
}


void compiler(struct Node* root){
    char name[20];
    int dist=0;
    int num_auto=0;
    int a;
    int autonomie[MAX_AUTONOMIE];
    int i;

    while(!feof(stdin)){
        memset(name, '0', sizeof(name));
        if(scanf("%s", name)==1){
            if(strcmp(name, "aggiungi-stazione")==0){
                scanf("%d", &dist);
                scanf("%d", &num_auto);
                for(i=0; i<num_auto;i++){
                    scanf("%d", &autonomie[i]);
                }
                root=aggiungi_stazione(dist, num_auto, autonomie, root);

            } else if(strcmp(name, "demolisci-stazione")==0){
                scanf("%d", &dist);
                root=delete_node(root, dist);    
             }else if(strcmp(name, "aggiungi-auto")==0){ 
                scanf("%d", &dist);
                scanf("%d", &a);
                aggiungiauto(root, dist, a);
             }else if(strcmp(name, "rottama-auto")==0){
                scanf("%d", &dist);
                scanf("%d", &a);
                rimuoviauto(root, dist, a); 
             }else if(strcmp(name, "pianifica-percorso")==0){
                scanf("%d", &a);
                scanf("%d", &dist);
                pianifica_percorso(root, a, dist);
                printf("\n");
        }
     }
    }

}



int main() {
    struct Node* root=NULL;

    compiler(root);
   
    return 0;
}
