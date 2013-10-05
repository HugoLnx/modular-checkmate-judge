#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  Módulo de definição: LIS  Lista duplamente encadeada genérica
*
*  Arquivo gerado:              lista.h
*  Letras identificadoras:      LIS
*
*	Autores:
*     - rc: Robert Correa
*     - hg: Hugo Roque
*
*  Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       rc    12/set/2013 Adaptação da função CriarLista para ser testavel e inserção de somente valores char.
*     2       rc    15/set/2013 Implementação e adaptação do restante das funções para trabalhar somente com o tipo char.
*     3       hg    10/out/2013 Adaptação do módulo para trabalhar com uma lista cujos valores terão um tipo genérico.
*
*  Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas com manipulação,
*	  ou seja, é possivel criar, inserir elementos na lista, antes,
*     ou após além de esvaziar a lista, remover elementos, procurar elementos,
*	  navegar para o inicio e final da lista e destruir a lista
*
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*	  
*     Cada lista armazena dados genéricos.
*     Cada elemento da lista não possui uma referencia e sim o próprio valor.
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_stLista * LIS_tppLista ;


/***********************************************************************
*
*  Tipo de dados: LIS Condições de retorno
*
*
*  Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista não contém elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         LIS_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  Função: LIS Criar lista
*
*  Descrição
*     Cria uma lista genérica duplamente encadeada.
*
*
*  Retorno
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista(LIS_tppLista* pLista , 
      void (*destruirValor)(void * pValor) ,
      int (*compararValores)(void * pValor1, void * pValor2) ) ;

/***********************************************************************
*
*  Função: LIS Destruir lista
*
*  Descrição
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  Retorno
*     LIS_CondRetOK    - destruiu sem problemas
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saída
*     <assertivas de saída>
*
***********************************************************************/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  Função: LIS Esvaziar lista
*
*  Descrição
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saída
*     <assertivas de saída>
*
***********************************************************************/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  Função: LIS Inserir elemento antes
*
*  Descrição
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  Parâmetros
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
*  Assertivas de saída
*     <assertivas de saída>
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor) ;


/***********************************************************************
*
*  Função: LIS  Inserir elemento após
*
*  Descrição da função
*     Insere novo elemento após o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  Parâmetros
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
*  Assertivas de saída
*     <assertivas de saída>
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor);


/***********************************************************************
*
*  Função: LIS  Excluir elemento
*
*  Descrição
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento à esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  Retorno
*     LIS_CondRetOK         - se o elemento foi excluido
*     LIS_CondRetListaVazia - se a lista estiver vazia
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saída
*     <assertivas de saída>
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  Função: LIS Obter o valor contido no elemento
*
*  Descrição
*     Obtem o valor contido no elemento corrente da lista
*
*  Parâmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*     pValor - ponteiro que terá o valor obtido.
*
*  Retorno
*     CondRetOK         - se o elemento foi obtido
*	  CondRetListaVazia - se a lista estiver vazia
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saída
*     <assertivas de saída>
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista, void ** ppValor ) ;

/***********************************************************************
*
*  Função: LIS Ir para o elemento inicial
*
*  Descrição
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista está vazia.
*
*  Parâmetros
*     pLista - ponteiro para a lista a manipular
*     ppValor - ponteiro para o ponteiro do valor
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saída
*     <assertivas de saída>
*
***********************************************************************/

   LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista pLista ) ;

/***********************************************************************
*
*  Função: LIS Ir para o elemento final
*
*  Descrição
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista está vazia.
*
*  Parâmetros
*     pLista - ponteiro para a lista a manipular
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saída
*     <assertivas de saída>
*
***********************************************************************/

   LIS_tpCondRet LIS_IrFinalLista( LIS_tppLista pLista ) ;

   /***********************************************************************
*
*  Função: LIS Avançar elemento
*
*  Descrição
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança em direção ao final
*     Se numElem for negativo avança em direção ao início
*     numElem pode ser maior do que o númro de elementos existentes na
*               direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  Retorno
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista está vazia
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saída
*     <assertivas de saída>
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;

/***********************************************************************
*
*  Função: LIS Procurar elemento contendo valor
*
*  Descrição
*     Procura o elemento que referencia o valor dado.
*
*  Parâmetros
*     pLista  - ponteiro para a lista onde procura
*     pValor   - ponteiro para o ponteiro do valor procurado
*
*  Retorno
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contém o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro não foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saída
*     <assertivas de saída>
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor) ;
/***********************************************************************
*
*  Função: LIS Esta Vazia
*
*  Descrição
*     Checa se a lista está vazia
*
*  Parâmetros
*     pLista   - ponteiro para a lista onde procura
*     pResposta - ponteiro para valor de resposta
*
*  Retorno
*     LIS_CondRetOK  - Elemento corrente está nulo, indicando que a lista esta vazia
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saída
*     <assertivas de saída>
*
***********************************************************************/

    LIS_tpCondRet LIS_EstaVazia( LIS_tppLista pLista ,
                                              int *pResposta ) ;

	/***********************************************************************
*
*  Função: LIS Num Elementos
*
*  Descrição
*     Pega o numero de elementos contido na lista
*
*  Parâmetros
*     pLista        - ponteiro para a lista onde procura
*     pNumElementos - ponteiro que ira armazenar o numero de elementos da lista
*
*  Retorno
*     LIS_CondRetOK  - Retornou o numero de elementos
*
*  Assertivas de entrada
*     <assertivas de entrada>
*
*  Assertivas de saída
*     <assertivas de saída>
*
***********************************************************************/

	LIS_tpCondRet LIS_NumELementos(LIS_tppLista pLista ,
                                      int *pNumElementos);

/***********************************************************************/
#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif
