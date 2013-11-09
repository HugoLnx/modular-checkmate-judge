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

#undef PECA_EXT

/********** Fim do m�dulo de defini��o: M�dulo matriz **********/

#else
#endif
