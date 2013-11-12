#if ! defined( DIRECAO_ )
#define DIRECAO_
/***************************************************************************
*
*  M�dulo de defini��o: DIR  Dire��o
*
*  Arquivo gerado:              direcao.h
*  Letras identificadoras:      DIR
*
*	Autores:
*     - hg: Hugo Roque
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data             Observa��es
*     1       hg       11/nov/2013      Manipula��o b�sica de dire��o
*
*  Descri��o do m�dulo
*     M�dulo respons�vel por opera��es com dire��o.
*
***************************************************************************/
 
#if defined( DIRECAO_OWN )
   #define DIRECAO_EXT
#else
   #define DIRECAO_EXT extern
#endif

#define TOTAL_DIRECOES 8

/***********************************************************************
*
*  Tipo de dados: DIR Dire��es
*
*
*  Descri��o do tipo
*     Representa��o de todas as dire��es dispon�veis.
*
***********************************************************************/
typedef enum {
   NORTE    = 0,

   NORDESTE = 1,

   ESTE     = 2,

   SUDESTE  = 3,  

   SUL      = 4,
   
   SUDOESTE = 5,

   OESTE    = 6,

   NOROESTE = 7
} DIR_tpDirecao;


/***********************************************************************
*
*  Tipo de dados: DIR Condi��es de retorno
*
*
*  Descri��o do tipo
*     Condi��es de retorno das fun��es exportadas.
*
***********************************************************************/
typedef enum {

      DIR_CondRetOK = 0 ,
            /* Executou correto */

      DIR_CondRetFaltouMemoria = 1 ,
            /* Faltou mem�ria ao alocar dados */

      DIR_CondRetNaoPodeSeTornarString
} DIR_tpCondRet;


/***********************************************************************
*
*  Fun��o: DIR Dire��o orientada para
*
*  Descri��o
*     Mudar orienta��o da dire��o do padr�o NORTE para
*     alguma outra dire��o qualquer.
*
*  Par�metros
*     direcao     - Dire��o base.
*     orientacao  - Dire��o da orienta��o.
*     dirRetorno - Refer�ncia para retornar a dire��o resultante.
*
*  Condi��es de retorno
*     DIR_CondRetOK;
*
*  Retorno por refer�ncia
*     dirRetorno - Retorna uma nova dire��o que � resultado da dire��o base
*                   orientada para a dire��o da orienta��o.
*
*  Assertivas de entrada
*     - dirRetorno � um ponteiro v�lido.
*
*  Assertivas de saida
*     - dirRetorno aponta para a dire��o resultante.
*
***********************************************************************/
DIR_tpCondRet DIR_DirecaoOrientadaPara(DIR_tpDirecao direcao,
   DIR_tpDirecao orientacao, DIR_tpDirecao *dirRetorno);


/***********************************************************************
*
*  Fun��o: DIR Dire��o como string
*
*  Descri��o
*     Cria uma vers�o string da dire��o.
*
*  Par�metros
*     direcao     - Dire��o � ser convertida.
*     pRetornoStr - Refer�ncia para retornar a string representando a dire��o.
*
*  Condi��es de retorno
*     DIR_CondRetOK
*     DIR_CondRetFaltouMemoria
*     DIR_CondRetNaoPodeSeTornarString
*
*  Retorno por refer�ncia
*     pRetornoStr - Retorna uma string caso seja poss�vel fazer a convers�o.
*
*  Assertivas de entrada
*     - dire��o est� entre um dos 8 pontos cardeais.
*     - pRetornoStr � um ponteiro v�lido.
*
*  Assertivas de saida
*     - pRetornoStr aponta para uma string que representa a dire��o.
*
***********************************************************************/
DIR_tpCondRet DIR_DirecaoComoString(DIR_tpDirecao direcao, char **pRetornoStr);

#undef DIRECAO_EXT

/********** Fim do m�dulo de defini��o: M�dulo Dire��o **********/

#else
#endif
