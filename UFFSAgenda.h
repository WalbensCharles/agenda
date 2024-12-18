#ifndef UFFSAGENDA_H
#define UFFSAGENDA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estrutura para data do evento
struct _data {
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
};
typedef struct _data Data;

//estrutura de infos do evento
    struct _evento {
    int codigo;
    Data dataEvento;
    float duracao;
    char descricao[100];
    struct _evento *proximo;
};
typedef struct _evento Evento;

//implementacao das funcao
Evento *criarEvento(int id, Data date, float duration, char description[100]);
void inserirEvento(int id ,Data date, float duration, char description[100]);
void consultarEventos(Data date);
void AlterarEvento(Data date, float duration ,char description[100]);
void ExcluirEvento(Data date);
void ListarEventos();
void lerData(Data *data);
void lerHora(Data *data);

#endif