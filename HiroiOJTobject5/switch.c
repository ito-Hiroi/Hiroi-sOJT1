//*****************************************************************************
/// @file
//  SW判定ファイル
//*****************************************************************************

//=============================================================================
// includeファイル
//=============================================================================
#include "switch.h"

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
unsigned char Sw_nowinput;
unsigned char Sw_lastinput;
unsigned char Sw_cnt;
unsigned char Sw_event;

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
/// SWを切り替える関数
//*****************************************************************************
void SW_Main( void )
{
	if(Sw_event == SW_EVENT_ON){
		Sw_event = SW_EVENT_NONE;
		Led_switch();
	}
}


//*****************************************************************************
/// チャタリング除去用関数
//*****************************************************************************
void SW_Interrupt( void )
{
	Sw_nowinput = PORT_SW_INPUT;

	if(Sw_nowinput!=Sw_lastinput){			//前回と比較
		Sw_cnt=0;
	} else{
		if(Sw_cnt<CHATIME){					//チャタリング除去30ms
			Sw_cnt++;
			if(Sw_cnt == CHATIME){
				if(Sw_nowinput == LOW){
					Sw_event=SW_EVENT_ON;	//スイッチが押された判定
				} else{
					Sw_event=SW_EVENT_OFF;	//スイッチが離れた判定
				}
			}
		}
	}
	Sw_lastinput=Sw_nowinput;				//次と比較するために保存
}