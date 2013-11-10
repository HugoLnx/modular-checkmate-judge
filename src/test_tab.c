/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TESTTAB.C
*  Letras identificadoras:      TTAB
*
*  Autores: hg - Hugo Roque
*           nf - Nino Fabrizio
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor     Data     Observa��es
*       1.00   hg e nf  15/09/2013 Adapta��o do m�dulo para manipular matrizes
*
*  $ED Descri��o do m�dulo
*     Este m�odulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo matriz. Ilustra como redigir um interpretador de comandos
*     de teste espec�ficos utilizando o arcabou�o de teste para C.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo matriz:
*
*
*     "=criar"           - chama a fun��o TAB_CriarMatriz( )
*     "=irPara"         - chama a fun��o TAB_IrPara( )
*     "=atribuir" <Char> - chama a fun��o TAB_AtribuirValorCorr(  )
*     "=destroi"         - chama a fun��o TAB_DestruirMatriz( )
*     "=obter" <Char>    - chama a fun��o TAB_ObterValorCorr( ) e compara
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

/* Tabela dos nomes dos comandos de teste relacionados ao m�dulo */

#define     CRIAR_TAB_CMD       "=criar"
#define     OBTER_VAL_CMD       "=obter"
#define     ATRIBUIR_VAL_CMD    "=atribuir"
#define     DESTROI_CMD         "=destruir"

#define     COPIAR_TAB_CMD     "=copiarTabuleiro"
#define     IR_PARA_CMD        "=irPara"
#define     IR_CASA_CMD        "=ircasa"

#define     FIM_CMD         "=fim"

/* Tabela dos nomes dos comandos de teste espec�ficos do teste */
#define     SELECIONAR_CMD       "=selecionar"

#define     TABULEIROS_SIZE 10

static void DestruirValor(void *pValor);

static TAB_tppTabuleiro Tabuleiros[TABULEIROS_SIZE];

static int iTab = 0 ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TTAB Efetuar opera��es de teste espec�ficas para matriz
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     matriz sendo testado.
*
*  $EP Par�metros
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
									"N�o � poss�vel destruir um tabuleiro que n�o existe.") ;

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
									"N�o foi poss�vel ir para essa direcao.") ;

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
								"N�o foi poss�vel ir para a casa.") ;

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
								"N�o foi poss�vel copiar o tabuleiro.");

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
				TST_NotificarFalha("S� � poss�vel fazer sele��o nos indices de 0 � 9") ;
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

   } /* Fim fun��o: TTAB Efetuar opera��es de teste espec�ficas para matriz */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/

void DestruirValor(void *pValor)
{
   MEM_Free(pValor);
}