#include <stdio.h>
#include <stdlib.h>
/**************************************************************************/
/**CONSTANTES**/
#define arm 20
/**************************************************************************/
/**************************************************************************/
/**VARIAVEIS E COMANDOS EXTERNOS**/
extern armaz_enxame,armaz_especie;
extern get_id_enxame(),get_idespec_enxame();
extern atualizar_Especies();;
extern enviar_dados_enxame(),enviar_dados_especie();
extern receber_dados_producaoR();
/**************************************************************************/
/**************************************************************************/
/**VARIAEIS**/
double prod_Total;//Armazena o valor total de produção
double prod_Especie[arm];//Armazena a produção de espécies em um vetor
//Auxiliar
double produc;//variavel auxiliar de valor estavel
/**************************************************************************/
/**************************************************************************/
/**FUNCOES**/
/////PRINCIPAIS/////
void atualizar_producaoTot(){//Atualiza o total de produção somando o valor de cada enxame
    prod_Total=0;
    for(int i=0;i<armaz_enxame;i++){
        if(get_id_enxame(i)!=0){
            enviar_dados_enxame('p',i,0);
            prod_Total+=produc;
        }
    }
}
void exibir_prod_especie(){//Atualiza e exibe a produção por espécie
    atualizar_Especies();
    for(int i=0;i<armaz_especie;i++){
        if(get_id_especie(i)!=0){
            enviar_dados_especie('p',i,0);
            exibir_especie(i);
            printf("|=> Total: %.2f",prod_Especie[i]);
            printf("\n===================================");
        }
    }
}
void exibir_producaoTot(){//retorna a produção total
    atualizar_producaoTot();
    printf("%.2f L",prod_Total);
}
void renovar_producao(){
    prod_Total=0;
    for(int i=0;i<arm;i++){
        prod_Especie[i]=0;
    }
    for(int i=0;i<armaz_enxame;i++){
      if(get_id_enxame(i)!=0){
            set_prod_enxame(0.0,i);
        }
    }
    atualizar_Especies();
}

/////ESPECIAIS/////
//recebe
void receber_dados_enxameP(double producao){//recebe dados da produção de um enxame e adiciona a variavel auxiliar
    produc=producao;
}
void receber_dados_especieP(double producao,int pe){//recebe dados da produção das especies e adiciona a variavel
    prod_Especie[pe]=producao;
}
//envia
void enviar_dados_producao(char op){//envia por parametro dados da producao para variaveis em outro arquivo
    atualizar_producaoTot();
    if(op=='r')receber_dados_producaoR(prod_Total);//relarorio
}
/**************************************************************************/
/**************************************************************************/
