/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTPAR.C
*  Letras identificadoras:      TPAR
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Histórico de evolução:
*     Versão  Autor     Data     Observações
*       1.00   hg e nf  15/09/2013 Adaptação do módulo para manipular matrizes
*
*  $ED Descrição do módulo
*     Este mÇodulo contém as funções específicas para o teste do
*     módulo matriz. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo matriz:
*
*
*     "=criar"           - chama a função PAR_CriarMatriz( )
*     "=irPara"         - chama a função PAR_IrPara( )
*     "=atribuir" <Char> - chama a função PAR_AtribuirValorCorr(  )
*     "=destroi"         - chama a função PAR_DestruirMatriz( )
*     "=obter" <Char>    - chama a função PAR_ObterValorCorr( ) e compara
*                          o valor retornado com o valor <Char>
*=alterarPeca  nomeAtual   novoNome   novosPassos   novoTipoMovimento   condRet
*
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <stdlib.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include "peca.h"
#include "mem_manager.h"

/* Tabela dos nomes dos comandos de teste relacionados ao módulo */

#define     CRIAR_PEC_CMD                "=criar"
#define     ADICIONAR_TIME_PEC_CMD       "=adicionarTime"
#define     DESTROI_PEC_CMD              "=destruir"
#define     ALTERAR_PECA_CMD             "=alterar"

 
/*****  Código das funções exportadas pelo módulo  *****/

//static PAR_tppPartida Partidas[PARTIDAS_SIZE];

static PEC_tppPeca ppPeca = NULL;

//static int iPar = 0 ;


TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{

   PEC_tpCondRet CondRetObtido;
   PEC_tpCondRet CondRetEsperada;

   int IndiceValorEsperado = -1;
   int IndiceValorObtido = -1;
   int IndiceValorDado = -1;

   int NumLidos = -1;

   // Testar criação de peça

   if ( strcmp( ComandoTeste , CRIAR_PEC_CMD ) == 0 )
   {
      char *pNomePeca, *pPassos;
      PEC_tpTipoMovimento tipoMovimento;

      MEM_Alloc(sizeof(char)*20,(void**)&pNomePeca);
      MEM_Alloc(sizeof(char)*50,(void**)&pPassos);

      NumLidos = LER_LerParametros( "ssii" , pNomePeca, pPassos, &tipoMovimento, &CondRetEsperada ) ;
      if ( NumLidos != 4 )
      {
         return TST_CondRetParm ;
      }

      CondRetObtido = PEC_CriarPeca(&ppPeca,pNomePeca,pPassos,tipoMovimento);

      return TST_CompararInt( CondRetEsperada , CondRetObtido ,
         "Nao foi possivel criar peca.") ;

   } 

   // Testar destruir peça

   else if ( strcmp( ComandoTeste , DESTROI_PEC_CMD ) == 0 )
   {
      NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
      if ( NumLidos != 1 )
      {
         return TST_CondRetParm ;
      }

      CondRetObtido = PEC_DestruirPeca(&ppPeca);

      return TST_CompararInt( CondRetEsperada , CondRetObtido ,
         "Nao foi possivel destruir peca.") ;
   } 

   // Testar Alterar peça

   else if ( strcmp( ComandoTeste , ALTERAR_PECA_CMD ) == 0 )
   {
      char *pNovoNome, *pNovosPassos;
      PEC_tpTipoMovimento novoTipoMovimento;

      MEM_Alloc(sizeof(char)*20,(void**)&pNovoNome);
      MEM_Alloc(sizeof(char)*50,(void**)&pNovosPassos);

      NumLidos = LER_LerParametros( "ssii" , pNovoNome, pNovosPassos, &novoTipoMovimento ,&CondRetEsperada ) ;
      if ( NumLidos != 4 )
      {
         return TST_CondRetParm ;
      }

      CondRetObtido = PEC_AlterarPeca(ppPeca,pNovoNome,pNovosPassos,novoTipoMovimento);

      return TST_CompararInt( CondRetEsperada , CondRetObtido ,
         "Nao foi possivel alterar peca.") ;
   }

   // Testar Adicionar time a peça

   else if ( strcmp( ComandoTeste , ADICIONAR_TIME_PEC_CMD ) == 0 )
   {
      PEC_tpTimePeca time;

      NumLidos = LER_LerParametros( "ii" , &time, &CondRetEsperada ) ;
      if ( NumLidos != 2 )
      {
         return TST_CondRetParm ;
      }

      CondRetObtido = PEC_AdicionarTime(ppPeca, time);

      return TST_CompararInt( CondRetEsperada , CondRetObtido ,
         "Nao foi possivel Adicionar time a peca.") ;
   } 

   return TST_CondRetNaoConhec ;

} /* Fim função: TPAR Efetuar operações de teste específicas para matriz */

/********** Fim do módulo de implementação: Módulo de teste específico **********/
