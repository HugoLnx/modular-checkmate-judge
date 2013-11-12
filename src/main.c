/***************************************************************************
*
*  Módulo de principal
*
*  Arquivo gerado:              main.c
*
*	Autores:
*     - rc: Robert Correa
*
*  Histórico de evolução:
*     Versão  Autor    Data             Observações
*     1       rc       11/nov/2013      Funções para menu.
*
***************************************************************************/

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"mem_manager.h"
#include"input_string_parser.h"
#include"partida.h"
#include "checkmate_judge.h"

/***** Protótipos das funções encapuladas no módulo *****/

static void MenuInserirPeca(PAR_tppPartida ppPartida, const int time);
static void MenuCadastrarPeca(PAR_tppPartida ppPartida);
static void MenuAlterarPeca(PAR_tppPartida ppPartida);
static void MenuRemoverPeca(PAR_tppPartida ppPartida);
static void MenuSalvarPartida(PAR_tppPartida ppPartida);
static void MenuCarregarPartida(PAR_tppPartida* ppPartida);
static void MenuInserirRei(PAR_tppPartida ppPartida);
static void MenuXequeMate(PAR_tppPartida ppPartida);
static void MenuRemoverRei(PAR_tppPartida ppPartida);

static void Mensagem(char *erroMsg);

/***** Protótipos das funções encapuladas no módulo *****/



int main()
{
   int opcao = -1;
   PAR_tppPartida ppPartida = NULL;

   PAR_CriarPartida(&ppPartida);

   while(opcao != 13)
   {
      printf("1  - Cadastrar pecas\n");
      printf("2  - Alterar pecas\n");
      printf("3  - Inserir pecas para o jogador ALIADO\n");
      printf("4  - Inserir pecas para o jogador INIMIGO\n");
      printf("5  - Inserir rei para jogador ALIADO\n");
      printf("6  - Remover Rei\n");
      printf("7  - Remover peca\n");
      printf("8  - Exibir tabuleiro\n");
      printf("9  - Checar xeque mate\n");
      printf("10 - Salvar jogo\n");
      printf("11 - Carregar jogo\n");
      printf("12 - Resetar jogo\n");
      printf("13 - Sair\n");

      printf("\nEscolha uma opcao: ");
      scanf("%d",&opcao);
      system("cls");

      switch(opcao)
      {
      case 1:
         {
            MenuCadastrarPeca(ppPartida);

         }break;
      case 2:
         {
            MenuAlterarPeca(ppPartida);

         }break;
      case  3:
         {
            MenuInserirPeca(ppPartida,ALIADA);

         }break;
      case 4:
         {
            MenuInserirPeca(ppPartida,INIMIGA);

         }break;
      case 5:
         {
            MenuInserirRei(ppPartida);

         }break;
      case 6:
         {
            MenuRemoverRei(ppPartida);

         }break;
      case 7:
         {
            MenuRemoverPeca(ppPartida);

         }break;
      case 8:
         {
            PAR_Exibir(ppPartida);
            system("cls");

         }break;
      case 9:
         {
            MenuXequeMate(ppPartida);

         }break;
      case 10:
         {
            MenuSalvarPartida(ppPartida);
         }break;
      case 11:
         {
            MenuCarregarPartida(&ppPartida);
         }break;
      case 12:
         {
            PAR_DestruirPartida(&ppPartida);
            PAR_CriarPartida(&ppPartida);

         }break;
      default:
         {
            printf("Opcao invalida\n");

         }
      }
   }

   return 0;
}

/********** Implementação das funções encapsuladas **********/

static void MenuInserirPeca(PAR_tppPartida ppPartida, const PEC_tpTimePeca time)
{
   char *nome, *nomeCasa;
   PAR_tpCondRet condRet;

   MEM_Alloc(sizeof(char)*20,(void**)&nome);
   MEM_Alloc(sizeof(char)*2,(void**)&nomeCasa);

   printf("Nome da peca (20 caracteres): ");
   scanf("%s", nome);

   printf("Nome da casa que deseja inserir a peca (2 caracteres - convenção do xadrez): ");
   scanf("%s", nomeCasa);

   nomeCasa[0] = toupper(nomeCasa[0]);

   condRet = PAR_IrCasa(ppPartida, nomeCasa);

   if(condRet !=  PAR_CondRetOK)
   {
      return Mensagem("Erro ao inserir - Casa nao existe!");
   }

   condRet = PAR_InserirPeca(ppPartida,nome,time);

   if(condRet == PAR_CondRetPecaNaoEncontrada)
   {
      return Mensagem("Erro ao inserir - Peca nao encontrada!");
   }

   return Mensagem("Peca inserida no time com sucesso!");
}

static void MenuCadastrarPeca(PAR_tppPartida ppPartida)
{
   char *nome, *passos, *tipoMov;
   ISP_tpCondRet ispCondRet;
   MPEC_tpTipoMovimento tipoMovimento;
   LIS_tppLista pPassos;

   MEM_Alloc(sizeof(char)*20,(void**)&nome);
   MEM_Alloc(sizeof(char)*200,(void**)&passos);
   MEM_Alloc(sizeof(char)*4,(void**)&tipoMov);

   printf("Nome da peca (20 caracteres): ");
   scanf("%s",nome);
   printf("Movimentos ([n]coordenada_[n]coordenada): ");
   scanf("%s", passos);
   printf("Tipo de movimento(Anda | Voa): ");
   scanf("%s",tipoMov);

   ispCondRet = ISP_LerTipoMovimento(tipoMov,&tipoMovimento);

   if(ispCondRet != ISP_CondRetOK)
   {
      return Mensagem("Tipo de movimento invalido!");
   }

   ISP_LerPassos(passos,&pPassos);

   PAR_CriarPeca(ppPartida, nome, pPassos, tipoMovimento);

   return Mensagem("Peca cadastrada com sucesso!");
}

static void MenuAlterarPeca(PAR_tppPartida ppPartida)
{
   char *nomeAtual, *novoNome, *novosPassos, *movimento;
   ISP_tpCondRet ispCondRet;
   PAR_tpCondRet parCondRet;
   MPEC_tpTipoMovimento novoTipoMovimento;
   LIS_tppLista pPassos;

   MEM_Alloc(sizeof(char)*20,(void**)&nomeAtual);
   MEM_Alloc(sizeof(char)*20,(void**)&novoNome);
   MEM_Alloc(sizeof(char)*200,(void**)&novosPassos);
   MEM_Alloc(sizeof(char)*4,(void**)&movimento);

   printf("\nNome da peca que quer alterar (20 caracteres): ");
   scanf("%s", nomeAtual);
   printf("Novo nome (20 caracteres): ");
   scanf("%s", novoNome);
   printf("Novo movimento ([n]coordenada): ");
   scanf("%s", novosPassos);
   printf("Novo tipo de movimento (Anda | Voa): ");
   scanf("%s", movimento);

   ispCondRet = ISP_LerTipoMovimento(movimento,&novoTipoMovimento);

   if(ispCondRet != ISP_CondRetOK)
   {
      return Mensagem("Tipo de movimento invalido!");
   }

   ISP_LerPassos(novosPassos,&pPassos);

   parCondRet = PAR_AlterarPeca(ppPartida,nomeAtual,novoNome,pPassos,novoTipoMovimento);

   if(parCondRet != PAR_CondRetOK)
   {
      return Mensagem("Erro ao alterar peca!");
   }

   return Mensagem("Peca alterada com sucesso!");
}

static void MenuRemoverPeca(PAR_tppPartida ppPartida)
{
   char *nomeDaCasa;
   PAR_tpCondRet condRet;

   MEM_Alloc(sizeof(char)*2,(void**)&nomeDaCasa);

   printf("Nome da casa onde esta a peca a ser removida: ");
   scanf("%s",nomeDaCasa);

   nomeDaCasa[0] = toupper(nomeDaCasa[0]);

   condRet = PAR_IrCasa(ppPartida,nomeDaCasa);

   if(condRet !=  PAR_CondRetOK)
   {
      return Mensagem("Erro ao remover - Casa nao existe!");
   }

   condRet = PAR_RemoverPeca(ppPartida);

   if(condRet == PAR_CondRetPecaNaoEncontrada)
   {
      return Mensagem("Erro ao remover - casa esta vazia!");
   }

   return Mensagem("Peca removida com sucesso!");
}

static void MenuSalvarPartida(PAR_tppPartida ppPartida)
{
   char *pNomeArquivo;
   PAR_tpCondRet parCondRet;
   MEM_Alloc(sizeof(char)*200,(void**)&pNomeArquivo);

   printf("Nome do arquivo: (ex: save1.txt): ");
   scanf("%s",pNomeArquivo);

   parCondRet = PAR_Salvar(ppPartida,pNomeArquivo);

   if(parCondRet != PAR_CondRetOK)
   {
      return Mensagem("Erro ao salvar partida!");
   }

   return Mensagem("Partida salva com sucesso!");
}

static void MenuCarregarPartida(PAR_tppPartida *ppPartida)
{
   char *pNomeArquivo;
   PAR_tpCondRet parCondRet;
   PAR_tppPartida **pPartuda = NULL;
   MEM_Alloc(sizeof(char)*200,(void**)&pNomeArquivo);

   printf("Nome do arquivo: (save1.txt): ");
   scanf("%s",pNomeArquivo);

   PAR_DestruirPartida(ppPartida);

   parCondRet = PAR_Carregar(ppPartida,pNomeArquivo);

   if(parCondRet != PAR_CondRetOK)
   {
      return Mensagem("Erro ao carregar partida!");
   }

   return Mensagem("Partida carregar com sucesso!");

}

static void MenuInserirRei(PAR_tppPartida ppPartida)
{
   char *nomeCasa;
   PAR_tpCondRet condRet;

   MEM_Alloc(sizeof(char)*2,(void**)&nomeCasa);

   printf("Nome da casa que deseja inserir o rei (2 caracteres - convenção do xadrez): ");
   scanf("%s", nomeCasa);

   nomeCasa[0] = toupper(nomeCasa[0]);

   condRet = PAR_IrCasa(ppPartida, nomeCasa);

   if(condRet !=  PAR_CondRetOK)
   {
      return Mensagem("Erro ao inserir - Casa nao existe!");
   }

   condRet = PAR_InserirRei(ppPartida);

   if(condRet != PAR_CondRetOK)
   {
      return Mensagem("Erro ao inserir o rei!");
   }

   return Mensagem("Rei inserido com sucesso!");
}

static void MenuXequeMate(PAR_tppPartida ppPartida)
{
   int resposta;
   JUD_tpCondRet judCondRet;
   judCondRet = JUD_EhCheckmate(ppPartida,&resposta);

   if(judCondRet != JUD_CondRetOK)
   {
      return Mensagem("Erro ao analisar xeque mate - Rei não inserido!");
   }

   if(resposta == 1)
   {
      return Mensagem("Xeque-mate!");
   }
   else
   {
      return Mensagem("Rei fora de perigo!");
   }
}

static void MenuRemoverRei(PAR_tppPartida ppPartida)
{
   PAR_tpCondRet parCondRet;

   parCondRet = PAR_RemoverRei(ppPartida);

   if(parCondRet != PAR_CondRetOK)
   {
      return Mensagem("Erro ao remover rei - Não existe rei inserido no tabuleiro!");
   }

   Mensagem("Rei removido com sucesso");
}

static void Mensagem(char *erroMsg)
{
   printf("\n%s\n",erroMsg);
   system("pause");
   system("cls");
   return;
}

/********** Fim do módulo de implementação: Módulo principal **********/