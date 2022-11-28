#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/**************************************************************************/
/**VARIAVEIS E COMANDOS EXTERNOS**/
extern armaz_enxame,armaz_especie,numero_tarefa,qtd;
extern get_cod_relat();
extern excluir_enxame();
extern gerar_relatorioenxame(),gerar_relatorioespecies(),gerar_relatorioproducao();
extern inserir_bd_usuario(),acessar_bd_usuario();//bd
/**************************************************************************/
/**************************************************************************/
/**ESTRUTURA**/
struct Usuario{//cria uma estrutura para armazenar dados do usuário
    char nome[11];
    int senha;
    _Bool status;// 0 falso(conta não ativa) 1 verdadeiro(conta ativa)
    _Bool logado;//0 falso(deslogado) 1 verdadeiro(logado)
}user;
/**************************************************************************/
/**************************************************************************/
/**GETTERS and SETERS**/
int getuser_status(){//retorna o status da conta do usuario
    return user.status;
}
_Bool getuser_logado(){//retorna se o usuário está logado
    return user.logado;
}
/**************************************************************************/
/**************************************************************************/
/**FUNÇOES**/
/////PRINCIPAIS/////
int to_String(){//Exibe o nome e senha do usuaario
    return printf("Nome: %s Senha: %d",user.nome,user.senha);
}
int cad_user(char nome[11],int senha){//cadastra o nome e a senha do usuario e manda para o banco de arquivos
    strcpy(user.nome,nome);
    user.senha=senha;
    user.status=true;
    user.logado=true;
    salvar_dados_usuario(user.nome,user.senha);
    return 1;
}
char logar(char nome[11],int senha){//Ao fazaer login,acessa o banco de arquivos e verifica se o nome e a senha do usuario estão corretos.
    //acessar_bd_usuario();
    if(strcmp(user.nome,nome)==0){
    if(user.senha==senha){
        user.logado=true;
        user.status=true;
    }else{
        user.logado=false;
        return 's';
    }
    }else{
    user.logado=false;
        return 'n';
    }
}
void log_of(){//Desloga da conta
    user.logado=false;
}
void excluir_conta(){//exclui login , senha e todos os dados relacionados
    for(int i=0;i<=strlen(user.nome);i++){
        user.nome[i]=NULL;
    }
    user.senha=NULL;
    user.status=false;
    user.logado==false;
    salvar_dados_usuario("",000);
    for(int i=0;i<armaz_enxame;i++){
        excluir_enxame(i);
    }
    for(int i=0;i<armaz_especie;i++){
        excluir_especie(i);
    }
    for(int i=0;i<numero_tarefa;i++){
        excluir_tarefa(i);
    }
    gerar_relatorioenxame("Relatmaster");
    acessar_bd_Arquivo('x');
    for(int i=0;i<qtd;i++){
        if(get_cod_relat(i)!=0){
            excluir_relatorio('x',get_cod_relat(i));
        }
    }
    gerar_relatorioespecies("Relatmaster");
    acessar_bd_Arquivo('e');
    for(int i=0;i<qtd;i++){
        if(get_cod_relat(i)!=0){
            excluir_relatorio('e',get_cod_relat(i));
        }
    }
    gerar_relatorioproducao("Relatmaster");
    acessar_bd_Arquivo('p');
    for(int i=0;i<qtd;i++){
        if(get_cod_relat(i)!=0){
            excluir_relatorio('p',get_cod_relat(i));
        }
    }
    atualizar_bd_enxames();
    atualizar_bd_tarefas();
    resetar_especies();
}

/////SECUNDARIAS/////
int alt_usernome(char nome[11]){//altera o nome do usuario
    if(strcmp(nome,user.nome)==0){//verifica se o nome atual é diferente do anterior
        return 0;
    }else{
        strcpy(user.nome,nome);
        salvar_dados_usuario(user.nome,user.senha);
        return 1;
    }

    }
int alt_usersenha(int senha){//altera a senha do usuario
    if(senha!=user.senha){//verifica se a senha é diferente da anterior
        user.senha=senha;
        salvar_dados_usuario(user.nome,user.senha);
        return 1;
    }else{
        return 0;
    }
}
int tam_nome(){//retorna o temnho do nome do usuario
    return strlen(user.nome);
}

/////BANCO DE DADOS/////
void salvar_dados_usuario(char nome[11],int senha){
    inserir_bd_usuario(nome,senha);
}
void receber_bd_usuario(char nome[11],int senha){
   strcpy(user.nome,nome);
   user.senha=senha;
}
/**************************************************************************/
/**************************************************************************/
