#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"mem_manager.h"
#include"input_string_parser.h"
#include"partida.h"

// static void MenuInserirPeca(PAR_tppPartida* ppPartida, const int time);
// static void MenuCadastrarPeca(PAR_tppPartida* ppPartida);
// static void MenuAlterarPeca(PAR_tppPartida* ppPartida);
// static void MenuRemoverPeca(PAR_tppPartida* ppPartida);

int main()
{
//    int opcao = -1;
//    PAR_tppPartida *ppPartida = NULL;
// 
//    PAR_CriarPartida(ppPartida);
// 
//    while(opcao != 12)
//    {
//       printf("1  - Cadastrar pecas\n");
//       printf("2  - Alterar pecas\n");
//       printf("3  - Inserir pecas para o jogador ALIADO\n");
//       printf("4  - Inserir pecas para o jogador INIMIGO\n");
//       printf("5  - Inserir rei para jogador INIMIGO\n");
//       printf("6  - Remover peca\n");
//       printf("7  - Exibir tabuleiro\n");
//       printf("8  - Checar xeque mate\n");
//       printf("9  - Salvar jogo\n");
//       printf("10  - Carregar jogo\n");
//       printf("11 - Resetar jogo\n");
//       printf("12 - Sair\n");
// 
// 
//       printf("\nEscolha uma opcao: ");
//       scanf("%d",&opcao);
//       system("cls");
// 
//       //TODO [RCS] Criar módulo separado para cada uma das opcoes.
//       switch(opcao)
//       {
//       case 1:
//          {
//             MenuCadastrarPeca(ppPartida);
// 
//          }break;
// 
//       case 2:
//          {
//             MenuAlterarPeca(ppPartida);
// 
//          }break;
// 
//       case  3:
//          {
//             MenuInserirPeca(ppPartida,0);
// 
//          }break;
// 
//       case 4:
//          {
//             MenuInserirPeca(ppPartida,1);
// 
//          }break;
//       case 6:
//          {
//             MenuRemoverPeca(ppPartida);
//          }
//       case 11:
//          {
//             PAR_DestruirPartida(ppPartida);
//             PAR_CriarPartida(ppPartida);
// 
//          }break;
// 
//       default:
//          {
//             printf("Opcao invalida\n");
// 
//          }break;
//       }
//    }

   return 0;
}

// static void MenuInserirPeca(PAR_tppPartida* ppPartida, const int time)
// {
//    //TODO [RCS] checar porque não consigo usar PAR_tpTimePeca
// 
//    char *nome, *nomeCasa;
//    PAR_tpCondRet condRet;
// 
//    MEM_Alloc(sizeof(char)*20,(void**)&nome);
//    MEM_Alloc(sizeof(char)*2,(void**)&nomeCasa);
// 
//    printf("Nome da peca: ");
//    scanf("%s", nome);
// 
//    printf("Nome da casa que deseja inserir a peca: ");
//    scanf("%s", nomeCasa);
// 
//    nomeCasa[0] = toupper(nomeCasa[0]);
// 
//    condRet = PAR_IrCasa(*ppPartida, nomeCasa);
// 
//    if(condRet == PAR_CondRetNaoEhNo)
//    {
//       printf("\nErro ao inserir - Casa nao existe!\n");
//       system("pause");
//       system("cls");
//       return;
//    }
// 
//    // TODO: usar modulo de peça
//    //condRet = PAR_InserirPeca(*ppPartida,nome,time);
// 
//    if(condRet == PAR_CondRetPecaNaoEncontrada)
//    {
//       printf("\nErro ao inserir - Peca nao encontrada!\n");
//       system("pause");
//       system("cls");
//       return;
//    }
// 
//    printf("\nPeca inserida com sucesso!\n");
//    system("pause");
//    system("cls");
// 
// }
// 
// static void MenuCadastrarPeca(PAR_tppPartida* ppPartida)
// {
//    char* nome;
//    char* passos;
//    int tipoMov;
// 
//    PEC_tpTipoMovimento tipoMovimento;
//    LIS_tppLista pPassos;
// 
//    MEM_Alloc(sizeof(char)*10,(void**)&nome);
//    MEM_Alloc(sizeof(char)*200,(void**)&passos);
// 
//    printf("Nome da peca:(20 caracteres) ");
//    scanf("%s",nome);
//    printf("\nMovimentos: ");
//    scanf("%s", passos);
//    printf("Tipo de movimento(0 - Anda | 1 - Voa): ");
//    scanf("%d", &tipoMov);
// 
//    ISP_LerPassos(passos,&pPassos);
//    tipoMovimento = (PAR_tpTipoMovimento)tipoMov;
// 
//    // TODO: usar modulo de peça
//    //PAR_CriarPeca(ppPartida, nome, pPassos, tipoMovimento);
// 
//    printf("\nPeca cadastrada com sucesso!\n");
//    system("pause");
//    system("cls");
// }
// 
// static void MenuAlterarPeca(PAR_tppPartida* ppPartida)
// {
//    char *nomeAtual, *novoNome, *novosPassos;
//    int novoTipo;
//    PAR_tpTipoMovimento novoTipoMovimento;
//    LIS_tppLista pPassos;
// 
//    MEM_Alloc(sizeof(char)*10,(void**)&nomeAtual);
//    MEM_Alloc(sizeof(char)*10,(void**)&novoNome);
//    MEM_Alloc(sizeof(char)*200,(void**)&novosPassos);
// 
//    printf("\nNome da peca que quer alterar(20 caracteres): ");
//    scanf("%s", nomeAtual);
//    printf("\nNome novo nome: ");
//    scanf("%s", novoNome);
//    printf("\nNovo movimento: ");
//    scanf("%s", novosPassos);
//    printf("\nNovo tipo de movimento (0 - Anda | 1 - Voa): ");
//    scanf("%i", &novoTipo);
// 
//    ISP_LerPassos(novosPassos,&pPassos);
//    novoTipoMovimento = (PAR_tpTipoMovimento)novoTipo;
// 
//    // TODO: Usar modulo de criar peca
//    //PAR_AlterarPeca(ppPartida,nomeAtual,novoNome,pPassos,novoTipoMovimento);
// 
//    printf("\nPeca alterada com sucesso!\n");
//    system("pause");
//    system("cls");
// 
// }
// 
// static void MenuRemoverPeca(PAR_tppPartida* ppPartida)
// {
//    char *nomeDaCasa;
//    PAR_tpCondRet condRet;
//    MEM_Alloc(sizeof(char)*2,(void**)&nomeDaCasa);
//    printf("Nome da casa onde esta a peca a ser removida: ");
//    scanf("%s",nomeDaCasa);
// 
//    condRet = PAR_IrCasa(*ppPartida,nomeDaCasa);
// 
//    if(condRet == PAR_CondRetNaoEhNo)
//    {
//       printf("\nErro ao remover - Casa nao existe!\n");
//       system("pause");
//       system("cls");
//       return;
//    }
// 
//    // TODO: Usar modulo peça
//    //condRet = PAR_RemoverPeca(ppPartida);
//    if(condRet == PAR_CondRetPecaNaoEncontrada)
//    {
//       printf("\nErro ao remover - casa esta vazia!\n");
//       system("pause");
//       system("cls");
//       return;
//    }
// 
//    printf("\nPeca removida com sucesso!\n");
//    system("pause");
//    system("cls");
// }

