/**
  * @file       ledDrv.h
  * @brief      输出初始化头文件
  * @author     redoc
  * @version    v1.0
  * @date       2016-08-20
  *
  * @note
  * [2016-08-20] <redoc> v1.0
  * 初始版本
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

}ledDrv_Err_Typedef;


typedef enum
{
    LED0_OUT = 0,
    LED1_OUT,

    LED_MAX_OUT,

}ledDrv_ID_t;

/* define -----------------------------------------------------------*/

/**
  * @brief 输出口个数
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
  * @brief 输出时钟使能
  */
#define LEDx_GPIO_CLK_ENABLE()                 do { __HAL_RCC_GPIOA_CLK_ENABLE(); \
                                                 __HAL_RCC_GPIOC_CLK_ENABLE(); } while(0)

/**
  * @brief 输出时钟禁能
  */
#define LEDx_GPIO_CLK_DISABLE()               {  __HAL_RCC_GPIOA_CLK_DISABLE(); \
                                                 __HAL_RCC_GPIOC_CLK_DISABLE(); }



/* constants --------------------------------------------------------*/

/* variables --------------------------------------------------------*/


/* macro ------------------------------------------------------------*/



/* functions --------------------------------------------------------*/
ledDrv_Err_Typedef bsp_led_init(void *p_cookie);
ledDrv_Err_Typedef bsp_led_Set(void *p_cookie,uint8_t state);
ledDrv_Err_Typedef bsp_led_On(void *p_cookie);
ledDrv_Err_Typedef bsp_led_Off(void *p_cookie);
ledDrv_Err_Typedef bsp_led_Toggle(void *p_cookie);


#ifdef __cplusplus
}
#endif


#endif








