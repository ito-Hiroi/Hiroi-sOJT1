//*****************************************************************************
/// @file
/// led制御ファイル
//*****************************************************************************

//=============================================================================
// includeファイル
//=============================================================================
#include "iodefine.h"
#include "pwmled.h"
#include <stdio.h>
#include <stdlib.h>
//=============================================================================
// マクロ定義(定数, 関数マクロ)
//=============================================================================

//=============================================================================
// 型定義(typedef, 構造体等)
//=============================================================================

//=============================================================================
// 内部関数のプロトタイプ宣言
//=============================================================================

//=============================================================================
// 内部変数・内部定数定義
//=============================================================================
unsigned char PWM_NOW=PWM_INCREASE;
unsigned char Event_DUTY=MOVEDUTY;
unsigned char PWM_cnt;
unsigned char Rand_sec;
unsigned char i;
extern unsigned char Led_State;
//=============================================================================
// 外部変数・外部定数定義
//=============================================================================

//=============================================================================
//  内部関数
//=============================================================================

//*****************************************************************************
/// 関数の説明を記述する。
/// 
/// 内部関数は以下を除き外部関数の定義と同様
/// - 一文字目を小文字にする
/// - static定義する。
//*****************************************************************************

//=============================================================================
//  外部関数
//=============================================================================

//*****************************************************************************
/// 関数の説明を記述する。
///
/// 外部関数は以下のルールに従い記述する。
/// ・1文字目を大文字で定義。また単語の区切りは大文字にする
/// ・引数の説明はそれぞれの引数の宣言の横に「///<」を書いて記述する。
/// ・戻り値の説明は以下のように記述する
///
/// @retval true	戻り値がtrue になる場合の説明 
/// @retval false	戻り値がfalse になる場合の説明
//*****************************************************************************

//*****************************************************************************
/// PWMのDuty比を減少させる関数
//*****************************************************************************

void PWM_LOWERING1( void )
{
	MTU3.TGRC = MTU3.TGRA+5;				//Duty比減少
	if(MTU3.TGRC>=MTU3.TGRB-10){			//Dutyがマイナスにならないように止める
		MTU3.TGRC=MTU3.TGRB;				//Duty比を0％にする
		PWM_NOW=PWM_INCREASE;
		Event_DUTY=WAITDUTY;
		Rand_sec=3+(int)(rand()*(10-3+1)/(1+RAND_MAX));		//2〜10の乱数生成
	}
}

//*****************************************************************************
/// PWMのDUty比を増加させる関数
//*****************************************************************************
void PWM_INCREASE1( void )
{
	MTU3.TGRC=MTU3.TGRA-5;					//Duty比増加
	if(MTU3.TGRC<=100){						//Dutyが100%以上にならないように止める
		PWM_NOW=PWM_LOWERING;
		Event_DUTY=WAITDUTY;
		Rand_sec=3+(int)(rand()*(10-3+1)/(1+RAND_MAX));		//2〜10の乱数生成
	}
}

//*****************************************************************************
/// CMT1割り込みでの関数
// PWMのDuty比を2〜10秒間(ランダム)変化させない
//*****************************************************************************

void WaitorMove_PWM( void )
{
	if(Event_DUTY==WAITDUTY){				//Duty比が増減していなかったら
		PWM_cnt++;
	}else{
		PWM_cnt=0;
	}
}


//*****************************************************************************
/// ledPWM制御
//*****************************************************************************
void PWM_led( void )
{
	if(PWM_cnt==Rand_sec){		//ランダム秒間経過したらDuty比を増減できるようにする
		Event_DUTY=MOVEDUTY;
	}else{
		//何もしない
	}

	if((Event_DUTY==MOVEDUTY) && (Led_State == ON)){	//SWがONかつランダム秒経過後
		if(PWM_NOW == PWM_LOWERING){
			PWM_LOWERING1();							//Duty比を減らす関数へ（LEDを暗く）
		}
		else if(PWM_NOW == PWM_INCREASE){
			PWM_INCREASE1();							//Duty比を増やす関数へ（LEDを明るく）
		}
	}else {
		//何もしない
	}
}
