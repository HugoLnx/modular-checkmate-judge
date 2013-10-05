/***************************************************************************
*  M�dulo de implementa��o: LIS  Lista duplamente encadeada gen�rica
*
*  Arquivo gerado:              lista.c
*  Letras identificadoras:      LIS
*
*	Autores:
*     - rc: Robert Correa
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       rc    12/set/2013 Adapta��o da fun��o CriarLista para ser testavel e inser��o de somente valores char.
*     2       rc    15/set/2013 Implementa��o e adapta��o do restante das fun��es para trabalhar somente com o tipo char.
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "lista.h"
#undef LISTA_OWN

/***********************************************************************
*  Tipo de dados: LIS Elemento da lista
***********************************************************************/

   typedef struct stElemLista {

         void * pValor ;
               /* valor contido no elemento */

         struct stElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct stElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpElemLista ;

/***********************************************************************
*  Tipo de dados: LIS Descritor da cabe�a de lista
***********************************************************************/

   typedef struct LIS_stLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* N�mero de elementos da lista */

       void (*destruirValor)(void * pValor);
            /* L�gica respons�vel por destruir o valor da lista */

       
       int (*compararValores)(void * pValor1 , void * pValor2);
            /* L�gica respons�vel por comparar dois valores */

   } LIS_tpLista ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void * pValor ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: LIS Criar lista
*  ****/

   LIS_tpCondRet LIS_CriarLista(LIS_tppLista* ppLista,
      void (*destruirValor)(void * pValor),
      int (*compararValores)(void * pValor1, void * pValor2) )
   {
     LIS_tpLista* pLista;

      pLista = ( LIS_tpLista *) malloc( sizeof( LIS_tpLista )) ;
      if ( pLista == NULL )
      {
         return LIS_CondRetFaltouMemoria ;
      } /* if */

      LimparCabeca(pLista);

     pLista->destruirValor = destruirValor;
     pLista->compararValores = compararValores;

     *ppLista = pLista;

     return LIS_CondRetOK;

   }

/***************************************************************************
*
*  Fun��o: LIS Destruir lista
*  ****/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

     return LIS_CondRetOK;

   }

/***************************************************************************
*
*  Fun��o: LIS Esvaziar lista
*  ****/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

      LimparCabeca( pLista ) ;

     return LIS_CondRetOK;

   }


/***************************************************************************
*
*  Fun��o: LIS Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor)
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir antes */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento antes do elemento corrente */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pAnt != NULL )
            {
               pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
               pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } /* if */

         pLista->pElemCorr = pElem ;

         return LIS_CondRetOK ;

   }


/***************************************************************************
*
*  Fun��o: LIS Inserir elemento ap�s
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor)
      
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir ap�s */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento ap�s o elemento */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   }


/***************************************************************************
*
*  Fun��o: LIS Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      /* Desencadeia � esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia � direita */

         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   }

/***************************************************************************
*
*  Fun��o: LIS Obter o valor contido no elemento
*  ****/

   LIS_tpCondRet LIS_ObterValor(LIS_tppLista pLista, void ** ppValor )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
        return LIS_CondRetListaVazia ;
      } /* if */

     *ppValor = pLista->pElemCorr->pValor ;

     return LIS_CondRetOK ;
   }

/***************************************************************************
*
*  Fun��o: LIS Ir para o elemento inicial
*  ****/

   LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pOrigemLista ;

     return LIS_CondRetOK ;

   }

/***************************************************************************
*
*  Fun��o: LIS Ir para o elemento final
*  ****/

   LIS_tpCondRet LIS_IrFinalLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pFimLista ;

     return LIS_CondRetOK ;

   } /* Fim fun��o: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Fun��o: LIS Avan�ar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avan�ar para frente */

         if ( numElem > 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avan�ar para frente */

      /* Tratar avan�ar para tr�s */

         else if ( numElem < 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avan�ar para tr�s */

      /* Tratar n�o avan�ar */

         return LIS_CondRetOK ;

   }

/***************************************************************************
*
*  Fun��o: LIS Procurar elemento contendo 
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor)
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         if ( pLista->compararValores(pElem->pValor, pValor) == 0 )
         {
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */

      return LIS_CondRetNaoAchou ;

   }

   /***************************************************************************
*
*  Fun��o: LIS Esta Vazia
*  ****/

   LIS_tpCondRet LIS_EstaVazia( LIS_tppLista pLista ,
                                              int *pResposta )
   {
	   if(pLista->pElemCorr == NULL)
	   {
	      *pResposta = 1;
	   }
	   else
	   {
		   *pResposta = 0;
	   }

	   return LIS_CondRetOK;
		
	   
   }


   /***************************************************************************
*
*  Fun��o: LIS Numero de elementos
*  ****/
   LIS_tpCondRet LIS_NumELementos(LIS_tppLista pLista ,
                                      int *pNumElementos)

   {
	   if(pLista == NULL)
	   {
			int a= 0;
	   }

	   *pNumElementos = pLista->numElem;
	   return LIS_CondRetOK;
   }


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  Fun��o: LIS Criar o elemento
*
*  Descri��o:
*    <descri��o da fun��o>
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void * pValor )
   {
      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      pLista->numElem ++ ;

      return pElem ;

   }

/***********************************************************************
*
*  Fun��o: LIS Liberar elemento da lista
*
*  Descri��o:
*    <descri��o da fun��o>
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {
      
     pLista->destruirValor( pElem->pValor ) ;
      free( pElem ) ;

      pLista->numElem-- ;

   }

/***********************************************************************
*
*  Fun��o: LIS Limpar a cabe�a da lista
*
*  Descri��o:
*    <descri��o da fun��o>
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista    = NULL ;
      pLista->pElemCorr    = NULL ;
      pLista->numElem      = 0 ;

   }

/********** Fim do m�dulo de implementa��o: LIS Lista duplamente encadeada gen�rica **********/