#define AGENDA_H

struct _data {
   int dia;
   int mes;
   int ano;
   int hora;
   int minuto;
};

typedef struct _data Data;

struct _evento {
   int codigo;
   Data dataEvento;
   float duracao;
   char descricao[100];
   struct _evento *next;
};

typedef struct _evento Evento;

void criarNovoEvento();

void consultar();

void consultarEventoPorData(Data data);

void alterarEvento(Data data);

void excluirEvento(Data data);

void listarTodosEventos();

void liberarAgenda();

void consultarEventoPorDataEHora(Data data);

Evento* popularNovoEvento(Data data, float duracao, char descricao[]);

int novoCodigo();

void limparConsole();