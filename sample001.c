/* 
 * File:   sample001.c
 * Author: Tetsuya-PC
 *
 *Stared to create on 2015/06/18, 16:28
 */
//FreeRTOS��PIC�Ɏ������AL�`�J���^�X�N�P�Ƃ��Ď��s������

//#include <xc.h>
#include <p30f6014a.h>
#include "FreeRTOS.h"
#include "task.h"
#include <timer.h>
//#include "queue.h"



// DSPIC30F6014A Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

#define _XTAL_FREQ 8000000          //�N���b�N����`

// FOSC
#pragma config FOSFPR = FRC      // Oscillator (FRC w/PLL 8x)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV_27         // Brown Out Voltage (2.7V)
#pragma config BOREN = PBOR_ON          // PBOR Enable (Enabled)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)

// FBS
#pragma config BWRP = WR_PROTECT_BOOT_OFF// Boot Segment Program Memory Write Protect (Boot Segment Program Memory may be written)
#pragma config BSS = NO_BOOT_CODE       // Boot Segment Program Flash Memory Code Protection (No Boot Segment)
#pragma config EBS = NO_BOOT_EEPROM     // Boot Segment Data EEPROM Protection (No Boot EEPROM)
#pragma config RBS = NO_BOOT_RAM        // Boot Segment Data RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WR_PROT_SEC_OFF   // Secure Segment Program Write Protect (Disabled)
#pragma config SSS = NO_SEC_CODE        // Secure Segment Program Flash Memory Code Protection (No Secure Segment)
#pragma config ESS = NO_SEC_EEPROM      // Secure Segment Data EEPROM Protection (No Segment Data EEPROM)
#pragma config RSS = NO_SEC_RAM         // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = GSS_OFF            // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)




/* OSC�i�N���b�N�ݒ�j*/
//#pragma config FOSFPR = FRC             /* 8[MHz]�̓������M����g�p */
//#pragma config FCKSMEN = CSW_FSCM_OFF   /* �N���b�N�؂�ւ��𖳌� */

/* FWDT�i�E�H�b�`�h�b�O�E�^�C�}�ݒ�j*/
//#pragma config FWPSB = WDTPSB_16        /* �v���X�P�[��B�̐ݒ�i�f�t�H���g�j */
//#pragma config FWPSA = WDTPSA_512       /* �v���X�P�[��A�̐ݒ� �i�f�t�H���g�j*/
//#pragma config WDT = WDT_OFF            /* �E�H�b�`�h�b�O�E�^�C�}�𖳌� */

/* FBORPOR�i�u���E���E�A�E�g�E���Z�b�g�A�p���[�E�I���E���Z�b�g�ݒ�j*/
//#pragma config FPWRT = PWRT_64          /* 64[ms]�̃p���X���Ń��Z�b�g*/
//#pragma config BODENV = BORV_27         /* 2.7[V]�ȉ��ɂȂ����烊�Z�b�g*/
//#pragma config BOREN = PBOR_ON          /* �������Z�b�g��L��*/
//#pragma config MCLRE = MCLR_EN          /* MCLR�s����L��*/

/* FBS�i�u�[�g�ݒ�H�f�t�H���g�l�g�p�j*/
//#pragma config BWRP = WR_PROTECT_BOOT_OFF// Boot Segment Program Memory Write Protect (Boot Segment Program Memory may be written)
//#pragma config BSS = NO_BOOT_CODE       // Boot Segment Program Flash Memory Code Protection (No Boot Segment)
//#pragma config EBS = NO_BOOT_EEPROM     // Boot Segment Data EEPROM Protection (No Boot EEPROM)
//#pragma config RBS = NO_BOOT_RAM        // Boot Segment Data RAM Protection (No Boot RAM)

/* FSS�i�Z�L�����e�B�ݒ�H�f�t�H���g�l�g�p�j*/
//#pragma config SWRP = WR_PROT_SEC_OFF   // Secure Segment Program Write Protect (Disabled)
//#pragma config SSS = NO_SEC_CODE        // Secure Segment Program Flash Memory Code Protection (No Secure Segment)
//#pragma config ESS = NO_SEC_EEPROM      // Secure Segment Data EEPROM Protection (No Segment Data EEPROM)
//#pragma config RSS = NO_SEC_RAM         // Secure Segment Data RAM Protection (No Secure RAM)

/* FGS�i�R�[�h�v���e�N�g�ݒ�j*/
//#pragma config GWRP = GWRP_OFF          /* �R�[�h�������ݕی얳�� */
//#pragma config GCP = GSS_OFF            /* �R�[�h�ی얳�� */

// FICD
//#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)


/*
  �֐��v���g�^�C�v
 */
void __attribute__(( interrupt, auto_psv )) _T1Interrupt(void);

//void vTaskStartScheduler(void); //�^�X�N�J�n�����֐�
//void vTaskEndSchedular(void);   //�^�X�N�I�������֐�
//void vTaskSuspendAll(void);     //�^�X�N��~�����֐�
//void vTaskResumeAll(void);      //�^�X�N�ĊJ�����֐�
//void vTaskDelay(portTickType);  //�^�X�N�ꎞ��~�����֐�

//void vTask2( void *pvParameters );
//void vTask3( void *pvParameters );

//�^�X�N�P���e�ݒ�
void vTask1(void *pvParameters){
    while(1){
        LATFbits.LATF5 = 0;
        vTaskDelay(50);         //�ꎞ��~0.5�b�ʁH
        //vTaskDelay( 500 / portTICK_PERIOD_MS);        //FreeRTOS�̃f�B���C���g���Ă��邪���s����Ȃ�
        LATFbits.LATF5 = 1;     //�ꎞ��~0.5�b�ʁH
        vTaskDelay(50);
    }

}
//void vSetupEnvironment( void );

//xQueueHandle lcdQueue;
//�L���[�֐�


int main(void)
{
    //vSetupEnvironment();

    TRISF = 0x00;
    PORTF = 0x00;
    LATFbits.LATF5 = 1;             //40�s������LED�_��
    LATFbits.LATF5 = 0;             //����
    //LATFbits.LATF5 = 1;

    xTaskCreate( vTask1, (signed portCHAR *)"T1", 200, NULL, 1, NULL );     //�^�X�N�쐬�ƒ�`
  //xTaskCreate( vTask2, (signed portCHAR *)"T2", 100, NULL, 1, NULL );
  //xTaskCreate( vTask3, (signed portCHAR *)"T3", 100, NULL, 1, NULL );
    
    vTaskStartScheduler();      //�^�X�N�J�n

    while(1){}                  //��v�[��
    return (0);
}

//void vTask2(void *pvParamters){
        /*
        portTickType xLastExecutionTime;
        static unsigned char Msg1[] = "Task1Count = 0";
        static unsigned int Count1 = 0;
        unsigned int i;

        xLastExecutionTime = xTaskGetTickCount();
        */
  //  while(1){
  //�@�@vTaskDelayUntil(&xLastExecutionTime, 1000/portTICK_RATE_MS);
  //    LATFbits.LATF5 ^= LATFbits.LATF5;
        /*
        for(i =0; i < 5; i++){
            xQueueSendToBack(numQueue, &Count1, 0);
            Count1++;   
        }
        itostring(5, Count1, Msg1+11);
        xQueueSendToBack(lcdQueue, Msg1, portMAX_DELAY);
        */
// �@�@ vTaskDelay(200 / portTICK_RATE_MS);
   // }

//}



//void vTask3(void *pvParamters){
  //  while(1){
    //    LATFbits.LATF5 ^= LATFbits.LATF5;
      //  vTaskDelay(300 / portTICK_RATE_MS);
    //}
//}
