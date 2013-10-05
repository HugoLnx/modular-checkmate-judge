#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  M�dulo de defini��o: LIS  Lista duplamente encadeada gen�rica
*
*  Arquivo gerado:              lista.h
*  Letras identificadoras:      LIS
*
*	Autores:
*     - rc: Robert Correa
*     - hg: Hugo Roque
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       rc    12/set/2013 Adapta��o da fun��o CriarLista para ser testavel e inser��o de somente valores char.
*     2       rc    15/set/2013 Implementa��o e adapta��o do restante das fun��es para trabalhar somente com o tipo char.
*     3       hg    10/out/2013 Adapta��o do m�dulo para trabalhar com uma lista cujos valores ter�o um tipo gen�rico.
*
*  Descri��o do m�dulo
*     Implementa listas gen�ricas duplamente encadeadas com manipula��o,
*	  ou seja, � possivel criar, inserir elementos na lista, antes,
*     ou ap�s al�m de esvaziar a lista, remover elementos, procurar elementos,
*	  navegar para o inicio e final da lista e destruir a lista
*
*     Podem existir n listas em opera��o simultaneamente.
*     As listas possuem uma cabe�a encapsulando o seu estado.
*	  
*     Cada lista armazena dados gen�ricos.
*     Cada elemento da lista n�o possui uma referencia e sim o pr�prio valor.
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct LIS_stLista * LIS_tppLista ;


/***********************************************************************
*
*  Tipo de dados: LIS Condi��es de retorno
*
*
*  Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista n�o cont�m elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* N�o encontrou o valor procurado */

         LIS_CondRetFaltouMemoria
               /* Faltou mem�ria ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  Fun��o: LIS Criar lista
*
*  Descri��o
*     Cria uma lista gen�rica duplamente encadeada.
*
*
*  Retorno
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista(LIS_tppLista* pLista , 
      void (*destruirValor)(void * pValor) ,
      int (*compararValores)(void * pValor1, void * pValor2) ) ;

/***********************************************************************
*
*  Fun��o: LIS Destruir lista
*
*  Descri��o
*     Destr�i a lista fornecida.
*     O par�metro ponteiro para a lista n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  Retorno
*     LIS_CondRetOK    - destruiu sem problemas
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de sa�da
*     <assertivas de sa�da>
*
***********************************************************************/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  Fun��o: LIS Esvaziar lista
*
*  Descri��o
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  Par�metros
*     pLista - ponteiro para a lista a ser esvaziada
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de sa�da
*     <assertivas de sa�da>
*
***********************************************************************/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  Fun��o: LIS Inserir elemento antes
*
*  Descri��o
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  Par�metros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor  - ponteiro para valor do novo elemento
*
*  Retorno
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de sa�da
*     <assertivas de sa�da>
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor) ;


/***********************************************************************
*
*  Fun��o: LIS  Inserir elemento ap�s
*
*  Descri��o da fun��o
*     Insere novo elemento ap�s o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  Par�metros
*    pLista - ponteiro para a lista onde deve ser inserido o elemento
*    pValor  -  ponteiro para o valor do novo elemento
*           
*
*  Retorno
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de sa�da
*     <assertivas de sa�da>
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor);


/***********************************************************************
*
*  Fun��o: LIS  Excluir elemento
*
*  Descri��o
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento � esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o elemento � direita, este se tornar� corrente.
*     Se este tamb�m n�o existir a lista tornou-se vazia.
*
*  Par�metros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  Retorno
*     LIS_CondRetOK         - se o elemento foi excluido
*     LIS_CondRetListaVazia - se a lista estiver vazia
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de sa�da
*     <assertivas de sa�da>
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  Fun��o: LIS Obter o valor contido no elemento
*
*  Descri��o
*     Obtem o valor contido no elemento corrente da lista
*
*  Par�metros
*     pLista - ponteiro para a lista de onde se quer o valor
*     pValor - ponteiro que ter� o valor obtido.
*
*  Retorno
*     CondRetOK         - se o elemento foi obtido
*	  CondRetListaVazia - se a lista estiver vazia
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de sa�da
*     <assertivas de sa�da>
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista, void ** ppValor ) ;

/***********************************************************************
*
*  Fun��o: LIS Ir para o elemento inicial
*
*  Descri��o
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista est� vazia.
*
*  Par�metros
*     pLista - ponteiro para a lista a manipular
*     ppValor - ponteiro para o ponteiro do valor
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de sa�da
*     <assertivas de sa�da>
*
***********************************************************************/

   LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  Fun��o: LIS Ir para o elemento final
*
*  Descri��o
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista est� vazia.
*
*  Par�metros
*     pLista - ponteiro para a lista a manipular
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de sa�da
*     <assertivas de sa�da>
*
***********************************************************************/

   LIS_tpCondRet LIS_IrFinalLista( LIS_tppLista pLista ) ;

   /***********************************************************************
*
*  Fun��o: LIS Avan�ar elemento
*
*  Descri��o
*     Avan�a o elemento corrente numElem elementos na lista
*     Se numElem for positivo avan�a em dire��o ao final
*     Se numElem for negativo avan�a em dire��o ao in�cio
*     numElem pode ser maior do que o n�mro de elementos existentes na
*               dire��o desejada
*     Se numElem for zero somente verifica se a lista est� vazia
*
*  Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o n�mero de elementos a andar
*
*  Retorno
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista est� vazia
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de sa�da
*     <assertivas de sa�da>
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;

/***********************************************************************
*
*  Fun��o: LIS Procurar elemento contendo valor
*
*  Descri��o
*     Procura o elemento que referencia o valor dado.
*
*  Par�metros
*     pLista  - ponteiro para a lista onde procura
*     pValor   - ponteiro para o ponteiro do valor procurado
*
*  Retorno
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente � o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que cont�m o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro n�o foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de sa�da
*     <assertivas de sa�da>
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor) ;
/***********************************************************************
*
*  Fun��o: LIS Esta Vazia
*
*  Descri��o
*     Checa se a lista est� vazia
*
*  Par�metros
*     pLista   - ponteiro para a lista onde procura
*     pResposta - ponteiro para valor de resposta
*
*  Retorno
*     LIS_CondRetOK  - Elemento corrente est� nulo, indicando que a lista esta vazia
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de sa�da
*     <assertivas de sa�da>
*
***********************************************************************/

    LIS_tpCondRet LIS_EstaVazia( LIS_tppLista pLista ,
                                              int *pResposta ) ;

	/***********************************************************************
*
*  Fun��o: LIS Num Elementos
*
*  Descri��o
*     Pega o numero de elementos contido na lista
*
*  Par�metros
*     pLista        - ponteiro para a lista onde procura
*     pNumElementos - ponteiro que ira armazenar o numero de elementos da lista
*
*  Retorno
*     LIS_CondRetOK  - Retornou o numero de elementos
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de sa�da
*     <assertivas de sa�da>
*
***********************************************************************/

	LIS_tpCondRet LIS_NumELementos(LIS_tppLista pLista ,
                                      int *pNumElementos);

/***********************************************************************/
#undef LISTA_EXT

/********** Fim do m�dulo de defini��o: LIS  Lista duplamente encadeada **********/

#else
#endif
