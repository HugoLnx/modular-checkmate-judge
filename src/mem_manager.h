#if ! defined( MEMORY_MANAGER_ )
#define MEMORY_MANAGER_
/***************************************************************************
*
*  Módulo de definição: MEM  Memory Manager
*
*  Arquivo gerado:              mem_manager.h
*  Letras identificadoras:      MEM
*
*	Autores:
*     - hg: Hugo Roque
*
*  Histórico de evolução:
*     Versão  Autor    Data             Observações
*     1       hg       11/nov/2013      Usando lista para armazenar os ponteiros para espaços alocados.
*
*  Descrição do módulo
*     Módulo responsável por gerenciar toda a alocação dinâmica de memória.
*     Evitando assim que ao terminar o programa algum espaço de dados esteja
*     alocado. (house keeping)
*
***************************************************************************/

#if defined( MEMORY_MANAGER_OWN )
   #define MEMORY_MANAGER_EXT
#else
   #define MEMORY_MANAGER_EXT extern
#endif


/***********************************************************************
*
*  Tipo de dados: MEM Condições de retorno
*
*  Descrição do tipo
*     Condições de retorno das funções exportadas.
*
***********************************************************************/
   typedef enum {

         MEM_CondRetOK = 0,
               /* Executou correto */

         MEM_CondRetFaltouMemoria = 1,
               /* Faltou memória ao alocar dados */

         MEM_CondRetTamanhoInvalido = 2
               /* Tamanho do espaço de dados é inválido */

   } MEM_tpCondRet;

/* Protótipos das funções exportadas */

/***********************************************************************
*
*  Função: MEM Alloc
*
*  Descrição
*     Aloca espaço de dados, mantendo registro interno de um ponteiro
*     para o mesmo.
*
*  Parâmetros
*     size       - Tamanho em bytes do espaço de dados.
*     ppResult   - Referência para retornar um ponteiro apontando para
*                  o espaço de dados recém alocado.
*
*  Condições de retorno
*     MEM_CondRetOK
*     MEM_CondRetFaltouMemoria
*     MEM_CondRetTamanhoInvalido
*
*  Retorno por referência
*     ppResult - Retorna ponteiro para o espaço de dados recém alocado.
*
*  Assertivas de entrada
*     - size maior que zero.
*     - ppResult é um ponteiro válido.
*
*  Assertivas de saida
*     - ppResult apontará para um espaço de dados recém criado de tamanho
*       igual ao número de bytes passado por parâmetro.
*
***********************************************************************/
MEM_tpCondRet MEM_Alloc(int size, void **ppResult);


/***********************************************************************
*
*  Função: MEM Free
*
*  Descrição
*     Libera espaço de dados, eliminando também o ponteiro interno para
*     este espaço de dados.
*
*  Parâmetros
*     pointer - Ponteiro para espaço de dados à ser liberado.
*
*  Condições de retorno
*     MEM_CondRetOK
*
*  Assertivas de entrada
*     - pointer é um ponteiro válido.
*
*  Assertivas de saida
*     - espaço de dados apontado por pointer foi liberado.
*
***********************************************************************/
MEM_tpCondRet MEM_Free(void *pointer);


/***********************************************************************
*
*  Função: MEM Liberar toda memória alocada
*
*  Descrição
*     Libera toda a mémória previamente alocada.
*
*  Condições de retorno
*     MEM_CondRetOK
*
*  Assertivas de saida
*     Todos os espaços de dados alocados através do módulo foram liberados.
*
***********************************************************************/
MEM_tpCondRet MEM_LiberarTodaMemoriaAlocada();


#undef MEMORY_MANAGER_EXT

/********** Fim do módulo de definição: MEM Memory Manager **********/

#else
#endif