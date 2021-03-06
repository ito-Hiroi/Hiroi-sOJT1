#ifndef PWMLED_H
#define PWMLED_H

//*****************************************************************************
/// @file
//*****************************************************************************

//=============================================================================
// includeファイル
//=============================================================================

//=============================================================================
// マクロ定義(定数, 関数マクロ)
//=============================================================================
#define ON  (1)
#define OFF (0)
#define PWM_LOWERING (0)
#define PWM_INCREASE (1)
#define WAITDUTY (0)
#define MOVEDUTY (1)
//=============================================================================
// 型定義(typedef, 構造体等)
//=============================================================================

//=============================================================================
// 外部変数・外部定数宣言
//=============================================================================

//=============================================================================
//  外部関数宣言
//=============================================================================
extern void PWM_led( void );
extern void WaitorMove_PWM( void );

#endif	//PWMLED_H
