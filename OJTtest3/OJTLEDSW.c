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

#define EV1 1 //SW�����ꂽ
#define EV2 2 //SW���ꂽ
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
	MSTP(CMT1)		= 0;				//CMT�̏�����
	CMT.CMSTR0.BIT.STR1	= 0;       			// CMT1�J�E���g��~
	CMT1.CMCR.BIT.CKS	= 0x03;				// �������s�� PCLK/512  �����PCLK:20MHz
	CMT1.CMCR.BIT.CMIE	= 1;				// �R���y�A�}�b�`���荞�݋���
	CMT1.CMCOR              = 39-1;                         //1ms
        CMT1.CMCNT		= 0;                            //�R���y�A�}�b�`�^�C�}�J�E���^
	CMT.CMSTR0.BIT.STR1	= 1;       			// CMT1�J�E���g�X�^�[�g
	
	IPR(CMT1,CMI1)          = 14;                           //CMI1�̊��荞�ݗD��x��ݒ�(��)
        IEN(CMT1,CMI1)          = 1;                            //���荞�݂�������
	IR( CMT1, CMI1 )	= 0;                            // CMT0 �R���y�A�}�b�`���荞�ݗv���t���O���N���A
}


void LEDswitch(void)//LED�_�������֐�
{
	if(LEDState==LOW){
		PORTE.PODR.BIT.B7 = 0;//LED�_��
		LEDState=HIGH;
	} else if(LEDState==HIGH) {
		PORTE.PODR.BIT.B7 = 1;//LED����
		LEDState=LOW;
	}
}


/*
void SW()
{
	switch(State){
		case LEDON://LED���_�����Ă�����
			switch(Event){
				case EV1 :  PORTE.PODR.BIT.B7 = 1;//����������
					   State = LEDOFF;
					   break;
				case EV2 : break;
			}
			break;
			
		case LEDOFF://LED���������Ă�����
			switch(Event){
				case EV1 : PORTE.PODR.BIT.B7 = 0;//�_��������
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
		if(PORTE.PIDR.BIT.B2 == 1 && Event==EV2){ //SW�������ꂽ����
			Event=EV1;
        		LEDswitch();
		}else if(PORTE.PIDR.BIT.B2 == 0 && Event==EV1){ //SW�����ꂽ����
        		Event=EV2;
		}
	}
}


		
void HardwareSetup()
{
    SYSTEM.PRCR.WORD = 0x0A50b;             //�N���b�N�\�[�X�I���̕ی����
    SYSTEM.SCKCR.LONG = 0x00001111;         //�����̐ݒ�
    SYSTEM.SCKCR3.WORD = 0x0200;            //���C���N���b�N���g�p����
    SYSTEM.MOSCCR.BYTE = 0;                 //���C���N���b�N���U��𓮍삳����
    SYSTEM.SOSCCR.BYTE = 0;                 //�T�u�N���b�N���U��𓮍삳����
}



void main(void)
{
	HardwareSetup();
	//I/O�|�[�g��ݒ�
        PORTE.PMR.BIT.B7 = 0;//E7
	PORTE.PMR.BIT.B2 = 0;//E2
	//���o�͐ݒ�
 	PORTE.PDR.BIT.B7 = 1;// E7�o��
	PORTE.PDR.BIT.B2 = 0;// E2����
	///////
	PORTE.ODR1.BIT.B6 = 1;// E7���I�[�v���h���C���ɂ���
	PORTE.PODR.BIT.B7 = 1;// �ŏ��͂k����
	TimerInit();
	
	//�^�N�g�X�C�b�`�����������LED��_��/����������
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
