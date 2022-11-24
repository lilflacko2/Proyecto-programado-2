#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

//Se nombran structs y se llaman funciones
typedef struct recursos RECURSOS;
typedef struct nodec NODEC;
typedef struct nodeb NODEB;
typedef struct bitacora BITACORA;
typedef struct AdjListNode nodo;
typedef struct AdjListNodo ruta;
typedef struct Grafo graph;
void menuPrincipal();
void modificarColab(RECURSOS *recursos, int num);
void modificaC(NODEC *aux);
void eliminarColab();
void colaboradorAarchivoMod();
void colaboradorAarchivoMod();
void eliminarC(NODEC *aux);
void eliminarColab(RECURSOS *recursos, int num, NODEC *aux);
void bitacoras(BITACORA *ptr);
void aniadirBitacora(BITACORA bitacora);
void menuDomicilio();
struct AdjListNodo* newAdjListNodoMod(char origen[20], char destino[20], int tiempo, int dist, char tipo[12]);
void modificaRuta(struct Grafo* graph);


// ----------------------- REGISTRO COLABORADOR ------------------------------
//Struct del colaborador

// TODO: colaborador cambia por recurso
/*
se usa este struct en vez del de ellos
struct Resource {
    int ID;
    char *name;
    char *description;    
    int typeIndex;
    int capacityIndex;
    int availableQuantity;
    char *manager;
};
*/
struct recursos
{
    char ID[15];
    char name[15];
    char description[20];    
    char typeIndex[15];
    char capacityIndex[15];
    int availableQuantity[15];
    char manager[15];
};

struct nodec // Nodo
{
    struct nodec *next;
    struct nodec *prev;
    RECURSOS info;
};

NODEC *head = NULL;

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
    "Humanos", "Materiales", "Financieros", "De tiempo"
};
static const char *capacityIndex[] = {
    "Mensual", "Diaria", "Horas"
};

//Pide datos del colaborador TODO: cambiar por registrar datos del recurso
void registroColaborador(RECURSOS *recursos){
    
    printf("Ingrese los datos del colaborador\n");
    fgets(recursos->ID, 15, stdin);
    printf("Cedula: ");
    fgets(recursos->ID, 15, stdin);
    //fgets(recursos->name, 20, stdin);
    printf("Nombre: ");
    fgets(recursos->name, 15, stdin);
    printf("descripcion: ");
    fgets(recursos->description, 20, stdin);
    printf("tipo: ");
    fgets(recursos->typeIndex, 15, stdin);
    //fgets(recursos->capacityIndex, 15, stdin);
    printf("capacidad: ");
    fgets(recursos->capacityIndex, 15, stdin);
    printf("cantidad: ");
    scanf("%d%*c", &recursos->availableQuantity);
    printf("manager: ");
    fgets(recursos->manager, 15, stdin);
}

//Menu para modificar o eliminar colaborador TODO: cambiar por modificar o eliminar colaborador
void menuColabs(RECURSOS *recursos){
    int num;
    printf("\n\n1. Modificar colaborador\n");
    printf("2. Eliminar colaborador\n");
    printf("0. Volver al menu\n");
    printf("Ingrese la opcion que desea: \n");
    scanf("%d", &num);
    if (num == 1)
    {
        printf("Eligio modificar colaborador\n");
        modificaC(head);
    }
    else if (num == 2)
    {
        printf("Eligio eliminar\n");
        eliminarC(head);
    }
}


void aniadirColaborador(RECURSOS recursos) // agrega info de colaborador  a nodo
{
    NODEC *nuevoNodo;
    nuevoNodo = CreateNode();
    nuevoNodo->info = recursos;

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

 
void colaboradorAarchivo() //copia informacion a .txt
{
    NODEC *aux = head;
    FILE * fpuntero = fopen("colaboradores.txt", "a+");
    if (fpuntero != NULL)
    {
        if(aux != NULL)
        {
            fwrite(&aux->info, sizeof(RECURSOS), 1, fpuntero);
        }
    }
    fclose(fpuntero);
}

//Modifica colaborador 
void modificarColab(RECURSOS *recursos, int num)        
{
    if (num == recursos->ID)
    {
        printf("\n========================================================\n\n");
        printf("\t\t Detalles de colaborador\n");
        printf("========================================================\n\n");

        printf("\nID: %d\t\n", recursos->ID);
        printf("\nName: %s\t\n", recursos->name);
        printf("\nDescription: %s\t\n", recursos->description);
        printf("\nType: %d\t\n", recursos->typeIndex);
        printf("\nCapacity: %d\t\n", recursos->capacityIndex);
        printf("\nQuantity: %d\t\n", recursos->availableQuantity);
        printf("\nManager: %s\t\n", recursos->manager);

        
        printf("\nNuevo Name: ");
        fgets(recursos->name, 20, stdin);
        printf("\nDescription: ");
        fgets(recursos->description, 20, stdin);
        printf("\nType:");
        scanf("%d%*c", &recursos->typeIndex);
        printf("\nCapacity: ");
        scanf("%d%*c", &recursos->capacityIndex);
        printf("\nQuantity: ");
        scanf("%d%*c", &recursos->availableQuantity);
        printf("\nManager: ");
        scanf("%d%*c", &recursos->typeIndex);
        fgets(recursos->manager, 20, stdin);

        colaboradorAarchivoMod();
    }
}


void colaboradorAarchivoMod() //copia informacion a .txt
{
    NODEC *aux = head;
    FILE * fpuntero = fopen("colaboradores.txt", "r+");
    if (fpuntero != NULL)
    {
        while (aux != NULL)
        {
            fwrite(&aux->info, sizeof(RECURSOS), 1, fpuntero);
            fprintf(fpuntero, "\n");
            aux = aux->next;
        }
    }
    fclose(fpuntero);
}

//Modifica colaborador, llama a la funcion de cmodificarColab
void modificaC(NODEC *aux)  //modifica colaborador en base a su cedula
{
    RECURSOS *ptr, *id;
    int num;
    printf("Ingrese el ID del recurso a modificar: ");
    scanf("%d%*c", &num);
    if (aux == NULL)
    {
        printf("No se encontro recurso\n");
    }
    else
    {
        while (aux != NULL)
        {
            ptr = &aux->info;
            modificarColab(ptr, num);
            aux = aux->next;
        }
    }
}


//Funcion para eliminar colaborador
void eliminarColab(RECURSOS *recursos, int num, NODEC *aux)        
{
    if (num == recursos->ID)
    {
        printf("\n========================================================\n\n");
        printf("\t\t Detalles de colaborador antes de borrar\n");
        printf("========================================================\n\n");

        printf("\nID: %d\t\n", recursos->ID);
        printf("\nName: %s\t\n", recursos->name);
        printf("\nDescription: %s\t\n", recursos->description);
        printf("\nType: %d\t\n", recursos->typeIndex);
        printf("\nCapacity: %d\t\n", recursos->capacityIndex);
        printf("\nQuantity: %d\t\n", recursos->availableQuantity);
        printf("\nManager: %s\t\n", recursos->manager);
        free(head);
        printf("Borrado \n");
        menuPrincipal();
    }
    NODEC *auxx = head;
    FILE * fpuntero = fopen("colaboradores.txt", "w");
    if (fpuntero != NULL)
    {
        while (auxx != NULL)
        {
            if (num != recursos->ID)
            {
                fwrite(&auxx->info, sizeof(RECURSOS), 1, fpuntero);
                fprintf(fpuntero, "\n");
            }
            auxx = auxx->next;
        }
    }
    fclose(fpuntero);
}

//Elimina colaboradores, llama a la funcion eliminarColab
void eliminarC(NODEC *aux)  
{
    RECURSOS *ptr, *id;
    int num;
    printf("Ingrese el numero de cedula del colaborador a eliminar: ");
    scanf("%d%*c", &num);
    if (aux == NULL)
    {
        printf("No se encontro colaborador\n");
    }
    else
    {
        while (aux != NULL)
        {
            ptr = &aux->info;
            eliminarColab(ptr, num, aux);
            aux = aux->next;
        }
    }
}


//Elimina todos los archivos txt
void eliminarTodoColabs(){
    FILE * fpuntero = fopen("colaboradores.txt", "w");
    fclose(fpuntero);
    FILE * fp = fopen("domicilioLugar.txt", "w");
    fclose(fp);
    FILE * fpt = fopen("domicilioRuta.txt", "w");
    fclose(fpt);
    FILE * fptr = fopen("equipos.txt", "w");
    fclose(fptr);
}

// ----------------------- TERMINA REGISTRO COLABORADOR ------------------------------

// ----------------------- REGISTRO EQUIPOS ------------------------------------------

// TODO : equipos cambia por documentos (arbol binario)

//Struct con nombre y descripcion
struct dict {
  struct dict *left,*right;
  int ID;
  char type[15], route[50], description[50]; // TODO: se cambian estos campos por los que tiene un documento, 
}*Root=NULL;

/*
    Es decir estos: 
    int ID;
    char type[15];
    char route[50];
    char description[20];
    TODO: todos los lugares que usan nombre y descripcion pasan a usar esos campos, pero es la misma picha
    Haga CTRL + F y pone ´->nombre´ o ´->descripcion´ ahí le salen todos, tiene que ver cómo 
};

*/

//Definimos struct y se llaman funciones
typedef struct dict documento; // TODO: se cambia el nombre equipo por documento en todo lado
int check(char[],char[]);
void insert(documento *);
void Search();
void view(documento *);

//Se va a utilizar para insertar
int check(char a[],char b[]){
     int i,j,c;
     for(i=0,j=0 ; a[i]!='\0'&&b[j]!='\0' ; i++,j++){
       if(a[i]>b[j]){
         c=1;
         break;
       }
        else if(b[j]>a[i]){
          c=-1;
          break;
        }
      else
         c=0;
     }
     if(c==1)
       return 1;
      else if(c==-1)
        return -1;
      else
        return 0;
}

//Funcion para buscar equipo/colaborador
void Search(){
  int flag=0;
  documento *ptr;
  ptr=Root;
  char w[10];
  printf("\nIngrese equipo/colaborador: ");
  scanf("%s",&w);
  while(ptr!=NULL && flag==0){
    if(check(w,ptr->ID)>0)
       ptr=ptr->right;
    else if(check(w,ptr->ID)<0)
        ptr=ptr->left;
    else if(check(w,ptr->ID)==0)
       flag=1;
       //printf("\n%d",ptr->ID);
    }
    if(flag==0)
      printf("\nNo se encontro\n");
}


//Inserta equipo-colaborador
void insert(documento *temp){
  int flag=0;
  documento *ptr,*par;
  ptr=Root;

  if(Root==NULL)
     Root=temp;
  else{
     while(ptr!=NULL ){
       if(check(temp->ID,ptr->ID)>0){
         par=ptr;
         ptr=ptr->right;
       }

       else if(check(temp->ID,ptr->ID)<0)
     {
       par=ptr;
       ptr=ptr->left;
     }
       else if(check(temp->ID,ptr->ID)==0){
          flag=1;
            printf("\nExiste!");
          break;
       }

   }
       if(flag==0 && ptr==NULL){

         if(check(par->ID,temp->ID)==1)
            par->left=temp;
         else if(check(par->ID,temp->ID)==-1)
            par->right=temp;
       }

     }
     

}

//Imprime equipo-colaborador
void view(documento *ptr){
  	FILE * fpuntero = fopen("equipos.txt", "a+");
  	printf("Hola\n");
  if(Root==NULL)
    printf("\nEquipo vacio\n");

  else if(ptr !=NULL){
   view(ptr->left);
   printf("\nID:%d\n",ptr->ID);
   printf("HHHHHHH\n");
   printf("\ntipo:%s\n",ptr->type);
   printf("\nRuta:%s\n",ptr->route);
   printf("\nDescripcion:%s\n",ptr->description);
   fwrite(&ptr->ID, sizeof(documento), 1, fpuntero);
   fwrite(&ptr->description, sizeof(documento), 1, fpuntero);
   fwrite(&ptr->type, sizeof(documento), 1, fpuntero);
   fwrite(&ptr->route, sizeof(documento), 1, fpuntero);
   fprintf(fpuntero, "\n");
   fclose(fpuntero);
   
   view(ptr->right);
  }

}

void equipos() {
  int ch;
  int argc;
  documento *temp;
  while(ch!=4){
    printf("\n1.Buscar\n2.Insertar\n3.Ver\n4.Salir\nIngrese una opcion: ");
    scanf("%d",&ch);
    switch (ch) {
      case 1: Search();break;
      case 2:
      temp=(documento*)malloc(sizeof(documento));
      temp->left=NULL;
      temp->right=NULL;
      printf("\nInserte ID:\n");
      scanf("%d", &temp->ID);
      fgets(temp->type, 15, stdin);
      printf("\nInserte tipo:\n");
      fgets(temp->type, 15, stdin);
      printf("\nInserte ruta:\n");
      fgets(temp->route, 50, stdin);
      printf("\nInserte descripcion:\n");
      fgets(temp->description, 50, stdin);
       insert(temp);
      break;
      case 3:
      view(Root);
      break;
      case 4:menuPrincipal();
    }
  }
  
}

//----------------------------- TERMINA REGISTRO EQUIPOS ----------------------------

//----------------------------- DOMICILIOS DE COLABORADORES -------------------------
// LUGAR
// Estructura para representar lista de adyacencia
//Contiene datos

//TODO: cambiar codigo, nomLugar y codigoPostal por todo lo que tiene un Task ()
/*
struct Task {
    int ID;
    int time;
    int effort;    
    char asignee;
    char description[20];
    int typeIndex;
    
};
*/
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
    printf("Vertice en el cual va a insertar: ");
    scanf("%d", &vertice);
    printf("\nInserte ID: ");
    scanf("%d%*c", &ID);
    printf("\nInserte tiempo: ");
    scanf("%d%*c", &time);
    printf("\nInserte esfuerzo: ");
    scanf("%d%*c", &effort);
    printf("\nInserte asignee: ");
    scanf("%s", asignee);
    printf("\nInserte descripcion: ");
    scanf("%s", description);
    printf("\nInserte codigo postal: ");
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
void modificaLugar(struct Graph* graph)
{
    int vertice, ID, time, effort, typeIndex;
    char asignee[20], description[50];
    printf("Vertice en el cual va a insertar: ");
    scanf("%d", &vertice);
    printf("\nInserte ID: ");
    scanf("%d%*c", &ID);
    printf("\nInserte tiempo: ");
    scanf("%d%*c", &time);
    printf("\nInserte esfuerzo: ");
    scanf("%d%*c", &effort);
    printf("\nInserte asignee: ");
    scanf("%s", asignee);
    printf("\nInserte descripcion: ");
    scanf("%s", description);
    printf("\nInserte codigo postal: ");
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
        
        printf("\n Lista de adyacencia del vertice %d\n head ", v);
        while (pCrawl)
        {
            //Almacena en el archivo txt
            FILE * fpuntero = fopen("domicilioLugar.txt", "a+");
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
        
        printf("\n Lista de adyacencia del vertice %d\n head ", v);
        while (pCrawl)
        {
            //Cambia el grafo en el archivo txt
            FILE * fpuntero = fopen("domicilioLugar.txt", "r+");
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

//Imprime grafo eliminado
void printGraphElim(struct Graph* graph)
{
    int v;
    char nom[15];
    printf("Inserte nombre del lugar por eliminar: ");
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
}

//Ejecuta insercion de datos
void domicilios(){
    int V = 2;
    struct Graph* graph = createGraph(V);
    addEdge(graph);
    addEdge(graph);
    addEdge(graph);

    printGraph(graph);
}

//Ejecuta modificacion de datos
void domiciliosMod(){
    int V = 1;
    struct Graph* graph = createGraph(V);
    modificaLugar(graph);

    printGraphMod(graph);
}

//Ejecuta eliminacion de datos
void domiciliosElim(){
    int V = 1;
    struct Graph* graph = createGraph(V);

    printGraphElim(graph);
}

// RUTA 
//Nodo de la ruta
struct AdjListNodo
{
    char origen[20], destino[20];
    int tiempo, dist;
    char tipo[12];

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
struct AdjListNodo* newAdjListNodo(char origen[20], char destino[20], int tiempo, int dist, char tipo[12])
{
    struct AdjListNodo* newNode =
     (struct AdjListNodo*) malloc(sizeof(struct AdjListNodo));
    strcpy(newNode->origen, origen);
    strcpy(newNode->destino, destino);
    newNode->tiempo = tiempo;
    newNode->dist = dist;
    strcpy(newNode->tipo, tipo);
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
    char origen[20], destino[20];
    int tiempo, dist;
    char tipo[12];
    printf("Vertice en el cual va a insertar: ");
    scanf("%d%*c", &vertice);
    printf("\nOrigen: ");
    scanf("%s", origen);
    printf("\nDestino: ");
    scanf("%s", destino);
    printf("\nTiempo que durara en minutos: ");
    scanf("%d", &tiempo);
    printf("\nDistancia en Km: ");
    scanf("%d%*c", &dist);
    printf("\nTipo de ruta (terrestre, aerea, maritima): ");
    scanf("%s", tipo);
    printf("\n");
   
    struct AdjListNodo* newNode = newAdjListNodo(origen, destino, tiempo, dist, tipo);
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
            printf("-> %s, %s, %d, %d, %s", pCrawl->origen, pCrawl->destino, pCrawl->tiempo, pCrawl->dist, pCrawl->tipo);
            fwrite(&pCrawl->origen, sizeof(ruta), 1, fpuntero);
            fwrite(&pCrawl->destino, sizeof(ruta), 1, fpuntero);
            fprintf(fpuntero, "%d", pCrawl->tiempo);
            fprintf(fpuntero, "\n");
            fprintf(fpuntero, "%d", pCrawl->dist);
            fprintf(fpuntero, "\n");
            fwrite(&pCrawl->tipo, sizeof(ruta), 1, fpuntero);
            pCrawl = pCrawl->next;
            fclose(fpuntero);
        }
        printf("\n");
    }
}

//Ejecuta insersion de datos
void domiciliosRuta(){
    int V = 2;
    struct Grafo* graph = crearGrafo(V);
    addEdges(graph);
    addEdges(graph);
    //addEdge(graph);

    printGrafo(graph);
}


//Almacena nodo en lista
struct AdjListNodo* newAdjListNodoMod(char origen[20], char destino[20], int tiempo, int dist, char tipo[12])
{
    struct AdjListNodo* newNode =
     (struct AdjListNodo*) malloc(sizeof(struct AdjListNodo));
    strcpy(newNode->origen, origen);
    strcpy(newNode->destino, destino);
    newNode->tiempo = tiempo;
    newNode->dist = dist;
    strcpy(newNode->tipo, tipo);
    newNode->next = NULL;
    return newNode;
}

//Modifica ruta
void modificaRuta(struct Grafo* graph)
{
    int vertice;
    char origen[20], destino[20];
    int tiempo, dist;
    char tipo[12];
    printf("Vertice en el cual va a insertar: ");
    scanf("%d%*c", &vertice);
    printf("\nNuevo origen: ");
    scanf("%s", origen);
    printf("\nNuevo destino: ");
    scanf("%s", destino);
    printf("\nNuevo tiempo que durara en minutos: ");
    scanf("%d", &tiempo);
    printf("\nNueva distancia en Km: ");
    scanf("%d%*c", &dist);
    printf("\nNuevo tipo de ruta (terrestre, aerea, maritima): ");
    scanf("%s", tipo);
    printf("\n");
   
    struct AdjListNodo* newNode = newAdjListNodoMod(origen, destino, tiempo, dist, tipo);
    newNode->next = graph->array[vertice].head;
    graph->array[vertice].head = newNode;
}

//Imprime ruta modificada
void printGrafoMod(struct Grafo* graph)
{
    int v;
    for (v = 0; v <= graph->V; ++v)
    {
        struct AdjListNodo* pCrawl = graph->array[v].head;
        
        printf("\n Lista de adyacencia del vertice %d\n head ", v);
        while (pCrawl)
        {
            FILE * fpuntero = fopen("domicilioRuta.txt", "r+");
            printf("-> %s, %s, %d, %d, %s", pCrawl->origen, pCrawl->destino, pCrawl->tiempo, pCrawl->dist, pCrawl->tipo);
            fwrite(&pCrawl->origen, sizeof(ruta), 1, fpuntero);
            fwrite(&pCrawl->destino, sizeof(ruta), 1, fpuntero);
            fprintf(fpuntero, "%d", pCrawl->tiempo);
            fprintf(fpuntero, "\n");
            fprintf(fpuntero, "%d", pCrawl->dist);
            fprintf(fpuntero, "\n");
            fwrite(&pCrawl->tipo, sizeof(ruta), 1, fpuntero);
            pCrawl = pCrawl->next;
            fclose(fpuntero);
        }
        printf("\n");
    }
}

//Ejecuta modificacion ruta
void domiciliosRutaMod(){
    int V = 1;
    struct Grafo* graph = crearGrafo(V);
    modificaRuta(graph);

    printGrafoMod(graph);
}

//Imprime grafo eliminado
void printGrafoElim(struct Grafo* grafo)
{
    int v;
    char origen[15];
    printf("Inserte origen por eliminar: ");
    scanf("%s", origen);
    for (v = 0; v < grafo->V; ++v)
    {
        struct AdjListNodo* pCrawl = grafo->array[v].head;
        
        printf("\n Lista de adyacencia del vertice %d\n head ", v);
        while (pCrawl)
        {
            FILE * fpuntero = fopen("domicilioRuta.txt", "r+");
            free(head);
            printf("-> %s, %s, %d, %d, %s", pCrawl->origen, pCrawl->destino, pCrawl->tiempo, pCrawl->dist, pCrawl->tipo);
            fwrite(&pCrawl, sizeof(ruta), 1, fpuntero);
            pCrawl = pCrawl->next;
            fclose(fpuntero);
        }
        printf("\n");
    }
}

//Ejecuta eliminacion de datos
void domiciliosElimRuta(){
    int V = 1;
    struct Grafo* grafo = crearGrafo(V);

    printGrafoElim(grafo);
}

//Menu de domicilio
void menuDomicilio(){
    int num;
    while(num!=4){
    printf("\n1.Registrar lugar\n2.Modificar lugar\n3.Borrar lugar\n4.Registrar ruta\n5.Modificar ruta\n6.Eliminar ruta\n7.Salir\nIngrese una opcion: ");
    scanf("%d%*c",&num);
    switch (num) {
      case 1: 
      domicilios();
      break;
      case 2:
      domiciliosMod();
      break;
      case 3:
      printf("Eliminar lugar\n");
      domiciliosElim();
      break;
      case 4:
      domiciliosRuta();
      break;
      case 5:
      domiciliosRutaMod();
      break;
      case 6:
      printf("Eliminar ruta\n");
      domiciliosElimRuta();
      break;
      case 7:
      menuPrincipal();
    }
  }
}
//----------------------------- TERMINA DOMICILIOS DE COLABORADORES ---------------------------

//--------------------------------------- BITACORA TRABAJO --------------------------------------
//datos bitacora
struct bitacora
{
    int cedula;
    char descripcion[30];
};

//Nodo bitacora
struct nodeb // Nodo 
{
    struct nodeb *next;
    struct nodeb *prev;
    BITACORA info;
};

NODEB *head2 = NULL;

//Crea el nodo
NODEB *CrearNode() 
{
    NODEB *temp;
    temp = (NODEB *)malloc(sizeof(NODEB));
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

//Pide datos y los almacena en el archivo txt
void bitacoras(BITACORA *ptr){
    FILE * fpuntero = fopen("colaboradores.txt", "a+");
    printf("Rendimiento de los colaboradores!\n");
    printf("Ingrese el numero de cedula del colaborador: ");
    scanf("%d%*c", &ptr->cedula);
    fprintf(fpuntero, "%d", ptr->cedula);
    printf("\nObservacion del rendimiento: ");
    fgets(ptr->descripcion, 30, stdin);
    fwrite(&ptr->descripcion, sizeof(BITACORA), 1, fpuntero);

    fclose(fpuntero);
}

//Aniade datos al nodo
void aniadirBitacora(BITACORA bitacora) // agrega info de colaborador  a nodo
{
    NODEB *nuevoNodo;
    nuevoNodo = CrearNode();
    nuevoNodo->info = bitacora;

    if (head2 == NULL)
    {
        head2 = nuevoNodo;
    }
    else
    {
        nuevoNodo->next = head2;
        head2->prev = nuevoNodo;
        head2 = nuevoNodo;
    }
}


//menu principal
void menuPrincipal()       
{
    int opcion, colabEquip = 2;
    int cantMensajes = 0;
    char repetir = TRUE;

    do
    {
        printf("\t\t\tMENU PRINCIPAL\n");
        printf("\t\t\t--------------\n");
        printf("\n\t1. Registrar colaborador\n");
        printf("\t2. Registro de equipo\n");
        printf("\t3. Arbol de archivos\n");
        printf("\t4. Catalogos para lugares de domicilio\n");
        printf("\t5. Bitacora de rendimiento\n");
        printf("\t6. Chat\n");
        printf("\t7. Ruta del paseo\n");
        printf("\t8. Analisis de datos\n");
        //9 es para eliminar todo el contenido de los txts
        printf("\t9. Eliminar contenido txts\n");
        printf("\n\t0. SALIR\n");
        printf("\n\tIngrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Eligio registrar colaborador\n");
            RECURSOS recursos;
            NODEC *aux;
            //ingresan datos
            registroColaborador(&recursos);
            //info colab a nodo
            aniadirColaborador(recursos);
            //guardo nodo en el archivo
            colaboradorAarchivo();
            //menuColabs(&recursos);
            break;
        case 2:
            printf("Eligio registrar equipo\n");
            equipos();
            break;
        case 3:
            break;
        case 4:
            menuDomicilio();
            break;
        case 5:
            printf("Eligio bitacora de trabajo\n");
            BITACORA ptr;
            bitacoras(&ptr);
            aniadirBitacora(ptr);
            break;
        case 6:
            //chat();
            cantMensajes += 1;
            break;
        case 7:
            break;
        case 8:
            //Funcion de analis de datos se hizo dentro del menu principal
            printf("\nEligio analisis de datos\n");
            int numero = 0;
            while(numero!=7){
                printf("1. Cantidad mensajes\n");
                printf("2. Promedio de lugares que se visitan en rutas de paseo\n");
                printf("3. Cantidad de archivos en total\n");
                printf("4. Cantidad de archivos en promedio\n");
                printf("5. Promedio de colaboradores en equipo\n");
                printf("6. Top 5 con mayor cantidad de colaboradores\n");
                printf("7. Salir\n");
                printf("Ingrese opcion: ");
                scanf("%d",&numero);
                switch (numero) {
                    case 1: 
                        printf("La cantidad de mensajes enviados es: %d\n\n", cantMensajes);
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        printf("El promedio de colaboradores por equipo es de: %d\n\n", colabEquip);
                        break;
                    case 6:
                        break;
                    case 7:
                        numero = 7;
                        break;
                    }
            }
            break;
        case 9:
            eliminarTodoColabs();
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