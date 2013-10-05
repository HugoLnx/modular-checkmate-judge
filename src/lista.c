/***************************************************************************
*  Módulo de implementação: LIS  Lista duplamente encadeada genérica
*
*  Arquivo gerado:              lista.c
*  Letras identificadoras:      LIS
*
*	Autores:
*     - rc: Robert Correa
*
*  Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       rc    12/set/2013 Adaptação da função CriarLista para ser testavel e inserção de somente valores char.
*     2       rc    15/set/2013 Implementação e adaptação do restante das funções para trabalhar somente com o tipo char.
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
*  Tipo de dados: LIS Descritor da cabeça de lista
***********************************************************************/

   typedef struct LIS_stLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* Número de elementos da lista */

       void (*destruirValor)(void * pValor);
            /* Lógica responsável por destruir o valor da lista */

       
       int (*compararValores)(void * pValor1 , void * pValor2);
            /* Lógica responsável por comparar dois valores */

   } LIS_tpLista ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void * pValor ) ;

   static void LimparCabeca( LIS_tppLista pLista ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS Criar lista
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
*  Função: LIS Destruir lista
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
*  Função: LIS Esvaziar lista
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
*  Função: LIS Inserir elemento antes
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
*  Função: LIS Inserir elemento após
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor)
      
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir após */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento após o elemento */

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
*  Função: LIS Excluir elemento
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

      /* Desencadeia à esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia à direita */

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
*  Função: LIS Obter o valor contido no elemento
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
*  Função: LIS Ir para o elemento inicial
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
*  Função: LIS Ir para o elemento final
*  ****/

   LIS_tpCondRet LIS_IrFinalLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      pLista->pElemCorr = pLista->pFimLista ;

     return LIS_CondRetOK ;

   } /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Função: LIS Avançar elemento
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

      /* Tratar avançar para frente */

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

         } /* fim ativa: Tratar avançar para frente */

      /* Tratar avançar para trás */

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

         } /* fim ativa: Tratar avançar para trás */

      /* Tratar não avançar */

         return LIS_CondRetOK ;

   }

/***************************************************************************
*
*  Função: LIS Procurar elemento contendo 
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
*  Função: LIS Esta Vazia
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
*  Função: LIS Numero de elementos
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


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  Função: LIS Criar o elemento
*
*  Descrição:
*    <descrição da função>
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
*  Função: LIS Liberar elemento da lista
*
*  Descrição:
*    <descrição da função>
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
*  Função: LIS Limpar a cabeça da lista
*
*  Descrição:
*    <descrição da função>
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista    = NULL ;
      pLista->pElemCorr    = NULL ;
      pLista->numElem      = 0 ;

   }

/********** Fim do módulo de implementação: LIS Lista duplamente encadeada genérica **********/