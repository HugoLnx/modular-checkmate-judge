#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"mem_manager.h"
#include"input_string_parser.h"
#include"partida.h"

static void MenuInserirPeca(PAR_tppPartida ppPartida, const int time);
static void MenuCadastrarPeca(PAR_tppPartida ppPartida);
static void MenuAlterarPeca(PAR_tppPartida ppPartida);
static void MenuRemoverPeca(PAR_tppPartida ppPartida);
static void MenuSalvarPartida(PAR_tppPartida ppPartida);
static void MenuCarregarPartida(PAR_tppPartida* ppPartida);
static void MenuInserirRei(PAR_tppPartida* ppPartida);

int main()
{
   int opcao = -1;
   PAR_tppPartida ppPartida = NULL;

   PAR_CriarPartida(&ppPartida);

   while(opcao != 12)
   {
      printf("1  - Cadastrar pecas\n");
      printf("2  - Alterar pecas\n");
      printf("3  - Inserir pecas para o jogador ALIADO\n");
      printf("4  - Inserir pecas para o jogador INIMIGO\n");
      printf("5  - Inserir rei para jogador INIMIGO\n");
      printf("6  - Remover peca\n");
      printf("7  - Exibir tabuleiro\n");
      printf("8  - Checar xeque mate\n");
      printf("9  - Salvar jogo\n");
      printf("10 - Carregar jogo\n");
      printf("11 - Resetar jogo\n");
      printf("12 - Sair\n");


      printf("\nEscolha uma opcao: ");
      scanf("%d",&opcao);
      system("cls");

      //TODO [RCS] Criar módulo separado para cada uma das opcoes.
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
            MenuRemoverPeca(ppPartida);
         }break;
      case 9:
         {
            MenuSalvarPartida(ppPartida);
         }break;
      case 10:
         {
            MenuCarregarPartida(&ppPartida);
         }break;
      case 11:
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
      printf("\nErro ao inserir - Casa nao existe!\n");
      system("pause");
      system("cls");
      return;
   }

   condRet = PAR_InserirPeca(ppPartida,nome,time);

   if(condRet == PAR_CondRetPecaNaoEncontrada)
   {
      printf("\nErro ao inserir - Peca nao encontrada!\n");
      system("pause");
      system("cls");
      return;
   }

   printf("\nPeca inserida no time com sucesso!\n");
   system("pause");
   system("cls");

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
   printf("Movimentos ([n]coordenada): ");
   scanf("%s", passos);
   printf("Tipo de movimento(Anda | Voa): ");
   scanf("%s",tipoMov);

   ispCondRet = ISP_LerTipoMovimento(tipoMov,&tipoMovimento);

   if(ispCondRet != ISP_CondRetOK)
   {
      printf("\nTipo de movimento invalido\n");
      system("pause");
      system("cls");
      return;
   }

   ISP_LerPassos(passos,&pPassos);

   PAR_CriarPeca(ppPartida, nome, pPassos, tipoMovimento);

   printf("\nPeca cadastrada com sucesso!\n");
   system("pause");
   system("cls");
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
      printf("\nTipo de movimento invalido\n");
      system("pause");
      system("cls");
      return;
   }

   ISP_LerPassos(novosPassos,&pPassos);

   parCondRet = PAR_AlterarPeca(ppPartida,nomeAtual,novoNome,pPassos,novoTipoMovimento);

   if(parCondRet != PAR_CondRetOK)
   {
      printf("\nErro ao alterar peca!\n");
      system("pause");
      system("cls");
   }

   printf("\nPeca alterada com sucesso!\n");
   system("pause");
   system("cls");

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
      printf("\nErro ao remover - Casa nao existe!\n");
      system("pause");
      system("cls");
      return;
   }

   condRet = PAR_RemoverPeca(ppPartida);

   if(condRet == PAR_CondRetPecaNaoEncontrada)
   {
      printf("\nErro ao remover - casa esta vazia!\n");
      system("pause");
      system("cls");
      return;
   }

   printf("\nPeca removida com sucesso!\n");
   system("pause");
   system("cls");
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
      printf("\nErro ao salvar partida!\n");
      system("pause");
      system("cls");
      return;
   }

   printf("\nPartida salva com sucesso!\n");
   system("pause");
   system("cls");
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
      printf("\nErro ao carregar partida!\n");
      system("pause");
      system("cls");
      return;
   }

   printf("\nPartida carregar com sucesso!\n");
   system("pause");
   system("cls");

}

static void MenuInserirRei(PAR_tppPartida* ppPartida)
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
      printf("\nErro ao inserir - Casa nao existe!\n");
      system("pause");
      system("cls");
      return;
   }

   condRet = PAR_InserirRei(ppPartida);

   if(condRet != PAR_CondRetOK)
   {
      printf("\nErro ao inserir o rei!\n");
      system("pause");
      system("cls");
      return;
   }

   printf("\nRei inserido com sucesso!\n");
   system("pause");
   system("cls");

}