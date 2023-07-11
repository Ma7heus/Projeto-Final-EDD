#include <stdio.h>
#include <stdlib.h>

typedef struct _data {
   int dia;
   int mes;
   int ano;
   int hora;
   int minuto;
} Data;

typedef struct _evento {
   int codigo;
   Data dataEvento;
   float duracao;
   char descricao[100];
   struct _evento *proximo;
} Evento;

Evento *agenda = NULL;

Evento* criarEvento(int codigo, Data data, float duracao, char descricao[]) {
   Evento *evento = (Evento*)malloc(sizeof(Evento));
   evento->codigo = codigo;
   evento->dataEvento = data;
   evento->duracao = duracao;
   strcpy(evento->descricao, descricao);
   evento->proximo = NULL;
   return evento;
}

void incluirEvento() {
   int codigo;
   Data data;
   float duracao;
   char descricao[100];

   printf("Digite o código do evento: ");
   scanf("%d", &codigo);

   printf("Digite a data do evento (dia/mes/ano hora:minuto): ");
   scanf("%d/%d/%d %d:%d", &data.dia, &data.mes, &data.ano, &data.hora, &data.minuto);

   printf("Digite a duração do evento: ");
   scanf("%f", &duracao);

   printf("Digite a descrição do evento: ");
   scanf(" %[^\n]", descricao);

   Evento *evento = criarEvento(codigo, data, duracao, descricao);

   if (agenda == NULL) {
      agenda = evento;
   } else {
      Evento *temp = agenda;
      while (temp->proximo != NULL) {
         temp = temp->proximo;
      }
      temp->proximo = evento;
   }

   printf("Evento incluído com sucesso!\n");
}

void consultarEventoPorData(Data data) {
   Evento *temp = agenda;
   int encontrado = 0;

   while (temp != NULL) {
      if (temp->dataEvento.dia == data.dia && temp->dataEvento.mes == data.mes && temp->dataEvento.ano == data.ano) {
         printf("Código: %d\n", temp->codigo);
         printf("Data: %d/%d/%d %d:%d\n", temp->dataEvento.dia, temp->dataEvento.mes, temp->dataEvento.ano, temp->dataEvento.hora, temp->dataEvento.minuto);
         printf("Duração: %.2f\n", temp->duracao);
         printf("Descrição: %s\n", temp->descricao);
         printf("\n");
         encontrado = 1;
      }
      temp = temp->proximo;
   }

   if (!encontrado) {
      printf("Agenda vazia para a data informada.\n");
   }
}

void consultarEventoPorDataEHora(Data data) {
   Evento *temp = agenda;
   int encontrado = 0;

   while (temp != NULL) {
      if (temp->dataEvento.dia == data.dia && temp->dataEvento.mes == data.mes && temp->dataEvento.ano == data.ano && temp->dataEvento.hora == data.hora && temp->dataEvento.minuto == data.minuto) {
         printf("Código: %d\n", temp->codigo);
         printf("Data: %d/%d/%d %d:%d\n", temp->dataEvento.dia, temp->dataEvento.mes, temp->dataEvento.ano, temp->dataEvento.hora, temp->dataEvento.minuto);
         printf("Duração: %.2f\n", temp->duracao);
         printf("Descrição: %s\n", temp->descricao);
         printf("\n");
         encontrado = 1;
         break;
      }
      temp = temp->proximo;
   }

   if (!encontrado) {
      printf("Agenda vazia para a data e hora informadas.\n");
   }
}

void alterarEvento(Data data) {
   Evento *temp = agenda;
   int encontrado = 0;

   while (temp != NULL) {
      if (temp->dataEvento.dia == data.dia && temp->dataEvento.mes == data.mes && temp->dataEvento.ano == data.ano && temp->dataEvento.hora == data.hora && temp->dataEvento.minuto == data.minuto) {
         printf("Digite a nova descrição do evento: ");
         scanf(" %[^\n]", temp->descricao);

         printf("Digite a nova duração do evento: ");
         scanf("%f", &temp->duracao);

         printf("Evento alterado com sucesso!\n");
         encontrado = 1;
         break;
      }
      temp = temp->proximo;
   }

   if (!encontrado) {
      printf("Compromisso não encontrado.\n");
   }
}

void excluirEvento(Data data) {
   Evento *temp = agenda;
   Evento *anterior = NULL;
   int encontrado = 0;

   while (temp != NULL) {
      if (temp->dataEvento.dia == data.dia && temp->dataEvento.mes == data.mes && temp->dataEvento.ano == data.ano && temp->dataEvento.hora == data.hora && temp->dataEvento.minuto == data.minuto) {
         if (anterior == NULL) {
            agenda = temp->proximo;
         } else {
            anterior->proximo = temp->proximo;
         }

         free(temp);
         printf("Evento excluído com sucesso!\n");
         encontrado = 1;
         break;
      }

      anterior = temp;
      temp = temp->proximo;
   }

   if (!encontrado) {
      printf("Compromisso não encontrado.\n");
   }
}

void listarTodosEventos() {
   Evento *temp = agenda;

   if (temp == NULL) {
      printf("Agenda vazia.\n");
   } else {
      while (temp != NULL) {
         printf("Código: %d\n", temp->codigo);
         printf("Data: %d/%d/%d %d:%d\n", temp->dataEvento.dia, temp->dataEvento.mes, temp->dataEvento.ano, temp->dataEvento.hora, temp->dataEvento.minuto);
         printf("Duração: %.2f\n", temp->duracao);
         printf("Descrição: %s\n", temp->descricao);
         printf("\n");
         temp = temp->proximo;
      }
   }
}

void liberarAgenda() {
   Evento *temp = agenda;
   Evento *proximo = NULL;

   while (temp != NULL) {
      proximo = temp->proximo;
      free(temp);
      temp = proximo;
   }

   agenda = NULL;
}

int main() {
   int opcao;
   Data data;

   do {
      printf("---- matheus-Agenda ----\n");
      printf("1. Incluir\n");
      printf("2. Consultar por data\n");
      printf("3. Consultar por data e hora\n");
      printf("4. Alterar\n");
      printf("5. Excluir\n");
      printf("6. Listar todos\n");
      printf("0. Sair\n");
      printf("Digite a opção desejada: ");
      scanf("%d", &opcao);

      switch (opcao) {
         case 1:
            incluirEvento();
            break;
         case 2:
            printf("Digite a data do evento (dia/mes/ano): ");
            scanf("%d/%d/%d", &data.dia, &data.mes, &data.ano);
            consultarEventoPorData(data);
            break;
         case 3:
            printf("Digite a data e hora do evento (dia/mes/ano hora:minuto): ");
            scanf("%d/%d/%d %d:%d", &data.dia, &data.mes, &data.ano, &data.hora, &data.minuto);
            consultarEventoPorDataEHora(data);
            break;
         case 4:
            printf("Digite a data e hora do evento a ser alterado (dia/mes/ano hora:minuto): ");
            scanf("%d/%d/%d %d:%d", &data.dia, &data.mes, &data.ano, &data.hora, &data.minuto);
            alterarEvento(data);
            break;
         case 5:
            printf("Digite a data e hora do evento a ser excluído (dia/mes/ano hora:minuto): ");
            scanf("%d/%d/%d %d:%d", &data.dia, &data.mes, &data.ano, &data.hora, &data.minuto);
            excluirEvento(data);
            break;
         case 6:
            listarTodosEventos();
            break;
         case 0:
            liberarAgenda();
            printf("Encerrando o programa. Até mais!\n");
            break;
         default:
            printf("Opção inválida. Por favor, tente novamente.\n");
            break;
      }

      printf("\n");
   } while (opcao != 0);

   return 0;
}
