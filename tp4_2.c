#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define max 100

struct {
int TareaID;//Numérico autoincremental comenzando en 1000
char *Descripcion; //
int Duracion; // entre 10 – 100
}typedef Tarea;


typedef struct Nodo
{
   Tarea T;
   struct Nodo * Siguiente;
}Nodo;

// funciones
Tarea cargarTareasPendientes(int id);


//funciones lista enlazada
Nodo* crearListaVacia();
void crearNodo(Nodo **start,int id);
void moverNodo(Nodo **startPendientes,Nodo **starRealizada);
void insertarNodo(Nodo **start,Nodo *Nnodo);
void mostrarTarea(Tarea tarea);
void mostrarLista(Nodo *start);
void buscarTareaPorId(Nodo *startpendiente, Nodo *startRealizada);
void buscarTareaPorPalabra(Nodo *startpendiente, Nodo *startRealizada);


int main()
{
    int id=999;
    Nodo *startPendientes;
    Nodo *startRealizadas;
    startPendientes = crearListaVacia();
    startRealizadas = crearListaVacia();
    
    int menu=0;
    do
    {
        printf("*/*/*/*/ Lista To-Do */*/*/*/\n");
        puts("presione un numero segun la accion que desea realizar");
        puts("0) Finalizar con la carga de tareas");
        puts("1) Agregar Tarea pendiente");
        puts("2) mostrar tareas pendientes");
        puts("3) Mostrar tareas realizadas");
        puts("4) mover tareas de pendientes a realizadas");
        puts("5) buscar tarea por ID");
        puts("6) buscar tarea por palabra clave");
        fflush(stdin);
        scanf("%d",&menu);
        switch (menu)
        {
        case 1:
            id++;
            crearNodo(&startPendientes,id);
            break;
        case 2:
            puts("*/*/*/ Lista De Tareas Pendientes */*/*/");
            mostrarLista(startPendientes);
            break;
        case 3:
            puts("*/*/*/ Lista De Tareas Realizadas */*/*/");
            mostrarLista(startRealizadas);
            break;
        case 4:
            moverNodo(&startPendientes,&startRealizadas);
            break;
        case 5:
            buscarTareaPorId(startPendientes,startRealizadas);
            break;
        case 6:
            buscarTareaPorPalabra(startPendientes,startRealizadas);
        default:
            puts("numero ingresado no valido, ingrese otro por favor:");
            scanf("%d",&menu);
            break;
        }
        
    } while (menu !=0);
    
    
}


Tarea cargarTareasPendientes(int id)
{
    Tarea t;
    char *buffer;  //consultar implementacion del buffer adentro o fuera de la funcion!!!
    buffer= (char*)malloc(sizeof(char)*max);
    t.TareaID = id;
    printf("ingrese la descripcion de la tarea:\n");
    fflush(stdin);
    gets(buffer);
    int tama= strlen(buffer)+1;
    t.Descripcion = (char*)malloc(sizeof(char)*tama);
    strcpy(t.Descripcion,buffer);
    free(buffer);
    t.Duracion = rand() % 91 +10;
    return t;
}

//funciones asociadas a la lista enlazada

Nodo* crearListaVacia()
{
    return NULL;
}


void crearNodo(Nodo **start,int id)
{
    Nodo* Nnodo = (Nodo*)malloc(sizeof(Nodo));
    Nnodo->T = cargarTareasPendientes(id);
    Nnodo->Siguiente = *start;
    *start = Nnodo; 
    
}

void insertarNodo(Nodo **start,Nodo *Nnodo)
 {
     Nnodo->Siguiente = *start;
     *start = Nnodo;
 }        



void moverNodo(Nodo **startPendientes,Nodo **startRealizada)
{
    int dato;
    puts("ingrese el ID de la tarea que desea mover:");
    fflush(stdin);
    scanf("%d",&dato);
    Nodo **aux = startPendientes;
    while (*aux != NULL && (*aux)->T.TareaID != dato)
    {
        aux= &(*aux)->Siguiente;
    }

    if (*aux)
    {
        Nodo *temp = *aux;
        *aux = (*aux)->Siguiente;
        insertarNodo(startRealizada,temp);
    }else
    {
        
        puts("id de tarea no encontrado");
    }
    
}


void mostrarTarea(Tarea tarea)
{
    puts("////-T-A-R-E-A-////");
    printf("el id de la tarea es: %d\n",tarea.TareaID);
    puts("descripcion de la tarea:");
    puts(tarea.Descripcion);
    printf("su duracion es: %d\n",tarea.Duracion);
}

void mostrarLista(Nodo *start)
{
    Nodo *aux = start;
    while (aux)
    {
        mostrarTarea(aux->T);
        aux = aux->Siguiente;
    }
}

void buscarTareaPorId(Nodo *startpendiente, Nodo *startRealizada)
{
    int buscado;
    puts("ingrese el ID de la tarea que busca:");
    fflush(stdin);
    scanf("%d",&buscado);
    Nodo *aux = startpendiente;
    while (aux && aux->T.TareaID != buscado)
    {
        aux = aux->Siguiente;
    }
    if (aux)
    {
        mostrarTarea(aux->T);
    }else
    {
        Nodo *aux = startRealizada;
        while (aux && aux->T.TareaID != buscado)
        {
            aux = aux->Siguiente;
        }
        if (aux)
        {
           mostrarTarea(aux->T); 
        }else
        {
            puts("el ID no pertenece a ninguna tarea pendiente ni realizada");
        }
    }
}



void buscarTareaPorPalabra(Nodo *startpendiente, Nodo *startRealizada)
{
    char *buffer;
    buffer = (char*)malloc(sizeof(char) * max);
    puts("ingrese la palabra clave de la tarea que buscas:");
    gets(buffer);
    int longitud = strlen(buffer)+1;
    char *aguja;
    aguja = (char*)malloc(sizeof(char)*longitud);
    strcpy(aguja,buffer);
    free(buffer);
    Nodo *aux = startpendiente;
    while (aux != NULL && strstr(aux->T.Descripcion,aguja) == NULL)
    {
        aux = aux->Siguiente;
    }
    if (aux)
    {
        mostrarTarea(aux->T);
    }else
    {
        Nodo *aux = startRealizada;
        while (aux != NULL && strstr(aux->T.Descripcion,aguja) == NULL )
        {
            aux = aux->Siguiente;
        }
        if (aux)
        {
           mostrarTarea(aux->T); 
        }else
        {
            puts("La palabra clave no pertenece a ninguna tarea pendiente ni realizada");
        }
    }
}


void liberarmemoria(Nodo **lista)
{
    Nodo *aux;
    while (*lista)
    {
        aux = *lista;
        *lista = (*lista)->Siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }
}


 