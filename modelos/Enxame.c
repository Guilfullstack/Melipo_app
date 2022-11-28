#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/**************************************************************************/
/**CONSTANTES**/
#define armazenamento_enxame 30//define a capacidade de armazenmento de enxames;
#define tdec 500//capacidade descricao do enxame
/**************************************************************************/
/**************************************************************************/
/**VARIAVEIS E COMANDOS EXTERNOS**/
extern armaz_especie;
extern receber_dados_enxameP(),receber_dados_enxameR(),receber_dados_enxameE(),receber_dados_enxameBD();
extern get_id_especie(),inicializar_especies(),enviar_dados_especie();
extern inserir_bd_enxames(),atualizar_bd_enxames();
/**************************************************************************/
/**************************************************************************/
/**VARIAVEIS**/
int total_enxames;//total de enxames cadastrados
const int armaz_enxame=armazenamento_enxame;//recebe a capacidade de armazenamento de enxames
/**************************************************************************/
/**************************************************************************/
/**ESTRUTURA**/
struct Enxames{//cria uma estrutura para armazenar informaçoes do enxame
    int id_enxame;
    char data[21];
    char especie[21];
    int  id_especie;
    double producao;
    _Bool status;
    char descricao[tdec];
}enxame[armazenamento_enxame];
/**************************************************************************/
/**************************************************************************/
/**GETERS AND SnETERS**/
int get_id_enxame(int pex){//retorna o codigo do enxame em determinada posição
    return enxame[pex].id_enxame;
}
int set_id_enxame(int id_enx){//insere um codigo na ṕosiçao determinada verificando se já nao está cadastrado e se a memoria esta vazia
    for(int i=0;i<armaz_enxame;i++){
        if(enxame[i].id_enxame!=id_enx){
            if(enxame[i].id_enxame==0){
                enxame[i].id_enxame=id_enx;
                return 1;
            }
        }else{
            return 0;
        }
    }
}
void set_data_enxame(char data[21],int p){//insere uma data ao enxame em determinada posicao
    strcpy(enxame[p].data,data);
}
int set_espec_enxame(int op,int p){//insere uma espécie em determinada posicao
    for(int i=0;i<armaz_especie;i++){
        if(op==get_id_especie(i)){
            enviar_dados_especie('x',i,p);
            return 1;
        }
    }
}
int get_idespec_enxame(int p){//retorna o id da especie no enxame em determinada posição
    return enxame[p].id_especie;
}
void add_prod_enxame(double producao,int p){//converte um valor em ml para litros e insere na produção do enxame;
    producao/=1000;
    enxame[p].producao+=producao;
}
void set_prod_enxame(double producao,int p){
    producao/=1000;
    enxame[p].producao=producao;
}
_Bool get_status_enxame(int p){//retorna o status do enxame 0fraco 1forte em determinada posição
    return enxame[p].status;
}
int set_status_enxame(int op,int p){//insere um status ao enxame o fraco 1 forte em determinada posição
    if(op==1){
        enxame[p].status=true;
        return 1;
    }else{
        if(op==2){
            enxame[p].status=false;
            return 1;
        }else{
            return 0;
        }
    }
}
void set_desc_enxame(char descricao[tdec],int p){//insere uma descrição ao enxame em determinada posicao
    strcpy(enxame[p].descricao,descricao);
}
int get_total_enxame(){//retorna o total de enxames
    int cont=0;
    for(int i=0;i<armaz_enxame;i++){
        if(get_id_enxame(i)!=0){
           cont++;
        }
    }
    total_enxames=cont;
    return total_enxames;
}
/**************************************************************************/
/**************************************************************************/
/**FUNÇOES**/
/////PRINCIPAIS/////
void info_enxame(int pex){//exibe informaçoes de um enxame em determinada posição
    if(enxame[pex].id_enxame!=0){
        printf("\n========================================");
        printf("\n|CODIGO|: %d",enxame[pex].id_enxame);
        printf("\n|DATA|: %s",enxame[pex].data);
        printf("\n|ESPECIE|: %s",enxame[pex].especie);
        if(enxame[pex].status==1){
            printf("\n|STATUS|: Forte");
        }else{
            printf("\n|STATUS|: Fraco");
        }
        printf("\n|PRODUCAO|: %.2f L",enxame[pex].producao);
        printf("\n|DESCRICAO|: %s",enxame[pex].descricao);
        printf("\n========================================");
    }
}
int excluir_enxame(int pex){//exclui um enxame em determinada posição
    if(enxame[pex].id_enxame!=0){
        enxame[pex].id_enxame=0;
        for(int i=0;i<=strlen(enxame[pex].data);i++){
            enxame[pex].data[i]=NULL;
        }
        for(int i=0;i<=strlen(enxame[pex].descricao);i++){
            enxame[pex].descricao[i]=NULL;
        }
        for(int i=0;i<=strlen(enxame[pex].especie);i++){
            enxame[pex].especie[i]=NULL;
        }
        enxame[pex].id_especie=0;
        enxame[pex].producao=0;
        enxame[pex].status=false;
        atualizar_bd_enxames();
        return 1;
    }else{
        return 0;
    }

}
void desempenho_enxame(double media){//exibe o desempenho de enxames( mais produtivo menos produtivo),abaixo e acima da média
    double maior;
    double menor;
    int pmaior,pmenor;
    int idmaior,idmenor;
    //mais produtivo,menos produtivo
    for(int i=0;i<armaz_enxame;i++){
        if(enxame[i].id_enxame!=0){
            if(maior<enxame[i].producao){
                maior=enxame[i].producao;
                idmaior=enxame[i].id_enxame;
            }else{
                menor=enxame[i].producao;
                idmenor=enxame[i].id_enxame;
            }
        }
    }

    printf("#############|  DENSENPENHO DE ENXAMES |###############");
    printf("\n=====================================================");
    printf("\n=Enxame + produtivo|Codigo [%d] |Producao=%.2f|",idmaior,maior);
    printf("\n=Enxame - produtivo|Codigo [%d] |Producao=%.2f|",idmenor,menor);
    printf("\n=====================================================");
    //Acima da media
    printf("\n-----------------------------------------------------");
    printf("\n= = = = = = = = = =ACIMA DA MEDIA= = = = = = = = = =");
    printf("\n-----------------------------------------------------");
    for(int i=0;i<armaz_enxame;i++){
        if(enxame[i].id_enxame!=0){
            if(enxame[i].producao>=media){
                printf("\n|Codigo [%d] |Producao=%.2f |Especie: %s|",enxame[i].id_enxame,enxame[i].producao,enxame[i].especie);
                printf("\n-----------------------------------------------------");
            }
        }
    }
    //Abaixo da media
    printf("\n-----------------------------------------------------");
    printf("\n= = = = = = = = = =ABAIXO DA MEDIA= = = = = = = = = =");
    printf("\n-----------------------------------------------------");
    for(int i=0;i<armaz_enxame;i++){
        if(enxame[i].id_enxame!=0){
            if(enxame[i].producao<media){
                printf("\n|Codigo [%d] |Producao=%.2f |Especie: %s|",enxame[i].id_enxame,enxame[i].producao,enxame[i].especie);
                printf("\n-----------------------------------------------------");
            }
        }
    }

}

/////SECUNDARIAS/////
int posicao_enxame(int id){//verifica e retorna a posição de um determinado codigo na estrutura de enxames
    for(int i=0;i<armaz_enxame;i++){
        if(id!=0){
            if(id==enxame[i].id_enxame){
                return i;
            }
        }
    }
}
int verificar_cod(int id){//verifica se o codigo está cadastrado
        for(int i=0;i<armaz_enxame;i++){
        if(id!=0){
            if(id==enxame[i].id_enxame){
                return 1;
            }
        }
    }
}
int limite_cadastro(){//verifica se tem espaço para cadastrar mais enxames
        int a=0;
        for(int i=0;i<armaz_enxame;i++){
            if(enxame[i].id_enxame==0){
                a++;
            }
        }
        return a;
}

/////ESPECIAIS/////
void enviar_dados_enxame(char op,int pex,int pe){//envia por parametro dados de um enxame em determinada posição para variaveis em outro arquivo
    if(op=='p')receber_dados_enxameP(enxame[pex].producao);//producao
    if(op=='e')receber_dados_enxameE(enxame[pex].producao,pe);//especie
    if(op=='r'){//relatorio
        //get_total_enxame();
        if(enxame[pex].status==true){
            receber_dados_enxameR(enxame[pex].id_enxame,enxame[pex].data,enxame[pex].especie,enxame[pex].id_especie,enxame[pex].producao,"forte",enxame[pex].descricao);
        }else{
            receber_dados_enxameR(enxame[pex].id_enxame,enxame[pex].data,enxame[pex].especie,enxame[pex].id_especie,enxame[pex].producao,"fraco",enxame[pex].descricao);
        }
    }
    if(op=='b'){//banco de dados
        get_total_enxame();
        receber_dados_enxameBD(enxame[pex].id_enxame,enxame[pex].data,enxame[pex].especie,enxame[pex].id_especie,enxame[pex].producao,enxame[pex].status,enxame[pex].descricao);
    }
}
void receber_dados_especieEx(int id_espc,char especie[21],int pex){//Recebe por parametro dados de uma especie e adiciona a um enxame em determinada posição
    strcpy(enxame[pex].especie,especie);
    enxame[pex].id_especie=id_espc;
}

/////BANCO DE DADOS/////
void salvar_dados_enxame(int pex){//Envia os dados de um enxame em determinada posicao para o banco de dados
   inserir_bd_enxames(enxame[pex].id_enxame,enxame[pex].data,enxame[pex].especie,enxame[pex].producao,enxame[pex].status,enxame[pex].id_especie,enxame[pex].descricao);
}
void receber_bd_enxames(int pex,int id_enxame,char data[21],char especie[21],int id_especie,double producao,_Bool status,char descricao[tdec]){//recebe dados do BD e adiciona no enxame em determida posicao
    enxame[pex].id_enxame=id_enxame;
    strcpy(enxame[pex].data,data);
    strcpy(enxame[pex].especie,especie);
    enxame[pex].id_especie=id_especie;
    enxame[pex].producao=producao;
    enxame[pex].status=status;
    strcpy(enxame[pex].descricao,descricao);
}
/**************************************************************************/
/**************************************************************************/
