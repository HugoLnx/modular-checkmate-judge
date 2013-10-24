/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo matriz
*
*  Arquivo gerado:              TABULEIRO.C
*  Letras identificadoras:      MAT
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor     Data     Observa��es
*       1.00   hg e nf  15/09/2013 Adapta��o do m�dulo para manipular matrizes
*
***************************************************************************/

#include <malloc.h>
#include <stdio.h>
#include "LISTA.H"

#define TABULEIRO_OWN
#include "tabuleiro.h"
#undef TABULEIRO_OWN

typedef enum {
   ANDA = 0,
   VOA = 1
} tpTipoMovimento;

typedef struct stMovimento {
   LIS_tppLista passos;
   tpTipoMovimento tipo;
} tpMovimento;

typedef struct stPeca {
   tpMovimento *pMovimento;
   char *nome;
} tpPeca;

typedef struct stPegada {
   tpPeca peca;
   struct stPegada *pAnterior;
} tpPegada;

typedef struct stCasa {
   tpPeca *pPeca;
   LIS_tppLista pegadas;
} tpCasa;


/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor do n� da matriz
*
*
*  $ED Descri��o do tipo
*     Descreve a organiza��o do n�
*
***********************************************************************/

   typedef struct stNoMatriz {
		 struct stNoMatriz * pNorte ;
               /* Ponteiro para n� adjacente ao norte
               *
               *$EED Assertivas estruturais
               *   se � o n� X � a origem, ent�o pNorte = NULL
			   *   se pNorte do n� X != NULL ent�o pSul de pNorte aponta para n� X */

         struct stNoMatriz * pSul ;
               /* Ponteiro para n� adjacente ao sul
               *
               *$EED Assertivas estruturais
			   *   se pSul do n� X != NULL ent�o pNorte de pSul aponta para n� X */

		 struct stNoMatriz * pEste ;
               /* Ponteiro para n� adjacente � este
               *
               *$EED Assertivas estruturais
			   *   se pEste do n� X != NULL ent�o pOeste de pEste aponta para n� X */

		 struct stNoMatriz * pOeste ;
               /* Ponteiro para n� adjacente � oeste
               *
               *$EED Assertivas estruturais
               *   se � o n� X � a origem, ent�o pOeste = NULL
			   *   se pOeste do n� X != NULL ent�o pEste de pOeste aponta para n� X */

		 struct stNoMatriz * pNordeste ;
               /* Ponteiro para n� adjacente � nordeste
               *
               *$EED Assertivas estruturais
               *   se � o n� X � a origem, ent�o pNordeste = NULL
			   *   se pNordeste do n� X != NULL ent�o pSudoeste de pNordeste aponta para n� X */


		 struct stNoMatriz * pSudeste ;
               /* Ponteiro para n� adjacente � sudeste
               *
               *$EED Assertivas estruturais
			   *   se pSudeste do n� X != NULL ent�o pNoroeste de pSudeste aponta para n� X */


		 struct stNoMatriz * pNoroeste ;
               /* Ponteiro para n� adjacente � noroeste
               *
               *$EED Assertivas estruturais
               *   se � o n� X � a origem, ent�o pNoroeste = NULL
			   *   se pNoroeste do n� X != NULL ent�o pSudeste de pNoroeste aponta para n� X */


		 struct stNoMatriz * pSudoeste ;
               /* Ponteiro para n� adjacente � sudoeste
               *
               *$EED Assertivas estruturais
               *   se � o n� X � a origem, ent�o pSudoeste = NULL
			   *   se pSudoeste do n� X != NULL ent�o pNordeste de pSudoeste aponta para n� X */


         LIS_tppLista Valor ;
               /* Valor do n� */

   } tpNoMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da cabe�a de uma matriz
*
*
*  $ED Descri��o do tipo
*     A cabe�a da matriz � o ponto de acesso para uma determinada matriz.
*     Por interm�dio da refer�ncia para o n� corrente e do ponteiro
*     pai pode-se navegar a matriz sem necessitar de uma pilha.
*
***********************************************************************/

   typedef struct stMatriz {

         tpNoMatriz * pNoOrigem ;
               /* Ponteiro para a origem da matriz */

         tpNoMatriz * pNoCorr ;
               /* Ponteiro para o n� corrente da matriz */

   } TAB_tpMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Dire��es que o n� pode ter ponteiros para outro n�.
*
*
***********************************************************************/
   typedef enum {
	     NORTE = 1 ,
		 
		 SUL = 2 ,
		 
		 ESTE = 3 ,

		 OESTE = 4 ,

		 NORDESTE = 5 ,

		 SUDESTE = 6 ,

		 SUDOESTE = 7 ,

		 NOROESTE = 8

   } tpDirecao ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   tpNoMatriz * CriarNo() ;

   TAB_tpCondRet CriarNoOrigem( TAB_tpMatriz * pMatriz ) ;

   void EsvaziarMatriz( TAB_tpMatriz * pMatriz ) ;

   tpNoMatriz * GetAdjacente( tpNoMatriz * pNo , tpDirecao dir ) ;

   TAB_tpCondRet ConstruirPrimeiraColuna( tpNoMatriz * pNoOrigem , int QntLinhas ) ;

   TAB_tpCondRet AddColuna( TAB_tpMatriz * pMatriz ) ;

   void ApontarDeVoltaEmTodasAsDirecoes( tpNoMatriz * pNo ) ;
   
   TAB_tpCondRet IrPara( TAB_tpMatriz * pMatriz , tpDirecao direcao );

   TAB_tpCondRet InicializarMatriz(TAB_tpMatriz *pMatriz, int Linhas, int Colunas);

   TAB_tpCondRet CriarMatriz(TAB_tpMatriz **ppMatriz);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


   TAB_tpCondRet TAB_CriarTabuleiro(TAB_tpMatriz ** ppMatriz)
   {
     CriarMatriz(ppMatriz);
     InicializarMatriz(*ppMatriz, 3, 3);
   }

/***************************************************************************
*
*  Fun��o: MAT Destruir matriz
*  ****/
   TAB_tpCondRet TAB_DestruirMatriz( TAB_tpMatriz ** ppMatriz )
   {
		TAB_tpMatriz * pMatriz ;

		if ( ppMatriz == NULL || *ppMatriz == NULL )
		{
			return TAB_CondRetMatrizNaoExiste ;
		} /* if */

		pMatriz = *ppMatriz ;
		if ( pMatriz->pNoOrigem == NULL )
		{
			return TAB_CondRetNaoCriouOrigem;
		} /* if */
         
		EsvaziarMatriz( pMatriz ) ;
		free( pMatriz ) ;
		*ppMatriz = NULL ;

		return TAB_CondRetOK ;
	  
   } /* Fim fun��o: MAT Destruir matriz */



/***************************************************************************
*
*  Fun��o: MAT Obter valor corrente
*  ****/
   TAB_tpCondRet TAB_ObterValorCorr( TAB_tpMatriz * pMatriz , LIS_tppLista * ValorParm )
   {

      if ( pMatriz == NULL )
      {
         return TAB_CondRetMatrizNaoExiste ;
      } /* if */
      if ( pMatriz->pNoCorr == NULL )
      {
         return TAB_CondRetNaoTemCorrente ;
      } /* if */
      * ValorParm = pMatriz->pNoCorr->Valor ;

      return TAB_CondRetOK ;

   } /* Fim fun��o: MAT Obter valor corrente */

   

/***************************************************************************
*
*  Fun��o: MAT Atribuir para valor corrente
*  ****/
   TAB_tpCondRet TAB_AtribuirValorCorr( TAB_tpMatriz * pMatriz , LIS_tppLista ValorParm )
   {

      if ( pMatriz == NULL )
      {
         return TAB_CondRetMatrizNaoExiste ;
      } /* if */
      if ( pMatriz->pNoCorr == NULL )
      {
         return TAB_CondRetNaoTemCorrente ;
      } /* if */
      pMatriz->pNoCorr->Valor =ValorParm ;

      return TAB_CondRetOK ;

   } /* Fim fun��o: MAT Atribuir valor corrente */

   

/***************************************************************************
*
*  Fun��o: MAT Ir para n� ao norte.
*  ****/
   TAB_tpCondRet TAB_IrNoNorte( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , NORTE );
   } /* Fim fun��o: MAT Ir para n� ao norte*/



/***************************************************************************
*
*  Fun��o: MAT Ir para n� ao sul.
*  ****/
   TAB_tpCondRet TAB_IrNoSul( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , SUL );
   } /* Fim fun��o: MAT Ir para n� ao sul*/



/***************************************************************************
*
*  Fun��o: MAT Ir para n� � este.
*  ****/
   TAB_tpCondRet TAB_IrNoEste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , ESTE );
   } /* Fim fun��o: MAT Ir para � n� este*/



/***************************************************************************
*
*  Fun��o: MAT Ir para n� � oeste.
*  ****/
   TAB_tpCondRet TAB_IrNoOeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , OESTE );
   } /* Fim fun��o: MAT Ir para � n� oeste*/
   



/***************************************************************************
*
*  Fun��o: MAT Ir para n� � nordeste.
*  ****/
   TAB_tpCondRet TAB_IrNoNordeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , NORDESTE );
   } /* Fim fun��o: MAT Ir para n� � nordeste*/
   



/***************************************************************************
*
*  Fun��o: MAT Ir para n� � sudeste.
*  ****/
   TAB_tpCondRet TAB_IrNoSudeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , SUDESTE );
   } /* Fim fun��o: MAT Ir para n� � sudeste*/
   



/***************************************************************************
*
*  Fun��o: MAT Ir para n� � sudoeste.
*  ****/
   TAB_tpCondRet TAB_IrNoSudoeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , SUDOESTE );
   } /* Fim fun��o: MAT Ir para n� � sudoeste */




/***************************************************************************
*
*  Fun��o: MAT Ir para n� � noroeste.
*  ****/
   TAB_tpCondRet TAB_IrNoNoroeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , NOROESTE );
   } /* Fim fun��o: MAT Ir para n� � noroeste*/



/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: MAT Criar n� da matriz
*
*  $FV Valor retornado
*     Ponteiro para o n� criado.
*     Ser� NULL caso a mem�ria tenha se esgotado.
*     Os ponteiros do n� criado estar�o nulos e o valor � igual ao do
*     par�metro.
*
***********************************************************************/

   tpNoMatriz * CriarNo()
   {

      tpNoMatriz * pNo ;

      pNo = ( tpNoMatriz * ) malloc( sizeof( tpNoMatriz )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      pNo->pNorte = NULL ;
	  pNo->pSul = NULL ;
	  pNo->pEste = NULL ;
	  pNo->pOeste = NULL ;
	  pNo->pNordeste = NULL ;
	  pNo->pSudeste = NULL ;
	  pNo->pSudoeste = NULL ;
	  pNo->pNoroeste = NULL ;
      pNo->Valor  = NULL ;
      return pNo ;

   } /* Fim fun��o: MAT Criar n� da matriz */


/***********************************************************************
*
*  $FC Fun��o: MAT Criar n� origem da matriz
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*     TAB_CondRetNaoCriouOrigem
*
***********************************************************************/

   TAB_tpCondRet CriarNoOrigem(TAB_tpMatriz * pMatriz )
   {

      TAB_tpCondRet CondRet ;
      tpNoMatriz * pNo ;

      if ( pMatriz == NULL )
      {
         CondRet = CriarMatriz( &pMatriz ) ;

         if ( CondRet != TAB_CondRetOK )
         {
            return CondRet ;
         } /* if */
      } /* if */

      if ( pMatriz->pNoOrigem == NULL )
      {
         pNo = CriarNo() ;
         if ( pNo == NULL )
         {
            return TAB_CondRetFaltouMemoria ;
         } /* if */
         pMatriz->pNoOrigem = pNo ;
         pMatriz->pNoCorr = pNo ;

         return TAB_CondRetOK ;
      } /* if */

      return TAB_CondRetNaoCriouOrigem ;

   } /* Fim fun��o: MAT Criar n� origem da matriz */



/***********************************************************************
*
*  $FC Fun��o: MAT Esvaziar matriz
*  
*  $ED Descri��o da fun��o
*  Libera a mem�ria de todos os n�s que comp�e a estrutura da matriz.
*  da matriz.
*  
*  $EP Par�metros
*     pMatriz - ponteiro para a matriz que ser� esvaziada.
*
***********************************************************************/
   void EsvaziarMatriz( TAB_tpMatriz * pMatriz )
   {
	   tpNoMatriz * pNo = pMatriz->pNoOrigem;
	   tpNoMatriz * pNoExtremidade = pNo ;
	   tpNoMatriz * pProxNoExtremidade ;
	   tpNoMatriz * pProxNo ;

	   while ( pNoExtremidade != NULL )
	   {
		   pProxNoExtremidade = pNoExtremidade->pEste ;
			while ( pNo != NULL )
			{
				pProxNo = pNo->pSul ;
				free( pNo ) ;
				pNo = pProxNo ;
			}
			pNoExtremidade = pProxNoExtremidade ;
			pNo = pNoExtremidade ;
	   }
	   
	   pMatriz->pNoOrigem = NULL;
	   pMatriz->pNoCorr = NULL;
	   
   } /* Fim fun��o: MAT Destruir a estrutura da matriz */




/***********************************************************************
*
*  $FC Fun��o: MAT Get n� adjacente
*  
*  $ED Descri��o da fun��o
*     Recupera o ponteiro para um n� adjacente
*     Exemplo de uso: GetAdjacente(noOrigem, ESTE)
*  
*  $EP Par�metros
*     pNo - ponteiro para n� que ser� usado como refer�ncia.
*     dir - representa a dire��o � qual ser� buscado o n�.
*
*  $FV Valor retornado
*    Ponteiro para n� adjacente na dire��o passada por
*    par�metro.
*
***********************************************************************/
   tpNoMatriz * GetAdjacente( tpNoMatriz * pNo , tpDirecao dir )
   {
		switch( dir )
		{
		case NORTE:    return pNo->pNorte ;
		case SUL:      return pNo->pSul ;
		case ESTE:     return pNo->pEste ;
		case OESTE:    return pNo->pOeste ;
		case NORDESTE: return pNo->pNordeste ;
		case SUDESTE:  return pNo->pSudeste ;
		case SUDOESTE: return pNo->pSudoeste ;
		case NOROESTE: return pNo->pNoroeste ;
		}
		return NULL;
   }  /* Fim fun��o: MAT Recupera o ponteiro para um n� adjacente*/



/***********************************************************************
*
*  $FC Fun��o: MAT Constroi a primeira coluna da matriz.
*  
*  $ED Descri��o da fun��o
*  Essa fun��o � chamada no momento de inicializa��o da matriz para
*  criar a primeira coluna com o n�mero de linhas correto e referenciando
*  todos os n�s adjacentes nas dire��es norte e sul
*
*  $EP Par�metros
*     pNoOrigem - ponteiro para o n� origem da matriz.
*     QntLinhas - quantidade de linhas que a coluna ter�.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
***********************************************************************/
   TAB_tpCondRet ConstruirPrimeiraColuna( tpNoMatriz * pNoOrigem , int QntLinhas )
   {
	   int i ;
	   tpNoMatriz * pNoNovo ;
	   tpNoMatriz * pNoAnterior ;
	   
	   pNoAnterior = pNoOrigem ;
	   for( i = 0 ; i < QntLinhas - 1 ; i++ )
	   {
		   pNoNovo = CriarNo() ;
		   if( pNoNovo == NULL )
		   {
			   return TAB_CondRetFaltouMemoria ;
		   }
		   pNoNovo->pNorte = pNoAnterior ;
		   pNoAnterior->pSul = pNoNovo ;
		   pNoAnterior = pNoNovo ;
	   }
	   
	   return TAB_CondRetOK ;
   }  /* Fim fun��o: MAT Construi a primeira coluna da matriz */



/***********************************************************************
*
*  $FC Fun��o: MAT Adiciona coluna.
*  
*  $ED Descri��o da fun��o
*  Adiciona mais uma coluna � matriz, mantendo o n�mero de linhas e
*  referenciando os n�s adjacentes em todas as 8 dire��es.
*
*  $EP Par�metros
*     pMatriz - ponteiro para matriz que ser� manipulada.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
***********************************************************************/
   TAB_tpCondRet AddColuna( TAB_tpMatriz * pMatriz )
   {
	   tpNoMatriz * pOrigem = pMatriz->pNoOrigem ;
	   tpNoMatriz * pNoNovo ;
	   tpNoMatriz * pNoExtremidade ;

	   pNoExtremidade = pMatriz->pNoOrigem ;
	   while( pNoExtremidade->pEste != NULL )
	   {
		   pNoExtremidade = pNoExtremidade->pEste ;
	   }

	   while( pNoExtremidade != NULL )
	   {
		   pNoNovo = CriarNo() ;
		   if( pNoNovo == NULL )
		   {
			   return TAB_CondRetFaltouMemoria ;
		   }


		   pNoNovo->pOeste = pNoExtremidade ;
		   pNoNovo->pNoroeste = pNoExtremidade->pNorte ;
		   pNoNovo->pSudoeste = pNoExtremidade->pSul ;
		   pNoNovo->pNorte = pNoExtremidade->pNordeste ;
		   pNoNovo->pSul = pNoExtremidade->pSudeste ;

		   ApontarDeVoltaEmTodasAsDirecoes( pNoNovo ) ;

		   pNoExtremidade = pNoExtremidade->pSul ;
	   }

	   return TAB_CondRetOK ;
   }  /* Fim fun��o: MAT Adiciona Coluna */



/***********************************************************************
*
*  $FC Fun��o: MAT Apontar de volta em todas as dire��es.
*  
*  $ED Descri��o da fun��o
*  A fun��o faz com que os adjacentes de um n� referenciem � ele.
*  
*  $EP Par�metros
*     pNo - ponteiro para n� que � referenciado por cada dire��o.
*
***********************************************************************/
   
   void ApontarDeVoltaEmTodasAsDirecoes( tpNoMatriz * pNo )
   {
		if( pNo->pNorte != NULL )
		{
			pNo->pNorte->pSul= pNo ;
		}

		if( pNo->pSul != NULL )
		{
			pNo->pSul->pNorte= pNo ;
		}
		
		if( pNo->pEste != NULL )
		{
			pNo->pEste->pOeste = pNo ;
		}
		
		if( pNo->pOeste != NULL )
		{
			pNo->pOeste->pEste= pNo ;
		}
	   
		if( pNo->pNordeste != NULL )
		{
			pNo->pNordeste->pSudoeste = pNo ;
		}
		
		if( pNo->pSudeste != NULL )
		{
			pNo->pSudeste->pNoroeste = pNo ;
		}
		
		if( pNo->pSudoeste != NULL )
		{
			pNo->pSudoeste->pNordeste = pNo ;
		}
		
		if( pNo->pNoroeste != NULL )
		{
			pNo->pNoroeste->pSudeste = pNo ;
		}
   }  /* Fim fun��o: MAT Apontar de volta em todas as dire��es */


      


/***************************************************************************
*
*  $FC Fun��o: MAT Ir para n� gen�rico.
*  
*  $ED Descri��o da fun��o
*  Muda o n� corrente da matriz para o n� na dire��o apontada
*  
*  $EP Par�metros
*     pMatriz - ponteiro para matriz que manipulada.
*     direcao - representa a dire��o que o n� corrente navegar�.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetMatrizNaoExiste
*     TAB_CondRetNaoTemCorrente
*     TAB_CondRetNaoEhNo
*
*  ****/

   TAB_tpCondRet IrPara( TAB_tpMatriz * pMatriz , tpDirecao direcao )
   {

      if ( pMatriz == NULL )
      {
         return TAB_CondRetMatrizNaoExiste ;
      } /* if */
      if ( pMatriz->pNoCorr == NULL )
      {
         return TAB_CondRetNaoTemCorrente ;
      } /* if */

      if ( GetAdjacente( pMatriz->pNoCorr , direcao ) == NULL )
      {
		  return TAB_CondRetNaoEhNo ;
      } /* if */

	  pMatriz->pNoCorr = GetAdjacente( pMatriz->pNoCorr , direcao ) ;
	  return TAB_CondRetOK ;

   } /* Fim fun��o: MAT Ir para n� gen�rico */


   
/***********************************************************************
*
*  $FC Fun��o: TAB Criar matriz
*
*  $ED Descri��o da fun��o
*     Cria uma nova matriz vazia.
*     Caso j� exista uma matriz, esta ser� destru�da.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
***********************************************************************/
   TAB_tpCondRet CriarMatriz(TAB_tpMatriz **ppMatriz)
   {
	  TAB_tpMatriz * pMatriz ;

      if ( ppMatriz != NULL && *ppMatriz != NULL )
      {
         TAB_DestruirMatriz( ppMatriz ) ;
      } /* if */
	  
	  pMatriz = ( TAB_tpMatriz * ) malloc( sizeof( TAB_tpMatriz )) ;
      if ( pMatriz == NULL )
      {
         return TAB_CondRetFaltouMemoria ;
      } /* if */


      pMatriz->pNoOrigem = NULL ;
      pMatriz->pNoCorr = NULL ;

	  *ppMatriz = pMatriz ;

      return TAB_CondRetOK ;

   }


   


/***********************************************************************
*
*  $FC Fun��o: TAB Inicializar a matriz
*
*  $EP Par�metros
*     $P pMatriz - matriz que ser� inicializada.
*                    Este par�metro � passado por refer�ncia.
*     $P Linhas - quantidade de linhas que a matriz ter�.
*     $P Colunas - quantidade de colunas que a matriz ter�.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetMatrizNaoExiste
*     TAB_CondRetFaltouMemoria
*
***********************************************************************/
   TAB_tpCondRet InicializarMatriz(TAB_tpMatriz * pMatriz , int Linhas , int Colunas )
   {
	   int i ;
	   TAB_tpCondRet Cond ;

	   if( pMatriz == NULL )
	   {
		   return TAB_CondRetMatrizNaoExiste ;
	   }

	   if ( pMatriz->pNoOrigem != NULL )
	   {
		   EsvaziarMatriz( pMatriz ) ;
	   }

	   Cond = CriarNoOrigem( pMatriz ) ;
	   if ( Cond != TAB_CondRetOK )
	   {
		   return Cond ;
	   }

	   Cond = ConstruirPrimeiraColuna( pMatriz->pNoOrigem , Linhas) ;
	   if ( Cond != TAB_CondRetOK )
	   {
		   return Cond ;
	   }

	   for ( i = 0 ; i < Colunas - 1 ; i++ )
	   {
		   Cond = AddColuna( pMatriz ) ;
		   if ( Cond != TAB_CondRetOK )
			{
				return Cond ;
			}
	   }

	   return TAB_CondRetOK ;
   }

/********** Fim do m�dulo de implementa��o: M�dulo matriz **********/