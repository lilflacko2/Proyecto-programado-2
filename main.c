#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TRUE 1
#define FALSE 0

//Se nombran structs y se llaman funciones
typedef struct resources RESOURCES;
typedef struct nodec NODEC;
typedef struct nodeb NODEB;
typedef struct AdjListNode nodo;
typedef struct AdjListNodo ruta;
typedef struct Grafo graph;
void menuPrincipal();
void menuTask();
struct AdjListNodo* newAdjListNodoMod(char origin[20], char destiny[20], int time, char effort[15], char type[12]);
void modifyRoute(struct Grafo* graph);




//----------------------------- AGREGAR/MODIFICAR TAREAS DEL PROYECTO Y ARMAR RUTA CRITICA -------------------------

struct AdjListNode
{
    int ID;
    int time;
    int effort;
    char asignee[20];
    char description[50];
    int typeIndex;
    struct AdjListNode* next;
};
  
// Lista adyacencia
struct AdjList
{
    struct AdjListNode *head; 
};
  
//Grafo
struct Graph
{
    int V;
    struct AdjList* array;
};
  
// Funcion para crear nueva lista de adyacencia
struct AdjListNode* newAdjListNode(int ID, int time, int effort, char asignee[20], char description[50], int typeIndex)
{
    struct AdjListNode* newNode =
     (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->ID = ID;
    newNode->time = time;
    newNode->effort = effort;
    strcpy(newNode->asignee, asignee);
    strcpy(newNode->description, description);
    newNode->typeIndex = typeIndex;
    newNode->next = NULL;
    return newNode;
}
  
// Crea grafo de V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = 
        (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
  
    // Crea lista de tamano V
    graph->array = 
      (struct AdjList*) malloc(V * sizeof(struct AdjList));
  
    // Inicia listas vacias
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
  
    return graph;
}
  
// Agrega datos al grafo
void addEdge(struct Graph* graph)
{
    int vertice, ID, time, effort, typeIndex;
    char asignee[20], description[50];
    // le solicita la informacion al usuario
    printf("Vertice in which you want to insert: ");
    scanf("%d", &vertice);
    printf("\nInsert ID: ");
    scanf("%d%*c", &ID);
    printf("\nInsert time: ");
    scanf("%d%*c", &time);
    printf("\nInsert effort: ");
    scanf("%d%*c", &effort);
    printf("\nInsert asignee: ");
    scanf("%s", asignee);
    printf("\nInsert description: ");
    scanf("%s", description);
    printf("\nInsert type: ");
    scanf("%d", &typeIndex);
    printf("\n");
    
    struct AdjListNode* newNode = newAdjListNode(ID, time, effort, asignee, description, typeIndex);
    newNode->next = graph->array[vertice].head;
    graph->array[vertice].head = newNode;

    newNode = newAdjListNode(vertice, time, effort, asignee, description, typeIndex);
    newNode->next = graph->array[ID].head;
    graph->array[ID].head = newNode;

    
}

//Funcion en la que se agregan datos al grafo
struct AdjListNode* newAdjListNodeMod(int ID, int time, int effort, char asignee[20], char description[50], int typeIndex)
{
    struct AdjListNode* newNode =
     (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->ID = ID;
    newNode->time = time;
    newNode->effort = effort;
    strcpy(newNode->asignee, asignee);
    strcpy(newNode->description, description);
    newNode->typeIndex = typeIndex;
    newNode->next = NULL;
    return newNode;
}

//Funcion para modificar lugar
void modifyTask(struct Graph* graph)
{
    int vertice, ID, time, effort, typeIndex;
    char asignee[20], description[50];
    // le solicita los datos al usuario
    printf("Vertice in which you want to insert: ");
    scanf("%d", &vertice);
    printf("\nInsert ID: ");
    scanf("%d%*c", &ID);
    printf("\nInsert time: ");
    scanf("%d%*c", &time);
    printf("\nInsert effort: ");
    scanf("%d%*c", &effort);
    printf("\nInsert asignee: ");
    scanf("%s", asignee);
    printf("\nInsert description: ");
    scanf("%s", description);
    printf("\nInsert type: ");
    scanf("%d", &typeIndex);
    printf("\n");
    
    struct AdjListNode* newNode = newAdjListNodeMod(ID, time, effort, asignee, description, typeIndex);
    newNode->next = graph->array[vertice].head;
    graph->array[vertice].head = newNode;
  
    newNode = newAdjListNodeMod(vertice, time, effort, asignee, description, typeIndex);
    newNode->next = graph->array[ID].head;
    graph->array[ID].head = newNode;
}

//Muestra el grafo
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        
        printf("\n Adjacency list of vertice %d\n head ", v);
        while (pCrawl)
        {
            //Almacena en el archivo txt
            FILE * fpuntero = fopen("tasks.txt", "a+");
            printf("-> %d, %d, %d, %s, %s, %d", pCrawl->ID, pCrawl->time, pCrawl->effort, pCrawl->asignee, pCrawl->description, pCrawl->typeIndex);
            fprintf(fpuntero, "%d", pCrawl->ID);
            fprintf(fpuntero, "\n");
            fprintf(fpuntero, "%d", pCrawl->time);
            fprintf(fpuntero, "\n");
            fprintf(fpuntero, "%d", pCrawl->effort);
            fprintf(fpuntero, "\n");
            fwrite(&pCrawl->asignee, sizeof(nodo), 1, fpuntero);
            fwrite(&pCrawl->description, sizeof(nodo), 1, fpuntero);
            fprintf(fpuntero, "%d", pCrawl->typeIndex);
            fprintf(fpuntero, "\n");
            pCrawl = pCrawl->next;
            fclose(fpuntero);
        }
        printf("\n");
    }
}

  
// Imprime grafo modificado
void printGraphMod(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        
        printf("\n Adjacency list of vertice %d\n head ", v);
        while (pCrawl)
        {
            //Cambia el grafo en el archivo txt
            FILE * fpuntero = fopen("tasks.txt", "r+");
            printf("-> %d, %d, %d, %s, %s, %d", pCrawl->ID, pCrawl->time, pCrawl->effort, pCrawl->asignee, pCrawl->description, pCrawl->typeIndex);
            fprintf(fpuntero, "%d", pCrawl->ID);
            fprintf(fpuntero, "\n");
            fprintf(fpuntero, "%d", pCrawl->time);
            fprintf(fpuntero, "\n");
            fprintf(fpuntero, "%d", pCrawl->effort);
            fprintf(fpuntero, "\n");
            fwrite(&pCrawl->asignee, sizeof(nodo), 1, fpuntero);
            fwrite(&pCrawl->description, sizeof(nodo), 1, fpuntero);
            fprintf(fpuntero, "%d", pCrawl->typeIndex);
            fprintf(fpuntero, "\n");
            pCrawl = pCrawl->next;
            fclose(fpuntero);
        }
        printf("\n");
    }
}

NODEC *head = NULL;

//Imprime grafo eliminado
/*void printGraphElim(struct Graph* graph)
{
	printf("Inserte nombre del lugar por eliminar: ");
    int v;
    char nom[15];
    scanf("%s", nom);
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        
        printf("\n Lista de adyacencia del vertice %d\n head ", v);
        while (pCrawl)
        {
            FILE * fpuntero = fopen("domicilioLugar.txt", "r+");
            free(head);
            printf("-> %d, %d, %d, %s, %s, %d", pCrawl->ID, pCrawl->time, pCrawl->effort, pCrawl->asignee, pCrawl->description, pCrawl->typeIndex);
            fprintf(fpuntero, "%d", pCrawl->ID);
            fprintf(fpuntero, "\n");
            fprintf(fpuntero, "%d", pCrawl->time);
            fprintf(fpuntero, "\n");
            fprintf(fpuntero, "%d", pCrawl->effort);
            fprintf(fpuntero, "\n");
            fwrite(&pCrawl->asignee, sizeof(nodo), 1, fpuntero);
            fwrite(&pCrawl->description, sizeof(nodo), 1, fpuntero);
            fprintf(fpuntero, "%d", pCrawl->typeIndex);
            fprintf(fpuntero, "\n");
            pCrawl = pCrawl->next;
            fclose(fpuntero);
        }
        printf("\n");
    }
}*/

//Ejecuta insercion de datos
void tasks(){
    int V = 2;
    struct Graph* graph = createGraph(V);
    addEdge(graph);
    addEdge(graph);
    addEdge(graph);

    printGraph(graph);
}

//Ejecuta modificacion de datos
void tasksMod(){
    int V = 1;
    struct Graph* graph = createGraph(V);
    modifyTask(graph);

    printGraphMod(graph);
}



// RUTA 
//Nodo de la ruta
struct AdjListNodo
{
    char origin[20], destiny[20], effort[15];
    int time;
    char type[12];

    struct AdjListNodo* next;
};
  
// Representa lista de adyacencia
struct AdjLista
{
    struct AdjListNodo *head; 
};
  
// Grafo
struct Grafo
{
    int V;
    struct AdjLista* array;
};

//Almacena nodo en lista adyacencia
struct AdjListNodo* newAdjListNodo(char origin[20], char destiny[20], int time, char effort[15], char type[12])
{
    struct AdjListNodo* newNode =
     (struct AdjListNodo*) malloc(sizeof(struct AdjListNodo));
    strcpy(newNode->origin, origin);
    strcpy(newNode->destiny, destiny);
    newNode->time = time;
    strcpy(newNode->effort, effort);
    strcpy(newNode->type, type);
    newNode->next = NULL;
    return newNode;
}

// Crea grafo de V vertices
struct Grafo* crearGrafo(int V)
{
    struct Grafo* graph = 
        (struct Grafo*) malloc(sizeof(struct Grafo));
    graph->V = V;
  
    // Crea lista de V largo
    graph->array = 
      (struct AdjLista*) malloc(V * sizeof(struct AdjLista));
  
    // Inicia lista vacia
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
  
    return graph;
}

//Agrega datos a la ruta
void addEdges(struct Grafo* graph)
{
    int vertice;
    char origin[20], destiny[20], effort[15];
    int time;
    char type[12];
    printf("Vertice in which you want to insert: ");
    scanf("%d%*c", &vertice);
    printf("\nOrigin: ");
    scanf("%s", origin);
    printf("\nDestiny: ");
    scanf("%s", destiny);
    printf("\nTime: ");
    scanf("%d", &time);
    printf("\nEffort: ");
    scanf("%s", effort);
    printf("\nRoute type: ");
    scanf("%s", type);
    printf("\n");
   
    struct AdjListNodo* newNode = newAdjListNodo(origin, destiny, time, effort, type);
    newNode->next = graph->array[vertice].head;
    graph->array[vertice].head = newNode;
}

//Imprime la ruta
void printGrafo(struct Grafo* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNodo* pCrawl = graph->array[v].head;
        
        printf("\n Lista de adyacencia del vertice %d\n head ", v);
        while (pCrawl)
        {
            //Almacena datos en el archivo txt
            FILE * fpuntero = fopen("domicilioRuta.txt", "a+");
            printf("-> %s, %s, %d, %s, %s", pCrawl->origin, pCrawl->destiny, pCrawl->time, pCrawl->effort, pCrawl->type);
            fwrite(&pCrawl->origin, sizeof(ruta), 1, fpuntero);
            fwrite(&pCrawl->destiny, sizeof(ruta), 1, fpuntero);
            fprintf(fpuntero, "%d", pCrawl->time);
            fprintf(fpuntero, "\n");
            fwrite(&pCrawl->effort, sizeof(ruta), 1, fpuntero);
            fprintf(fpuntero, "\n");
            fwrite(&pCrawl->type, sizeof(ruta), 1, fpuntero);
            pCrawl = pCrawl->next;
            fclose(fpuntero);
        }
        printf("\n");
    }
}

//Ejecuta insersion de datos
void tasksRoute(){
    int V = 2;
    struct Grafo* graph = crearGrafo(V);
    addEdges(graph);
    addEdges(graph);
    //addEdge(graph);

    printGrafo(graph);
}


//Almacena nodo en lista
struct AdjListNodo* newAdjListNodoMod(char origin[20], char destiny[20], int time, char effort[15], char type[12])
{
    struct AdjListNodo* newNode =
     (struct AdjListNodo*) malloc(sizeof(struct AdjListNodo));
    strcpy(newNode->origin, origin);
    strcpy(newNode->destiny, destiny);
    newNode->time = time;
    strcpy(newNode->effort, effort);
    strcpy(newNode->type, type);
    newNode->next = NULL;
    return newNode;
}

//Modifica ruta     NO ES NECESARIA
void modifyRoute(struct Grafo* graph)
{
    int vertice;
    char origin[20], destiny[20], effort[15];
    int time;
    char type[12];
    printf("Vertice in which you want to insert: ");
    scanf("%d%*c", &vertice);
    printf("\nOrigin: ");
    scanf("%s", origin);
    printf("\nDestiny: ");
    scanf("%s", destiny);
    printf("\nTime: ");
    scanf("%d", &time);
    printf("\nEffort: ");
    scanf("%s", effort);
    printf("\nRoute type: ");
    scanf("%s", type);
    printf("\n");
   
    struct AdjListNodo* newNode = newAdjListNodoMod(origin, destiny, time, effort, type);
    newNode->next = graph->array[vertice].head;
    graph->array[vertice].head = newNode;
}

//Imprime ruta modificada     NO ES NECESARIA
void printGrafoMod(struct Grafo* graph)
{
    int v;
    for (v = 0; v <= graph->V; ++v)
    {
        struct AdjListNodo* pCrawl = graph->array[v].head;
        
        printf("\n Adjacency list of vertice %d\n head ", v);
        while (pCrawl)
        {
            FILE * fpuntero = fopen("tasksRoute.txt", "r+");
            printf("-> %s, %s, %d, %s, %s", pCrawl->origin, pCrawl->destiny, pCrawl->time, pCrawl->effort, pCrawl->type);
            fwrite(&pCrawl->origin, sizeof(ruta), 1, fpuntero);
            fwrite(&pCrawl->destiny, sizeof(ruta), 1, fpuntero);
            fprintf(fpuntero, "%d", pCrawl->time);
            fprintf(fpuntero, "\n");
            fwrite(&pCrawl->effort, sizeof(ruta), 1, fpuntero);
            fprintf(fpuntero, "\n");
            fwrite(&pCrawl->type, sizeof(ruta), 1, fpuntero);
            pCrawl = pCrawl->next;
            fclose(fpuntero);
        }
        printf("\n");
    }
}

//Ejecuta modificacion ruta     NO ES NECESARIA
void tasksRouteMod(){
    int V = 1;
    struct Grafo* graph = crearGrafo(V);
    modifyRoute(graph);

    printGrafoMod(graph);
}

//Imprime grafo eliminado     NO ES NECESARIA
void printGrafoElim(struct Grafo* grafo)
{
    int v;
    char origen[15];
    printf("Insert origin to delete: ");
    scanf("%s", origen);
    for (v = 0; v < grafo->V; ++v)
    {
        struct AdjListNodo* pCrawl = grafo->array[v].head;
        
        printf("\n Adjacency list of vertice %d\n head ", v);
        while (pCrawl)
        {
            FILE * fpuntero = fopen("tasksRoute.txt", "r+");
            free(head);
            printf("-> %s, %s, %d, %s, %s", pCrawl->origin, pCrawl->destiny, pCrawl->time, pCrawl->effort, pCrawl->type);
            fwrite(&pCrawl, sizeof(ruta), 1, fpuntero);
            pCrawl = pCrawl->next;
            fclose(fpuntero);
        }
        printf("\n");
    }
}

//Ejecuta eliminacion de datos     NO ES NECESARIA
void domiciliosElimRuta(){
    int V = 1;
    struct Grafo* grafo = crearGrafo(V);

    printGrafoElim(grafo);
}


//Menu de domicilio
void menuTask(){
    int num;
    while(num!=4){
    printf("\n1.Register Task\n2.Modify Task\n3.Register Route\n4.Modify Route\n5.Salir\nIngrese una opcion: ");
    scanf("%d%*c",&num);
    switch (num) {
      case 1: 
      	tasks();
      	break;
      case 2:
      	tasksMod();
      	break;
      case 3:
      	tasksRoute();
     	break;
      case 4:
      	tasksRouteMod();
      	break;
      break;
      case 5:
      menuPrincipal();
    }
  }
}
//----------------------------- TERMINA AGREGAR/MODIFICAR TAREAS DEL PROYECTO ---------------------------



//----------------------------- GESTIONAR DOCUMENTOS DE TAREAS ---------------------------

typedef struct document{
    int ID;
    char route[20];
    char description[50];
    char type[20];
    struct document *left;
    struct document *right;
}document;

document* root = NULL;//root del arbol

//ENTRADAS: un codigo del pais, nombre, poblacion y el continente
//SALIDAS: genera un alamenamiento de la informacion de los paises
//RESTRICCIONES: se utilizan punteros 

document* new_document(int ID, char route[20], char description[50], char type[20]) {
    //para crear una nueva hoja de un country
    document* new = (document*) malloc(sizeof(document));
    new->ID = ID;
    strcpy(new->route, route);
    strcpy(new->description, description);
    strcpy(new->type, type);
    new->left = NULL;
    new->right = NULL;
    return new;
}

//ENTRADAS: un codigo del pais, nombre, poblacion y el continente
//SALIDAS: inserta el pais
//RESTRICCIONES: se usan punteros

void insert_document(document* node, int ID, char route[20], char description[50], char type[20]){
    //metodo para insertar un new country
    if(node == NULL){
        root = new_document(ID, route, description, type);
    }
    else if (ID > node->ID) {
        // primero a la derecha
        if (node->right == NULL) {
            node->right = new_document(ID, route, description, type);
        } else {
            // se aplica recursividad hasta encontrar una rama vacia
            insert_document(node->right, ID, route, description, type);
        }
    } else {
        // si no se hace la insercion a la izquierda
        if (node->left == NULL) {
            node->left = new_document(ID, route, description, type);
        } else {
            // se aplica recursividad hasta encontrar una rama vacia
            insert_document(node->left, ID, route, description, type);
        }
    }
}

//Metodo para la modificacion de un country
//ENTRADAS: un nodo y el codigo
//SALIDAS: modifica el pais
//RESTRICCIONES: se usan punteros
void modify_document(document* node, int ID)
{
    if(node == NULL){
        printf("ID not found!");
        return;
    }
    else if(node->ID == ID)
    {
        printf("Insert the new route: ");
        scanf("%s", &node->route);
        printf("Insert the new description: ");
        scanf("%s", &node->description);
        printf("Insert the new type: ");
        scanf("%s", &node->type);
        printf("Successfully modified!");
        getchar();
        getchar();
    }
    else if(ID < node->ID)
    {
        modify_document(node->left, ID);
    }
    else
    {
        modify_document(node->right, ID);
    }
}

document* minor_leaf( document* node)//metodo que busca la hoja menor del arbol
{
    document* aux = node;

    while (aux && aux->left) {
        aux = aux->left;
    }

    return aux;
}
//ENTRADAS: nodo y codigo
//SALIDAS: elimina un pais
//RESTRICCIONES: se usan punteros
document* delete_document(document* node, int ID)//metodo para eliminacion de un country
{
    if (node == NULL)
    {
        return node;
    }
    if (ID < node->ID){
        node->left = delete_document(node->left, ID);
    }
    else if (ID > node->ID){
        node->right = delete_document(node->right, ID);
    }
    else {
        if (node->left == NULL) {
            document* aux = node->right;
            free(node);
            return aux;
        }
        else if (node->right == NULL) {
            document* aux = node->left;
            free(node);
            return aux;
        }

        document* aux = minor_leaf(node->right);

        node->ID = aux->ID;
        node->right = delete_document(node->right, aux->ID);
    }
}

void in_order(document* node) //imprimir los countryes de menor a mayor
{
    if (node != NULL) 
    {
        in_order(node->left);
        printf("ID: %d\n", node->ID);
        printf("Route: %s\n", node->route);
        printf("Description: %s\n", node->description);
        printf("Type: %s\n", node->type);
        printf("****************************************\n");
        in_order(node->right);
    }
}
/*
//metodo para la impresion del orden jerarquico del arbol binario

//ENTRADAS: nodo, un primero y un count
//SALIDAS:  muestra el orden jerarquico del arbol binario 
//RESTRICCIONES: se usan punteros
void show_hierarchy(Country* node, int primero, int count)
{
    if(node!=NULL)
    {
        if(primero == 1)
        {
            printf("\tCodigo: %d , Nombre: %s, Habitantes: %d, Continente: %s\n", node->code, node->name, node->population, node->continent);
        }
        if(node->left != NULL)
        {
            for(int i = 0; i < count; i++){
                printf("\t");
            }
            printf("Codigo: %d , Nombre: %s, Habitantes: %d, Continente: %s\n", node->left->code, node->left->name, node->left->population, node->left->continent);
            show_hierarchy(node->left, 0, count + 1);
        }
        if(node->right != NULL)
        {
            for(int i = 0; i < count; i++){
                printf("\t");
            }
            printf("Codigo: %d , Nombre: %s, Habitantes: %d, Continente: %s\n", node->right->code, node->right->name, node->right->population, node->right->continent);
            show_hierarchy(node->right, 0, count + 1);
        }
    }
}
*/

void document_Menu()
{
	printf("\n\n");
    printf("\n********************************************************\n");
    printf("                 (1). Insert document\n");
    printf("                 (2). Modify document\n");
    printf("                 (3). Delete document\n");
    printf("                 (4). See document\n");
    printf("                 (5). Salir\n");
    printf("*******************************************************\n");
    printf("\n\n");
}

//BUSQUEDAS: 
document* print_task(document* node, int ID) //imprimir los countryes de menor a mayor
{

    if (node != NULL) 
    {
	if (ID < node->ID){
        node->left = print_task(node->left, ID);
    }
    else if (ID > node->ID){
        node->right = print_task(node->right, ID);
    }    
	else{	
        //in_order(node->left);
        printf("ID: %d\n", node->ID);
        printf("Route: %s\n", node->route);
        printf("Description: %s\n", node->description);
        printf("Type: %s\n", node->type);
        printf("****************************************\n");
        //in_order(node->right);
    }
}
}

//----------------------------- REGISTRO DE RECURSOS ---------------------------

struct resources
{
    char ID[15];
    char name[15];
    char description[20];    
    char typeIndex[15];
    char capacityIndex[15];
    int availableQuantity[15];
    char manager[15];
} RECUSROS;

struct nodec // Nodo
{
    struct nodec *next;
    struct nodec *prev;
    RESOURCES info;
};

void DisplayData(RESOURCES resources) // muestra informacion del nodo clientes
{
    printf("==================RESOURCES=============\n\n");
    printf("Name: %s\t\n", resources.name);  //ID, name, description, typeindex, capacityindex, vailablequantity, manager
    printf("Description: %s\t\n", resources.description);
    printf("Type: %s\t\n", resources.typeIndex);
    printf("Capacity: %s\t\n", resources.capacityIndex);
    printf("Quantity Available: %s\t\n", resources.availableQuantity);
    printf("Manager: %s\t\n", resources.manager);
    printf("ID: %s\t\n\n", resources.ID);
}

void showresources(NODEC *aux) // muestra todos los clientes disponibles
{
    if (aux == NULL)
    {
        printf("Resource not found\n");
    }
    else
    {
        printf("Available resources\n");
        while (aux != NULL)
        {
            DisplayData(aux->info);
            aux = aux->next;
        }
        printf("\n");
    }
}


//NODEC *head = NULL;

NODEC *CreateNode() // funcion para crear nodo
{
    NODEC *temp;
    temp = (NODEC *)malloc(sizeof(NODEC));
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

// Recurso
static const char *typeIndex[] = {
    "Human", "Material", "Financial", "Time"
};
static const char *capacityIndex[] = {
    "Hourly", "Daily", "Monthly"
};

//Pide datos del colaborador TODO: cambiar por registrar datos del recurso
void resourcesRegistry(RESOURCES *resources){
    
    printf("Insert resource information\n");
    fgets(resources->ID, 15, stdin);
    printf("ID: ");
    fgets(resources->ID, 15, stdin);
    //fgets(recursos->name, 20, stdin);
    printf("Name: ");
    fgets(resources->name, 15, stdin);
    printf("Description: ");
    fgets(resources->description, 20, stdin);
    printf("Type: ");
    fgets(resources->typeIndex, 15, stdin);
    //fgets(recursos->capacityIndex, 15, stdin);
    printf("Capacity: ");
    fgets(resources->capacityIndex, 15, stdin);
    printf("Quantity available: ");
    scanf("%d%*c", &resources->availableQuantity);
    printf("Manager: ");
    fgets(resources->manager, 15, stdin);
}

void addResource(RESOURCES resources) // agrega info de colaborador  a nodo
{
    NODEC *nuevoNodo;
    nuevoNodo = CreateNode();
    nuevoNodo->info = resources;

    if (head == NULL)
    {
        head = nuevoNodo;
    }
    else
    {
        nuevoNodo->next = head;
        head->prev = nuevoNodo;
        head = nuevoNodo;
    }
}


 
void resourcesArchive() //copia informacion a .txt
{
    NODEC *aux = head;
    FILE * fpuntero = fopen("resources.txt", "a+");
    if (fpuntero != NULL)
        {
            fwrite(&aux->info, sizeof(RESOURCES), 1, fpuntero);
        }

     {
        if(aux != NULL)
   fclose(fpuntero);
}}


void resourceArchiveMod() //copia informacion a .txt
{
    NODEC *aux = head;
    FILE * fpuntero = fopen("resources.txt", "r+");
    if (fpuntero != NULL)
    {
        while (aux != NULL)
        {
            fwrite(&aux->info, sizeof(RESOURCES), 1, fpuntero);
            fprintf(fpuntero, "\n");
            aux = aux->next;
        }
    }
    fclose(fpuntero);
}


//----------------------------- TERMINA REGISTRO DE RECURSOS ---------------------------


//menu principal
void menuPrincipal()       
{
	RESOURCES resources;
	NODEC *aux;
    int opcion, colabEquip = 2;
    int cantMensajes = 0;
    char repetir = TRUE;

    do
    {
        printf("\t\t\tMAIN MENU\n");
        printf("\t\t\t--------------\n");
        printf("\n\t1. Register and/or modify tasks\n");
        printf("\t2. Tasks documents management\n");
        printf("\t3. Register a resource\n");
        printf("\n\t0. BACK\n");
        printf("\n\tType an option: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("You chose Register and/or modify tasks\n");
            menuTask();
            break;
        case 2:
	{
			int choice2 = 0;
            while (choice2 != 6)
            {
                document_Menu();
                printf("Tyoe an option: ");
                scanf("%d", &choice2);
                if (choice2 == 1)
                {
                    int ID;
                    char route[20];
                    char description[50];
                    char type[20];
                    printf("Insert documents ID: ");
                    scanf("%d", &ID);
                    printf("Insert the route: ");
                    scanf("%s", &route);
                    printf("Insert a description for the resource: ");
                    scanf("%s", &description);
                    printf("Insert the type of resource: ");
                    scanf("%s", &type);
                    insert_document(root, ID, route, description, type);
                }
                else if (choice2 == 2)
                {
                    int ID;
                    printf("Insert documents ID: ");
                    scanf("%d", &ID);
                    modify_document(root, ID);
                }
                
                else if (choice2 == 3)
                {
                    int ID;
                    printf("Insert documents ID: ");
                    scanf("%d", &ID);
                    delete_document(root, ID);
                }
                else if(choice2 == 4)
                {
                    int ID;
                	printf("Insert documents ID: ");
                    scanf("%d", &ID);
                    print_task(root, ID);
                }
                else if(choice2 == 5)
                {
                    break;
                }
                else
                {
                    printf("Invalid entry!");
                }
            }
        }
            //printf("Eligio registrar equipo\n");
            break;
        int decision; //este int nos ayuda a ver si el usuario quiere ver los recurso
        case 3:
            //ingresan datos
            resourcesRegistry(&resources);
            //info colab a nodo
            addResource(resources);
            //guardo nodo en el archivo
            resourcesArchive();
            printf("Would you like to see all available resources? Yes = 1 y No = 0: ");
            scanf("%d", &decision);
            if (decision==1){
            	showresources(head);
			}
            //menuColabs(&recursos);
            break;
        case 0:
            repetir = FALSE;
            break;
        }
    } while (repetir);
}

//Main ejecuta menu principal
int main(){
    menuPrincipal();
    return 0;
}
