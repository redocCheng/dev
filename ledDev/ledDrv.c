/**
  * @file       ledDrv.c
  * @brief      输出驱动
  * @author     redoc
  * @version    v1.0
  * @date       2016-09-20
  *
  * @note
  * [2016-09-20] <redoc> v1.0
  * 初始版本
  *
  * @remark
  */

/* Includes ------------------------------------------------------------------*/
#include "ledDrv.h"



/* Private typedef -----------------------------------------------------------*/


typedef struct
{
    GPIO_TypeDef* *p_Ports;
    const uint16_t *p_pins;
    const GPIO_PinState *p_inits;

} ledDrv_info_t;




/* Private define ------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/**
  * @brief 电平参数
  */
const GPIO_PinState GPIO_INIT[OUTPUTn] = {

    LED0_OUT_INIT,
    LED1_OUT_INIT,
    LED_ALARM_OUT_INIT,
    LED_READY_OUT_INIT,
    LED_EXPOSURE_OUT_INIT,
    LED_RELEASE_OUT_INIT,

    BEEP_OUT_INIT,
};

/**
  * @brief 端口参数
  */
GPIO_TypeDef* GPIO_PORT[OUTPUTn] = {

    LED0_OUT_PORT,
    LED1_OUT_PORT,
    LED_ALARM_OUT_PORT,
    LED_READY_OUT_PORT,
    LED_EXPOSURE_OUT_PORT,
    LED_RELEASE_OUT_PORT,

    BEEP_OUT_PORT,
};

/**
  * @brief 引脚参数
  */
const uint16_t GPIO_PIN[OUTPUTn] = {

    LED0_OUT_PIN,
    LED1_OUT_PIN,
    LED_ALARM_OUT_PIN,
    LED_READY_OUT_PIN,
    LED_EXPOSURE_OUT_PIN,
    LED_RELEASE_OUT_PIN,

    BEEP_OUT_PIN,
};

static const ledDrv_info_t g_ledDrv_info =
{
    GPIO_PORT,
    GPIO_PIN,
    GPIO_INIT,
};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

ledDrv_Err_Typedef bsp_led_Init(void *p_cookie)
{
    GPIO_InitTypeDef  gpioinitstruct = {0};

    ledDrv_ID_t g_ledDrv_id = (ledDrv_ID_t )*p_cookie;

    if(g_ledDrv_id > OUTPUTn)
    {
        return EID_LED_DRV_PARAM;
    }

    gpioinitstruct.Pin    = g_ledDrv_info.p_pins[g_ledDrv_id];
    gpioinitstruct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpioinitstruct.Pull   = GPIO_NOPULL;
    gpioinitstruct.Speed  = GPIO_SPEED_FREQ_HIGH;

    if(HAL_OK == HAL_GPIO_Init(g_ledDrv_info.p_Ports[g_ledDrv_id], &gpioinitstruct))
    {
        return EID_LED_DRV_NOERR;
    }


}


ledDrv_Err_Typedef bsp_led_Set(void *p_cookie,uint8_t state)
{
    ledDrv_ID_t g_ledDrv_id = (ledDrv_ID_t )*p_cookie;

    if(g_ledDrv_id > OUTPUTn)
    {
       return EID_LED_DRV_PARAM;
    }

    HAL_GPIO_WritePin(g_ledDrv_info.p_Ports[g_ledDrv_id], \
                      g_ledDrv_info.p_pins[g_ledDrv_id],  \
                      (state == g_ledDrv_info.p_inits[g_ledDrv_id] ? GPIO_PIN_SET:GPIO_PIN_RESET));

    return EID_LED_DRV_NOERR;
}


ledDrv_Err_Typedef bsp_led_On(void *p_cookie)
{
    return bsp_led_Set(true);
}

ledDrv_Err_Typedef bsp_led_Off(void *p_cookie)
{
    return bsp_led_Set(false);
}

ledDrv_Err_Typedef bsp_led_Toggle(void *p_cookie)
{
    ledDrv_ID_t g_ledDrv_id = (ledDrv_ID_t)*p_cookie;

    if(g_ledDrv_id > OUTPUTn)
    {
       return EID_LED_DRV_PARAM;
    }

    HAL_GPIO_TogglePin(g_ledDrv_info.p_Ports[g_ledDrv_id], \
                       g_ledDrv_info.p_pins[g_ledDrv_id]);

    return EID_LED_DRV_NOERR;
}











