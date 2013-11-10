#if ! defined( ANALISE_PARTIDA_ )
#define ANALISE_PARTIDA_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              ANALISE_PARTIDA.H
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
 
#if defined( ANALISE_PARTIDA_OWN )
   #define ANALISE_PARTIDA_EXT
#else
   #define ANALISE_PARTIDA_EXT extern
#endif

#include "lista.h"
#include "direcao.h"
#include "tabuleiro.h"
#include "peca.h"
#include "modelo_peca.h"
#include "partida.h"

typedef struct APAR_stAnalise* APAR_tppAnalise;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         APAR_CondRetOK = 0 ,
               /* Executou correto */

         APAR_CondRetNaoCriouOrigem = 1 ,
               /* Não criou nó origem */

         APAR_CondRetNaoEhNo = 2 ,
               /* Não é nó na direção desejada */

         APAR_CondRetMatrizNaoExiste = 3 ,
               /* Matriz não existe */

         APAR_CondRetNaoTemCorrente = 4 ,
               /* Matriz está vazia */

         APAR_CondRetFaltouMemoria = 5 ,
               /* Faltou memória ao alocar dados */
         APAR_CondRetPecaNaoEncontrada = 6

   } APAR_tpCondRet ;

   
   APAR_tpCondRet APAR_CriarAnalise(APAR_tppAnalise *ppAnalise, PAR_tppPartida pPartida);

   APAR_tpCondRet APAR_AlgumaPegadaInimiga(APAR_tppAnalise pAnalise, int *pResposta);

   APAR_tpCondRet APAR_IrCasaRei(APAR_tppAnalise pAnalise);

/***********************************************************************
*
*  $FC Função: TAB Destruir matriz
*
*  $ED Descrição da função
*     Destrói o corpo e a cabeça da matriz, anulando a matriz corrente.
*     Faz nada caso a matriz corrente não exista.
*
*  $EP Parâmetros
*     $P ppAnalise - é o ponteiro para a matriz que será destruida.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     APAR_CondRetOK
*     APAR_CondRetMatrizNaoExiste
*
***********************************************************************/
   APAR_tpCondRet APAR_DestruirAnalise(APAR_tppAnalise *ppAnalise);

   APAR_tpCondRet APAR_IrCasa(APAR_tppAnalise pAnalise, char *nomeCasa);
   
   APAR_tpCondRet APAR_IrPara(APAR_tppAnalise pAnalise , DIR_tpDirecao direcao);

   APAR_tpCondRet APAR_CriarPeca(APAR_tppAnalise pAnalise, char *nome,
      LIS_tppLista pPassos, MPEC_tpTipoMovimento tipoMovimento);
   
   APAR_tpCondRet APAR_AlterarPeca(APAR_tppAnalise pAnalise, char *nomeAtual, char* nomeNovo,
      LIS_tppLista pNovosPassos, MPEC_tpTipoMovimento novoTipoMovimento);
   
   APAR_tpCondRet APAR_InserirPeca(APAR_tppAnalise pAnalise, char *nome, PEC_tpTimePeca time);
   
   APAR_tpCondRet APAR_RemoverPeca(APAR_tppAnalise pAnalise);



#undef ANALISE_PARTIDA_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
