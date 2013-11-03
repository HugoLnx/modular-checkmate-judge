#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"mem_manager.h"
#include"input_string_parser.h"
#include"tabuleiro.h"


int main()
{
   int opcao = -1;
   TAB_tpMatriz **ppTabuleiro = NULL;

   TAB_CriarTabuleiro(&ppTabuleiro);

   while(opcao != 11)
   {
      printf("1  - Cadastrar pecas\n");
      printf("2  - Alterar pecas\n");
      printf("3  - Inserir pecas para o jogador ALIADO\n");
      printf("4  - Inserir pecas para o jogador INIMIGO\n");
      printf("5  - Inserir rei para jogador INIMIGO\n");
      printf("6  - Exibir tabuleiro\n");
      printf("7  - Checar xeque mate\n");
      printf("8  - Salvar jogo\n");
      printf("9  - Carregar jogo\n");
      printf("10  - Resetar jogo\n");
      printf("11 - Sair\n");


      printf("\nEscolha uma opcao: ");
      scanf("%d",&opcao);
      system("cls");

      //TODO [RCS] Criar módulo separado para cada uma das opcoes.
      switch(opcao)
      {
      case 1:
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

         }break;

      case 2:
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

         }break;
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