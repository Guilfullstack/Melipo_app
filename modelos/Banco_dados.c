#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/**************************************************************************/
/**CONSTANTES**/
#define bdtif 800 //capacidade de informacao da especie
#define bdtdec 500 //define a capaciadade de descricao do enxame
#define bdtdc 500////define a capaciadade de descricao de uma tarefa
/**************************************************************************/
/**************************************************************************/
/**VARIAVEIS E COMANDOS EXTERNOS**/
extern armaz_especie,armaz_enxame,armaz_tat;
extern enviar_dados_producao(),enviar_dados_especie(),enviar_dados_enxame(),enviar_dados_tarefa();
extern get_total_enxame();
extern atualizar_Especies();
extern get_descricao_tat();
extern receber_bd_usuario(),receber_bd_enxames(),receber_bd_especie(),receber_bd_tarefa();
extern set_id_especie();
/**************************************************************************/
/**************************************************************************/
/**VARIAVEIS**/
//enxames
int id_ex=0;
char dat_ex[21];
char espec_ex[21];
double prod_ex=0;
float pro_ex=0;
_Bool status_ex=false;
int id_espec_ex=0;
char descric_ex[bdtdec];
//especie
int id_esp=0;
char esp[21];
double prod_esp;
float pro_ep;
int qtd_ex;
char descric_esp[bdtif];
//tarefa
char tarefa[bdtdc];
/**************************************************************************/
/**************************************************************************/
/**FUNCOES**/
/////USUARIO/////
void inserir_bd_usuario(char nome[11],int senha){//insere dados de um usuario no BD de arquivo
    char lin1[61]="============================================================";
    char lin2[61]="------------------------------------------------------------";
    FILE *fpuser;
    char diretorioU[61]=".//Repositorios//Banco_Dados//Usuario";
    fpuser=fopen(diretorioU,"w");
    if(fpuser==NULL){
        printf("\nFalha ao abrir banco de dados");
    }else{
        //titulo
        fprintf(fpuser,"%s\n           |----------|DADOS_USUARIO|----------|\n%s",lin1,lin1);
        //usuario
        fprintf(fpuser,"\n%s\n|SENHA: %d \n|NOME: %s \n%s",lin2,senha,nome,lin2);
        fflush(fpuser);
        fclose(fpuser);
    }
}
void acessar_bd_usuario(){//acessa dados do usuario no BD de arquivo e envia por paremetro
    FILE *fpuser;
    char diretorioU[61]=".//Repositorios//Banco_Dados//Usuario";
    char lin1[61];
    char lin2[61];
    char nome[11];
    int senha;
    char texto[61];
    char texto1[20],texto2[20];

    fpuser=fopen(diretorioU,"r");
    if(fpuser==NULL){
        printf("\nFalha ao abrir arquivo");
        fclose(fpuser);
        exit(1);
    }else{
        //titulo
        fscanf(fpuser,"%s\n %s \n%s",&lin1,&texto,&lin1);
        //usuario
        fscanf(fpuser,"\n%s\n%s %d \n%s %s \n%s",&lin2,&texto1,&senha,&texto2,&nome,&lin2);
        fflush(fpuser);
        fclose(fpuser);
        receber_bd_usuario(nome,senha);
    }

}

/////ENXAMES/////
void receber_dados_enxameBD(int id,char data[21],char especie[21],int id_especie,double producao,_Bool sts,char descricao[bdtdec]){//recebe dados de um enxame e adiciona as variaveis
    id_ex=id;
    strcpy(dat_ex,data);
    strcpy(espec_ex,especie);
    id_espec_ex=id_especie;
    prod_ex=producao;
    status_ex=sts;
    strcpy(descric_ex,descricao);
    if(strlen(descric_ex)>5){
        for(int i=0;i<=strlen(descric_ex);i++){
            if(descric_ex[i]==' '){
                descric_ex[i]='_';
            }
        }
    }else{
        char a[21]="++++++++++++++++++++";
        strcpy(descric_ex,a);

    }
}
void inserir_bd_enxames(int id,char data[21],char especie[21],double producao,_Bool sts,int id_especie,char descricao[301]){//insere dados de um enxame no final do BD de arquivos
    char lin1[61]="============================================================";
    char lin2[61]="------------------------------------------------------------";
    if(strlen(descricao)>5){
        for(int i=0;i<strlen(descricao);i++){
            if(descricao[i]==' '){
                descricao[i]='_';
            }
        }
    }else{
        char a[21]="++++++++++++++++++++";
        strcpy(descricao,a);

    }
    FILE *fpenx;
    char diretorioEx[61]=".//Repositorios//Banco_Dados//Enxame";
    fpenx=fopen(diretorioEx,"a");
    if(fpenx==NULL){
        printf("\nFalha ao abrir arquivo");
        fclose(fpenx);
        exit(1);
    }else{
        //enxames
        fprintf(fpenx,"\n%s\n|ID: %d  |DAT: %s  |ESPECIE: %s \n",lin2,id,data,especie);
        fprintf(fpenx,"|PRODUCAO: %.2f  |STATUS: %d  |ID_ESPECIE: %d \n|DESCRICAO: %s\n%s",producao,sts,id_especie,descricao,lin2);
        fflush(fpenx);
        fclose(fpenx);

    }
}
void atualizar_bd_enxames(){//Atualiza o BD de enxames subescrevendo o anterior
    char lin1[61]="============================================================";
    char lin2[61]="------------------------------------------------------------";
    FILE *fpenx;
    char diretorioEx[61]=".//Repositorios//Banco_Dados//Enxame";
    fpenx=fopen(diretorioEx,"w");
    if(fpenx==NULL){
        printf("\nFalha ao abrir arquivo");
        fclose(fpenx);
        exit(1);
    }else{
        //titulo
        fprintf(fpenx,"%s\n        |-----------|DADOS_ENXAMES|----------|\n%s",lin1,lin1);
        fflush(fpenx);
        fclose(fpenx);
        //enxame
        fpenx=fopen(diretorioEx,"a");
        for(int i=0;i<armaz_enxame;i++){
            if(get_id_enxame(i)!=0){
                //dependencia
                enviar_dados_enxame('b',i,0);
                //escrita
                fprintf(fpenx,"\n%s\n|ID: %d  |DATA: %s  |ESPECIE: %s\n",lin2,id_ex,dat_ex,espec_ex);
                fprintf(fpenx,"|PRODUCAO: %.2f  |STATUS: %d  |ID_ESPECIE: %d \n|DESCRICAO: %s\n%s",prod_ex,status_ex,id_espec_ex,descric_ex,lin2);
            }
        }
        fflush(fpenx);
        fclose(fpenx);

    }
}
void acessar_bd_enxames(){//acessa dados de todas as tarefas no BD de arquivo e envia por paremetro
    FILE *fpenx;
    char diretorioEX[61]=".//Repositorios//Banco_Dados//Enxame";
    char lin1[61];
    char lin2[61];
    char texto[61];
    char texto1[20],texto2[20],texto3[20];
    for(int i=0;i<armaz_enxame;i++){
        set_id_enxame(0);
    }
    fpenx=fopen(diretorioEX,"r");
    if(fpenx==NULL){
        printf("\nFalha ao abrir arquivo");
        fclose(fpenx);
        exit(1);
    }else{
        //titulo
        fscanf(fpenx,"%s\n %s \n%s\n",&lin1,&texto,&lin1);
        //enxames
        for(int i=0;!feof(fpenx);i++){
            fscanf(fpenx,"\n%s\n%s %d  %s %s %s %s",&lin2,&texto1,&id_ex,&texto2,&dat_ex,&texto3,&espec_ex);
            fscanf(fpenx,"\n%s %f  %s %d  %s %d",&texto1,&pro_ex,&texto2,&status_ex,&texto3,&id_espec_ex);
            fscanf(fpenx,"\n%s  %s \n%s",&texto1,&descric_ex,&lin2);
            for(int i=0;i<strlen(descric_ex);i++){
                if(descric_ex[i]=='_'){
                    descric_ex[i]=' ';
                }
            }
            receber_bd_enxames(i,id_ex,dat_ex,espec_ex,id_espec_ex,pro_ex,status_ex,descric_ex);
        }
        fclose(fpenx);
    }

}

/////ESPECIES/////
void receber_dados_especieBD(int id_especie,char especie[21],double producao,int qtd_enxames,char info[bdtif]){//recebe dados de uma especie e adiciona as variaveis
    id_esp=id_especie;
    strcpy(esp,especie);
    prod_esp=producao;
    qtd_ex=qtd_enxames;
    strcpy(descric_esp,info);
    if(strlen(descric_esp)>5){
        for(int i=0;i<strlen(descric_esp);i++){
            if(descric_esp[i]==' '){
                descric_esp[i]='_';
            }
        }
    }else{
        char a[21]="++++++++++++++++++++";
        strcpy(descric_esp,a);

    }
}
void inserir_bd_especie(int id_especie,char especie[21],double producao,int qtd_enxames,char info[bdtif]){//insere dados de uma especie no final do BD de arquivos
    char inf[bdtif];
    strcpy(inf,info);
    if(strlen(inf)>5){
            for(int i=0;i<strlen(inf);i++){
                if(inf[i]==' '){
                    inf[i]='_';
                }
            }
    }else{
        char a[21]="++++++++++++++++++++";
        strcpy(info,a);
    }

    char lin2[61]="============================================================";
    FILE *fpesp;
    char diretorioE[61]=".//Repositorios//Banco_Dados//Especie";
    fpesp=fopen(diretorioE,"a");
    if(fpesp==NULL){
        printf("\nFalha ao abrir arquivo");
        fclose(fpesp);
        exit(1);
    }else{
        //especie
        fprintf(fpesp,"\n%s\n|ID: %d  |ESPECIE: %s\n|PRODUCAO: %.2f  |N_ENXAMES: %d\nDESCRICAO: %s\n%s",lin2,id_especie,especie,producao,qtd_enxames,inf,lin2);
        fflush(fpesp);
        fclose(fpesp);

    }

}
void atualizar_bd_especies(){//Atualiza o BD de especies subescrevendo o anterior
    char lin1[61]="============================================================";
    char lin2[61]="------------------------------------------------------------";
    FILE *fpesp;
    char diretorioE[61]=".//Repositorios//Banco_Dados//Especie";
    fpesp=fopen(diretorioE,"w");
    if(fpesp==NULL){
        printf("\nFalha ao abrir arquivo");
        fclose(fpesp);
        exit(1);
    }else{
        atualizar_Especies();//dependencia
        //titulo
        fprintf(fpesp,"%s\n        |-----------|DADOS_ESPECIE|----------|\n%s",lin1,lin1);
        fflush(fpesp);
        fclose(fpesp);
        //especie
        fpesp=fopen(diretorioE,"a");
        for(int i=0;i<armaz_especie;i++){
            if(get_id_especie(i)!=0){
                //dependencia
                enviar_dados_especie('b',i,0);
                fprintf(fpesp,"\n%s\n|ID: %d  |ESPECIE: %s \n|PRODUCAO: %.2f  |N_ENXAMES: %d \nDESCRICAO: %s \n%s",lin1,id_esp,esp,prod_esp,qtd_ex,descric_esp,lin1);

            }
        }
        fflush(fpesp);
        fclose(fpesp);

    }
}
void acessar_bd_especies(){//acessa dados de todas as especies no BD de arquivo e envia por paremetro
    FILE *fpesp;
    char lin1[61];
    char lin2[61];
    char texto[61];
    char texto1[20];
    char texto2[20];
    char texto3[20];
    char texto4[20];
    char texto5[20];
    char diretorioE[61]=".//Repositorios//Banco_Dados//Especie";

    for(int i=0;i<armaz_especie;i++){
        set_id_especie(i);
    }

    fpesp=fopen(diretorioE,"r");

    if(fpesp==NULL){
        printf("\nFalha ao abrir arquivo");
        fclose(fpesp);
        exit(1);
    }else{
        //titulo
        fscanf(fpesp,"%s\n %s \n%s\n",&lin1,&texto,&lin1);
        //especie
        for(int i=0;!feof(fpesp);i++){
            fscanf(fpesp,"\n%s \n%s %d  %s %s\n%s %f  %s %d \n%s %s\n%s\n",&lin2,&texto1,&id_esp,&texto2,&esp,&texto3,&pro_ep,&texto4,&qtd_ex,&texto5,&descric_esp,&lin2);
            for(int i=0;i<strlen(descric_esp);i++){
                if(descric_esp[i]=='_'){
                    descric_esp[i]=' ';
                }
            }
            receber_bd_especie(i,id_esp,esp,pro_ep,qtd_ex,descric_esp);
        }
        fclose(fpesp);
    }


}

/////TAREFAS/////
void receber_dados_tarefa(char taref[bdtdc]){//recebe dados de uma tarefa e adiciona as variaveis
    strcpy(tarefa,taref);
    if(strlen(tarefa)>5){
        for(int i=0;i<strlen(tarefa);i++){
            if(tarefa[i]==' '){
                tarefa[i]='_';
            }
        }
    }else{
        char a[21]="++++++++++++++++++++";
        strcpy(tarefa,a);

    }

}
void inserir_bd_tarefa(char taref[bdtdc]){//insere dados de uma tarefa no final do BD de arquivos
    char lin1[61]="============================================================";
    char lin2[61]="------------------------------------------------------------";
    char tare[bdtdc];
    strcpy(tare,taref);
    if(strlen(tare)>5){
        for(int i=0;i<strlen(tare);i++){
            if(tare[i]==' '){
                tare[i]='_';
            }
        }
    }else{
        char a[21]="++++++++++++++++++++";
        strcpy(tare,a);

    }
    FILE *fptat;
    char diretorioT[61]=".//Repositorios//Banco_Dados//Tarefa";
    fptat=fopen(diretorioT,"a");
    if(fptat==NULL){
        printf("\nFalha ao abrir arquivo");
        fclose(fptat);
        exit(1);
    }else{
        //tarefa
        fprintf(fptat,"\n%s\n|TAREFA: %s \n%s",lin2,tare,lin2);
        fflush(fptat);
        fclose(fptat);
    }
}
void atualizar_bd_tarefas(){//Atualiza o BD de tarefas subescrevendo o anterior
    char lin1[61]="============================================================";
    char lin2[61]="------------------------------------------------------------";
    FILE *fptat;
    char diretorioT[61]=".//Repositorios//Banco_Dados//Tarefa";
    fptat=fopen(diretorioT,"w");
    if(fptat==NULL){
        printf("\nFalha ao abrir arquivo");
        fclose(fptat);
        exit(1);
    }else{
        //titulo
        fprintf(fptat,"%s\n        |-----------|DADOS_TAREFAS|----------|\n%s",lin1,lin1);
        fflush(fptat);
        fclose(fptat);
        fptat=fopen(diretorioT,"a");
        //tarefas
        for(int i=0;i<armaz_tat;i++){
            if(get_descricao_tat(i)!=NULL){
                //dependencia
                enviar_dados_tarefa(i);
                fprintf(fptat,"\n%s\n|TAREFA: %s \n%s",lin2,tarefa,lin2);

            }
        }
        fflush(fptat);
        fclose(fptat);

    }
}
void acessar_bd_tarefa(){//acessa dados de todas as tarefas no BD de arquivo e envia por paremetro
    FILE *fptat;
    char lin1[61];
    char lin2[61];
    char texto[61];
    char texto1[20];
    char diretorioT[61]=".//Repositorios//Banco_Dados//Tarefa";
    fptat=fopen(diretorioT,"r");
    if(fptat==NULL){
        printf("\nFalha ao abrir arquivo");
        fclose(fptat);
        exit(1);
    }else{
        //titulo
        fscanf(fptat,"%s\n %s \n%s\n",&lin1,&texto,&lin1);
        //tarefas
        for(int i=0;!feof(fptat);i++){
            fscanf(fptat,"%s\n%s %s \n%s\n",&lin2,&texto1,&tarefa,&lin2);
            for(int i=0;i<strlen(tarefa);i++){
                if(tarefa[i]=='_'){
                    tarefa[i]=' ';
                }
            }
            if(tarefa[0]!=NULL){
                receber_bd_tarefa(i,i+1,tarefa);
            }
        }
        fclose(fptat);
    }

}
/**************************************************************************/
/**************************************************************************/
