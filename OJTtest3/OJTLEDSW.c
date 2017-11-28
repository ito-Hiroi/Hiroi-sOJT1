/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :Tue, Oct 31, 2006                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
//#include "typedefine.h"
#include "iodefine.h"
int LEDState;
int cnt;

#define EV1 1 //SW押された
#define EV2 2 //SW離れた
#define HIGH 1
#define LOW 0

int Event =EV2;


#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif


void TimerInit()
{
	MSTP(CMT1)		= 0;				//CMTの初期化
	CMT.CMSTR0.BIT.STR1	= 0;       			// CMT1カウント停止
	CMT1.CMCR.BIT.CKS	= 0x03;				// 分周を行う PCLK/512  今回はPCLK:20MHz
	CMT1.CMCR.BIT.CMIE	= 1;				// コンペアマッチ割り込み許可
	CMT1.CMCOR              = 39-1;                         //1ms
        CMT1.CMCNT		= 0;                            //コンペアマッチタイマカウンタ
	CMT.CMSTR0.BIT.STR1	= 1;       			// CMT1カウントスタート
	
	IPR(CMT1,CMI1)          = 14;                           //CMI1の割り込み優先度を設定(高)
        IEN(CMT1,CMI1)          = 1;                            //割り込みを許可する
	IR( CMT1, CMI1 )	= 0;                            // CMT0 コンペアマッチ割り込み要求フラグをクリア
}


void LEDswitch(void)//LED点灯消灯関数
{
	if(LEDState==LOW){
		PORTE.PODR.BIT.B7 = 0;//LED点灯
		LEDState=HIGH;
	} else if(LEDState==HIGH) {
		PORTE.PODR.BIT.B7 = 1;//LED消灯
		LEDState=LOW;
	}
}


/*
void SW()
{
	switch(State){
		case LEDON://LEDが点灯していたら
			switch(Event){
				case EV1 :  PORTE.PODR.BIT.B7 = 1;//消灯させる
					   State = LEDOFF;
					   break;
				case EV2 : break;
			}
			break;
			
		case LEDOFF://LEDが消灯していたら
			switch(Event){
				case EV1 : PORTE.PODR.BIT.B7 = 0;//点灯させる
					   State = LEDON;
					   break;
				case EV2 : break;
			}
			break;
		
		default : break;
	}
}
*/

void LED_CTR()
{
	if(cnt>=5){ 
		if(PORTE.PIDR.BIT.B2 == 1 && Event==EV2){ //SWが押された判定
			Event=EV1;
        		LEDswitch();
		}else if(PORTE.PIDR.BIT.B2 == 0 && Event==EV1){ //SWが離れた判定
        		Event=EV2;
		}
	}
}


		
void HardwareSetup()
{
    SYSTEM.PRCR.WORD = 0x0A50b;             //クロックソース選択の保護解除
    SYSTEM.SCKCR.LONG = 0x00001111;         //分周の設定
    SYSTEM.SCKCR3.WORD = 0x0200;            //メインクロックを使用する
    SYSTEM.MOSCCR.BYTE = 0;                 //メインクロック発振器を動作させる
    SYSTEM.SOSCCR.BYTE = 0;                 //サブクロック発振器を動作させる
}



void main(void)
{
	HardwareSetup();
	//I/Oポートを設定
        PORTE.PMR.BIT.B7 = 0;//E7
	PORTE.PMR.BIT.B2 = 0;//E2
	//入出力設定
 	PORTE.PDR.BIT.B7 = 1;// E7出力
	PORTE.PDR.BIT.B2 = 0;// E2入力
	///////
	PORTE.ODR1.BIT.B6 = 1;// E7をオープンドレインにする
	PORTE.PODR.BIT.B7 = 1;// 最初はＬｏｗ
	TimerInit();
	
	//タクトスイッチを押下するとLEDを点灯/消灯させる
	while(1)
	{
		LED_CTR();
	}

}



#ifdef __cplusplus
void abort(void)
{

}
#endif
