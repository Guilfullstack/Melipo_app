#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**************************************************************************/
/**CONSTANTES**/
#define quantidade 20//define a quantidade de relatorios
#define rtif 800 //define a capaciadade de informacao da especie
#define rtdec 500 //define a capaciadade de descricao do enchame
/**************************************************************************/
/**************************************************************************/
/**VARIAVEIS E COMANDOS EXTERNOS**/
extern armaz_especie,armaz_enxame;
extern enviar_dados_producao(),enviar_dados_especie(),enviar_dados_enxame();
extern get_total_enxame(),get_id_especie();
extern atualizar_Especies();
/**************************************************************************/
/**************************************************************************/
/**VARIAEIS**/
const int qtd=quantidade;
int tr=0;
//diretorios
char diretorio1[40]=".//Repositorios//Relatorios//Producao//";
char diretorio2[40]=".//Repositorios//Relatorios//Enxame//";
char diretorio3[40]=".//Repositorios//Relatorios//Especie//";
char diretorio4[40]=".//Repositorios//Relatorios//Arquivos//";
//ponteiros
FILE *fpprod=NULL;
FILE *fpenx=NULL;
FILE *fparq=NULL;
FILE *fpesp=NULL;
//Producao
double producao_tot;
float pro_tot;
int tot_enx;
//especie
char especie_nom[21];
int id_espec;
double produt_espec;
float pro_esp;
char descrit[rtif];
int qtd_enx;
//enxame
int id_enx;
char dat_enx[21];
char espec_enx[21];
double prod_enx;
float pro_enx;
char sts_enx[6];
int id_espec_enx;
char descric_enx[rtdec];
/**************************************************************************/
/**************************************************************************/
/**ESTRUTURA**/
struct Relatorio{
    int cod;
    char nome[21];
    char diretorio[61];
}Relat[quantidade];
int get_cod_relat(p){
    return Relat[p].cod;
}
/**************************************************************************/
/**************************************************************************/
/**FUNCOES**/
/////PRINCIPAIS/////
//gerar relatorio
void gerar_relatorioproducao(char nomefile[20]){//gera um relatorio de produção
    char lin1[61]="============================================================";
    char lin2[61]="------------------------------------------------------------";
    char diretorioP[61];
    strcpy(diretorioP,diretorio1);
    strcat(diretorioP,nomefile);
    fpprod=fopen(diretorioP,"w");
    if(fpprod==NULL){
        printf("\nFalha ao abrir arquivo");
    }else{
        //dependencia
        enviar_dados_producao('r');
        //Producao total
        tot_enx=get_total_enxame();
        fprintf(fpprod,"%s\n       |----------|RELATORIO_PRODUCAO:%s|----------|\n%s",lin1,nomefile,lin1);
        fprintf(fpprod,"\n%s\n|PRODUCAOTOTAL: %.2f |TOTAL_ENXAMES: %d \n%s",lin2,producao_tot,tot_enx,lin2);
        fflush(fpprod);
        fclose(fpprod);
        //Producao por especie
        //dependencia
        atualizar_Especies();
        fpprod=fopen(diretorioP,"a");
        for(int i=0;i<armaz_especie;i++){
            if(get_id_especie(i)!=0){
                //dependencia
                enviar_dados_especie('r',i,0);
                fprintf(fpprod,"\n%s\n|ESPECIE: %s |PRODUCAO: %.2f |N_ENXAMES: %d\n%s",lin1,especie_nom,produt_espec,qtd_enx,lin1);
            }
        }
        salvar_arquivo(nomefile,'p',diretorioP);
        fflush(fpenx);
        fclose(fpprod);
    }
}
void gerar_relatorioenxame(char nomefile[20]){//gera um relatorio de enxames
    char lin1[61]="============================================================";
    char lin2[61]="------------------------------------------------------------";
    char diretorioEx[61];
    strcpy(diretorioEx,diretorio2);
    strcat(diretorioEx,nomefile);
    fpenx=fopen(diretorioEx,"w");
    if(fpenx==NULL){
        printf("\nFalha ao abrir arquivo");
    }else{
        //Titulo
        fprintf(fpenx,"%s\n      |-----------|RELATORIO_ENXAMES:%s|----------|\n%s",lin1,nomefile,lin1);
        fflush(fpenx);
        fclose(fpenx);
        //Enxames;
        fpenx=fopen(diretorioEx,"a");
        for(int i=0;i<armaz_enxame;i++){
                if(get_id_enxame(i)!=0){
                    //dependencia
                    enviar_dados_enxame('r',i,0);
                    fprintf(fpenx,"\n%s\n|ID: %d  |DATA: %s  |ESPECIE: %s\n",lin2,id_enx,dat_enx,espec_enx);
                    fprintf(fpenx,"|PRODUCAO: %.2f  |STATUS: %s  |ID_ESPECIE: %d \n|DESCRICAO: %s\n%s",prod_enx,sts_enx,id_espec_enx,descric_enx,lin2);
                }
        }
        salvar_arquivo(nomefile,'x',diretorioEx);
        fflush(fpenx);
        fclose(fpenx);

    }

}
void gerar_relatorioespecies(char nomefile[20]){//gera um relatorio de especies
    char lin1[61]="============================================================";
    char lin2[61]="------------------------------------------------------------";
    char diretorioEp[61];
    strcpy(diretorioEp,diretorio3);
    strcat(diretorioEp,nomefile);
    fpesp=fopen(diretorioEp,"w");
    if(fpesp==NULL){
        printf("\nFalha ao abrir arquivo");
    }else{
        //dependencia
        atualizar_Especies();
        //Titulo
        fprintf(fpesp,"%s\n      |-----------|RELATORIO_ESPECIES:%s|----------|\n%s",lin1,nomefile,lin1);
        fflush(fpesp);
        fclose(fpesp);
        //Especie
        fpesp=fopen(diretorioEp,"a");
        for(int i=0;i<armaz_especie;i++){
            //dependencia
            enviar_dados_especie('r',i,0);
            if(qtd_enx>0){
                //fprintf(fpesp,"\n%s\n|ESPECIE: %s  |PRODUCAO: %.2f  |N_ENXAMES: %d\nDESCRICAO: %s\n%s",lin1,especie_nom,produt_espec,qtd_enx,descrit,lin1);
                fprintf(fpesp,"\n%s\n|ID: %d  |ESPECIE: %s\n|PRODUCAO: %.2f  |N_ENXAMES: %d\nDESCRICAO: %s\n%s",lin1,id_espec,especie_nom,produt_espec,qtd_enx,descrit,lin1);
            }
        }
        salvar_arquivo(nomefile,'e',diretorioEp);
        fflush(fpesp);
        fclose(fpesp);
    }
}
//ler relatorio
void ler_relatorioproducao(char nomefile[20]){//ler um relatorio de produçao
    char lin1[61];
    char lin2[61];
    char texto[61];
    char texto1[20];
    char texto2[20];
    char texto3[20];

    char diretorioP[61];
    strcpy(diretorioP,diretorio1);
    strcat(diretorioP,nomefile);
    fpprod=fopen(diretorioP,"r");
    if(fpprod==NULL){
        printf("\nFalha ao abrir arquivo");
    }else{
        //Producao total
        fscanf(fpprod,"%s\n %s \n%s\n",&lin1,&texto,&lin1);
        printf("%s\n      %s\n%s\n",lin1,texto,lin1);
        fscanf(fpprod,"%s\n%s %f %s %d\n%s\n",&lin2,&texto1,&pro_tot,&texto2,&tot_enx,&lin2);
        printf("%s\n%s %.2f %s %d\n%s\n",lin2,texto1,pro_tot,texto2,tot_enx,lin2);
        //Producao por especie
        while(!feof(fpprod)){
            fscanf(fpprod,"%s\n%s %s %s %f %s %d\n%s",&lin1,&texto1,&especie_nom,&texto2,&pro_esp,&texto3,&qtd_enx,&lin1);
            printf("%s\n%s %s %s %2.f %s %d\n%s\n",lin1,texto1,especie_nom,texto2,pro_esp,texto3,qtd_enx,lin1);
        }
        fclose(fpprod);
    }


}
void ler_relatorioenxame(char nomefile[20]){//ler um relatorio de enxames
    char lin1[61];
    char lin2[61];
    char texto[61];
    char texto1[20];
    char texto2[20];
    char texto3[20];
    char diretorioX[61];

    strcpy(diretorioX,diretorio2);
    strcat(diretorioX,nomefile);
    fpenx=fopen(diretorioX,"r");
    if(fpenx==NULL){
        printf("\nFalha ao abrir arquivo");
    }else{
        //Titulo
        fscanf(fpenx,"%s\n %s \n%s\n",&lin1,&texto,&lin1);
        printf("%s\n      %s\n%s\n",lin1,texto,lin1);
        //Enxames
        for(int i=0;!feof(fpenx);i++){
            fscanf(fpenx,"%s\n%s %d  %s %s %s %s \n",&lin2,&texto1,&id_enx,&texto2,&dat_enx,&texto3,&espec_enx);
            printf("%s\n%s %d  %s %s  %s %s \n",lin2,texto1,id_enx,texto2,dat_enx,texto3,espec_enx);
            fscanf(fpenx,"%s %f  %s %s  %s %d \n",&texto1,&pro_enx,&texto2,&sts_enx,&texto3,&id_espec_enx);
            printf("%s %.2f  %s %s  %s %d \n",texto1,pro_enx,texto2,sts_enx,texto3,id_espec_enx);
            fscanf(fpenx,"\n%s  %s \n%s\n",&texto1,&descric_enx,&lin2);
            for(int i=0;i<strlen(descric_enx);i++){
                if(descric_enx[i]=='_'){
                    descric_enx[i]=' ';
                }
            }
            printf("%s %s \n%s \n",texto1,descric_enx,lin2);

        }
         fclose(fpenx);
    }
}
void ler_relatorioespecie(char nomefile[20]){//ler um relatorio de especies
    char lin1[61];
    char lin2[61];
    char texto[61];
    char texto1[20];
    char texto2[20];
    char texto3[20];
    char texto4[20];
    char texto5[20];
    char diretorioE[61];
    strcpy(diretorioE,diretorio3);
    strcat(diretorioE,nomefile);
    fpesp=fopen(diretorioE,"r");
    if(fpesp==NULL){
        printf("\nFalha ao abrir arquivo");
    }else{
        //Titulo
        fscanf(fpesp,"%s\n %s \n%s\n",&lin1,&texto,&lin1);
        printf("%s\n  %s\n%s\n",lin1,texto,lin1);
        //Especies
        for(int i=0;!feof(fpesp);i++){
            //fscanf(fpesp,"\n%s\n%s %d  %s %s \n %s %f %s %d \n%s %s \n%s\n",&lin2,&texto1,&id_espec,&texto2,&especie_nom,&texto3,&pro_esp,&texto4,&qtd_enx,&texto5,&descrit,&lin2);
            fscanf(fpesp,"\n%s \n%s %d  %s %s\n%s %f  %s %d \n%s %s\n%s\n",&lin2,&texto1,&id_espec,&texto2,&especie_nom,&texto3,&pro_esp,&texto4,&qtd_enx,&texto5,&descrit,&lin2);
            for(int i=0;i<strlen(descrit);i++){
                if(descrit[i]=='_'){
                    descrit[i]=' ';
                }
            }
            printf("\n%s\n%s %d %s %s \n%s %.2f  %s %d \n%s %s \n%s\n",lin2,texto1,id_espec,texto2,especie_nom,texto3,pro_esp,texto4,qtd_enx,texto5,descrit,lin2);
        }
        fclose(fpesp);
    }
}
//exclusao de relatorio
void excluir_relatorio(char op,int cod){//exclui um relatorio
    char diretorioR[61];
    char nomefile[20];
    for(int i=0;i<quantidade;i++){
        if(Relat[i].cod==cod){
            strcpy(nomefile,Relat[i].nome);
        }
    }
    if(op=='p'){
        strcpy(diretorioR,diretorio1);
        strcat(diretorioR,nomefile);
    }
    if(op=='x'){
        strcpy(diretorioR,diretorio2);
        strcat(diretorioR,nomefile);
    }
    if(op=='e'){
        strcpy(diretorioR,diretorio3);
        strcat(diretorioR,nomefile);
    }
    for(int i=0;i<quantidade;i++){
        if(Relat[i].cod==cod){
            for(int j=0;j<strlen(Relat[i].nome);j++){
                Relat[i].nome[j]=NULL;
            }
            for(int j=0;j<strlen(Relat[i].diretorio);j++){
                Relat[i].diretorio[j]=NULL;
            }
            Relat[i].cod=0;
            atualizar_arquivo(op);
            remove(diretorioR);
        }
    }
   // atualizar_arquivo(op);
    //remove(diretorioR);
}
// operacoes em Arquivos
void salvar_arquivo(char nomearq[20],char op,char diretorio[61]){//salva o nome de um relatorio em um arquivo quando é gerado se for gerado com o mesmo nome não acrecentara a mais
    int igual=0;
    int cod=0;
    int cont=0;
    for(int i=0;i<quantidade;i++){
       Relat[i].cod=0;
       Relat[i].nome[0]=NULL;
    }
    acessar_bd_Arquivo(op);
    for(int i=0;i<quantidade;i++){
        if(Relat[i].cod!=0){
            cont++;
        }
    }
    for(int i=0;i<quantidade;i++){
        if(strcmp(Relat[i].nome,nomearq)==0){
                igual=1;
                break;

        }
    }
    cod=cont+1;
    if(igual==0){
        char diretorioA[61];
        strcpy(diretorioA,diretorio4);
        if(op=='p')strcat(diretorioA,"Producao");
        if(op=='x')strcat(diretorioA,"Enxame");
        if(op=='e')strcat(diretorioA,"Especie");
        fparq=fopen(diretorioA,"a");
        if(fparq==NULL){
            printf("\nFalha ao abrir arquivo");
            fclose(fparq);
            exit(1);
        }else{
            //abrindo e adicionando no arquivo
            fprintf(fparq,"%d NOME: %s    %s\n",cod,nomearq,diretorio);
            fflush(fparq);
            fclose(fparq);
        }
    }
    acessar_bd_Arquivo(op);
    atualizar_arquivo(op);

}
int exibir_arquivos(char op){//exibe o nome e codigo dos relatorios na variavel
    int t=0;
    acessar_bd_Arquivo(op);
    for(int i=0;i<quantidade;i++){
        if(Relat[i].cod!=0){
            printf("Cod:%d  Nome:%s  Diretorio:%s\n---------------------------------\n",Relat[i].cod,Relat[i].nome,Relat[i].diretorio);
            t++;
        }
    }
    if(t==0){
            printf("*Não ha relatorios");
    }
    return t;
}
void ler_arquivo(char op){//ler arquivo que contem o nome dos diretorios
    char lin2[61]="------------------------------------------------------------";
    char diretorioA[61];
    char diretorioR[61];
    char nomearq[21]={NULL};
    char texto[20]={NULL};
    int cod=0;
    tr=0;
    strcpy(diretorioA,diretorio4);
    if(op=='p')strcat(diretorioA,"Producao");
    if(op=='x')strcat(diretorioA,"Enxame");
    if(op=='e')strcat(diretorioA,"Especie");

    fparq=fopen(diretorioA,"r");
    if(fparq==NULL){
        printf("\nFalha ao acessar banco de arquivo");
    }else{
        while(!feof(fparq)){
            fscanf(fparq,"%d %s %s %s\n",&cod,&texto,&nomearq,&diretorioR);
            if(cod!=0){
                printf("\n%s\n[%d]  %s %s   %s\n%s",lin2,cod,texto,nomearq,diretorioR,lin2);
                tr++;
            }else{
                tr=0;
                printf("\n*Não ha relatorios %d",tr);
            }

        }
        fclose(fparq);
    }
}
void acessar_bd_Arquivo(char op){//acessa o banco de dados do arquivo e manda dados para a variavel
    for(int i=0;i<quantidade;i++){
        for(int j=0;j<22;j++){
            Relat[i].nome[j]=NULL;
        }
        for(int j=0;j<61;j++){
            Relat[i].diretorio[j]=NULL;
        }
        Relat[i].cod=0;
    }
    char nomearq[21];
    char diretorioR[61];
    char texto[20];
    char diretorio[61];
    int cod;
    strcpy(diretorio,diretorio4);
    if(op=='p')strcat(diretorio,"Producao");
    if(op=='x')strcat(diretorio,"Enxame");
    if(op=='e')strcat(diretorio,"Especie");

    fparq=fopen(diretorio,"r");
    if(fparq==NULL){
        printf("\nFalha ao acessar banco de arquivo");
    }else{
        //abrindo e adicionando no arquivo
        for(int i=0;!feof(fparq);i++){
            fscanf(fparq,"%d %s %s %s\n",&cod,&texto,&nomearq,&diretorioR);
            //if(nomearq[0]!=NULL&cod!=0){
                strcpy(Relat[i].nome,nomearq);
                strcpy(Relat[i].diretorio,diretorioR);
                Relat[i].cod=i+1;
           //}
            cod=0;
            nomearq[0]=NULL;
        }
        fclose(fparq);
    }
}
void atualizar_arquivo(char op){//Envia os dados da variavel de relatorios para o arquivo
    char diretorio[61];
    strcpy(diretorio,diretorio4);
    int a=0;
    if(op=='p')strcat(diretorio,"Producao");
    if(op=='x')strcat(diretorio,"Enxame");
    if(op=='e')strcat(diretorio,"Especie");

    fparq=fopen(diretorio,"w");
    if(fparq==NULL){
        printf("\nFalha ao acessar banco de arquivo");
    }else{
        //abrindo e adicionando no arquivo
        for(int i=0;i<quantidade;i++){

            if(Relat[i].cod!=0){
                a++;
                fprintf(fparq,"%d NOME: %s    %s\n",a,Relat[i].nome,Relat[i].diretorio);
            }
        }
        fflush(fparq);
        fclose(fparq);
    }

}

/////ESPECIAIS/////
//recebe/////BANCO DE DADOS/////
void receber_dados_producaoR(double prod_tot){//recebe dados da produção e adiciona a variavel
    producao_tot=0;
    producao_tot=prod_tot;
}
void receber_dados_enxameR(int id,char data[21],char especie[21],int id_especie,double producao,char status[7],char descricao[rtdec]){//recebe dados de um enxame e adiciona a variavel
    id_enx=id;
    strcpy(dat_enx,data);
    strcpy(espec_enx,especie);
    id_espec_enx=id_especie;
    prod_enx=producao;
    strcpy(sts_enx,status);
    strcpy(descric_enx,descricao);
    if(strlen(descric_enx)>1){
        for(int i=0;i<=strlen(descric_enx);i++){
            if(descric_enx[i]==' '){
                descric_enx[i]='_';
            }
        }
    }else{
        char a[21]="++++++++++++++++++++";
        strcpy(descric_enx,a);

    }

}
void receber_dados_especieR(int id_especie,char especie[21],double producao,int qtd_enxames,char info[rtif]){//recebe dados de uma especie e adiciona a variavel
    id_espec=id_especie;
    strcpy(especie_nom,especie);
    produt_espec=producao;
    qtd_enx=qtd_enxames;
    strcpy(descrit,info);
    if(strlen(descrit)>1){
        for(int i=0;i<=strlen(descrit);i++){
            if(descrit[i]==' '){
                descrit[i]='_';
            }
        }
    }else{
        char a[21]="++++++++++++++++++++";
        strcpy(descrit,a);
    }
}
/**************************************************************************/
/**************************************************************************/
