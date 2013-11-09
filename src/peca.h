#if ! defined( PECA_ )
#define PECA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo matriz
*
*  Arquivo gerado:              PECA.H
*  Letras identificadoras:      PEC
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor     Data     Observa��es
*       1.00   hg e nf  15/09/2013 Adapta��o do m�dulo para manipular matrizes
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e
*     explorar matrizes.
*     A matriz possui uma cabe�a que cont�m uma refer�ncia para a ra�z da
*     matriz e outra para um n� corrente da matriz.
*     O modulo permite a manipula��o de m�ltiplas matrizes, por�m as fun��es
*     s� manipulam uma matriz de cada vez.
*     Ao iniciar a execu��o do programa n�o existe matriz.
*     A matriz poder� estar vazia. Neste caso a origem e o n� corrente
*     ser�o nulos, embora a cabe�a esteja definida.
*     O n� corrente ser� nulo se e somente se a matriz estiver vazia.
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
   /* N�o criou n� origem */

   PEC_CondRetNaoEhNo = 2 ,
   /* N�o � n� na dire��o desejada */

   PEC_CondRetMatrizNaoExiste = 3 ,
   /* Matriz n�o existe */

   PEC_CondRetNaoTemCorrente = 4 ,
   /* Matriz est� vazia */

   PEC_CondRetFaltouMemoria = 5 ,
   /* Faltou mem�ria ao alocar dados */
   PEC_CondRetPecaNaoEncontrada = 6

} PEC_tpCondRet ;


PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca *ppPeca, char* nome, char* passos, PEC_tpTipoMovimento tipoMovimento);
void PEC_ObterNomeModeloPEca(PEC_tppPeca ppPeca, char *nomePeca);
#undef PECA_EXT

/********** Fim do m�dulo de defini��o: M�dulo matriz **********/

#else
#endif
