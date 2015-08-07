/* 
 * File:   sample001.c
 * Author: Tetsuya-PC
 *
 *Stared to create on 2015/06/18, 16:28
 */
//FreeRTOSをPICに実装し、Lチカをタスク１として実行させる

//#include <xc.h>
#include <p30f6014a.h>
#include "FreeRTOS.h"
#include "task.h"
#include <timer.h>
//#include "queue.h"



// DSPIC30F6014A Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

#define _XTAL_FREQ 8000000          //クロック数定義

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




/* OSC（クロック設定）*/
//#pragma config FOSFPR = FRC             /* 8[MHz]の内部発信器を使用 */
//#pragma config FCKSMEN = CSW_FSCM_OFF   /* クロック切り替えを無効 */

/* FWDT（ウォッチドッグ・タイマ設定）*/
//#pragma config FWPSB = WDTPSB_16        /* プリスケーラBの設定（デフォルト） */
//#pragma config FWPSA = WDTPSA_512       /* プリスケーラAの設定 （デフォルト）*/
//#pragma config WDT = WDT_OFF            /* ウォッチドッグ・タイマを無効 */

/* FBORPOR（ブラウン・アウト・リセット、パワー・オン・リセット設定）*/
//#pragma config FPWRT = PWRT_64          /* 64[ms]のパルス幅でリセット*/
//#pragma config BODENV = BORV_27         /* 2.7[V]以下になったらリセット*/
//#pragma config BOREN = PBOR_ON          /* 自動リセットを有効*/
//#pragma config MCLRE = MCLR_EN          /* MCLRピンを有効*/

/* FBS（ブート設定？デフォルト値使用）*/
//#pragma config BWRP = WR_PROTECT_BOOT_OFF// Boot Segment Program Memory Write Protect (Boot Segment Program Memory may be written)
//#pragma config BSS = NO_BOOT_CODE       // Boot Segment Program Flash Memory Code Protection (No Boot Segment)
//#pragma config EBS = NO_BOOT_EEPROM     // Boot Segment Data EEPROM Protection (No Boot EEPROM)
//#pragma config RBS = NO_BOOT_RAM        // Boot Segment Data RAM Protection (No Boot RAM)

/* FSS（セキュリティ設定？デフォルト値使用）*/
//#pragma config SWRP = WR_PROT_SEC_OFF   // Secure Segment Program Write Protect (Disabled)
//#pragma config SSS = NO_SEC_CODE        // Secure Segment Program Flash Memory Code Protection (No Secure Segment)
//#pragma config ESS = NO_SEC_EEPROM      // Secure Segment Data EEPROM Protection (No Segment Data EEPROM)
//#pragma config RSS = NO_SEC_RAM         // Secure Segment Data RAM Protection (No Secure RAM)

/* FGS（コードプロテクト設定）*/
//#pragma config GWRP = GWRP_OFF          /* コード書き込み保護無効 */
//#pragma config GCP = GSS_OFF            /* コード保護無効 */

// FICD
//#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)


/*
  関数プロトタイプ
 */
void __attribute__(( interrupt, auto_psv )) _T1Interrupt(void);

//void vTaskStartScheduler(void); //タスク開始処理関数
//void vTaskEndSchedular(void);   //タスク終了処理関数
//void vTaskSuspendAll(void);     //タスク停止処理関数
//void vTaskResumeAll(void);      //タスク再開処理関数
//void vTaskDelay(portTickType);  //タスク一時停止処理関数

//void vTask2( void *pvParameters );
//void vTask3( void *pvParameters );

//タスク１内容設定
void vTask1(void *pvParameters){
    while(1){
        LATFbits.LATF5 = 0;
        vTaskDelay(50);         //一時停止0.5秒位？
        //vTaskDelay( 500 / portTICK_PERIOD_MS);        //FreeRTOSのディレイを使っているが実行されない
        LATFbits.LATF5 = 1;     //一時停止0.5秒位？
        vTaskDelay(50);
    }

}
//void vSetupEnvironment( void );

//xQueueHandle lcdQueue;
//キュー関数


int main(void)
{
    //vSetupEnvironment();

    TRISF = 0x00;
    PORTF = 0x00;
    LATFbits.LATF5 = 1;             //40ピンからLED点灯
    LATFbits.LATF5 = 0;             //消灯
    //LATFbits.LATF5 = 1;

    xTaskCreate( vTask1, (signed portCHAR *)"T1", 200, NULL, 1, NULL );     //タスク作成と定義
  //xTaskCreate( vTask2, (signed portCHAR *)"T2", 100, NULL, 1, NULL );
  //xTaskCreate( vTask3, (signed portCHAR *)"T3", 100, NULL, 1, NULL );
    
    vTaskStartScheduler();      //タスク開始

    while(1){}                  //空プール
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
  //　　vTaskDelayUntil(&xLastExecutionTime, 1000/portTICK_RATE_MS);
  //    LATFbits.LATF5 ^= LATFbits.LATF5;
        /*
        for(i =0; i < 5; i++){
            xQueueSendToBack(numQueue, &Count1, 0);
            Count1++;   
        }
        itostring(5, Count1, Msg1+11);
        xQueueSendToBack(lcdQueue, Msg1, portMAX_DELAY);
        */
// 　　 vTaskDelay(200 / portTICK_RATE_MS);
   // }

//}



//void vTask3(void *pvParamters){
  //  while(1){
    //    LATFbits.LATF5 ^= LATFbits.LATF5;
      //  vTaskDelay(300 / portTICK_RATE_MS);
    //}
//}
