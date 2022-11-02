#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>


typedef struct resource
{
    char ID[20];       // ID del recurso
    char name[50];       // Nombre del recurso
    char type[50];      // Tipo del recurso
    char capacity[50];       // Capacidad del recurso
    char amountAvailable[50];         // Cantidad disponible
    char manager[50];        // Encargado de reaizar el recurso
    struct POSTAL *next
} RESOURCE;


typedef struct nodes // Nodo donde se almacena cada recurso
{
    struct nodes *next;
    struct nodes *prev;
    RESOURCE info;
} NODES;

NODES *head = NULL;

NODES *CreateNode() // funcion para crear nodo
{
    NODES *temp;
    temp = (NODES *)malloc(sizeof(NODES));
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}


// REGISTRO DE RECURSOS DEL PROYECTO
void registrarRecurso(RESOURCE*resource) // Funcion para solicitar informacion con la cual se llenara el nodo
{
	fgets(resource->ID, 20, stdin);
    printf("Ingrese el codigo de la postal a registrar: \n");
    fgets(resource->name, 10, stdin);
    printf("Ingrese el nombre del equipo al que pertenece la postal: \n");
    fgets(resource->type, 50, stdin);
    printf("Ingrese el nombre del jugador, estadio o elemento de la postal: \n");
    fgets(resource->capacity, 50, stdin);
    printf("Ingrese el tipo de postal (base, bronce, plata, oro): \n");
    fgets(resource->amountAvailable, 50, stdin);
    printf("Ingrese el tipo de postal (base, bronce, plata, oro): \n");
    fgets(resource->manager, 50, stdin);
}

// Agrega los nodos al archivo.dat
void agregarRecursoDat(RESOURCE resource) // agrega info de recursos a nodo
{
    NODES *newNode;
    newNode = CreateNode();
    newNode->info = resource;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void leerRecursoDeArchivo() // agrega todos los recursos del archivo .dat a memoria
{
    RESOURCE resource;
    FILE *fp;
    fp = fopen("listaDeRecursos.dat", "rb");
    if (fp != NULL)
    {
        while ((fread(&resource, sizeof(RESOURCE), 1, fp)) != 0)
        {
            agregarRecursoDat(resource);
        }
    }
    fclose(fp);
}

void archivoDeRecurso() // copia informacion a .dat
{
    NODES *aux = head;
    FILE *fp;
    fp = fopen("listaDeRecursos.dat", "wb");
    if (fp != NULL)
    {
        while (aux != NULL)
        {
            fwrite(&aux->info, sizeof(RESOURCE), 1, fp);
            aux = aux->next;
        }
    }
    fclose(fp);
}

