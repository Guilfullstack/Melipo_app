#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/**************************************************************************/
/**CONSTANTES**/
#define armazenamento_especie 20//define a capacidade de armazenmento de especies;
#define tif 1000//tamanho de armazenamento informacao
const int armaz_especie=armazenamento_especie;//recebe a capacidade de armazenamento de especies
/**************************************************************************/
/**************************************************************************/
/**VARIAVEIS E COMANDOS EXTERNOS**/
extern armaz_enxame;
extern enviar_dados_enxame();
extern receber_dados_especieEx(),receber_dados_especieR(),receber_dados_especieP(),receber_dados_especieBD();
extern get_id_enxame(),get_idespec_enxame();
extern inserir_bd_especie(),atualizar_bd_especies();
/**************************************************************************/
/**************************************************************************/
/**ESTRUTURA**/
struct Especie{//estrutura para armazenar informaçoes das opçoes de especies predefinidas
    int id_especie;
    char nome[21];
    double producao;
    int qtd_enxames;
    char informacao[tif];
}especie[armazenamento_especie];
/**************************************************************************/
/**************************************************************************/
/**GETERS AND SnETERS**/
int get_id_especie(int pe){//retorna o nomero da minha especie predefinida em determinada posição
    return especie[pe].id_especie;
}
int get_Qenx_especie(int pe){//retorna a quantidade de enxames em uma especie
    return especie[pe].qtd_enxames;
}
set_Info_especie(int pe,char info[tif]){//insere uma descricao a especie
    strcpy(especie[pe].informacao,info);
}
set_prod_especie(double product,int pe){//insere um valor a producao da especie
    especie[pe].producao=product;
}
set_id_especie(int pe){
    especie[pe].id_especie=0;
}
/**************************************************************************/
/**************************************************************************/
/**FUNÇOES**/
/////PRINCIPAIS/////
void resetar_especies(){//Reseta as especies para forma padrão
    for(int i=0;i<armaz_especie;i++){
        excluir_especie(i);
    }
    strcpy(especie[0].nome,"Jatai");
    especie[0].id_especie=1;

    set_Info_especie(0,"A Jataí(Tetragonisca angustula) possui cor amarelo-ouro e tem corbículas pretas (aparelho coletor onde o pólen é recolhido).\
Também não possui ferrão. É uma abelha muito mansa, no máximo, dá uns pequenos beliscões ou gruda cerume nos intrusos quando se sente ameaçada.\
Essa característica permite que ela seja criada perto de casa, de pessoas e animais sem oferecer riscos de ataques.");
    especie[0].qtd_enxames=0;
    especie[0].producao=0.0;

    strcpy(especie[1].nome,"Irai");
    especie[1].id_especie=2;
    set_Info_especie(1,"A abelha Irai (Nannotrigona testaceicornes) mede em torno de 4 mm de comprimento, é preta, possuindo pilosidade grisalha\
e asas esfumaçadas no terço apical (ponta das asas). Tem população considerada mediana, com colônias contendo entre 2.000 e 3.000 elementos.");
    especie[1].qtd_enxames=0;
    especie[1].producao=0.0;

    strcpy(especie[2].nome,"Jatai_da_terra");
    especie[2].id_especie=3;
    set_Info_especie(2,"Jataí-da-Terra (Paratrigona subnuda) é popularmente conhecida como Jataí-da-Terra ou Mirim-sem-Brilho.\
 É uma espécie muito mansa, de fácil manejo, frequentemente encontrada nas flores.\
 Constrói seu ninho subterrâneo, ocupando panelas abandonadas de saúvas, cujos ninhos foram destruídos.\
 Para localizar o ninho no solo, é preciso cavar cuidadosamente seguindo o tubo de entrada.\
 As rainhas virgens andam livremente pela colmeia, sendo encontradas ocasionalmente em repouso nos potes de alimento vazios.\
 Já os machos formam grupos dentro da colmeia, muitas vezes, junto ao depósito de detritos da colônia.\
 Esta espécie possui a cabeça negra e o corpo alaranjado, com asas maiores que a extensão corporal, o que é comum nas meliponas.");
    especie[2].qtd_enxames=0;
    especie[2].producao=0.0;

    strcpy(especie[3].nome,"Moca_branca");
    especie[3].id_especie=4;
    set_Info_especie(3,"Abelha Moça branca (Frieseomelitta doederleini) A Abelha Moça Branca tem como localidade típica o bioma Caatinga.\
 Apontada como espécie endêmica do Nordeste.A moça branca se caracteriza pelo seu pequeno porte, cabeça preta, tórax, abdômen e pernas paracentas.\
 Produz mel claro, de aroma suave e muito valorizado.\
 Abelha que tolera a seca, produz mel a partir das flores do umbu, umburana, espécies que florescem no período mais seco da região.");
    especie[3].qtd_enxames=0;
    especie[3].producao=0.0;

    strcpy(especie[4].nome,"Mirim_Droryana");
    especie[4].id_especie=5;
    set_Info_especie(4,"Mirim Droryana (Plebeia droryana) Abelha rústica e resistente, a Plebeia droryana é uma abelha social, pertencente à subfamília dos meliponíneos.\
 É conhecida popularmente como Mirim Droryana, Abelha-Mosquito, Jataí-Mosquito, Jataí-Preta, Jati e Jati-preta.\
 É pequena e mansa. Possui uma mancha amarela em forma de gota, na frente da cabeça, já o seu corpo é escuro.\
 Nidifica em fendas de árvores ocas e buracos nas rochas ou muros, desde que os ocos ou fendas sejam de tamanho apropriado e não aquecidos pelo sol em demasia.\
 A espécie possui coloração escura, com desenhos amarelos na cabeça, e cerca de 3 mm de comprimento.\ ");
    especie[4].qtd_enxames=0;
    especie[4].producao=0.0;

    strcpy(especie[5].nome,"Mandacaia");
    especie[5].id_especie=6;
    set_Info_especie(5,"Mandaçaia (Melipona mandacaia)  Mandaçaia é uma palavra indígena que significa “vigia bonito” (mandá:vigia/çai:bonito),\
fato este por se observar no orifício de entrada da colmeia uma abelha sempre presente, ou seja, a vigia.\
 É uma abelha de cor negra, tendo em seu abdômen quatro listras amarelas brilhantes transversais nos tergitos, placa dorsal dos segmentos do corpo dos artrópodes.\
 A região entre as antenas, geralmente possui pelos negros. Na parte inferior da face, possui uma pontuação muito fraca.\
 O ventre e a porção mediana superior do tórax são menos lustrosos na base do que no ápice. É uma abelha robusta que mede entre 8 a 12 mm.");
    especie[5].qtd_enxames=0;
    especie[5].producao=0.0;

    strcpy(especie[6].nome,"Manduri");
    especie[6].id_especie=7;
    set_Info_especie(6,"Manduri (Melipona marginata) A Melipona marginata é uma abelha social indígena do gênero Melipona, da subfamília dos meliponíneos.\
 Essa espécie também é conhecida pelos nomes de Guarapu-Miúdo, Taipeira, Tiúba-Preta e Uruçu-Mirim. Nidifica em ocos de árvore, ou em paredões de taipa.\
 No entanto, adapta-se bem em caixas racionais. A Manduri é bastante agressiva e tem mandíbulas bem fortes. Seu ataque é intenso, mordiscando a vítima incansavelmente.\
 Mas o ataque só ocorre se a abelha se sentir ameaçada.A Manduri é uma abelha social indígena, de 6 a 7 mm de comprimento, com a coloração negra, provida de pelos grisalhos,\
com faixas amarelas onduladas no abdome.");
    especie[6].qtd_enxames=0;
    especie[6].producao=0.0;

    strcpy(especie[7].nome,"Marmelada_Amarela");
    especie[7].id_especie=8;
    set_Info_especie(7,"Marmelada Amarela (Frieseomelitta varia) A abelha Marmelada Amarela é bastante agressiva, quando ameaçada, mas, após algum tempo, geralmente se acalma.\
 Ela se defende depositando pelotas de própolis pegajoso sobre quem a importuna.É uma abelha que pode roubar o pólen de outras espécies.\
 Sua colmeia é coberta com própolis depositado pela própria abelha. A cria é produzida em células que encostam levemente umas nas outras ou são ligadas por um cabo pequeno de cerume, formando grupos parecidos com cachos.\
 Há células reais, inclusive formadas a partir de células comuns, na ausência da rainha.");
    especie[7].qtd_enxames=0;
    especie[7].producao=0.0;

    strcpy(especie[8].nome,"Tubuna");
    especie[8].id_especie=9;
    set_Info_especie(8,"Tubuna (Scaptotrigona bipunctata) A abelha Tubuna, também conhecida como Mandaguari Tubuna, pertence ao grupo das Trigonas (sem ferrão).\
 É uma abelha bastante agressiva que, ao ser ameaçada, solta um grude, principalmente nos cabelos, além de mordiscar a vítima com suas mandíbulas.\
 Pode viajar mais de 1 km à procura de uma nova morada: caixas de madeira velha, ocos em arvore e muros. Essa espécie concentra  suas atividades pela manhã, evitando forragear nas horas mais quentes do dia.\
 Seu ninho tem o formato da entrada como um tubo, um funil ou uma trombeta.Essa espécie possui coloração negra e brilhante, com as asas bem negras, ou fumadas, e o abdômen negro, com 2 pontos na cor prata (ou 1 listra prata).");
    especie[8].qtd_enxames=0;
    especie[8].producao=0.0;

    strcpy(especie[9].nome,"Urucu");
    especie[9].id_especie=10;
    set_Info_especie(9,"Uruçu (Melipona scutellaris) Uruçu é uma palavra que vem do tupi “eiru su”, que nessa língua indígena significa “abelha grande”.\
 Essa nomenclatura está relacionada com diversas abelhas do mesmo gênero, encontradas não só no Nordeste, mas também na região Norte.\
 A Uruçu possui corpo robusto (marrom e preto), vértice marrom-amarelado, com pelos abundantes amarelo-ruivos, frequentemente com alguns mais claros, cor de ouro.\
 O clípeo, estrutura da cabeça que liga as peças bucais, é levemente convexo, e a face, relativamente estreita. Seu tórax é preto no dorso, com pelos densos e amarelo-dourados, e face ventral, com fina penugem acinzentada.\
 O comprimento das operárias é de 10 a 12 mm. A Uruçu possui abdômen escuro, com cinco listras claras.");
    especie[9].qtd_enxames=0;
    especie[9].producao=0.0;

    strcpy(especie[10].nome,"Urucu_Amarela");
    especie[10].id_especie=11;
    set_Info_especie(10," Melipona rufiventris é uma abelha social brasileira, da tribo dos meliponíneos.\
 É conhecida popularmente como Uruçu-Amarela, Tujuba, Tujuva, Tiúba, Tiúva e Teúba. Vive em colônias grandes, sendo pouco agressiva, cujo comportamento defensivo é beliscar a pele.\
 A sua raridade, tanto na natureza quanto na meliponicultura racional, eleva os custos de aquisição de novas matrizes, mas, mesmo assim, é uma das espécies viáveis com grandes possibilidades,\
 principalmente para divulgação da atividade, pois sua beleza chama muito atenção.\
 Essa espécie apresenta o tegumento com a coloração variando do negro ao ferrugíneo, com o corpo coberto de pelos ferrugíneos/amarelados.");
    especie[10].qtd_enxames=0;
    especie[10].producao=0.0;
//////////////
//atualizar_Especies();
atualizar_bd_especies();
}
void exibir_especie(int pe){//exibe as opçoes de especie
    if(especie[pe].id_especie!=0&&especie[pe].nome[0]!=NULL){
        printf("\n[%d]-%s",especie[pe].id_especie,especie[pe].nome);
    }
}
void info_especie(int pe){//exibe as informacoes das especies cadastradas
    char lin1[61]="============================================================";
    if(especie[pe].id_especie!=0){
        printf("\n%s\n|ID: %d  |ESPECIE: %s\n|PRODUCAO: %.2f  |N_ENXAMES: %d\nDESCRICAO:\n%s\n%s",lin1,especie[pe].id_especie,especie[pe].nome,especie[pe].producao,especie[pe].qtd_enxames,especie[pe].informacao,lin1);
    }
}
int atualizar_Especies(){//Atualiza a quantidade de enxames e a producao de uma especie
    for(int i=0;i<armaz_especie;i++){
        especie[i].producao=0;
        int cont_nex=0;
        for(int j=0;j<armaz_enxame;j++){
            if(get_id_enxame(j)!=0){
                if(get_idespec_enxame(j)==especie[i].id_especie){
                    enviar_dados_enxame('e',j,i);
                    cont_nex++;
                }
            }
        }
        especie[i].qtd_enxames=cont_nex;
    }
    return 1;
}
void cad_especie(int cod,char nome[21],char informacao[tif]){//Cadastra uma nova espécie no sistema
    for(int i=0;i<=armaz_especie;i++){
        if(especie[i].id_especie!=cod){
            if(especie[i].id_especie==0){
                especie[i].id_especie=cod;
                strcpy(especie[i].nome,nome);
                strcpy(especie[i].informacao,informacao);
                especie[i].producao=0.0;
                especie[i].qtd_enxames=0;
                salvar_dados_especie(i);
                info_especie(i);
                break;
            }
        }
    }
}
void excluir_especie(int pe){//exclui uma espécie em determinada posicao

        especie[pe].id_especie=0;
        especie[pe].qtd_enxames=0;
        especie[pe].producao=0;
        for(int i=0;i<21;i++){
            especie[pe].nome[i]=NULL;
        }
        for(int i=0;i<tif;i++){
            especie[pe].informacao[i]=NULL;
        }
        atualizar_bd_especies();
}

/////SECUNDARIAS/////
int tot_esp(){//Verifica o total de especies cadastradas
    int tot=0;
    for(int i=0;i<armaz_especie;i++){
        if(get_id_especie(i)!=0){
          tot++;
        }
    }
    return tot;
}
int posicao_especie(int cod){//retorna a posicao de uma especie atraves do codigo
    for(int i=0;i<armaz_especie;i++){
        if(especie[i].id_especie==cod){
            return i;
        }
    }
}
int limite_cad_esp(){//verifica se tem espaço para cadastrar mais enxames
        int a=0;
        for(int i=0;i<armaz_especie;i++){
            if(especie[i].id_especie==0){
                a++;
            }
        }
        return a;
}
int verificar_cod_esp(int id){//verifica se o codigo está cadastrado
    for(int i=0;i<armaz_especie;i++){
        if(id!=0){
            if(id==especie[i].id_especie){
               return 1;
            }
        }
    }
}

/////ESPECIAIS/////
//enviar
void enviar_dados_especie(char op,int pe,int pex){//envia por parametro dados de uma especie em determinada posição para variaveis em outro arquivo
    if(op=='x')receber_dados_especieEx(especie[pe].id_especie,especie[pe].nome,pex);
    if(op=='r'){
        receber_dados_especieR(especie[pe].id_especie,especie[pe].nome,especie[pe].producao,especie[pe].qtd_enxames,especie[pe].informacao);
    }
    if(op=='p'){
        receber_dados_especieP(especie[pe].producao,pe);
    }
    if(op=='b'){
        receber_dados_especieBD(especie[pe].id_especie,especie[pe].nome,especie[pe].producao,especie[pe].qtd_enxames,especie[pe].informacao);
    }
}
//receber
void receber_dados_enxameE(double producao,int pe){//recebe um valor da produção de um enxame e adiciona a variavel producao da especie em uma determinada posicao
    especie[pe].producao+=producao;
}

/////BANCO DE DADOS/////
void receber_bd_especie(int pe,int id_especie,char nome[21],double producao,int qtd_enxames,char informacao[tif]){//recebe dados do BD e adiciona a especie em determida posicao
    especie[pe].id_especie=id_especie;
    strcpy(especie[pe].nome,nome);
    especie[pe].producao=producao;
    especie[pe].qtd_enxames=qtd_enxames;
    strcpy(especie[pe].informacao,informacao);
}
void salvar_dados_especie(int pe){//Envia dados de uma espécie ao banco de dados
    inserir_bd_especie(especie[pe].id_especie,especie[pe].nome,especie[pe].producao,especie[pe].qtd_enxames,especie[pe].informacao);
}
/**************************************************************************/
/**************************************************************************/
