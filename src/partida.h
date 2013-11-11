#if ! defined( PARTIDA_ )
#define PARTIDA_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              PARTIDA.H
*  Letras identificadoras:      TAB
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Histórico de evolução:
*     Versão  Autor     Data     Observações
*       1.00   hg e nf  15/09/2013 Adaptação do módulo para manipular matrizes
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar matrizes.
*     A matriz possui uma cabeça que contém uma referência para a raíz da
*     matriz e outra para um nó corrente da matriz.
*     O modulo permite a manipulação de múltiplas matrizes, porém as funções
*     só manipulam uma matriz de cada vez.
*     Ao iniciar a execução do programa não existe matriz.
*     A matriz poderá estar vazia. Neste caso a origem e o nó corrente
*     serão nulos, embora a cabeça esteja definida.
*     O nó corrente será nulo se e somente se a matriz estiver vazia.
*
***************************************************************************/
 
#if defined( PARTIDA_OWN )
   #define PARTIDA_EXT
#else
   #define PARTIDA_EXT extern
#endif

#include "lista.h"
#include "direcao.h"
#include "tabuleiro.h"
#include "peca.h"
#include "modelo_peca.h"

typedef struct PAR_stPartida* PAR_tppPartida;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         PAR_CondRetOK = 0 ,
               /* Executou correto */

         PAR_CondRetNaoCriouOrigem = 1 ,
               /* Não criou nó origem */

         PAR_CondRetNaoEhNo = 2 ,
               /* Não é nó na direção desejada */

         PAR_CondRetMatrizNaoExiste = 3 ,
               /* Matriz não existe */

         PAR_CondRetNaoTemCorrente = 4 ,
               /* Matriz está vazia */

         PAR_CondRetFaltouMemoria = 5 ,
               /* Faltou memória ao alocar dados */
         PAR_CondRetPecaNaoEncontrada = 6,

         PAR_CondRetCaminhoErrado
         /* caminho para salvar e/ou carregar é inválido */

   } PAR_tpCondRet ;


   PAR_tpCondRet PAR_CriarPartida(PAR_tppPartida *ppPartida);

   //PAR_tpCondRet PAR_AlgumaPegadaInimiga(PAR_tpPartida *pPartida, int *pResposta);
   
   PAR_tpCondRet PAR_InserirRei(PAR_tppPartida pPartida);
   
   PAR_tpCondRet PAR_RemoverRei(PAR_tppPartida pPartida);
   
   PAR_tpCondRet PAR_IrCasaRei(PAR_tppPartida pPartida);
   //
   //PAR_tpCondRet PAR_EhCheckmate(PAR_tpPartida *pPartida, int *pResposta);
   //
   //PAR_tpCondRet PAR_CriarPegadas(PAR_tpPartida *pPartida);

/***********************************************************************
*
*  $FC Função: TAB Destruir matriz
*
*  $ED Descrição da função
*     Destrói o corpo e a cabeça da matriz, anulando a matriz corrente.
*     Faz nada caso a matriz corrente não exista.
*
*  $EP Parâmetros
*     $P ppPartida - é o ponteiro para a matriz que será destruida.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     PAR_CondRetOK
*     PAR_CondRetMatrizNaoExiste
*
***********************************************************************/
   PAR_tpCondRet PAR_DestruirPartida(PAR_tppPartida *ppPartida);

   PAR_tpCondRet PAR_IrCasa(PAR_tppPartida pPartida, char *nomeCasa);
   
   PAR_tpCondRet PAR_CriarPeca(PAR_tppPartida pPartida, char *nome,
      LIS_tppLista pPassos, MPEC_tpTipoMovimento tipoMovimento);
   
   PAR_tpCondRet PAR_AlterarPeca(PAR_tppPartida pPartida, char *nomeAtual, char* nomeNovo,
      LIS_tppLista pNovosPassos, MPEC_tpTipoMovimento novoTipoMovimento);
   
   PAR_tpCondRet PAR_InserirPeca(PAR_tppPartida pPartida, char *nome, PEC_tpTimePeca time);
   
   PAR_tpCondRet PAR_RemoverPeca(PAR_tppPartida pPartida);


   PAR_tpCondRet PAR_Salvar(PAR_tppPartida ppPartida, char *caminho);

   PAR_tpCondRet PAR_ObterPeca(PAR_tppPartida pPartida, PEC_tppPeca *ppPeca);

   PAR_tpCondRet PAR_Salvar(PAR_tppPartida ppPartida, char *caminho);

   PAR_tpCondRet PAR_Carregar(PAR_tppPartida ppPartida, char *caminho);

#undef PARTIDA_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
