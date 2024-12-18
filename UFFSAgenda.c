#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UFFSAgenda.h"


//criar uma agenda e iniciar com NULL
Evento *agenda=NULL;

//funcao para Criar un novo evento

Evento *criarEvento(int id, Data date, float duration ,char description[100]){
    Evento *novo=(Evento*)malloc(sizeof(Evento));
    novo->codigo=id;
    novo->dataEvento=date;
    novo->duracao=duration;
    strcpy(novo->descricao, description);
    novo->proximo=NULL;
    return novo;
}

//funcoa para inserir um evento na agenda
void inserirEvento(int id, Data date, float duration, char description[100]){
    Evento *novo=criarEvento(id,date,duration,description);
    if(agenda==NULL){
        agenda=novo;

    }else{
        Evento *aux=agenda;
        while(aux->proximo!=NULL){
            aux=aux->proximo;
        }
        aux->proximo=novo;
    }
    printf("\n\tEvento adicionado com succeso\n");
}

//Funcao para consulta evento na agenda por data ou hora
void consultarEventos(Data date) {
    if (agenda == NULL) {  // Verifica se a agenda esta vazia antes de consultar
        printf("Infelizmente! A agenda esta vazia.\n");
        return;  // Sai da funcao se a agenda estiver vazia
    }

    Evento *aux = agenda;
    int achou = 0;
    while (aux != NULL) {
        if (aux->dataEvento.dia == date.dia && aux->dataEvento.mes == date.mes && aux->dataEvento.ano == date.ano) {
            if (date.hora == -1 || (aux->dataEvento.hora == date.hora && aux->dataEvento.minuto == date.minuto)) {
                printf("Codigo: %d\n", aux->codigo);
                printf("Data: %02d/%02d/%04d\n", aux->dataEvento.dia, aux->dataEvento.mes, aux->dataEvento.ano);
                printf("Hora: %02d:%02d\n", aux->dataEvento.hora, aux->dataEvento.minuto);
                printf("Duracao: %.1f horas\n", aux->duracao);
                printf("Descricao: %s\n\n", aux->descricao);
                achou = 1;
                if (date.hora != -1) break;  // Interrompe o loop se a consulta especificou uma hora e foi encontrada
            }
        }
        aux = aux->proximo;
    }
    if (!achou) {
        printf("\nLamento! Nao existir evento cadastrado para esta data.\n");
    }
}


//funcao para alterar descricao e a duracao
void alterarEvento(Data date,float duration,char description[100]){
    if(agenda==NULL){
        printf("Infelizmente a Agenda esta vazia. Nenhum evento para alterar\n");
    }
    Evento *aux=agenda;
    int achou=0;

    while(aux!=NULL){
        if(aux->dataEvento.dia==date.dia && aux->dataEvento.mes==date.mes &&aux->dataEvento.ano==date.ano && aux->dataEvento.hora==date.hora && aux->dataEvento.minuto==date.minuto){
            achou=1;
            break;
        }
        aux=aux->proximo;
    }
    if(achou){
        strcpy(aux->descricao,description);
        aux->duracao=duration;
        printf("Evento Alterado com sucesso! \n");
    }else{
        printf("infelizmente Evento nao encontrado\n");
    }
}

//funcao para excluir um evento
void excluirEvento(Data date){
    if(agenda==NULL){
        printf("infelizmente a agenda esta vazia.nenhum evento para excluir.\n");
    }else{
            Evento *atual=agenda;
            Evento *ante=NULL;
            int achou=0;
            while(atual!=NULL){
                if(atual->dataEvento.dia==date.dia && atual->dataEvento.mes && atual->dataEvento.ano==date.ano && atual->dataEvento.hora==date.hora && atual->dataEvento.minuto==date.minuto){
                    achou=1;
                    break;
                }
                ante=atual;
                atual=atual->proximo;
            }
            if(achou){
                if(ante==NULL){
                    agenda=atual->proximo;
                }else{
                    ante->proximo=atual->proximo;
                }
                free(atual);
                printf("Evento excluir com sucesso!\n");
            }else{
                printf("Infelizmente evento nao encontrado .\n");
            }   
    }
}

 //funcao para listar todos eventos
 void listarEventos(){
    if(agenda==NULL){
        printf("Infelizmente a agenda esta vazia. \n");
    }
    Evento *aux=agenda;
    while(aux!=NULL){
        printf("Codigo do evento: %d\n",aux->codigo);
        printf("Data do evento: %02d/%02d/%04d\n",aux->dataEvento.dia,aux->dataEvento.mes, aux->dataEvento.ano);
        printf("Hora do evento: %02d:%02d\n",aux->dataEvento.hora, aux->dataEvento.minuto);
        printf("Duracao do evento : %.1f\n",aux->duracao);
        printf("Descicao do evento %s\n\n",aux->descricao);
        aux=aux->proximo;
    }      
 }

 void lerData(Data *data) {
    printf("Digite a data do evento em formato [dd/mm/aaaa]: ");
    scanf("%d/%d/%d", &data->dia, &data->mes, &data->ano);
}

void lerHora(Data *data) {
    printf("Digite a hora do evento em formato [hh:mm]: ");
    scanf("%d:%d", &data->hora, &data->minuto);
}


 int main(){
    int option;
    Data date;
    int id;
    float duration;
    char description[100]; 
    char answer;

    do{
        printf("\n\tIt's UFFS agenda\n\n");
        printf("\t1 - Incluir\n\t2 - Consultar\n\t3 - Alterar\n\t4 - Excluir\n\t5 - Listar todos\n\t6 - Sair\n");
        scanf("%d", &option);
        switch(option){
//incluir
            case 1:
            printf("Digite o codigo do evento : ");
            scanf("%d",&id);
            //funcao reutilizaveis
            lerData(&date);
            lerHora(&date);

            printf("Digite a duracao do evento : ");
            scanf("%f",&duration);
            printf("Digite a descricoa do evento : ");
            scanf(" %[^\n]",description);
            inserirEvento(id, date, duration, description);
            break;
//consultar
            case 2:
            if (agenda == NULL) {
                printf("infelizmente ! a agenda esta vazia.\n");
            } else {
                lerData(&date);
                
                printf("Deseja consultar por hora especifica? (S/N): ");
                scanf(" %c", &answer);  // Espaço antes do %c para consumir qualquer espaço em branco no buffer
                if (answer == 's' || answer == 'S') {
                    lerHora(&date);
                } else {
                    date.hora = -1;  // Define -1 para hora quando a consulta é apenas por data
                }
                consultarEventos(date);
            }
            break;


//alterar
            case 3:
            if(agenda==NULL){
                printf("Infelizmente ! a agenda est a vazia.\n");
            }else{
                lerData(&date);
                lerHora(&date);
                printf("Digite a nova descripcao do evento : ");
                scanf(" %[^\n]", description);
                printf("Digite a nove duracao do evento : ");
                scanf("%f", &duration);
                alterarEvento(date,duration,description);
            }
            break;

//excluir
            case 4:
            if(agenda==NULL){
                printf("infelizmente ! a agenda esta vazia.\n");
            }else{
                lerData(&date);
                lerHora(&date);
                excluirEvento(date);
            }
            break;

//listartodos
            case 5:

            listarEventos();
            break;
//sair
            case 6:
            printf("ate mais......\n");
            break;
        }
        printf("\n");


    }while(option!=6);
    return 0;

 }