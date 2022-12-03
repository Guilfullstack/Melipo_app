#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/***********************************************************************************/
/***********************************************************************************/
/**VARIAVEIS E COMANDOS EXTERNOS**/
/////Usuario/////
extern getuser_status(),getuser_logado();//gets
extern cad_user(),logar(),log_of(),excluir_conta(),to_String();//principais
extern tam_nome(),alt_usernome(),alt_usersenha();//secundarias
/////Enxames/////
extern total_enxames,armaz_enxame;//variaveis e  constantes
extern get_id_enxame(),get_total_enxame();//get
extern set_id_enxame(),set_data_enxame(),set_espec_enxame(),set_status_enxame(),set_desc_enxame(),set_prod_enxame();//set
extern excluir_enxame(),info_enxame(),desempenho_enxame();// principais
extern limite_cadastro(),posicao_enxame(),verificar_cod();// secundarias
extern salvar_dados_enxame();//bd
/////Especie/////
extern armaz_especie;//constant
extern atualizar_Especies(),exibir_especie(),resetar_especies(),info_especie(),cad_especie(),excluir_especie();//principais
extern limite_cad_esp(),tot_esp(),posicao_especie(),verificar_cod_esp();//secundarias
/////Producao/////
extern prod_Total;//Variaveis
extern atualizar_producaoTot(),exibir_prod_especie(),exibir_producaoTot(),renovar_producao();//principais
/////Relatorio/////
extern gerar_relatorioproducao(),gerar_relatorioenxame(),gerar_relatorioespecies(),excluir_relatorio();//escrita
extern ler_relatorioproducao(),ler_relatorioenxame(),ler_relatorioespecie();//leitura
extern salvar_arquivo(),ler_arquivo(),acessar_bd_Arquivo(),atualizar_arquivo(),exibir_arquivos();//operacoes em arquivos
/////TAREFAS/////
extern criar_tarefa(),excluir_tarefa(),exibir_tarefas();//principais
extern posicao_tarefa(),tot_taref();
/////Banco de dados/////
extern acessar_bd_usuario(),acessar_bd_enxames(),acessar_bd_especies(),acessar_bd_tarefa(),acessar_bd_Arquivo();
extern atualizar_bd_enxames(),atualizar_bd_especies(),atualizar_bd_tarefas();
/***********************************************************************************/
/***********************************************************************************/
/**FUNÇOES**/
void painel(){//exibi o nome do Sistema
    char nome_app[30]="MELIPO_APP [=|=] ";
    printf("\n=============================\
    \n===|  %s  |===\
    \n=============================",nome_app);
}
void delay(char del[21],int p){// delay a etapas de processo
    int tempo;
    if(p==2){
        tempo=100000000;
    }
    if(p==3){
        tempo=100000000;
    }
    if(p==4){
        tempo=100000000;
    }
    printf("%s\n",del);
    printf("-------------------------------\n");
    for(int l=1;l<=p;l++){
        for(int c=1;c<=3;c++){
            printf("...=|=...  ");
            for(int i=0;i<=tempo;i++){
            }
        }
        printf("\n");
    }
    printf("-------------------------------");
}
void linha(int t){//exibir determinada formatação de linha
    if(t==1) printf("----------------------------");
    if(t==2) printf("\n----------------------------");
    if(t==3) printf("----------------------------\n");
    if(t==4) printf("\n----------------------------\n");
    if(t==5) printf("\n+++++++++++++++++++++++++++++\n");
}
void pros(){//interromper continuação de determinado processo até que seja informado
    printf("\nContinuar[Enter]= ");
    char c;
    //scanf("%c",c);
    while(c!='\n'){
        setbuf(stdin,NULL);
        char t=getchar();
        c=t;
    }
    printf("----------------------------");
}
void info_geral(){
    printf("\nºººººººººººººººººººººººººººººººººººººº");
    printf("\n||Especies: %d ||Enxames: %d \n||Tarefas: %d  ||Producao: ",tot_esp(),get_total_enxame(),tot_taref());
    exibir_producaoTot();
    printf("\nºººººººººººººººººººººººººººººººººººººº");

}
/**************************************************************************/
/**CONSTANTES**/
#define mtdec 500//capacida de armazenameto de descricao enxame
#define mtif 800//capacida de armazenameto de descricao especie
#define mtdc 500//capacida de armazenameto de descricao tarefa
/***********************************************************************************/
/***********************************************************************************/
/**FUNCAO PRINCIPAL**/
int main(){
    //dependencia
    acessar_bd_usuario();
    //Variaveis
    int op=0,resp=0;
    char nome[11];
    int senha=0;
    int escl=0;
//////////////////////////////////////////////////////////////////////////////////////
/////Primeiro bloco/////
printf("=======================================================================");
printf("\n####    #### ####### ##     ##     ## ######### #########      \\/   ");
printf("\n## ##  ## ## ##      ##     ##     ## ######### #########      00    ");
printf("\n##  ###   ## ####### ##     ##     ## ##     ## ##     ##  ====##====");
printf("\n##        ## ####### ##     ##     ## ######### ##     ##  ====##====");
printf("\n##        ## ##      ##     ##     ## ##        #########      ##    ");
printf("\n##        ## ####### ###### ###### ## ##        #########  ----------");
printf("\n===================================================================\n");
delay("iniciando...",2);
//primeiro menu inicio do programa
   do{
        painel();
        printf("\nBEM VINDO!\nDIGITE UMA OPCAO!");
        printf("\n1- LOGAR \
                \n2- CADASTRAR \
                \n3- SAIR \
                \n=");
        setbuf(stdin,NULL);
        scanf("%i",&op);
        linha(3);
        switch (op){
            //Logar
            case 1:
                delay("carregando...",2);
                linha(2);
                printf("\nDigite o seu nome de usuario!\n=");
                setbuf(stdin,NULL);
                gets(nome);
                printf("Digite a sua senha!\n=");
                setbuf(stdin,NULL);
                scanf("%d",&senha);
                linha(3);
                printf("verificando...");
                linha(4);
                resp=logar(nome,senha);
                if(getuser_logado()==1){
                   printf("Login confirmado!...");
                }else{
                    if(resp=='n'){
                        printf("=>Nome de usuario incorreto!\nTente novamente!");
                    }
                    if(resp=='s'){
                        printf("=>Senha incorreta!\nTente novamente!");
                    }
                }
                linha(4);
            break;
            //cadastro
            case 2:
                printf("Esse programa suporta somente um usuario por vez\n se caso ja tenha um cadastro todos os dados anteriores\
            \nserao apagados! Deseja continuar?\
            \n1-sim\
            \n2-nao\n=");
                scanf("%d",&escl);
                if(escl==1){
                    excluir_conta();
                    delay("carregando...",2);
                    linha(2);
                    printf("\nDigite um nome de usuario!\n=");
                    setbuf(stdin,NULL);
                    gets(nome);
                    printf("Digite uma senha numerica!\n=");
                    setbuf(stdin,NULL);
                    scanf("%d",&senha);
                    cad_user(nome,senha);
                    linha(1);
                    printf("\nCadastrado com sucesso!\n");
                    to_String();
                    linha(4);
                }else{
                    linha(1);
                    escl=0;
                }

            break;
            //Sair
            case 3:
                log_of();
                delay("saindo...",2);
                linha(2);
            break;
            //Erro
            default:
                printf("\n=>Opcao invalida tente novamente!");
            break;
        }
    }while(op!=3&getuser_logado()==false);

////////////////////////////////////////////////////////////////////////////////////////////////////
/////Segundo bloco/////
getuser_status();
    //menu principal
    if(getuser_logado()==true){//verifica se o usuário esta logado
        acessar_bd_especies();
        acessar_bd_enxames();
        acessar_bd_tarefa();
        delay("Acessando o Sistema...",3);
        while(getuser_status()==true & getuser_logado()==true){//verifica o status da conta e se o usuario esta logado
            painel();
            info_geral();
            printf("\nO QUE DESEJA FAZER?\n");
            printf("1- PERFIL \
                   \n2- ENXAMES \
                   \n3- ESPPECIES \
                   \n4- TAREFAS \
                   \n5- PRODUCAO\
                   \n6- RELATORIOS \
                   \n7- ENCERRAR\n=");
            setbuf(stdin,NULL);
            scanf("%d",&op);
            linha(1);
            if(op==1|op==2|op==3|op==4|op==5|op==6){
                delay("",2);
            }
            switch (op){
            //perfil
            case 1:
                painel();
                //printf("\n********|  PERFIL  |********");
                menuperfil();
            break;
            //enxame
            case 2:
                painel();
                //printf("\n********|  ENXAMES  |********");
                menuenxames();
            break;
            //especie
            case 3:
                painel();
                //printf("\n********|  ESPECIES  |********");
                menuespecies();
            break;
            //tarefas
            case 4:
                painel();
                //printf("\n********|  TAREFAS  |********");
                menutarefas();
            break;
            //produçao
            case 5:
                painel();
                //printf("\n********|  PRODUCAO  |********");
                menuproducao();
            break;
            //relatorios
            case 6:
                painel();
                //printf("\n********|  RELATORIOS  |********");
                menurelatorios();
            break;
            //sair
            case 7:
                atualizar_bd_enxames();
                atualizar_bd_especies();
                atualizar_bd_tarefas();
                delay("\nencerrando..",3);
                log_of();
            break;
            default:
                printf("\n=>Opcao invalida tente novamente!\n");
                linha(1);
            break;
            }
        }
    }

    return 0;
}

/***********************************************************************************/
/***********************************************************************************/
/***********************************************************************************/
/** MENUS**/
/////menu perfil/////
void menuperfil(){
    int op;
    int esc;
    do{
        linha(2);
        printf("\n********|  PERFIL  |********");
        linha(2);
        printf("\nO QUE DESEJA FAZER?!");
        printf("\n1-Exibir meus dados\
        \n2-Alterar login\
        \n3-Excluir conta\
        \n4-Sair\n=");
        setbuf(stdin,NULL);
        scanf("%d",&op);
        linha(1);
        if(op==1|op==2|op==3){
            delay("",2);
        }
        switch(op){
            //informaçoes do usuario
            case 1:
                linha(5);
                printf("##|  Dados do usuário  |##");
                linha(5);
                linha(3);
                to_String();
                linha(2);
                pros();
            break;
            case 2:
            //alterar login
                do{
                    linha(5);
                    printf("##|  Alterar login  |##");
                    linha(5);
                    linha(3);
                    to_String();
                    linha(2);
                    printf("\nO que deseja alterar? \
                    \n1-Usuario \
                    \n2-Senha \
                    \n3-Sair\n=");
                    setbuf(stdin,NULL);
                    scanf("%d",&esc);
                    linha(1);
                    //usuario
                    if(esc==1){
                        char nome[11];
                        int resp;
                        printf("\nEscolha um novo nome de usuario\n=");
                        setbuf(stdin,NULL);
                        gets(nome);
                        linha(1);
                        resp=alt_usernome(nome);
                        if(resp==1){
                            printf("\nNome de usuario modificado com sucesso!");
                        }else{
                            printf("\n=>Operacao nao concluida\nDigite um usuario diferente!");
                        }
                        linha(2);
                    }else{
                        //senha
                        if(esc==2){
                            int senha;
                            int s;
                            printf("\nEscolha uma nova senha!\n=");
                            setbuf(stdin,NULL);
                            scanf("%d",&senha);
                            linha(1);
                            s=alt_usersenha(senha);
                            if(s==1){
                            printf("\nSenha modificada com sucesso!");
                            }else{
                            printf("\n=>Operacao nao concluida\nDigite uma senha diferente!");
                            }
                            linha(2);
                        }else{
                            //sair
                            if(esc==3){

                            }else{//erro
                                printf("\n=>Opcao invalida!Tente novamente");
                                linha(2);
                            }
                        }
                    }
                }while(esc!=3);
            break;
            //excluir conta
            case 3:
                linha(5);
                printf("##|  Excluir conta  |##");
                linha(5);
                printf("A exclusão da sua conta removera\
                 \no seu acesso ao sistema tabem serao apagadas\
                \ntodas as informacao relacionada a este usuario!\
                 \nTem certeza que quer continuar essa operacao?[s/n]\n=");
                char opx;
                setbuf(stdin,NULL);
                scanf("%s",&opx);
                linha(3);
                if(opx=='s'){
                    delay("removendo conta...",4);
                    excluir_conta();
                    printf("\nOperacao concluida...\nConta excluida com sucesso!");
                }else{
                    if(opx=='n'){
                        printf("Operacao cancelada!...");
                    }else{
                        printf("=>Opcao invalida tente novamente!");
                    }
                }
                linha(2);
            break;
            //sair
            case 4:
            break;
            //erro
            default:
                printf("\n=>Opcao invalida tente novamente");
            break;
        }
    }while(op!=4&&getuser_status()==1);
}
/***********************************************************************************/
/***********************************************************************************/

/////menu de enxames/////
void menuenxames(){
    int codigo,status,especie;
    char data[21],descricao[mtdec],especi_e[21];
    float producao;
    int op=0,qtd=0,posicao=0,resp=0,esc=0;
    do{
        linha(2);
        printf("\n********|  ENXAMES  |********");
        linha(2);
        printf("\nO QUE DESEJA FAZER?!");
        printf("\n1-Cadastrar enxame\
        \n2-Alterar informacoes\
        \n3-Exibir enxame\
        \n4-Excluir enxame\
        \n5-Relacao de enxames\
        \n6-Sair\n=");
        setbuf(stdin,NULL);
        scanf("%d",&op);
        linha(1);
        if(op==1|op==2|op==3|op==4|op==5){
            delay("",2);
        }
        switch(op){
            //Cadastro enxames
            case 1:
                linha(5);
                printf("##|  Cadastro de enxames  |##");
                linha(5);
                if(limite_cadastro()!=0){
                    printf("Quantos enxames você deseja cadastrar?\n=");
                    setbuf(stdin,NULL);
                    scanf("%d",&qtd);
                    linha(1);
                    if(qtd>limite_cadastro()){
                        printf("\n*Limite para cadastro será atingido\nTennte cadastrar um por vez\n");
                        linha(1);
                        qtd=1;
                    }
                    for(int i=1;i<=qtd;i++){
                        printf("\n#Cadastro[%d]#",i);
                        acessar_bd_enxames();
                        //codigo
                        do{
                            printf("\nDigite o codigo do enxame!\n=");
                            setbuf(stdin,NULL);
                            scanf("%d",&codigo);
                            resp=set_id_enxame(codigo);
                            if(resp==1){
                                printf("*Codigo cadastrado!");
                                posicao=posicao_enxame(codigo);
                            }else{
                                printf("*Codigo invalido já está cadastrado\nTente novamente!");
                            }
                            linha(2);
                        }while(resp==0);
                        //data
                        printf("\nDigite a data em que obteve o enxame!\n=");
                        setbuf(stdin,NULL);
                        gets(data);
                        set_data_enxame(data,posicao);
                        printf("*Data cadastrada");
                        linha(2);
                        //especie
                        do{
                            printf("\nDigite uma opcao para a especie do enxame![0 para ausencia]\n");
                            for(int i=0;i<armaz_especie;i++){
                                exibir_especie(i);
                            }
                            printf("\n=");
                            setbuf(stdin,NULL);
                            scanf("%d",&especie);
                            resp=set_espec_enxame(especie,posicao);
                            if(resp==1){
                                printf("*Especie cadastrada!");
                            }else{
                                printf("=>Opçao invalida,tente novamente!");
                                resp=0;
                            }
                            linha(2);
                        }while(resp==0);
                        //status
                        do{
                            printf("\nDigite o status atual do enxame!\
                            \n1-Forte\
                            \n2-Fraco\
                            \n=");
                            setbuf(stdin,NULL);
                            scanf("%d",&status);
                            resp=set_status_enxame(status,posicao);
                            if(resp==1){
                                printf("*Status cadastrado!");
                            }else{
                                printf("=>Opçao invalida,tente novamente!");
                            }
                            linha(2);
                        }while(resp==0);
                        //descriçao
                        printf("\nDigite uma descriçao para o enxame!\n=");
                        setbuf(stdin,NULL);
                        gets(descricao);
                        set_desc_enxame(descricao,posicao);
                        salvar_dados_enxame(posicao);
                        linha(3);
                        delay("salvando...",2);
                        info_enxame(posicao);
                    }
                    pros();
                //erro
                }else{
                    printf("Espaço para cadastro atingiu o limite");
                    linha(2);
                }
            break;
            //Alteração
            case 2:
                linha(5);
                printf("##|  Alterar informacoes  |##");
                linha(5);
                acessar_bd_enxames();
                printf("Digite o codigo do enxame que vc quer alterar\n=");
                setbuf(stdin,NULL);
                scanf("%d",&codigo);
                linha(3);
                resp=verificar_cod(codigo);
                if(resp==1){
                    delay("Acessando informacoes...",2);
                    do{
                        posicao=posicao_enxame(codigo);
                        info_enxame(posicao);
                        printf("\nO que deseja alterar?\
                        \n1-Data\
                        \n2-Especie\
                        \n3-Producao\
                        \n4-Status\
                        \n5-Descricao\
                        \n6-Sair\n=");
                        setbuf(stdin,NULL);
                        scanf("%d",&esc);
                        linha(1);
                        switch(esc){
                            //data
                            case 1:
                                printf("\nDigite a data em que obteve o enxame!\n=");
                                setbuf(stdin,NULL);
                                gets(data);
                                set_data_enxame(data,posicao);
                                printf("*Data modificada com sucesso!");
                            break;
                            //espécie
                            case 2:
                                do{
                                    printf("\nDigite uma opcao para a especie do enxame![0 para ausencia]\n");
                                    for(int i=0;i<armaz_especie;i++){
                                        exibir_especie(i);
                                    }
                                    printf("\n=");
                                    setbuf(stdin,NULL);
                                    scanf("%d",&especie);
                                    linha(3);
                                    resp=set_espec_enxame(especie,posicao);
                                    if(resp==1){
                                        printf("*Especie modificada com sucesso!");
                                    }else{
                                        printf("=>Opçao invalida,tente novamente!");
                                    }
                                }while(resp==0);
                            break;
                            //producao
                            case 3:
                                printf("\nDigite a producao em ml!\n=");
                                setbuf(stdin,NULL);
                                scanf("%f",&producao);
                                set_prod_enxame(producao,posicao);
                                printf("*Producao modificada com sucesso!");
                            break;
                            //status
                            case 4:
                                do{
                                    printf("\nDigite o status atual do enxame!\
                                    \n1-Forte\
                                    \n2-Fraco\
                                    \n=");
                                    setbuf(stdin,NULL);
                                    scanf("%d",&status);
                                    resp=set_status_enxame(status,posicao);
                                    if(resp==1){
                                        printf("*Status modificado com sucesso!");
                                    }else{
                                        printf("=>Opçao invalida,tente novamente!");
                                        linha(2);
                                    }
                                }while(resp==0);
                            break;
                            //descricao
                            case 5:
                                printf("\nDigite uma descriçao para o enxame!\n=");
                                setbuf(stdin,NULL);
                                gets(descricao);
                                set_desc_enxame(descricao,posicao);
                                printf("\n*Descricao modificada com sucesso");
                            break;
                            //sair
                            case 6:

                            break;
                            //erro
                            default:
                                printf("\n=>Opcao invalida tente novamente!");
                            break;
                        }
                        if(esc==1|esc==2|esc==3|esc==4|esc==5){
                            atualizar_bd_enxames();
                        }
                        linha(2);
                    }while(esc!=6);
                }else{
                    printf("=>Codigo invalido tente novamente");
                    linha(2);
                }

            break;
            //Exibir informaçoes
            case 3:
                linha(5);
                printf("##|  Exibir informacoes  |##");
                linha(5);
                acessar_bd_enxames();
                printf("Digite o codigo do enxame que deseja exibir informacoes\n=");
                setbuf(stdin,NULL);
                scanf("%d",&codigo);
                resp=verificar_cod(codigo);
                if(resp==1){
                    delay("Acessando informacoes...",2);
                    posicao=posicao_enxame(codigo);
                    info_enxame(posicao);
                    pros();
                }else{
                    printf("=>Codigo invalido tente novamente");
                    linha(2);
                }
            break;
            //Excluir
            case 4:
                linha(5);
                printf("##|  Excluir enxame  |##");
                linha(5);
                acessar_bd_enxames();
                printf("Digite o codigo do enxame que deseja excluir\n=");
                setbuf(stdin,NULL);
                scanf("%d",&codigo);
                linha(3);
                resp=verificar_cod(codigo);
                posicao=posicao_enxame(codigo);
                if(resp==1){
                    printf("Tem certeza que quer excluir esse enxame?\
                    \n1- sim\
                    \n2- nao\n=");
                    scanf("%d",&esc);
                    linha(3);
                    if(esc==1){
                        excluir_enxame(posicao);
                        //atualizar_bd_enxames();
                        atualizar_producaoTot();
                        atualizar_Especies();
                        delay("excluindo informacoes...",2);
                        printf("\n*Operacao concluida");
                    }else{
                        printf("=>Operacao cancelada");
                    }
                }else{
                    printf("=>Codigo invalido tente novamente");
                }
                linha(2);
            break;
            //  Relacao de enxames
            case 5:
                linha(5);
                printf("##|  Relacao de enxames  |##");
                linha(5);
                acessar_bd_enxames();
                if(get_total_enxame()>0){
                    delay("exibindo...",2);
                    for(int i=0;i<armaz_enxame;i++){
                        info_enxame(i);
                    }
                }else{
                    printf("*Não ha enxames!");
                }
                pros();
            break;
            //Sair
            case 6:
            break;
            //Erro
            default:
                printf("\n=>Opcao invalida tente novamente");
            break;
        }
    }while(op!=6);
}
/***********************************************************************************/
/***********************************************************************************/

/////menu de especies/////
void menuespecies(){
    char especie[21],informacao[mtif];
    int codigo;
    int op=0,p=0,esc=0,v=0;
    do{
        linha(2);
        printf("\n********|  ESPECIES  |********");
        linha(2);
        printf("\nO QUE DESEJA FAZER?!");
        printf("\n1-Cadastrar especie\
        \n2-Relacao de especies\
        \n3-Excluir especie\
        \n4-Resetar especies\
        \n5-Sair\n=");
        setbuf(stdin,NULL);
        scanf("%d",&op);
        linha(1);
        if(op==1|op==2|op==3|op==4){
            delay("",2);
        }
        switch (op){
            //cadostro de especie
            case 1:
                if(limite_cad_esp()!=0){
                    linha(5);
                    printf("##|  Cadastro de especies  |##");
                    linha(5);
                    printf("Digite o id da especie!\n=");
                    setbuf(stdin,NULL);
                    scanf("%d",&codigo);
                    linha(3);

                    if(verificar_cod_esp(codigo)!=1){
                        printf("Digite nome da especie!\n=");
                        setbuf(stdin,NULL);
                        gets(especie);
                        linha(3);
                        printf("Digite a descricao da especie!\n=");
                        setbuf(stdin,NULL);
                        gets(informacao);
                        linha(1);
                        cad_especie(codigo,especie,informacao);
                        printf("\nEspecie cadastrada com sucesso!");
                    }else{
                        printf("*Codigo invalido já está cadastrado\nTente novamente!");
                    }
                    pros();
                }else{
                    printf("=>Espaço para cadastro atingiu o limite");
                    linha(2);
                }
            break;
            //relacao de especies
            case 2:
                linha(5);
                printf("##|  Relacao de especies  |##");
                linha(5);
                linha(1);
                acessar_bd_especies();
                atualizar_Especies();
                if(tot_esp()>0){
                    for(int i=0;i<armaz_especie;i++){
                        info_especie(i);
                    }
                }else{
                    printf("\n*Nao ha especies!");
                }
                linha(2);
                pros();
            break;
            //exclusao de especies
            case 3:
                linha(5);
                printf("##|  Excluir especies  |##");
                linha(5);
                for(int i=0;i<armaz_especie;i++){
                    info_especie(i);
                }
                if(tot_esp()>0){
                    printf("\nDigite o id da especie que quer excluir!\n=");
                    setbuf(stdin,NULL);
                    scanf("%d",&codigo);
                    linha(3);
                    v=verificar_cod_esp(codigo);
                    if(v==1){
                        p=posicao_especie(codigo);
                        excluir_especie(p);
                        acessar_bd_especies();
                        printf("Exclusao concluida!");
                    }else{
                        printf("=>Codigo invalido tente novamente!");
                    }
                    }else{
                        printf("*Nao ha especies!");
                    }
                    pros();
            break;
            //resetar especies
            case 4:
                linha(5);
                printf("##|  Resetar especies  |##");
                linha(5);
                printf("Ao resetar as especies todas especies voltarão ao padrão!\
                \nDeseja continuar?\
                \n1-sim\
                \n2-nao\n=");
                scanf("%d",&esc);
                linha(3);
                if(esc==1){
                    resetar_especies();
                    printf("*Especies voltaram ao modo padrao!");
                    pros();
                }else{
                    printf("=>Operacao cancelada");
                }
            break;
            //sair
            case 5:
            break;
            //erro
            default:
                printf("\n=>Opcao invalida tente novamente!");
            break;
        };
    }while(op!=5);

}
/***********************************************************************************/
/***********************************************************************************/

/////menu de tarefas/////
void menutarefas(){
    char descricao[500];
    int cod;
    int pt;
    int op=0;
    do{
        linha(2);
        printf("\n********|  TAREFAS  |********");
        linha(2);
        printf("\nO QUE DESEJA FAZER?!");
        printf("\n1-Criar tarefa\
        \n2-Exibir tarefas\
        \n3-Excluir tarefa\
        \n4-Sair\n=");
        setbuf(stdin,NULL);
        scanf("%d",&op);
        linha(1);
        if(op==1|op==2|op==3|op==4){
           delay("",2);
        }
        switch (op){
            //criar tarefas
            case 1:
                linha(5);
                printf("##|  Criar tarefas  |##");
                linha(5);
                printf("Digite uma descrição para sua tarefa!\n=");
                setbuf(stdin,NULL);
                gets(descricao);
                linha(1);
                criar_tarefa(descricao);
            break;
            //exibir tarefas
            case 2:
                linha(5);
                printf("\n##|  Exibir tarefas  |##");
                linha(5);
                linha(1);
                if(tot_taref()>0){
                    exibir_tarefas();
                    linha(2);
                }else{
                    printf("*\nNao ha tarefas!");
                }
                pros();
            break;
            //excluir tarefas
            case 3:
                linha(5);
                printf("##|  Excluir tarefas  |##");
                linha(5);
                exibir_tarefas();
                if(tot_taref()>0){
                    printf("\nDigite uma opcao!\n=");
                    setbuf(stdin,NULL);
                    scanf("%d",&cod);
                    linha(3);
                    pt=posicao_tarefa(cod);
                    if(pt==55){
                        printf("=>Codigo invalido!");
                    }else{
                        excluir_tarefa(pt);
                        atualizar_bd_tarefas();
                        printf("*Tarefa foi excluida com sucesso!");
                    }
                }else{
                    printf("*Não ha tarefas!");
                }
                linha(2);
                pros();
            break;
            //sair
            case 4:
            break;
            //erro
            default:
                printf("\n=>Opcao invalida tente novamente!");
            break;
        }
    }while(op!=4);
}
/***********************************************************************************/
/***********************************************************************************/

/////producao/////
void menuproducao(){
    int codigo=0,status=0,especie=0;
    char data[21],descricao[301],especi_e[21];
    int op=0,qtd=0,posicao=0,resp=0,esc=0;
    float mel=0;
    do{
        linha(2);
        printf("\n********|  PRODUCAO  |********");
        linha(2);
        printf("\nO QUE DESEJA FAZER?!");
        printf("\n1-Adicionar a produção\
        \n2-Visualizar producao\
        \n3-Verificar desempenho\
        \n4-Renovar producao\
        \n5-Sair\n=");
        setbuf(stdin,NULL);
        scanf("%d",&op);
        //op=4;
        linha(1);
        if(op==1|op==2|op==3|op==4){
          delay("",2);
        }
        switch(op){
            //Adicionar a produção
            case 1:
                linha(5);
                printf("##|  Adicionar a produção  |##");
                linha(5);
                acessar_bd_enxames();
                printf("De quantos enxames você deseja informar?\n=");
                setbuf(stdin,NULL);
                scanf("%d",&qtd);
                linha(3);
                if(get_total_enxame()>=qtd){
                    for(int i=1;i<=qtd;i++){
                       do{
                            linha(1);
                            printf("\nDigite o codigo do enxame\n=");
                            setbuf(stdin,NULL);
                            scanf("%i",&codigo);
                            resp=verificar_cod(codigo);
                            printf("resp=",resp);
                            if(resp==1){
                                posicao=posicao_enxame(codigo);
                                printf("Informe a quantidade de mel retirada em ml!\n=");
                                setbuf(stdin,NULL);
                                scanf("%f",&mel);
                                add_prod_enxame(mel,posicao);
                                printf("*Operacao concluida foi adicionado %2.f ml a producao\n",mel);
                            }else{
                                printf("=>Codigo invalido!\n");
                            }
                            codigo=0;
                            mel=0.0;
                       }while(resp!=1);
                    }
                    atualizar_Especies();
                    atualizar_bd_especies();
                    atualizar_producaoTot();
                }else{
                    printf("*Esse numero ultrapassa o total de enxames cadastrados\
                    \nou nao foi cadastrado nenhum enxame tente novamente!\n");
                }
                linha(1);
                atualizar_bd_enxames();
            break;
            //Visualizar produção
            case 2:
            linha(5);
               printf("##|  Visualizar producao  |##");
               linha(5);
               linha(3);
               delay("exibindo...",2);
               linha(2);
               printf("\nPRODUCAO TOTAL  |=> ");
               exibir_producaoTot();
               printf("\nTOTAL DE ENXAMES|=> %d",get_total_enxame());
               linha(2);
               printf("\nPRODUCAO POR ESPECIE:");
               linha(2);
               exibir_prod_especie();
               linha(2);
               pros();
            break;
            //Verificar desempenho
            case 3:
                linha(5);
                printf("##|  Desempenho de enxames  |##");
                linha(5);
                acessar_bd_enxames();
                if(get_total_enxame()>0){
                    printf("Digite a media de producao por enxame\n=");
                    setbuf(stdin,NULL);
                    scanf("%f",&mel);
                    linha(3);
                    delay("exibindo...",2);
                    linha(4);
                    desempenho_enxame(mel);
                }else{
                    printf("*Não ha enxames!");
                }
                pros();
            break;
            //renovar produção
            case 4:
                char nomearquivo[20];
                linha(5);
                printf("##|  Renovar produção  |##");
                linha(5);
                printf("Tem certeza que deseja renovar a producao?\
                \nTodos os dados da producao serão apagados!\
                \n1-sim\
                \n2-nao\n=");
                setbuf(stdin,NULL);
                scanf("%d",&esc);
                linha(3);
                if(esc==1){
                    printf("Deseja gerar um relatorio?\
                    \n1-sim\
                    \n2-nao\n=");
                    setbuf(stdin,NULL);
                    scanf("%d",&esc);
                    if(esc==1){
                        printf("Digite o nome do relatorio:\n=");
                        setbuf(stdin,NULL);
                        gets(nomearquivo);
                        printf("Gerando um relatorio");
                        gerar_relatorioproducao(nomearquivo);
                        renovar_producao();
                        atualizar_bd_enxames();
                        atualizar_bd_especies();
                    }else{
                        renovar_producao();
                        atualizar_bd_enxames();
                        atualizar_bd_especies();
                        printf("*Produção foi renovada com sucesso!");

                    }
                }else{
                    if(esc==2){
                        printf("Operacao cancelada!");
                    }else{
                        printf("=>Opcao invalida!");
                    }
                }
            break;
            //Sair
            case 5:
            break;
            //Erro
            default:
                printf("\n=>Opcao invalida tente novamente");
                linha(2);
            break;
        }
        if(op==1|op==2|op==3|op==4){
            delay("",2);
        }

    }while(op!=5);
}
/***********************************************************************************/
/***********************************************************************************/

/////menu relatorios/////
void menurelatorios(){
    char nomerelat[21];
    int op=0,esc=0,cod=0,resp=0;
    do{
        linha(2);
        printf("\n********|  RELATORIOS  |********");
        linha(2);
        printf("\nO QUE DESEJA FAZER?!");
        printf("\n1-Gerar relatorio\
        \n2-Exibir relatorio\
        \n3-Excluir relatorio\
        \n4-Sair\n=");
        setbuf(stdin,NULL);
        scanf("%d",&op);
        linha(1);
        if(op==1|op==2|op==3){
          delay("",2);
        }
        switch (op){
            //gerar relatorios
            case 1:
                linha(5);
                printf("##|  Gerar relatorio  |##");
                linha(5);
                printf("Qual tipo de relatorio voce deseja gerar!\
                \n1-enxames\
                \n2-especies\
                \n3-producao\n=");
                setbuf(stdin,NULL);
                scanf("%d",&esc);
                linha(3);
                if(esc==1|esc==2|esc==3){
                    printf("Digite um nome para o relatorio!\n=");
                    setbuf(stdin,NULL);
                    gets(nomerelat);
                    if(esc==1){
                        gerar_relatorioenxame(nomerelat);
                    }else{
                        if(esc==2){
                            gerar_relatorioespecies(nomerelat);
                        }else{
                            if(esc==3){
                                gerar_relatorioproducao(nomerelat);
                            }
                        }
                    }
                    printf("*Relatorio gerado com sucesso");
                }else{
                    printf("=>Opcao invalida!");
                }
            break;
            //exibir relatorios
            case 2:
                linha(5);
                printf("##| Exibir Relatorio|##");
                linha(5);
                printf("Qual tipo de relatorio você quer exibir!\
                \n1-enxames\
                \n2-especies\
                \n3-producao\n=");
                setbuf(stdin,NULL);
                scanf("%d",&esc);
                linha(1);
                printf("\nHISTORICO DE RELATORIOS");
                if(esc==1|esc==2|esc==3){
                    if(esc==1){
                        ler_arquivo('x');
                    }else{
                        if(esc==2){
                            ler_arquivo('e');
                        }else{
                            if(esc==3){
                                ler_arquivo('p');
                            }
                        }
                }
                if(esc!=0){
                    printf("\nDigite o nome do relatorio!\n=");
                    setbuf(stdin,NULL);
                    scanf("%s",&nomerelat);
                    linha(3);
                    delay("exibindo...",2);
                    linha(4);
                    switch(esc){
                        case 1:
                            ler_relatorioenxame(nomerelat);
                            pros();
                        break;
                        case 3:
                            ler_relatorioproducao(nomerelat);
                            pros();
                        break;
                        case 2:
                            ler_relatorioespecie(nomerelat);
                            pros();
                        break;
                    }
                }
                }else{
                    printf("=>Opcao invalida!");
                }
                //pros();
            break;
            //excluir relatorios
            case 3:
                linha(5);
                printf("##|  Excluir relatorio  |##");
                linha(5);
                printf("Qual tipo de relatorio!\
                \n1-enxames\
                \n2-especies\
                \n3-producao\n=");
                setbuf(stdin,NULL);
                scanf("%d",&esc);
                linha(1);
                printf("\nHISTORICO DE RELATORIOS\n");
                if(esc==1|esc==2|esc==3){
                    if(esc==1){
                        resp=exibir_arquivos('x');
                    }else{
                        if(esc==2){
                            resp=exibir_arquivos('e');
                        }else{
                            if(esc==3){
                                resp=exibir_arquivos('p');
                            }
                        }
                    }
                    if(resp>0){
                        printf("\nDigite o codigo do relatorio!\n=");
                        setbuf(stdin,NULL);
                        scanf("%d",&cod);
                        switch(esc){
                            case 1:
                                excluir_relatorio('x',cod);
                            break;
                            case 3:
                                excluir_relatorio('p',cod);
                            break;
                            case 2:
                                excluir_relatorio('e',cod);
                            break;
                        }
                        printf("*Exclusao concluida!");
                    }
                    pros();
                }else{
                    printf("=>Opcao invalida!");
                }
            break;
            //sair
            case 4:
            break;
            //erro
            default:
                printf("\n=>Opcao invalida tente novamente!");
            break;
        }
    }while(op!=4);
}
/***********************************************************************************/
/***********************************************************************************/
