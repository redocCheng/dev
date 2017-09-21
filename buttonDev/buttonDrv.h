/**
  * @file       buttonDrv.h
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
#ifndef __BUTTON_DRV_H
#define __BUTTON_DRV_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"


#ifdef __cplusplus
extern "C" {
#endif


/* types ------------------------------------------------------------*/

typedef enum
{
    EID_BUTTON_DRV_PARAM = -1,
    EID_BUTTON_DRV_NOERR = 0,

}buttonDrv_err_t;


/**
  * @brief ����ڶ���
  */
typedef enum
{
    KEY_EXPOUSE_IN=0,       //�عⰴ��
    KEY_RELEASE_IN,         //һ���ͷŰ���

    BUTTON_MAX,

} buttonDrv_ID_t;


/* Exported constants --------------------------------------------------------*/



/**
  * @brief ����ڸ���
  */
#define INPUTn                         BUTTON_MAX


/**
  * @brief  KEY_EXPOUSE_IN     �عⰴ��
  */
#define KEY_EXPOUSE_IN_PIN              GPIO_PIN_6
#define KEY_EXPOUSE_IN_PORT             GPIOB
#define KEY_EXPOUSE_IN_PULL             GPIO_PULLUP
#define KEY_EXPOUSE_IN_INIT             GPIO_PIN_RESET

/**
  * @brief  KEY_RELEASE_IN     һ���ͷ�
  */
#define KEY_RELEASE_IN_PIN              GPIO_PIN_7
#define KEY_RELEASE_IN_PORT             GPIOB
#define KEY_RELEASE_IN_PULL             GPIO_PULLUP
#define KEY_RELEASE_IN_INIT             GPIO_PIN_RESET





/* Exported variables --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/**
  * @brief ����ʱ��ʹ��
  */
#define BUTTONx_GPIO_CLK_ENABLE()           do { __HAL_RCC_GPIOB_CLK_ENABLE(); } while(0)

/**
  * @brief ����ʱ�ӽ���
  */
#define BUTTONx_GPIO_CLK_DISABLE()              {__HAL_RCC_GPIOB_CLK_DISABLE();}



/* functions --------------------------------------------------------*/
buttonDrv_err_t bsp_button_init(buttonDrv_ID_t g_buttonDrv_id);
buttonDrv_err_t bsp_button_get(buttonDrv_ID_t g_buttonDrv_id,GPIO_PinState *status);



#ifdef __cplusplus
}
#endif


#endif








