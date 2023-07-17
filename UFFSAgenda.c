#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UFFSAgenda.h"

Evento *agenda = NULL;
int contadorCodigo = 0;

int main() {
    limparConsole();
    int opcao;
    Data data;

    do
    {
        printf("*******UFFSAgenda-MENU DE SELECAO*******\n");
        printf("1. Incluir\n");
        printf("2. Consultar\n");
        printf("3. Alterar\n");
        printf("4. Excluir\n");
        printf("5. Listar todos\n");
        printf("6. Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            criarNovoEvento();
            break;
        case 2:
            consultar();
            break;
        case 3:
            printf("Digite a data e hora do evento a ser alterado (dia/mes/ano hora:minuto): ");
            scanf("%d/%d/%d %d:%d", &data.dia, &data.mes, &data.ano, &data.hora, &data.minuto);
            alterarEvento(data);
            break;
        case 4:
            printf("Digite a data e hora do evento a ser excluido (dia/mes/ano hora:minuto): ");
            scanf("%d/%d/%d %d:%d", &data.dia, &data.mes, &data.ano, &data.hora, &data.minuto);
            excluirEvento(data);
            break;
        case 5:
            listarTodosEventos();
            break;
        case 6:
            liberarAgenda();
            printf("Saindo da agenda, volte sempre!\n");
            break;
        default:
            printf("Opcao invalida. Por favor, tente novamente.\n");
            break;
        }

        printf("\n");
    } while (opcao != 6);

    return 0;
}

void criarNovoEvento()
{
    limparConsole();
    printf("*****CADASTRO DE NOVO EVENTO*****\n");
    Data data;
    float duracao;
    char descricao[100];

    printf("Digite a data do evento (dia/mes/ano hh:mm): ");
    scanf("%d/%d/%d %d:%d", &data.dia, &data.mes, &data.ano, &data.hora, &data.minuto);

    printf("Digite a duracao do evento em horas: ");
    scanf("%f", &duracao);

    getchar();

    printf("Digite a descricao do evento: ");
    fgets(descricao, sizeof(descricao), stdin);

    descricao[strcspn(descricao, "\n")] = '\0';

    Evento *evento = popularNovoEvento(data, duracao, descricao);

    if (agenda == NULL)
    {
        agenda = evento;
    }
    else
    {
        Evento *temp = agenda;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = evento;
    }

    printf("Evento incluido com sucesso!\n");
}

Evento *popularNovoEvento(Data data, float duracao, char descricao[])
{
    Evento *evento = (Evento *)malloc(sizeof(Evento));
    evento->codigo = novoCodigo();
    evento->dataEvento = data;
    evento->duracao = duracao;
    strcpy(evento->descricao, descricao);
    evento->next = NULL;
    return evento;
}

int novoCodigo()
{
    contadorCodigo += 1;
    return contadorCodigo;
}

void consultar() {
    limparConsole();
    printf("*****CONSULTANDO AGENDA*****\n");
    int opcao;
    Data data;
    
    do {
        printf("1. Deseja consultar por data\n");
        printf("2. Deseja consultar por data e hora\n");
        printf("0. Sair da consulta\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1:
            printf("Digite a data do evento (dia/mes/ano): ");
            scanf("%d/%d/%d", &data.dia, &data.mes, &data.ano);
            consultarEventoPorData(data);
            break;
        case 2:
            printf("Digite a data e hora do evento (dia/mes/ano hora:minuto): ");
            scanf("%d/%d/%d %d:%d", &data.dia, &data.mes, &data.ano, &data.hora, &data.minuto);
            consultarEventoPorDataEHora(data);
            break;
        case 0:
            break;
        default:
            printf("Opcao invalida. Por favor, tente novamente.\n");
            break;
        }
    } while (opcao != 0);
    
}

void consultarEventoPorData(Data data)
{
    limparConsole();
    printf("*****CONSULTA POR DATA*****\n");
    Evento *temp = agenda;
    int encontrado = 0;

    while (temp != NULL)
    {
        if (temp->dataEvento.dia == data.dia && temp->dataEvento.mes == data.mes && temp->dataEvento.ano == data.ano)
        {
            printf("Codigo: %d\n", temp->codigo);
            printf("Data: %d/%d/%d %d:%d\n", temp->dataEvento.dia, temp->dataEvento.mes, temp->dataEvento.ano, temp->dataEvento.hora, temp->dataEvento.minuto);
            printf("Duracao: %.2f\n", temp->duracao);
            printf("Descricao: %s\n", temp->descricao);
            printf("\n");
            encontrado = 1;
        }
        temp = temp->next;
    }

    if (!encontrado)
    {
        printf("Agenda vazia.\n");
    }
}

void consultarEventoPorDataEHora(Data data)
{
    limparConsole();
    printf("*****CONSULTA POR DATA E HORA*****\n");
    Evento *temp = agenda;
    int encontrado = 0;

    while (temp != NULL)
    {
        if (temp->dataEvento.dia == data.dia && temp->dataEvento.mes == data.mes && temp->dataEvento.ano == data.ano && temp->dataEvento.hora == data.hora && temp->dataEvento.minuto == data.minuto)
        {
            printf("Codigo: %d\n", temp->codigo);
            printf("Data: %d/%d/%d %d:%d\n", temp->dataEvento.dia, temp->dataEvento.mes, temp->dataEvento.ano, temp->dataEvento.hora, temp->dataEvento.minuto);
            printf("Duracao: %.2f\n", temp->duracao);
            printf("Descricao: %s\n", temp->descricao);
            printf("\n");
            encontrado = 1;
            break;
        }
        temp = temp->next;
    }

    if (!encontrado)
    {
        printf("Agenda vazia.\n");
    }
}

void alterarEvento(Data data)
{
    limparConsole();
    printf("*****EDITANDO EVENTO*****\n");
    Evento *temp = agenda;
    int encontrado = 0;

    while (temp != NULL)
    {
        if (temp->dataEvento.dia == data.dia && temp->dataEvento.mes == data.mes && temp->dataEvento.ano == data.ano && temp->dataEvento.hora == data.hora && temp->dataEvento.minuto == data.minuto)
        {
            printf("Digite a nova descricao do evento: ");
            scanf(" %[^\n]", temp->descricao);

            printf("Digite a nova duracao do evento: ");
            scanf("%f", &temp->duracao);

            printf("Evento alterado com sucesso!\n");
            encontrado = 1;
            break;
        }
        temp = temp->next;
    }

    if (!encontrado)
    {
        printf("Compromisso nao encontrado.\n");
    }
}

void excluirEvento(Data data)
{
    limparConsole();
    printf("*****EXCLUINDO EVENTO*****\n");
    Evento *temp = agenda;
    Evento *anterior = NULL;
    int encontrado = 0;

    while (temp != NULL)
    {
        if (temp->dataEvento.dia == data.dia && temp->dataEvento.mes == data.mes && temp->dataEvento.ano == data.ano && temp->dataEvento.hora == data.hora && temp->dataEvento.minuto == data.minuto)
        {
            if (anterior == NULL)
            {
                agenda = temp->next;
            }
            else
            {
                anterior->next = temp->next;
            }
            free(temp);
            printf("Evento excluido com sucesso!\n");
            encontrado = 1;
            break;
        }

        anterior = temp;
        temp = temp->next;
    }

    if (!encontrado)
    {
        printf("Compromisso nao encontrado.\n");
    }
}

void listarTodosEventos()
{
    limparConsole();
    printf("*****CONSULTA TODOS EVENTOS*****\n");
    Evento *temp = agenda;

    if (temp == NULL)
    {
        printf("Agenda vazia.\n");
    }
    else
    {
        while (temp != NULL)
        {
            printf("Codigo: %d\n", temp->codigo);
            printf("Data: %d/%d/%d %d:%d\n", temp->dataEvento.dia, temp->dataEvento.mes, temp->dataEvento.ano, temp->dataEvento.hora, temp->dataEvento.minuto);
            printf("Duracao: %.2f\n", temp->duracao);
            printf("Descricao: %s\n", temp->descricao);
            printf("\n");
            temp = temp->next;
        }
    }
}

void liberarAgenda()
{
    Evento *temp = agenda;
    Evento *next = NULL;

    while (temp != NULL)
    {
        next = temp->next;
        free(temp);
        temp = next;
    }

    agenda = NULL;
}

void limparConsole()
{
    system("cls");
}