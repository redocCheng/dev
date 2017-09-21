/**
  * @file       ledDrv.h
  * @brief      �����ʼ��ͷ�ļ�
  * @author     redoc
  * @version    v1.0
  * @date       2016-08-20
  *
  * @note
  * [2016-08-20] <redoc> v1.0
  * ��ʼ�汾
  * BEEP_CTRL_OUT PB14 -> PE7
  * @remark
  */



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_DRV_H
#define __LED_DRV_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"


#ifdef __cplusplus
extern "C" {
#endif


/* types ------------------------------------------------------------*/

typedef enum
{
    EID_LED_DRV_PARAM = -1,
    EID_LED_DRV_NOERR = 0,

}ledDrv_err_t;


typedef enum
{
    LED0_OUT = 0,
    LED1_OUT,

    LED_MAX_OUT,
}ledDrv_ID_t;

/* define -----------------------------------------------------------*/

/**
  * @brief ����ڸ���
  */
#define OUTPUTn                           LED_MAX_OUT





/**
  * @brief  LED0_OUT
  */
#define LED0_OUT_PIN                       GPIO_PIN_4
#define LED0_OUT_PORT                      GPIOC
#define LED0_OUT_INIT                      GPIO_PIN_RESET
/**
  * @}
  */

/**
  * @brief  LED1_OUT
  */
#define LED1_OUT_PIN                       GPIO_PIN_5
#define LED1_OUT_PORT                      GPIOC
#define LED1_OUT_INIT                      GPIO_PIN_RESET


/**
  * @brief ���ʱ��ʹ��
  */
#define LEDx_GPIO_CLK_ENABLE()                 do { __HAL_RCC_GPIOA_CLK_ENABLE(); \
                                                 __HAL_RCC_GPIOC_CLK_ENABLE(); } while(0)

/**
  * @brief ���ʱ�ӽ���
  */
#define LEDx_GPIO_CLK_DISABLE()               {  __HAL_RCC_GPIOA_CLK_DISABLE(); \
                                                 __HAL_RCC_GPIOC_CLK_DISABLE(); }



/* constants --------------------------------------------------------*/

/* variables --------------------------------------------------------*/


/* macro ------------------------------------------------------------*/



/* functions --------------------------------------------------------*/
ledDrv_err_t bsp_led_init(ledDrv_ID_t g_ledDrv_id);
ledDrv_err_t bsp_led_set(ledDrv_ID_t g_ledDrv_id,uint8_t state);
ledDrv_err_t bsp_led_on(ledDrv_ID_t g_ledDrv_id);
ledDrv_err_t bsp_led_off(ledDrv_ID_t g_ledDrv_id);
ledDrv_err_t bsp_led_toggle(ledDrv_ID_t g_ledDrv_id);


#ifdef __cplusplus
}
#endif


#endif








