/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : CodeGenerator for RL78/G14 V2.05.06.02 [08 Nov 2021]
* Device(s)    : R5F104LE
* Tool-Chain   : CCRL
* Description  : This file implements main function.
* Creation Date: 2024/03/29
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_intc.h"
#include "r_cg_serial.h"
#include "r_cg_timer.h"
#include "r_cg_it.h"
/* Start user code for include. Do not edit comment generated here */
#include	<string.h>
#include	<stdio.h>
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */

/******************************************************************************
 Typedef definitions
******************************************************************************/
/* 標準的な定義 */
#define LOW			0U
#define HIGH		1U	
#define DISABLE		0U
#define ENABLE		1U							
#define FALSE		0U
#define TRUE		1U
#define CLEAR		0U
#define SET			1U

#define	FREE		0U
#define	BUSY		1U

#define	CLR			0U
#define SET			1U


#define	ON			1U		//sticTEST用0U  本番は1U Activ"H"
#define	OFF			0U		//sticTEST用　


/* Switch InPut用*/
#define	CARD		0	
#define	DIST		1
#define	MAKE		2
#define	CHIME		3
#define	R_UP		4
#define	R_DN		5
#define	BSIDE		6
#define	BED_R		7
#define	BED_L		8
#define	DESK		9
#define	FOOT		10
#define	B_UP		11
#define	B_DN		12
#define	BATH		13
#define	MIRR		14
#define	K3			15
#define	K4			16
#define	K5			17
#define	K6			18			//増設
#define	WORKS		19
#define	MAINT		23



//#define	DL3		1			//設定はここ
//#define	JS1		1
#define	JS3_T	1
//#define	JS3_K 	1
//#define	STANDARD	1


//#define		release		1		//設定はここ




/* Relay OutPut用 relay[index] */
//relay[CARD/*0*/]	
//relay[DIST]		ini_data= ******** ******** *******1
//relay[MAKE]		ini_data= ******** ******** ******1*
//relay[CHIME]		ini_data= ******** ******** *****1**
//relay[R_UP]		ini_data= ******** ******** ****1***
//relay[R_DN]		ini_data= ******** ******** ***1****
//relay[MAST]		ini_data= ******** ******** **1*****
//relay[BED_R]		ini_data= ******** ******** *1******
//relay[BED_L]		ini_data= ******** ******** 1*******
//relay[DESK]		ini_data= ******** *******1 ********
//relay[FOOT]		ini_data= ******** ******1* ********
//relay[B_UP]		ini_data= ******** *****1** ********	F800
//relay[B_DN]		ini_data= ******** ****1*** ********  	F000
//relay[BATH]		ini_data= ******** ***1**** ********
//relay[MIRR]		ini_data= ******** **1***** ********
//relay[K3]			ini_data= ******** *1****** ********
//relay[K4]			ini_data= ******** 1******* ********
//relay[K5]			ini_data= *******1 ******** ********
//relay[WORKS]		ini_data= ******1* ******** ********
#define TV			20
//relay[TV]			ini_data= *****1** ******** ********
#define	MAIN1		21
//relay[MAIN1]		ini_data= ****1*** ******** ********		0x080000
#define	MAIN2		22
//relay[MAIN2]		ini_data= ***1**** ******** ********		0x100000
//relay[WORKS]		ini_data= **1***** ******** ********
#define	OFFCMD		24
//relay[OFFCMD]		ini_data= *1****** ******** ********


/*****************************************************************************
	sreg変数 boolean変数 FFE20 - FFEB3 148byte 								*/

__saddr	volatile unsigned long	lifeCnt		= 0U;	
__saddr volatile char		loopTimer	= 0U;


/*****************************************************************************
											 								*/
																			
#if 0

const unsigned int dimnum[160]={
	
		0x0000,0x0100,0x0200,0x0300,0x0400,0x0500,0x0600,0x0700,0x0800,0x0900,
		0x0A00,0x0B00,0x0C00,0x0D00,0x0E00,0x0F00,0x1000,0x1100,0x1200,0x1300,
		0x1400,0x1500,0x1600,0x1700,0x1800,0x1900,0x1A00,0x1B00,0x1C00,0x1D00,
		0x1E00,0x1F00,0x2000,0x2100,0x2200,0x2300,0x2400,0x2500,0x2600,0x2700,
		0x2800,0x2900,0x2A00,0x2B00,0x2C00,0x2D00,0x2E00,0x2F00,0x3000,0x3100,
		0x3200,0x3300,0x3400,0x3500,0x3600,0x3700,0x3800,0x3900,0x3A00,0x3B00,
		0x3C00,0x3D00,0x3E00,0x3F00,0x4000,0x4100,0x4200,0x4300,0x4400,0x4500,
		0x4600,0x4700,0x4800,0x4900,0x4A00,0x4B00,0x4C00,0x4D00,0x4E00,0x4F00,
		0x5000,0x5100,0x5200,0x5300,0x5400,0x5500,0x5600,0x5700,0x5800,0x5900,
		0x5A00,0x5B00,0x5C00,0x5D00,0x5E00,0x5F00,0x6000,0x6100,0x6200,0x6300,
		0x6400,0x6500,0x6600,0x6700,0x6800,0x6900,0x6A00,0x6B00,0x6C00,0x6D00,
		0x6E00,0x6F00,0x7000,0x7100,0x7200,0x7300,0x7400,0x7500,0x7600,0x7700,
		0x7800,0x7900,0x7A00,0x7B00,0x7C00,0x7D00,0x7E00,0x7F00,0x8000,0x8100,
		0x8200,0x8300,0x8400,0x8500,0x8600,0x8700,0x8800,0x8900,0x8A00,0x8B00,
		0x8C00,0x8D00,0x8E00,0x8F00,0x9000,0x9100,0x9200,0x9300,0x9400,0x9500,
		0x9600,0x9700,0x9800,0x9900,0x9A00,0x9B00,0x9C00,0x9C00,0x9C00
};

#define BDARK	30		//Bath
#define BRIGH	140

#define RDARK	30		//DARK 暗い	MIN 0x0500 0x0500-- 64段
#define	RRIGH	140

#define BOFF	BDARK-1
#define ROFF	RDARK-1
#define DL50ON	50		// RRIGH 立ち上がり50%


#else
	
const unsigned int dimnum[92]={
	
		0x0000,0x0100,0x0200,0x0300,0x0400,0x0500,0x0550,0x0600,0x0650,0x700,
		0x0750,0x0800,0x0850,0x0900,0x0950,0x0A00,0x0B00,0x0C00,0x0D00,
		
		0x0E00,
		0x1000,0x1400,0x1600,0x1800,0x1A00,0x1C00,0x1E00,0x2000,0x2200,0x2400,
		0x2600,0x2800,0x2A00,0x2C00,0x2E00,0x3000,0x3200,0x3400,0x3600,0x3800,
		0x3A00,0x3C00,0x3E00,0x4000,0x4200,0x4400,0x4600,0x4800,0x4A00,0x4C00,		//49
		0x4E00,0x5000,0x5200,0x5400,0x5600,0x5800,0x5A00,0x5C00,0x5E00,0x6000,
		0x6200,0x6200,0x6400,0x6600,0x6800,0x6A00,0x6C00,0x6E00,0x7000,0x7200,
		0x7400,0x7600,0x7800,0x7A00,0x7C00,0x7E00,0x8000,0x8200,0x8400,0x8600,
		0x8800,0x8A00,0x8C00,0x8E00,0x9000,0x9200,0x9400,0x9600,0x9800,0x9A00,
		0x9C00,0x9C00
};

#define BDARK	25		//19 LED		//Bath 0x0E00-- 32段
#define BRIGH	80		//48 LED		//BRIGHT 明るい MAX

#define RDARK	5		//DARK 暗い	MIN 0x0500 0x0500-- 64段
#define	RRIGH	79

#define BOFF	BDARK-1
#define ROFF	RDARK-1
#define DL50ON	30		// RRIGH 立ち上がり50%

#endif



unsigned char	bathDim = BDARK;		//BATH_DL
unsigned char	sideDim = RDARK;		//BSIDE_DL
unsigned char	dim3 = RDARK;




volatile uint8_t g_tx0_ready_flag= FREE;
char	gbuf[10];


unsigned int	gTime =10;

char	outmoni[]=	{	"main1=0 main2=0 k08=0 K09=0 K10=0 K11=0 K12=0 K13=0 K14=0 TVP=0 CHM=0 K03=0 K04=0 K05=0 EXT=0 \n"	};
					


/*****************************************************************
functions																*/


void	zeroCross(void);
void 	Delay(unsigned long i);
void	AplCall(void);

unsigned int 	cardScan(unsigned char num, unsigned int timecnt);
unsigned int 	allOn(unsigned char num, unsigned int timecnt);
unsigned int 	pswScan(unsigned char num, unsigned int timecnt);
unsigned int 	rswScan(unsigned char num, unsigned int cnt);
unsigned int   	dimScan(unsigned char num, unsigned int timecnt);
unsigned int	allOff(unsigned int timecnt);
unsigned int 	oneCall0(unsigned int cnt);

void			portOut(unsigned char num, unsigned char data);
unsigned char	portScan(unsigned char num);
void			ryInit(unsigned long data);
unsigned char	ryCont(unsigned char number, char cnt, unsigned char flg);
unsigned int	delayOff(unsigned int timecnt);
void			comSelect(char num);
unsigned int 	ledCall(unsigned int cnt);
void			cardOn(char num);
void			cardOff(void);
char			swSearch(unsigned char num);

unsigned int 	mainte(unsigned char num, unsigned int cnt);
unsigned int 	zeroWait(unsigned int j);
unsigned int 	outputTask(unsigned int cnt);
uint8_t			serialPrint0(char *buff, unsigned int num);
void			serialEnd(void);
void			info(void);
void			DebugPrint(int8_t *s,uint16_t n);
void			outMoni(void);

/*--------------------------------------------------------------------
		<<機種依存しないビット単位アクセス可能なユーザ型定義>>
			ビットアクセスが必要な変数にのみに、ここのビット単位アクセス変数宣言を使う。

			通常変数は、符号付標準宣言、または、下記 int8_t ～ init32_t を使う。
			typedef signed char         int8_t;
			typedef unsigned char       uint8_t;
			typedef signed short        int16_t;
			typedef unsigned short      uint16_t;
			typedef signed long         int32_t;
			typedef unsigned long       uint32_t;		
---------------------------------------------------------------------*/
/*** 8 bits type declaration. ビット単位アクセス可能 ***/
typedef union{
	unsigned char ubyte;		/* Byte access */
	struct{						/* Bit access */
		unsigned char b0 : 1;	/* Bit 0 */
		unsigned char b1 : 1;	/* Bit 1 */
		unsigned char b2 : 1;	/* Bit 2 */
		unsigned char b3 : 1;	/* Bit 3 */
		unsigned char b4 : 1;	/* Bit 4 */
		unsigned char b5 : 1;	/* Bit 5 */
		unsigned char b6 : 1;	/* Bit 6 */
		unsigned char b7 : 1;	/* Bit 7 */
	}b;							/* RL78は、bitでは予約語エラー発生 */
}ubyte_t;						/* 機種依存なしunsigned char */

/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */
	
	
	ryInit(0);

	info();
	
	portOut(MAIN1,ryCont(MAIN1,'r',0));
	portOut(MAIN2,ryCont(MAIN2,'r',0));
		
	bathDim= BOFF;		//DL50ON;	//BATH_DL
	ryCont(BATH,'w',0);	
	
	ryCont(FOOT,'w',0);
	ryCont(DESK,'w',0);
		
	sideDim= ROFF;
	ryCont(BSIDE,'w',0);		
	ryCont(TV,'w',0);	

	
    while (1U){
       	//P12_bit.no0 = 1;
		//Delay(50000);
		//
		AplCall();
		
    }
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
	
	R_IT_Start();
	R_INTC0_Start();		// ZeroCross
	R_TMR_RD0_Start();
	
	R_UART0_Stop();			//Moni用serial0
	SDR00 = 0x8A00U;		//115200Bps設定 Baseは76800Bps
	R_UART0_Start();
	
	
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */

/******************************************************************************
* Function Name: 
* Description  : r_cg_intc_user.cから呼ばれる
* Arguments    : Code
* Return Value : None

 コンペア10mSECで0x9C3F(39999)なので180°で割ると1°当たり0x64(約104)
*******************************************************************************/
void	zeroCross(void){
	
	__saddr static	unsigned short	lcnt;
	__saddr static	unsigned char	r1= 1;
	__saddr static	unsigned char	r2= 1;
	__saddr static	unsigned char	r3= 1;
	unsigned char d;
	
	R_TMR_RD0_Stop();
	//R_TMR_RD1_Stop();
	
	TRD0EN = 1U;    /* enable input clock supply */ 
	TRD0 = 0;
	TRD1 = 0;
	
#if 1	
	      	      
	TRDOCR |= _01_TMRD_TRDIOA0_INITIAL_OUTPUT_H | _02_TMRD_TRDIOB0_INITIAL_OUTPUT_H |
              _04_TMRD_TRDIOC0_INITIAL_OUTPUT_H;
#endif

	if((lcnt= ++lcnt % 2)== 0){
		
		if(r1 != bathDim){
			if(r1> bathDim) --r1;
			else ++r1;
			TRDGRA0 = (dimnum[r1]);		//P1_bit.no7
		}
		if(r2 != sideDim){
			if(r2> sideDim) --r2;
			else ++r2;
			TRDGRB0 = (dimnum[r2]);		//P1_bit.no5
		}
		if(r3 != dim3){
			if(r3> dim3) --r3;
			else ++r3;
			TRDGRC0 = (dimnum[r3]);
		}
		d= (r1 < BDARK)? 0: 1;
		ryCont(BATH,'w',d);
		
		d= (r2 < RDARK)? 0: 1;
		ryCont(BSIDE,'w',d);
	}
	R_TMR_RD0_Start();
}
/*******************************************************************************
* Function Name: 
* Description  : 
* Arguments    : Code
* Return Value : None
*******************************************************************************/
void Delay(unsigned long i){

	while(i){
		i--;
		NOP();
	}
}
/*******************************************************************************
* Function Name: アプリ関数の起動処理
* Description  : 
* Arguments    : Code
* Return Value : None
* Note:			 
* History:  
*******************************************************************************/
void	AplCall(void){
	

	static unsigned int	taskTime0= 1;		//10mS * 1
	static unsigned int	taskTime1= 10;		//10mS * 10= 100mSec
	static unsigned int	taskTime2= 20;		//10mS * 20= 200msec
	static unsigned int	udTime1= 10;		//1mS * Universal
	//static unsigned int	udTime2= 10;	//Universal
	
	static unsigned char	now= 0;

	for(;;){
		
		if(loopTimer != now){	//CountUpは 1mS
			now =loopTimer;		//0-9を繰り返す
		
			switch(now){
			
				case 0:	/*10ｍSで発生*/
					comSelect('1');				//この位置にあること
					if(ryCont(CARD,'r',0)==1) dimScan(R_UP,taskTime0);
					if(ryCont(CARD,'r',0)==1) dimScan(R_DN,taskTime0);
					if(ryCont(CARD,'r',0)==1) pswScan(BSIDE,taskTime0);		
					pswScan(BED_R,taskTime0);
					pswScan(BED_L,taskTime0);
					pswScan(DESK,taskTime0);
					pswScan(FOOT,taskTime0);	
					comSelect('0');
				
					/* マルチプレックス無し*/
					mainte(MAINT,taskTime2);	// メンテ用SW 200*7
					rswScan(CARD,taskTime1);	// CARD 100*7
					pswScan(DIST,taskTime0);		
					pswScan(MAKE,taskTime0);
					pswScan(CHIME,taskTime0);
					rswScan(WORKS,taskTime2);	//LAN WORKSは200*7
					break;
				
				case 5: /*10ｍSで発生*/
					comSelect('2');				//この位置にあること				
					if(ryCont(CARD,'r',0)==1) dimScan(B_UP,taskTime0);
					if(ryCont(CARD,'r',0)==1) dimScan(B_DN,taskTime0);
					if(ryCont(CARD,'r',0)==1) pswScan(BATH,taskTime0);
					pswScan(MIRR,taskTime0);
					pswScan(K3,taskTime0);
					pswScan(K4,taskTime0);
					pswScan(K5,taskTime0);
					
#ifndef	STANDARD				
					pswScan(K6,taskTime0);	//増設分
#endif
					comSelect('0');	
					break;
				
				default:
					/* ここは1m?毎に通過する */
					portOut(DIST,ryCont(DIST,'r',0));
					portOut(MAKE,ryCont(MAKE,'r',0));
		
					udTime1= oneCall0(udTime1);	//CHIME用Oneshot
		
					portOut(BSIDE,ryCont(BSIDE,'r',0));
					portOut(BED_R,ryCont(BED_R,'r',0));
					portOut(BED_L,ryCont(BED_L,'r',0));
					portOut(DESK,ryCont(DESK,'r',0));
					portOut(BATH,ryCont(BATH,'r',0));
					portOut(MIRR,ryCont(MIRR,'r',0));
					portOut(K3,ryCont(K3,'r',0));
					portOut(K4,ryCont(K4,'r',0));
					portOut(K5,ryCont(K5,'r',0));
				
#ifndef	STANDARD				
					portOut(K6,ryCont(K6,'r',0));	//増設
#endif			
					portOut(TV,ryCont(TV,'r',0));
		
					gTime =outputTask(gTime);
					ledCall(500);
			
			}
		}	
	//高速loopはここ
	} //for loop
	
}
/*******************************************************************************
* Function Name: 
* Description  : 
* Arguments    : Code
* Return Value : None
* Note:
* History:
*******************************************************************************/
unsigned int outputTask(unsigned int cnt){
	
	static unsigned int lcnt= 0;

	if((lcnt= ++lcnt % cnt)== 0){
	
		portOut(DESK,ryCont(DESK,'r',0));
		portOut(FOOT,ryCont(FOOT,'r',0));
		portOut(MAIN1,ryCont(MAIN1,'r',0));
		portOut(MAIN2,ryCont(MAIN2,'r',0));
		cnt =10;
	
	}
	return	cnt;
}
/*******************************************************************************
* Function Name: 
* Description  : CARD用にSAMPLING多め
* Arguments    : Code
* Return Value : None
* Note:
* History:
*******************************************************************************/
unsigned int rswScan(unsigned char num, unsigned int cnt){
	
	static unsigned int lcnt[2] ={0};
	static ubyte_t swreg[2] ={OFF,OFF};	//SWレジスタ
	unsigned char nowsw;
	unsigned char n =0;
	
	if(num ==CARD) 	n =0;		//CARDとWORKSしかない
	if(num ==WORKS)	n =1;
	
	if((lcnt[n]= ++lcnt[n] % cnt) ==0){
		
		nowsw = portScan(num);		// Works= P0_bit.no6
		swreg[n].b.b0 = nowsw;
	
		if((nowsw==ON)&&(swreg[n].b.b1==ON)&&(swreg[n].b.b2==ON)&&(swreg[n].b.b3==ON)&&(swreg[n].b.b4==ON)){	// 新旧データ3回連続
			
			if(swreg[n].b.b5== OFF){	// 5スキャン前が"OFF"
			/* ONエッジ検出 */ 
				
				swSearch(num);				
			}
			if((swreg[n].b.b4== ON)&&(swreg[n].b.b5== ON)&&(swreg[n].b.b6== ON)&&(swreg[n].b.b7== ON)){
			/* 連続押し*/
			
				if(ryCont(CARD,'r',0)==0)	ryCont(CARD,'w',1);
			}
		}
		if((nowsw==OFF)&&(swreg[n].b.b1==OFF)&&(swreg[n].b.b2==OFF)&&(swreg[n].b.b3==OFF)&&(swreg[n].b.b4==OFF)&&(swreg[n].b.b5==OFF)&&(swreg[n].b.b6==OFF)){	// 新旧データ7回連続	
			if(swreg[n].b.b7== ON){
			/* OFFエッジ検出 */
				if(num ==CARD){
					cardOff();
					gTime =7000;
				}
			}
			if(swreg[n].b.b7== OFF){
			/* 連続解放*/
			}
		}
		swreg[n].b.b7 = swreg[n].b.b6;	// 7スキャン前旧データ更新
		swreg[n].b.b6 = swreg[n].b.b5;	// 6スキャン前旧データ更新
		swreg[n].b.b5 = swreg[n].b.b4;	// 5スキャン前旧データ更新
		swreg[n].b.b4 = swreg[n].b.b3;	// 4スキャン前旧データ更新
		
		swreg[n].b.b3 = swreg[n].b.b2;	// 3スキャン前旧データ更新
		swreg[n].b.b2 = swreg[n].b.b1;	// 2スキャン前旧データ更新
		swreg[n].b.b1 = nowsw;			// 1スキャン前旧データ更新
	}
	return	cnt;
}
/*******************************************************************************
* Function Name: 
* Description  : メンテナンス用 CardOnと同じ動作をする(極性が違う)
* Arguments    : Code
* Return Value : None
* Note:
* History:
*******************************************************************************/
unsigned int mainte(unsigned char num, unsigned int cnt){
	
	static unsigned int lcnt= 0;
	static ubyte_t swreg = {0xff};	// SWレジスタ
	unsigned char nowsw;
	
	if((lcnt= ++lcnt % cnt)== 0){
		
		nowsw = portScan(num);		// Works= P0_bit.no6
		swreg.b.b0 = nowsw;
	
		if((nowsw==0)&&(swreg.b.b1==0)&&(swreg.b.b2==0)&&(swreg.b.b3==0)&&(swreg.b.b4==0)&&(swreg.b.b5==0)&&(swreg.b.b6==0)){	// 新旧データ7回連続"Low"
			
			if(swreg.b.b7== 1){		// 7スキャン前が"High"
			/* ONエッジ検出 */ 
				cardOn('c');				
			}
			if(swreg.b.b7== 0){		// 7スキャン前も"Low"
			/* 連続押し*/
			}
		}
		if((nowsw==1)&&(swreg.b.b1==1)&&(swreg.b.b2==1)&&(swreg.b.b3==1)&&(swreg.b.b4==1)&&(swreg.b.b5==1)&&(swreg.b.b6==1)){	// 新旧データ7回連続"High"
			
			if(swreg.b.b7== 0){		// 7スキャン前が"Low"
			/* OFFエッジ検出 */ 
				cardOff();			// ALL OFF??
				gTime =10000;
			}
			if(swreg.b.b7== 1){		// 7スキャン前も"High"
			/* 連続解放*/
			}
		}
		swreg.b.b7 = swreg.b.b6;	// 7スキャン前旧データ更新
		swreg.b.b6 = swreg.b.b5;	// 6スキャン前旧データ更新
		swreg.b.b5 = swreg.b.b4;	// 5スキャン前旧データ更新
		swreg.b.b4 = swreg.b.b3;	// 4スキャン前旧データ更新
		
		swreg.b.b3 = swreg.b.b2;	// 3スキャン前旧データ更新
		swreg.b.b2 = swreg.b.b1;	// 2スキャン前旧データ更新
		swreg.b.b1 = nowsw;			// 1スキャン前旧データ更新
	}
	return	cnt;
}
/*******************************************************************************
* Function Name: 
* Description  : 
* Arguments    : Code
* Return Value : None
* Note:
*			DIST[1] MAKE[2] CHIME[3] BSIDE[6] BED_R[7] BED_L[8] 
*			DESK[9] FOOT[10] BATH[13] MIRR[14] K3[15] K4[16] ROOM3[17] ROOM4[18]
* History:  
*******************************************************************************/
unsigned int pswScan(unsigned char num, unsigned int cnt){
	
	static unsigned int lcnt[20]= {0};
	static ubyte_t swreg[20] = {OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,
								OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF};	// SWレジスタ
	unsigned char 	nowsw;
	
	
	if((lcnt[num]= ++lcnt[num] % cnt)== 0){
		
		nowsw = portScan(num);			//SW データ取得
		swreg[num].b.b0 = nowsw;	

		if((nowsw==ON)&& (swreg[num].b.b1==ON)&& (swreg[num].b.b2==ON)&& (swreg[num].b.b3==ON)){// 新旧データ4回連続SW_PUSH
			
			if(swreg[num].b.b4 == OFF){	// 4スキャン前
			/* LedToggle(); */
			
				swSearch(num);
				
			}
			if(swreg[num].b.b4 == ON){	// 4スキャン前も0N
			/* 連続押し*/
			}
		}
		if((nowsw==OFF)&& (swreg[num].b.b1==OFF)&& (swreg[num].b.b2==OFF)&& (swreg[num].b.b3==OFF)){
			
			if(swreg[num].b.b4 == ON){
			/* OFFエッジ検出 */ 

				if(num==CARD){
					cardOff();
					gTime =10000;
				}
			}
			if(swreg[num].b.b4 == OFF){
			/* 連続解放*/
			}
		}
		swreg[num].b.b7 = swreg[num].b.b6;	// 7スキャン前旧データ更新
		swreg[num].b.b6 = swreg[num].b.b5;	// 6スキャン前旧データ更新
		swreg[num].b.b5 = swreg[num].b.b4;	// 5スキャン前旧データ更新
		
		swreg[num].b.b4 = swreg[num].b.b3;	// 4スキャン前旧データ更新
		swreg[num].b.b3 = swreg[num].b.b2;	// 3スキャン前旧データ更新
		swreg[num].b.b2 = swreg[num].b.b1;	// 2スキャン前旧データ更新
		swreg[num].b.b1 = nowsw;			// 1スキャン前旧データ更新
	}
	return	cnt;
}
/*******************************************************************************
* Function Name: 
* Description  : 
* Arguments    : Code
* Return Value : None
* Note:			
* History:
*******************************************************************************/
char	swSearch(unsigned char num){
	
	DebugPrint("SW=",(uint16_t)num);	//TEST
	
	switch(num){			

		case CARD:	cardOn('c');
			break;
			
		case BSIDE:
			if(ryCont(BSIDE,'r',0)==0) sideDim =DL50ON;
			else if(ryCont(BSIDE,'r',0)==1)	sideDim =ROFF;
			break;
		case WORKS:
			if(ryCont(CARD,'r',0)==0){// CARD有りではwelcome ONしない(誤動作防止の為)
				
				cardOn('f');
			}
			break;
		case CHIME:	
			if(ryCont(DIST,'r',0)==0)	ryCont(CHIME,'w',1);
			break;
		case DIST:
			if(ryCont(CARD,'r',0)==0)	break;
			
		case MAKE:
		case BED_R:
		case BED_L:
		case FOOT:
		case DESK:
			ryCont(num,'w',!(ryCont(num,'r',0)));	//反転
			break;

		case BATH:
			if(ryCont(BATH,'r',0)==0) bathDim= BRIGH;
			else if(ryCont(BATH,'r',0)==1) 	bathDim= BOFF;
			break;
		case MIRR:		
		case K3:		//以降STANDARDでは呼ばれない	
		case K4:
		case K5:
		case K6:
			ryCont(num,'w',!(ryCont(num,'r',0)));	//反転
			break;
			
			
		default:
			break;
	}
	
#ifndef	release
	outMoni();			//TEST
#endif

	return	num;
}


#if 1
/*******************************************************************************
* Function Name: 
* Description  : 
* Arguments    : Code
* Return Value : None
* Note:			ubyte_t 構造体
* History:
*******************************************************************************/
unsigned int dimScan(unsigned char num, unsigned int cnt){

	static unsigned int lcnt[20]= {0};
	static ubyte_t  swreg[20] = {OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF};		// SWレジスタ

	unsigned char 	nowsw;
	static unsigned int	tc;
	
	
	if((lcnt[num]= ++lcnt[num] %cnt) ==0){
		
		nowsw = portScan(num);
		swreg[num].b.b0 =nowsw;
		
		if((nowsw== ON) &&(swreg[num].b.b1 ==ON) &&(swreg[num].b.b2 ==ON)){	// 新旧データ3回連続SW_PUSH
			
			if(swreg[num].b.b3 ==OFF){	// 3スキャン前がSW_OPEN
			/* ONエッジ検出 */
			
				tc =40;
				if(num==R_UP && sideDim <RRIGH) ++sideDim;
				else if(num==R_DN &&sideDim >RDARK)	--sideDim;
				else if(num==R_DN &&sideDim <RDARK) sideDim =RDARK;
			
				if(num==B_UP && bathDim <BRIGH) ++bathDim;
				else if(num==B_DN &&bathDim >BDARK)	--bathDim;
				else if(num==B_DN &&bathDim <BDARK)	bathDim =BDARK;
			}
			
			if(swreg[num].b.b3 ==ON){		// 3スキャン前も0N
			/* 連続押し */
					
				if((tc =zeroWait(tc)) ==0){
					
					tc= 4;
					if(num==R_UP &&sideDim <RRIGH)	++sideDim;
					else if(num==R_DN &&sideDim >RDARK)	--sideDim;
				
					if(num==B_UP &&bathDim <BRIGH)	++bathDim;
					else if(num ==B_DN &&bathDim >BDARK)	--bathDim;
				}
			}
		}	
		if((nowsw==OFF) &&(swreg[num].b.b1==OFF) &&(swreg[num].b.b2==OFF)){
			
			if(swreg[num].b.b3 ==ON){
			/* OFFエッジ検出 */
			}	
			if(swreg[num].b.b3 ==OFF){
			/* 連続解放*/			
			}
		}
		swreg[num].b.b5 =swreg[num].b.b4;	// 5スキャン前旧データ更新
		swreg[num].b.b4 =swreg[num].b.b3;	// 4スキャン前旧データ更新
		swreg[num].b.b3 =swreg[num].b.b2;	// 3スキャン前旧データ更新
		swreg[num].b.b2 =swreg[num].b.b1;	// 2スキャン前旧データ更新
		swreg[num].b.b1 =nowsw;		// 1スキャン前旧データ更新
	}
	return cnt;
}
#endif
/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : Code
* Return Value : None
***********************************************************************************************************************/
unsigned int zeroWait(unsigned int j){
	
	if(j >0) --j;
	return j;
}
/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : Code
* Return Value : None
***********************************************************************************************************************/
unsigned int oneCall0(unsigned int cnt){
	
	static unsigned int lcnt;
	unsigned int ans;
	
	ans= cnt;
	
	if((lcnt= ++lcnt % cnt)== 0){
		
		if(ryCont(CHIME,'r',0)==1){
			portOut(CHIME,1);
			ryCont(CHIME,'w',0);
			ans=500;
		}
		else{
			portOut(CHIME,0);
			ans= 10;
		}
	}
	return	ans;	
}
/*******************************************************************************
* Function Name: 
* Description  : 
* Arguments    : Code
* Return Value : None
* Note:
* History:  
*******************************************************************************/
unsigned int ledCall(unsigned int cnt){
	
	static unsigned int __saddr	lcnt;
	
	if((lcnt= ++lcnt % cnt)== 0)	P12_bit.no0 = !P12_bit.no0;
	
	return	cnt;
}
/*******************************************************************************
* Function Name: 
* Description  : management relays ry=14個
* Arguments    : relay num , 'w'or'r' , 0
* Return Value : None
* Note:
* History:	relay[CARD]		0		//記憶域としての使用	
			relay[DIST]		1
			relay[MAKE]		2
			relay[CHIME]	3
			relay[R_UP]		4
			relay[R_DN]		5
			relay[MAST]		6
			relay[BED_R]	7	
			relay[BED_L]	8
			relay[DESK]		9
			relay[FOOT]		10
			relay[B_UP]		11
			relay[B_DN]		12
			relay[BATH]		13
			relay[MIRR]		14
			relay[K3]		15
			relay[K4]		16
			relay[ROOM3]	17
			relay[ROOM4]	18
			
			relay{WORKS}	19
			relay[TV]		20
			relay[MAIN1]	21
			relay[MAIN2]	22
			relay[OFFCMD]	24		//記憶域としての使用
*******************************************************************************/
unsigned char	ryCont(unsigned char num, char cnt, unsigned char flg){	

	static unsigned char	relay[26]= {0};

	if(cnt =='w' || cnt =='r'){

		if(cnt=='r')	flg= relay[num];
		else	relay[num]= flg;
	}
	return	flg;
}
/*******************************************************************************
* Function Name: 
* Description  : management relays 初期化dataはintで与えるが保持dataはchar配列[]
* Arguments    : Code
* Return Value : None
* Note:			: 
* History:  
*******************************************************************************/
void	ryInit(unsigned long data){ //initdata= 0x0000 0*** **** ****
	
	unsigned short i= 0;
	unsigned short j= 1;
	
	for(i =1;i <OFFCMD;i++,j <<=1){	//ryCont(0,'r',0)は RoomCardStatus	

		ryCont(i,'w',(data & j));	//ryは1-25迄 i添字は1からなのでrelay[0]に入ることはない
	}
}
/*******************************************************************************
* Function Name: 
* Description  : SW入力
* Arguments    : Code
* Return Value : None
* Note:
* History:  
*******************************************************************************/
unsigned char	portScan(unsigned char num){
	
	unsigned char	ans= 0;		//本番はactiv'H'だから
	
	if(num== CARD)			ans= P0_bit.no5;	//CARD

	else if(num== DIST)		ans= P7_bit.no1;
	else if(num== MAKE)		ans= P7_bit.no2;
	else if(num== CHIME)	ans= P7_bit.no3;
	
	else if(num== R_UP)		ans= (P5_bit.no4 & P14_bit.no0);//BED SIDE UP
	else if(num== R_DN)		ans= (P5_bit.no4 & P14_bit.no1);//BED SIDE DOWN
	
	else if(num== BSIDE)	ans= (P5_bit.no4 & P7_bit.no4);//BED SIDE ON/OFF 
	else if(num== BED_R)	ans= (P5_bit.no4 & P7_bit.no5);//読書灯 BED R
	else if(num== BED_L)	ans= (P5_bit.no4 & P7_bit.no6);//読書灯 BED L
	else if(num== DESK)		ans= (P5_bit.no4 & P3_bit.no0);//入口 通路 DESK これがMaster
	else if(num== FOOT)		ans= (P5_bit.no4 & P3_bit.no1);//FOOT
	
	else if(num== B_UP)		ans= (P5_bit.no5 & P14_bit.no0);//BATH UP	
	else if(num== B_DN)		ans= (P5_bit.no5 & P14_bit.no1);//BATH DOWN
	else if(num== BATH)		ans= (P5_bit.no5 & P7_bit.no4);//BATH ON/OFF
	else if(num== MIRR) 	ans= (P5_bit.no5 & P7_bit.no5);//MIRROR ON/OFF
	
	else if(num== K3)	ans= (P5_bit.no5 & P7_bit.no6);
	else if(num== K4)	ans= (P5_bit.no5 & P3_bit.no0);
	else if(num== K5)	ans= (P5_bit.no5 & P3_bit.no1);
	else if(num== K6)	ans= (P5_bit.no5 & P1_bit.no6);//増設
	
	else if(num== WORKS)	ans= P0_bit.no6;	// Lon Works
	
	else if(num== MAINT)	ans= P0_bit.no1;	// 内部SW
	
	return	ans;
}
/*******************************************************************************
* Function Name: 
* Description  : 
* Arguments    : Code
* Return Value : None
* Note:
* History:  
*******************************************************************************/
void	comSelect(char num){
	
	if(num=='1'){	
		P5_bit.no4= 1;
		P5_bit.no5= 0;
	}
	else if(num=='2'){
		P5_bit.no4= 0;
		P5_bit.no5= 1;
	}
	else{
		P5_bit.no4= 0;
		P5_bit.no5= 0;
	}
}
/*******************************************************************************
* Function Name: 
* Description  : 
*				P14_6 	K3
*				P1_0 	K4
*				P1_1	K5
*				P1_2	K1
*				P13_0	K2
*				
* Arguments    : Code
* Return Value : None
* Note:			Ry= 12個 chime= 1 LED= 2
* History:  	relay[25]= {0};	Card= 0
*******************************************************************************/
void	portOut(unsigned char num, unsigned char data){
	
#ifdef	STANDARD

		if(num== DIST/*1*/)			P5_bit.no2= data;	// do not disturb
		else if(num== MAKE/*2*/)	P5_bit.no3= data;	// make up room
		else if(num==CHIME/*3*/)	P13_bit.no0=data;	// RY13-> K2(chime)
		//			4	R_UP
		//			5	R_DN
		else if(num==BSIDE/*6*/)	P14_bit.no7=data;	// RY8 2-4 -> K14(DIM2)
		else if(num==BED_R/*7*/)	P2_bit.no6= data;	// RY6 2-2 -> K12(BED_R)
		else if(num==BED_L/*8*/)	P2_bit.no7= data;	// RY7 2-3 -> K13(BED_L)
		else if(num== DESK/*9*/)	P2_bit.no5= data;	// RY5 2-1 -> K11(DESK)
		else if(num== FOOT/*10*/) 	P2_bit.no4= data;	// RY4 1-3 -> K9 (MIRRER FOOT)
		//			11	B_UP
		//			12	B_DN
		else if(num== BATH/*13*/)	P2_bit.no3= data;	// RY3 1-2 -> K10(DIM1)
		else if(num== MIRR/*14*/)	P2_bit.no2= data;	// RY2 1-1-> K8 (MIRRER)
		
		else if(num== TV/*19*/)		P1_bit.no2= data;	// RY12-> K1(TV)
		else if(num== MAIN1/*20*/)	P2_bit.no0= data;	// RY0 -> K6(MAS1)
		else if(num== MAIN2/*21*/)	P2_bit.no1= data;	// RY1 -> K7(MAS2)
		
		//STANDARDにK3-K6は使用しない
		
#endif
/*************************************************************************
		JS3_T															*/

#ifdef	JS3_T

		if(num== DIST/*1*/)			P5_bit.no2= data;	// do not disturb
		else if(num== MAKE/*2*/)	P5_bit.no3= data;	// make up room
		else if(num==CHIME/*3*/)	P13_bit.no0=data;	// RY13-> K2(chime)
		//			4	R_UP
		//			5	R_DN
		else if(num==BSIDE/*6*/)	P14_bit.no7=data;	// RY8 2-4 -> K14(DIM2)
		else if(num==BED_R/*7*/)	P2_bit.no6= data;	// RY6 2-2 -> K12(BED_R)
		else if(num==BED_L/*8*/)	P2_bit.no7= data;	// RY7 2-3 -> K13(BED_L)
		
		//else if(num== DESK/*9*/)	P2_bit.no5= data;	// RY5 2-1 -> K11(DESK)
		else if(num== DESK/*9*/)	P1_bit.no1= data;	// -> K5(DESK)
		
		else if(num== FOOT/*10*/) 	P2_bit.no4= data;	// RY4 1-3 -> K9 (MIRRER FOOT)
		//			11	B_UP@
		//			12	B_DN
		else if(num== BATH/*13*/)	P2_bit.no3= data;	// RY3 1-2 -> K10(DIM1)
		else if(num== MIRR/*14*/)	P2_bit.no2= data;	// RY2 1-1-> K8 (MIRRER)
		
		else if(num== TV/*19*/)		P1_bit.no2= data;	// RY12-> K1(TV)
		else if(num== MAIN1/*20*/)	P2_bit.no0= data;	// RY0 -> K6(MAS1)
		else if(num== MAIN2/*21*/)	P2_bit.no1= data;	// RY1 -> K7(MAS2)
	
		else if(num== K3/*ROOM1 15*/)	P14_bit.no6=data;	// P14_6->K3
		else if(num== K4/*ROOM2 16*/)	P1_bit.no0= data;	// P1_0-> K4
		else if(num== K5/*ROOM3 17*/)	P2_bit.no5= data;	// RY5 2-1 -> K11(DESK)
		//else if(num== K6/*ROOM4 18*/)	P1_bit.no1= data;	// P1_1	K5

#endif



#if defined(JS1) || defined(JS3_K) || defined(DL3)

		if(num== DIST/*1*/)			P5_bit.no2= data;	// do not disturb
		else if(num== MAKE/*2*/)	P5_bit.no3= data;	// make up room
		else if(num==CHIME/*3*/)	P13_bit.no0=data;	// RY13-> K2(chime)
		//			4	R_UP
		//			5	R_DN
		else if(num==BSIDE/*6*/)	P14_bit.no7=data;	// RY8 2-4 -> K14(DIM2)
		else if(num==BED_R/*7*/)	P2_bit.no6= data;	// RY6 2-2 -> K12(BED_R)
		else if(num==BED_L/*8*/)	P2_bit.no7= data;	// RY7 2-3 -> K13(BED_L)
		else if(num== DESK/*9*/)	P2_bit.no5= data;	// RY5 2-1 -> K11(DESK)
		else if(num== FOOT/*10*/) 	P2_bit.no4= data;	// RY4 1-3 -> K9 (MIRRER FOOT)
		//			11	B_UP@
		//			12	B_DN
		else if(num== BATH/*13*/)	P2_bit.no3= data;	// RY3 1-2 -> K10(DIM1)
		else if(num== MIRR/*14*/)	P2_bit.no2= data;	// RY2 1-1-> K8 (MIRRER)
		
		else if(num== TV/*19*/)		P1_bit.no2= data;	// RY12-> K1(TV)
		else if(num== MAIN1/*20*/)	P2_bit.no0= data;	// RY0 -> K6(MAS1)
		else if(num== MAIN2/*21*/)	P2_bit.no1= data;	// RY1 -> K7(MAS2)
		
		else if(num== K3/*ROOM1 15*/)	P14_bit.no6=data;	// P14_6-> K3
		else if(num== K4/*ROOM2 16*/)	P1_bit.no0= data;	// P1_0-> K4
		else if(num== K5/*ROOM3 17*/)	P1_bit.no1= data;	// RY11-> K5
		else if(num== K6/*ROOM4 18*/)	P0_bit.no0= data;	// P0_0-> 増設Ry
		
#endif		
				
}
/*******************************************************************************
* Function Name: WELLCOME設定はこちら
* Description  : 
* Arguments    : Code 
* Return Value : None
* Note:
* History:  
*******************************************************************************/
void	cardOn(char num){		
		
		sideDim= DL50ON;
		
		bathDim= BOFF;		//DL50ON;	//BATH_DL
		
		ryCont(BATH,'w',0);
		ryCont(MIRR,'w',0);
		ryCont(FOOT,'w',0);
		
		if(num== 'f'){
			
			ryCont(CARD,'w',0);
			ryCont(TV,'w',0);
			ryCont(MAIN1,'w',0);
			ryCont(MAIN2,'w',0);
		}

		if(num== 'c'){
			
			ryCont(CARD,'w',1);			// relay[0]= 1;
			ryCont(TV,'w',1);
			ryCont(MAIN1,'w',1);
			ryCont(MAIN2,'w',1);
		}
		
		ryCont(DESK,'w',1);				//K11
		ryCont(BSIDE,'w',1);
		
		
#ifdef	DL3		
		ryCont(K5,'w',1);
#endif

#ifdef	JS1
		ryCont(K3,'w',1);
		ryCont(K4,'w',1);
#endif

#ifdef	JS3_T
		ryCont(K3,'w',1);
		ryCont(K5,'w',1);
#endif

#ifdef	JS3_K
		ryCont(K3,'w',1);
		ryCont(K4,'w',1);
		ryCont(K5,'w',1);
#endif

}


void	cardOff(void){
		sideDim= ROFF;				//BSIDE_DL
		bathDim= BOFF;				//BATH_DL
									// ALL_OFF slowOutの為のこの方式
		//ryCont(OFFCMD,'w',MAIN2);	// MAIN2はEND兼用			
		ryCont(CARD,'w',0);			// relay[0]= 0;
		ryCont(DIST,'w',0);
		ryCont(DESK,'w',0);
		ryCont(FOOT,'w',0);
		ryCont(BSIDE,'w',0);
		ryCont(BED_R,'w',0);
		ryCont(BED_L,'w',0);
	
		ryCont(BATH,'w',0);
		ryCont(MIRR,'w',0);
		ryCont(K3,'w',0);
		ryCont(K4,'w',0);
		ryCont(K5,'w',0);
		
		ryCont(K6,'w',0);			//増設
		ryCont(TV,'w',0);
	
		ryCont(MAIN1,'w',0);
		ryCont(MAIN2,'w',0);
}
/*******************************************************************************
* Function Name: 
* Description  : 
* Arguments    : Code
* Return Value : None
* Note:	CARD OFFでOFFCMDにMAIN2(21)を書いている
* History:  
*******************************************************************************/
unsigned int	delayOff(unsigned int cnt){
	
	unsigned char i;
	unsigned char	j;
	static unsigned int lcnt;

	
	if((lcnt= ++lcnt % cnt)== 0){
	
		j= ryCont(OFFCMD,'r',0);	//21が書いてある
		if(j==0) return cnt;
	
		i= (MAIN2+1)-j;
		ryCont(i,'w',0);			//1 - J 迄 0を書いていく
		j--;
		ryCont(OFFCMD,'w',j);
		
	}
		return cnt;
}
/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void	serialEnd(void){

	g_tx0_ready_flag =FREE;

}
/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
unsigned char	serialPrint0(char *buff, unsigned int num){
	
	while(g_tx0_ready_flag != FREE) __nop();
	
	g_tx0_ready_flag = BUSY;
	R_UART0_Send((uint8_t *)buff,num);
		
	return 0;
}
/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void	info(void){
	
	char	buf[50];

#ifdef	DL3
	sprintf(buf ,"DL3 DATE is %s \n" ,__DATE__);
#endif

#ifdef JS1
	sprintf(buf ,"JS1 DATE is %s \n" ,__DATE__);
#endif

#ifdef JS3_T
	sprintf(buf ,"JS3-T DATE is %s \n" ,__DATE__);
#endif

#ifdef JS3_K
	sprintf(buf ,"JS3-K DATE is %s \n" ,__DATE__);
#endif

#ifdef STANDARD
	sprintf(buf ,"STANDARD DATE is %s \n" ,__DATE__);
#endif

    //sprintf(buf ,"DATE is %s \n" ,__DATE__);
    serialPrint0(buf,strlen(buf));
}

#if 1
/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void	DebugPrint(int8_t *s,uint16_t n){
	
	char	buf[50];
		
	sprintf(buf,"%s%d\n" ,s ,n );
	serialPrint0(buf,strlen(buf));
}
#else
/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void	DebugPrint(char *s){
	
    static char	__buf__[50];
						
    sprintf(__buf__ ,"%s (File:%s ,Line:%d)" ,*s ,__FILE__ ,__LINE__);	
		//uint8_t bl= sizeof buff; この場合のsizeofはポインタのサイズ
	serialPrint0(__buf__,strlen(__buf__));
}
#endif

/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void	outMoni(void){
	
	char	*buf= outmoni;
			buf+=	6;
			*(buf)=	0x30|(ryCont(MAIN1,'r',0));
			buf+=	8;
			*(buf)=	0x30|(ryCont(MAIN2,'r',0));
			buf+=	6;
			*(buf)=	0x30|(ryCont(MIRR,'r',0));
			buf+=	6;
			*(buf)=	0x30|(ryCont(FOOT,'r',0));
			buf+=	6;
			*(buf)=	0x30|(ryCont(BATH,'r',0));
			buf+=	6;
			*(buf)=0x30|(ryCont(DESK,'r',0));
			buf+=	6;
			*(buf)=0x30|(ryCont(BED_R,'r',0));
			buf+=	6;
			*(buf)=0x30|(ryCont(BED_L,'r',0));
			buf+=	6;
			*(buf)=0x30|(ryCont(BSIDE,'r',0));
			buf+=	6;
			*(buf)=0x30|(ryCont(TV,'r',0));
			buf+=	6;
			*(buf)=0x30|(ryCont(CHIME,'r',0));
			buf+=	6;
			*(buf)=0x30|(ryCont(K3,'r',0));
			buf+=	6;
			*(buf)=0x30|(ryCont(K4,'r',0));
			buf+=	6;
			*(buf)=0x30|(ryCont(K5,'r',0));
			buf+=	6;
			*(buf)=0x30|(ryCont(K6,'r',0));
			
			serialPrint0(outmoni,strlen(outmoni));
}

/* End user code. Do not edit comment generated here */
