/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTTAB.C
*  Letras identificadoras:      TTAB
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
*     "=criar"           - chama a função TAB_CriarMatriz( )
*     "=irPara"         - chama a função TAB_IrPara( )
*     "=atribuir" <Char> - chama a função TAB_AtribuirValorCorr(  )
*     "=destroi"         - chama a função TAB_DestruirMatriz( )
*     "=obter" <Char>    - chama a função TAB_ObterValorCorr( ) e compara
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

#include    "tabuleiro.h"
#include    "mem_manager.h"

/* Tabela dos nomes dos comandos de teste relacionados ao módulo */

#define     CRIAR_TAB_CMD       "=criar"
#define     OBTER_VAL_CMD       "=obter"
#define     ATRIBUIR_VAL_CMD    "=atribuir"
#define     DESTROI_CMD         "=destruir"

#define     COPIAR_TAB_CMD     "=copiarTabuleiro"
#define     IR_PARA_CMD        "=irPara"
#define     IR_CASA_CMD        "=ircasa"

#define     FIM_CMD         "=fim"

/* Tabela dos nomes dos comandos de teste específicos do teste */
#define     SELECIONAR_CMD       "=selecionar"

#define     TABULEIROS_SIZE 10

static void DestruirValor(void *pValor);

static TAB_tppTabuleiro Tabuleiros[TABULEIROS_SIZE];

static int iTab = 0 ;

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TTAB Efetuar operações de teste específicas para matriz
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     matriz sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      TAB_tpCondRet CondRetObtido   = TAB_CondRetOK ;
      TAB_tpCondRet CondRetEsperada = TAB_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

     int IndiceValorEsperado = -1;
	  int IndiceValorObtido = -1;
	  int IndiceValorDado = -1;

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;

      /* Testar TAB Criar matriz */

         if ( strcmp( ComandoTeste , CRIAR_TAB_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            }

            CondRetObtido = TAB_CriarTabuleiro(Tabuleiros + iTab, DestruirValor, DestruirValor);

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar tabuleiro." ) ;

         }


      /* Testar TAB Destruir matriz */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            }

            CondRetObtido = TAB_DestruirTabuleiro(Tabuleiros + iTab) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"Não é possível destruir um tabuleiro que não existe.") ;

         } /* fim ativa: Testar TAB Destruir matriz */

		 
      /* Testar TAB Ir para */

		 else if ( strcmp( ComandoTeste , IR_PARA_CMD ) == 0 )
         {
            int iDirecao;
			   NumLidos = LER_LerParametros("ii" , &iDirecao, &CondRetEsperada);
            if (NumLidos != 2)
            {
               return TST_CondRetParm ;
            }

			   CondRetObtido = TAB_IrPara(Tabuleiros[iTab], (DIR_tpDirecao) iDirecao);

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
									"Não foi possível ir para essa direcao.") ;

         }


		/* Testar TAB Ir casa */

		 else if ( strcmp( ComandoTeste , IR_CASA_CMD ) == 0 )
       {

         char *nome;
         MEM_Alloc(sizeof(char)*50, (void**) &nome);
         NumLidos = LER_LerParametros( "si", nome, &CondRetEsperada ) ;
         if (NumLidos != 2)
         {
            return TST_CondRetParm ;
         }

			CondRetObtido = TAB_IrCasa(Tabuleiros[iTab], nome) ;

         return TST_CompararInt( CondRetEsperada , CondRetObtido ,
								"Não foi possível ir para a casa.") ;

         }

       
		/* Testar TAB Copiar tabuleiro */

		 else if (strcmp( ComandoTeste, COPIAR_TAB_CMD) == 0 )
       {
          int iCopia;
			 NumLidos = LER_LerParametros("ii", &iCopia, &CondRetEsperada) ;
          if (NumLidos != 2)
          {
             return TST_CondRetParm ;
          }
          
          CondRetObtido = TAB_CopiarTabuleiro(Tabuleiros[iTab], &Tabuleiros[iCopia]);
          
          return TST_CompararInt(CondRetEsperada, CondRetObtido,
								"Não foi possível copiar o tabuleiro.");

       }
       
       


      /* Testar Selecionar indice na array de tabuleiros */

         else if ( strcmp( ComandoTeste , SELECIONAR_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" ,
                               &iTab ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			if ( iTab < 0 || iTab > TABULEIROS_SIZE - 1 )
			{
				TST_NotificarFalha("Só é possível fazer seleção nos indices de 0 à 9") ;
				return TST_CondRetErro ;
			}

			return TST_CondRetOK ;

         }


      /* Testar Finalizar teste */

         else if ( strcmp( ComandoTeste , FIM_CMD ) == 0 )
         {
            MEM_LiberarTodaMemoriaAlocada();
            return TST_CondRetOK;
         }

      return TST_CondRetNaoConhec ;

   } /* Fim função: TTAB Efetuar operações de teste específicas para matriz */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

void DestruirValor(void *pValor)
{
   MEM_Free(pValor);
}