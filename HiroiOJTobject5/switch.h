#ifndef SWITCH_H
#define SWITCH_H

//*****************************************************************************
/// @file
//*****************************************************************************

//=============================================================================
// includeファイル
//=============================================================================
#include "iodefine.h"

//=============================================================================
// マクロ定義(定数, 関数マクロ)
//=============================================================================
#define SW_EVENT_NONE	(0)							//SWに何もしていない
#define	SW_EVENT_ON		(1)							//SW押された
#define	SW_EVENT_OFF	(2)							//SW離れた
#define	HIGH			(1)
#define	LOW 			(0)
#define	PORT_SW_INPUT	(PORTE.PIDR.BIT.B2)
#define	CHATIME			(3)							//CMTの割り込み時間×CHATIME

//=============================================================================
// 型定義(typedef, 構造体等)
//=============================================================================

//=============================================================================
// 外部変数・外部定数宣言
//=============================================================================

//=============================================================================
//  外部関数宣言
//=============================================================================
extern void SW_Interrupt( void );

#endif	//SWITCH_H
