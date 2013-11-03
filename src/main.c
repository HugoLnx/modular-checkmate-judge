#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"mem_manager.h"
#include"input_string_parser.h"
#include"tabuleiro.h"

static void MenuInserirPeca(TAB_tpMatriz** ppTabuleiro, const int time);
static void MenuCadastrarPeca(TAB_tpMatriz** ppTabuleiro);
static void MenuAlterarPeca(TAB_tpMatriz** ppTabuleiro);
static void MenuRemoverPeca(TAB_tpMatriz** ppTabuleiro);

int main()
{
   int opcao = -1;
   TAB_tpMatriz **ppTabuleiro = NULL;

   TAB_CriarTabuleiro(&ppTabuleiro);

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
      printf("10  - Carregar jogo\n");
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
            MenuCadastrarPeca(ppTabuleiro);

         }break;

      case 2:
         {
            MenuAlterarPeca(ppTabuleiro);

         }break;

      case  3:
         {
            MenuInserirPeca(ppTabuleiro,0);

         }break;

      case 4:
         {
            MenuInserirPeca(ppTabuleiro,1);

         }break;
      case 6:
         {
            MenuRemoverPeca(ppTabuleiro);
         }
      case 11:
         {
            TAB_DestruirMatriz(&ppTabuleiro);
            TAB_CriarTabuleiro(&ppTabuleiro);

         }break;

      default:
         {
            printf("Opcao invalida\n");

         }break;
      }
   }

   return 0;
}

static void MenuInserirPeca(TAB_tpMatriz** ppTabuleiro, const int time)
{
   //TODO [RCS] checar porque não consigo usar TAB_tpTimePeca

   char *nome, *nomeCasa;
   TAB_tpCondRet tabCondRet;

   MEM_Alloc(sizeof(char)*20,(void**)&nome);
   MEM_Alloc(sizeof(char)*2,(void**)&nomeCasa);

   printf("Nome da peca: ");
   scanf("%s", nome);

   printf("Nome da casa que deseja inserir a peca: ");
   scanf("%s", nomeCasa);

   nomeCasa[0] = toupper(nomeCasa[0]);

   tabCondRet = TAB_IrCasa(ppTabuleiro,nomeCasa);

   if(tabCondRet == TAB_CondRetNaoEhNo)
   {
      printf("\nErro ao inserir - Casa nao existe!\n");
      system("pause");
      system("cls");
      return;
   }

   tabCondRet = TAB_InserirPeca(ppTabuleiro,nome,time);

   if(tabCondRet == TAB_CondRetPecaNaoEncontrada)
   {
      printf("\nErro ao inserir - Peca nao encontrada!\n");
      system("pause");
      system("cls");
      return;
   }

   printf("\nPeca inserida com sucesso!\n");
   system("pause");
   system("cls");

}

static void MenuCadastrarPeca(TAB_tpMatriz** ppTabuleiro)
{
   char* nome;
   char* passos;
   int tipoMov;

   TAB_tpTipoMovimento tipoMovimento;
   LIS_tppLista pPassos;

   MEM_Alloc(sizeof(char)*10,(void**)&nome);
   MEM_Alloc(sizeof(char)*200,(void**)&passos);

   printf("Nome da peca:(20 caracteres) ");
   scanf("%s",nome);
   printf("\nMovimentos: ");
   scanf("%s", passos);
   printf("Tipo de movimento(0 - Anda | 1 - Voa): ");
   scanf("%d", &tipoMov);

   ISP_LerPassos(passos,&pPassos);
   tipoMovimento = (TAB_tpTipoMovimento)tipoMov;

   TAB_CriarPeca(ppTabuleiro, nome, pPassos, tipoMovimento);

   printf("\nPeca cadastrada com sucesso!\n");
   system("pause");
   system("cls");
}

static void MenuAlterarPeca(TAB_tpMatriz** ppTabuleiro)
{
   char *nomeAtual, *novoNome, *novosPassos;
   int novoTipo;
   TAB_tpTipoMovimento novoTipoMovimento;
   LIS_tppLista pPassos;

   MEM_Alloc(sizeof(char)*10,(void**)&nomeAtual);
   MEM_Alloc(sizeof(char)*10,(void**)&novoNome);
   MEM_Alloc(sizeof(char)*200,(void**)&novosPassos);

   printf("\nNome da peca que quer alterar(20 caracteres): ");
   scanf("%s", nomeAtual);
   printf("\nNome novo nome: ");
   scanf("%s", novoNome);
   printf("\nNovo movimento: ");
   scanf("%s", novosPassos);
   printf("\nNovo tipo de movimento (0 - Anda | 1 - Voa): ");
   scanf("%i", &novoTipo);

   ISP_LerPassos(novosPassos,&pPassos);
   novoTipoMovimento = (TAB_tpTipoMovimento)novoTipo;

   TAB_AlterarPeca(ppTabuleiro,nomeAtual,novoNome,pPassos,novoTipoMovimento);

   printf("\nPeca alterada com sucesso!\n");
   system("pause");
   system("cls");

}

static void MenuRemoverPeca(TAB_tpMatriz** ppTabuleiro)
{
   char *nomeDaCasa;
   TAB_tpCondRet tabCondRet;
   MEM_Alloc(sizeof(char)*2,(void**)&nomeDaCasa);
   printf("Nome da casa onde esta a peca a ser removida: ");
   scanf("%s",nomeDaCasa);

   tabCondRet = TAB_IrCasa(ppTabuleiro,nomeDaCasa);

   if(tabCondRet == TAB_CondRetNaoEhNo)
   {
      printf("\nErro ao remover - Casa nao existe!\n");
      system("pause");
      system("cls");
      return;
   }

   tabCondRet = TAB_RemoverPeca(ppTabuleiro);
   if(tabCondRet == TAB_CondRetPecaNaoEncontrada)
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

