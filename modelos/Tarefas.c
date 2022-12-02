#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**************************************************************************/
/**CONSTANTES**/
#define nt 40 //capacidadde de armazenameto de tarefas
#define tdc 500 //capacidade de descricao da tarefa
/**************************************************************************/
/**************************************************************************/
/**VARIAVEIS E COMANDOS EXTERNOS**/
extern inserir_bd_tarefa(),receber_dados_tarefa(),atualizar_bd_tarefas(),acessar_bd_tarefa();
/**************************************************************************/
/**************************************************************************/
const numero_tarefa=nt;
/**ESTRUTURA**/
int armaz_tat=nt;
struct Tarefa{
    int cod;
    char descricao[tdc];
}tat[nt];
/**************************************************************************/
/**************************************************************************/
/**FUNCOES**/
char get_descricao_tat(int pt){//retorna o valor da primeira posição do array descrição
    return tat[pt].descricao[0];
}

/////PRINCIPAIS/////
void criar_tarefa(char descricao[tdc]){//Cria uma nova tarefa e envia para o BD de arquivos
   for(int i=0;i<nt;i++){
        if(tat[i].descricao[0]==NULL){
            strcpy(tat[i].descricao,descricao);
            salvar_dados_tarefa(i);
            break;
        }
   }
}
void exibir_tarefas(){//Exibe as tarefas criadas
    for(int i=0;i<nt;i++){
        excluir_tarefa(i);
    }
    acessar_bd_tarefa();
    for(int i=0;i<nt;i++){
        if(tat[i].cod!=0&&tat[i].descricao[0]!=NULL){
            printf("\n|[%d]Tarefa|: %s",tat[i].cod,tat[i].descricao);
            printf("\n---------------------------------------------");
        }
   }
}
void excluir_tarefa(int p){//Exclui uma tarefa em determinada posicao
    tat[p].descricao[0]=NULL;
    tat[p].descricao[1]=NULL;
    tat[p].descricao[2]=NULL;
    tat[p].cod=0;
}

/////SECUNDARIAS/////
int tot_taref(){//retorna o total de tarefas
    int t=0;
    acessar_bd_tarefa();
    for(int i =0;i<nt;i++){
        if(tat[i].cod!=0){
            t++;
        }
    }
    return t;
}
int posicao_tarefa(int cod){//retorna a posicao de uma tarefa no vetor
    int a=0;
    for(int i=0;i<nt;i++){
        if(tat[i].cod==cod){
            a=1;
            return i;
        }
   }
   if(a==0){
        return 55;
   }
}
/////ESPECIAIS/////
void enviar_dados_tarefa(int pt){//Envia os dados da tarefa atraves de parametro
    if(tat[pt].descricao[0]!=NULL){
        receber_dados_tarefa(tat[pt].descricao);
    }
}

/////BANCO DE DADOS/////
void receber_bd_tarefa(int pt,int cod,char descricao[tdc]){//Recebe dados por parametro do BD de arquivos
    tat[pt].cod=cod;
    strcpy(tat[pt].descricao,descricao);
}
void salvar_dados_tarefa(int pt){//Envia os dados de uma tarefa criada para o BD de arquivos
    inserir_bd_tarefa(tat[pt].descricao);
}
/**************************************************************************/
/**************************************************************************/
