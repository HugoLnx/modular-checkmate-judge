/***************************************************************************
*  $MCI Módulo de implementação: Módulo matriz
*
*  Arquivo gerado:              TABULEIRO.C
*  Letras identificadoras:      MAT
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Histórico de evolução:
*     Versão  Autor     Data     Observações
*       1.00   hg e nf  15/09/2013 Adaptação do módulo para manipular matrizes
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
*  $TC Tipo de dados: MAT Descritor do nó da matriz
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

   typedef struct stNoMatriz {
		 struct stNoMatriz * pNorte ;
               /* Ponteiro para nó adjacente ao norte
               *
               *$EED Assertivas estruturais
               *   se é o nó X é a origem, então pNorte = NULL
			   *   se pNorte do nó X != NULL então pSul de pNorte aponta para nó X */

         struct stNoMatriz * pSul ;
               /* Ponteiro para nó adjacente ao sul
               *
               *$EED Assertivas estruturais
			   *   se pSul do nó X != NULL então pNorte de pSul aponta para nó X */

		 struct stNoMatriz * pEste ;
               /* Ponteiro para nó adjacente à este
               *
               *$EED Assertivas estruturais
			   *   se pEste do nó X != NULL então pOeste de pEste aponta para nó X */

		 struct stNoMatriz * pOeste ;
               /* Ponteiro para nó adjacente à oeste
               *
               *$EED Assertivas estruturais
               *   se é o nó X é a origem, então pOeste = NULL
			   *   se pOeste do nó X != NULL então pEste de pOeste aponta para nó X */

		 struct stNoMatriz * pNordeste ;
               /* Ponteiro para nó adjacente à nordeste
               *
               *$EED Assertivas estruturais
               *   se é o nó X é a origem, então pNordeste = NULL
			   *   se pNordeste do nó X != NULL então pSudoeste de pNordeste aponta para nó X */


		 struct stNoMatriz * pSudeste ;
               /* Ponteiro para nó adjacente à sudeste
               *
               *$EED Assertivas estruturais
			   *   se pSudeste do nó X != NULL então pNoroeste de pSudeste aponta para nó X */


		 struct stNoMatriz * pNoroeste ;
               /* Ponteiro para nó adjacente à noroeste
               *
               *$EED Assertivas estruturais
               *   se é o nó X é a origem, então pNoroeste = NULL
			   *   se pNoroeste do nó X != NULL então pSudeste de pNoroeste aponta para nó X */


		 struct stNoMatriz * pSudoeste ;
               /* Ponteiro para nó adjacente à sudoeste
               *
               *$EED Assertivas estruturais
               *   se é o nó X é a origem, então pSudoeste = NULL
			   *   se pSudoeste do nó X != NULL então pNordeste de pSudoeste aponta para nó X */


         LIS_tppLista Valor ;
               /* Valor do nó */

   } tpNoMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da cabeça de uma matriz
*
*
*  $ED Descrição do tipo
*     A cabeça da matriz é o ponto de acesso para uma determinada matriz.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a matriz sem necessitar de uma pilha.
*
***********************************************************************/

   typedef struct stMatriz {

         tpNoMatriz * pNoOrigem ;
               /* Ponteiro para a origem da matriz */

         tpNoMatriz * pNoCorr ;
               /* Ponteiro para o nó corrente da matriz */

   } TAB_tpMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Direções que o nó pode ter ponteiros para outro nó.
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

/***** Protótipos das funções encapuladas no módulo *****/

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

/*****  Código das funções exportadas pelo módulo  *****/


   TAB_tpCondRet TAB_CriarTabuleiro(TAB_tpMatriz ** ppMatriz)
   {
     CriarMatriz(ppMatriz);
     InicializarMatriz(*ppMatriz, 3, 3);
   }

/***************************************************************************
*
*  Função: MAT Destruir matriz
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
	  
   } /* Fim função: MAT Destruir matriz */



/***************************************************************************
*
*  Função: MAT Obter valor corrente
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

   } /* Fim função: MAT Obter valor corrente */

   

/***************************************************************************
*
*  Função: MAT Atribuir para valor corrente
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

   } /* Fim função: MAT Atribuir valor corrente */

   

/***************************************************************************
*
*  Função: MAT Ir para nó ao norte.
*  ****/
   TAB_tpCondRet TAB_IrNoNorte( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , NORTE );
   } /* Fim função: MAT Ir para nó ao norte*/



/***************************************************************************
*
*  Função: MAT Ir para nó ao sul.
*  ****/
   TAB_tpCondRet TAB_IrNoSul( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , SUL );
   } /* Fim função: MAT Ir para nó ao sul*/



/***************************************************************************
*
*  Função: MAT Ir para nó à este.
*  ****/
   TAB_tpCondRet TAB_IrNoEste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , ESTE );
   } /* Fim função: MAT Ir para à nó este*/



/***************************************************************************
*
*  Função: MAT Ir para nó à oeste.
*  ****/
   TAB_tpCondRet TAB_IrNoOeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , OESTE );
   } /* Fim função: MAT Ir para à nó oeste*/
   



/***************************************************************************
*
*  Função: MAT Ir para nó à nordeste.
*  ****/
   TAB_tpCondRet TAB_IrNoNordeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , NORDESTE );
   } /* Fim função: MAT Ir para nó à nordeste*/
   



/***************************************************************************
*
*  Função: MAT Ir para nó à sudeste.
*  ****/
   TAB_tpCondRet TAB_IrNoSudeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , SUDESTE );
   } /* Fim função: MAT Ir para nó à sudeste*/
   



/***************************************************************************
*
*  Função: MAT Ir para nó à sudoeste.
*  ****/
   TAB_tpCondRet TAB_IrNoSudoeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , SUDOESTE );
   } /* Fim função: MAT Ir para nó à sudoeste */




/***************************************************************************
*
*  Função: MAT Ir para nó à noroeste.
*  ****/
   TAB_tpCondRet TAB_IrNoNoroeste( TAB_tpMatriz * pMatriz )
   {
	   return IrPara( pMatriz , NOROESTE );
   } /* Fim função: MAT Ir para nó à noroeste*/



/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: MAT Criar nó da matriz
*
*  $FV Valor retornado
*     Ponteiro para o nó criado.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros do nó criado estarão nulos e o valor é igual ao do
*     parâmetro.
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

   } /* Fim função: MAT Criar nó da matriz */


/***********************************************************************
*
*  $FC Função: MAT Criar nó origem da matriz
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

   } /* Fim função: MAT Criar nó origem da matriz */



/***********************************************************************
*
*  $FC Função: MAT Esvaziar matriz
*  
*  $ED Descrição da função
*  Libera a memória de todos os nós que compõe a estrutura da matriz.
*  da matriz.
*  
*  $EP Parâmetros
*     pMatriz - ponteiro para a matriz que será esvaziada.
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
	   
   } /* Fim função: MAT Destruir a estrutura da matriz */




/***********************************************************************
*
*  $FC Função: MAT Get nó adjacente
*  
*  $ED Descrição da função
*     Recupera o ponteiro para um nó adjacente
*     Exemplo de uso: GetAdjacente(noOrigem, ESTE)
*  
*  $EP Parâmetros
*     pNo - ponteiro para nó que será usado como referência.
*     dir - representa a direção à qual será buscado o nó.
*
*  $FV Valor retornado
*    Ponteiro para nó adjacente na direção passada por
*    parâmetro.
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
   }  /* Fim função: MAT Recupera o ponteiro para um nó adjacente*/



/***********************************************************************
*
*  $FC Função: MAT Constroi a primeira coluna da matriz.
*  
*  $ED Descrição da função
*  Essa função é chamada no momento de inicialização da matriz para
*  criar a primeira coluna com o número de linhas correto e referenciando
*  todos os nós adjacentes nas direções norte e sul
*
*  $EP Parâmetros
*     pNoOrigem - ponteiro para o nó origem da matriz.
*     QntLinhas - quantidade de linhas que a coluna terá.
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
   }  /* Fim função: MAT Construi a primeira coluna da matriz */



/***********************************************************************
*
*  $FC Função: MAT Adiciona coluna.
*  
*  $ED Descrição da função
*  Adiciona mais uma coluna à matriz, mantendo o número de linhas e
*  referenciando os nós adjacentes em todas as 8 direções.
*
*  $EP Parâmetros
*     pMatriz - ponteiro para matriz que será manipulada.
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
   }  /* Fim função: MAT Adiciona Coluna */



/***********************************************************************
*
*  $FC Função: MAT Apontar de volta em todas as direções.
*  
*  $ED Descrição da função
*  A função faz com que os adjacentes de um nó referenciem à ele.
*  
*  $EP Parâmetros
*     pNo - ponteiro para nó que é referenciado por cada direção.
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
   }  /* Fim função: MAT Apontar de volta em todas as direções */


      


/***************************************************************************
*
*  $FC Função: MAT Ir para nó genérico.
*  
*  $ED Descrição da função
*  Muda o nó corrente da matriz para o nó na direção apontada
*  
*  $EP Parâmetros
*     pMatriz - ponteiro para matriz que manipulada.
*     direcao - representa a direção que o nó corrente navegará.
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

   } /* Fim função: MAT Ir para nó genérico */


   
/***********************************************************************
*
*  $FC Função: TAB Criar matriz
*
*  $ED Descrição da função
*     Cria uma nova matriz vazia.
*     Caso já exista uma matriz, esta será destruída.
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
*  $FC Função: TAB Inicializar a matriz
*
*  $EP Parâmetros
*     $P pMatriz - matriz que será inicializada.
*                    Este parâmetro é passado por referência.
*     $P Linhas - quantidade de linhas que a matriz terá.
*     $P Colunas - quantidade de colunas que a matriz terá.
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

/********** Fim do módulo de implementação: Módulo matriz **********/