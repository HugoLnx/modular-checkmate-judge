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

	while(opcao != 12)
	{
		printf("1  - Cadastrar pecas para o jogador 1\n");
		printf("2  - Cadastrar pecas para o jogador 2\n");
		printf("3  - Alterar pecas para o jogador 1\n");
		printf("4  - Alterar pecas para o jogador 2\n");
		printf("5  - Inserir pecas para o jogador 1\n");
		printf("6  - Inserir pecas para o jogador 2\n");
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
				char* nome;
				char* passos;
				int tipoMov;

				TAB_tpTipoMovimento tipoMovimento;
				LIS_tppLista pPassos;

				MEM_Alloc(sizeof(char)*10,(void**)&nome);
				MEM_Alloc(sizeof(char)*200,(void**)&passos);
				printf("Nome da peca:(20 caracters) ");
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

			default:
			{
				printf("Opcao invalida\n");

			}break;
		}
	}
	
	return 0;
}