#if ! defined( MEMORY_MANAGER_ )
#define MEMORY_MANAGER_
/***************************************************************************
*
*  M�dulo de defini��o: MEM  Memory Manager
*
*  Arquivo gerado:              mem_manager.h
*  Letras identificadoras:      MEM
*
*	Autores:
*     - hg: Hugo Roque
*
*  Hist�rico de evolu��o:
*     Vers�o  Autor    Data             Observa��es
*     1       hg       11/nov/2013      Usando lista para armazenar os ponteiros para espa�os alocados.
*
*  Descri��o do m�dulo
*     M�dulo respons�vel por gerenciar toda a aloca��o din�mica de mem�ria.
*     Evitando assim que ao terminar o programa algum espa�o de dados esteja
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
*  Tipo de dados: MEM Condi��es de retorno
*
*  Descri��o do tipo
*     Condi��es de retorno das fun��es exportadas.
*
***********************************************************************/
   typedef enum {

         MEM_CondRetOK = 0,
               /* Executou correto */

         MEM_CondRetFaltouMemoria = 1,
               /* Faltou mem�ria ao alocar dados */

         MEM_CondRetTamanhoInvalido = 2
               /* Tamanho do espa�o de dados � inv�lido */

   } MEM_tpCondRet;

/* Prot�tipos das fun��es exportadas */

/***********************************************************************
*
*  Fun��o: MEM Alloc
*
*  Descri��o
*     Aloca espa�o de dados, mantendo registro interno de um ponteiro
*     para o mesmo.
*
*  Par�metros
*     size       - Tamanho em bytes do espa�o de dados.
*     ppResult   - Refer�ncia para retornar um ponteiro apontando para
*                  o espa�o de dados rec�m alocado.
*
*  Condi��es de retorno
*     MEM_CondRetOK
*     MEM_CondRetFaltouMemoria
*     MEM_CondRetTamanhoInvalido
*
*  Retorno por refer�ncia
*     ppResult - Retorna ponteiro para o espa�o de dados rec�m alocado.
*
*  Assertivas de entrada
*     - size maior que zero.
*     - ppResult � um ponteiro v�lido.
*
*  Assertivas de saida
*     - ppResult apontar� para um espa�o de dados rec�m criado de tamanho
*       igual ao n�mero de bytes passado por par�metro.
*
***********************************************************************/
MEM_tpCondRet MEM_Alloc(int size, void **ppResult);


/***********************************************************************
*
*  Fun��o: MEM Free
*
*  Descri��o
*     Libera espa�o de dados, eliminando tamb�m o ponteiro interno para
*     este espa�o de dados.
*
*  Par�metros
*     pointer - Ponteiro para espa�o de dados � ser liberado.
*
*  Condi��es de retorno
*     MEM_CondRetOK
*
*  Assertivas de entrada
*     - pointer � um ponteiro v�lido.
*
*  Assertivas de saida
*     - espa�o de dados apontado por pointer foi liberado.
*
***********************************************************************/
MEM_tpCondRet MEM_Free(void *pointer);


/***********************************************************************
*
*  Fun��o: MEM Liberar toda mem�ria alocada
*
*  Descri��o
*     Libera toda a m�m�ria previamente alocada.
*
*  Condi��es de retorno
*     MEM_CondRetOK
*
*  Assertivas de saida
*     Todos os espa�os de dados alocados atrav�s do m�dulo foram liberados.
*
***********************************************************************/
MEM_tpCondRet MEM_LiberarTodaMemoriaAlocada();


#undef MEMORY_MANAGER_EXT

/********** Fim do m�dulo de defini��o: MEM Memory Manager **********/

#else
#endif