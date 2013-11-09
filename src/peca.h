#if ! defined( PECA_ )
#define PECA_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              PECA.H
*  Letras identificadoras:      PEC
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

#if defined( PECA_OWN )
#define PECA_EXT
#else
#define PECA_EXT extern
#endif

//TODO fazer o do peca
typedef struct PEC_stPeca* PEC_tppPeca;

typedef enum {
   ANDA = 0,
   VOA = 1
} PEC_tpTipoMovimento;


typedef enum {
   ALIADA = 0,
   INIMIGA = 1
} PEC_tpTimePeca;




/***********************************************************************
*
*  $TC Tipo de dados: PEC Condicoes de retorno
*
*
***********************************************************************/

typedef enum {

   PEC_CondRetOK = 0 ,
   /* Executou correto */

   PEC_CondRetNaoCriouOrigem = 1 ,
   /* Não criou nó origem */

   PEC_CondRetNaoEhNo = 2 ,
   /* Não é nó na direção desejada */

   PEC_CondRetMatrizNaoExiste = 3 ,
   /* Matriz não existe */

   PEC_CondRetNaoTemCorrente = 4 ,
   /* Matriz está vazia */

   PEC_CondRetFaltouMemoria = 5 ,
   /* Faltou memória ao alocar dados */
   PEC_CondRetPecaNaoEncontrada = 6

} PEC_tpCondRet ;


PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca *ppPeca, char* nome, char* passos, PEC_tpTipoMovimento tipoMovimento);
void PEC_ObterNomeModeloPEca(PEC_tppPeca ppPeca, char *nomePeca);
#undef PECA_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
