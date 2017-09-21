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
#include "stdbool.h"


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

};

/**
  * @brief 端口参数
  */
GPIO_TypeDef* GPIO_PORT[OUTPUTn] = {

    LED0_OUT_PORT,
    LED1_OUT_PORT,

};

/**
  * @brief 引脚参数
  */
const uint16_t GPIO_PIN[OUTPUTn] = {

    LED0_OUT_PIN,
    LED1_OUT_PIN,

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

ledDrv_err_t bsp_led_init(ledDrv_ID_t g_ledDrv_id)
{
    GPIO_InitTypeDef  gpioinitstruct = {0};

    LEDx_GPIO_CLK_ENABLE();

    if(g_ledDrv_id > OUTPUTn)
    {
        return EID_LED_DRV_PARAM;
    }

    gpioinitstruct.Pin    = g_ledDrv_info.p_pins[g_ledDrv_id];
    gpioinitstruct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpioinitstruct.Pull   = GPIO_NOPULL;
    gpioinitstruct.Speed  = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(g_ledDrv_info.p_Ports[g_ledDrv_id], &gpioinitstruct);


	return EID_LED_DRV_NOERR;
}


ledDrv_err_t bsp_led_set(ledDrv_ID_t g_ledDrv_id,uint8_t state)
{


    if(g_ledDrv_id > OUTPUTn)
    {
       return EID_LED_DRV_PARAM;
    }

    HAL_GPIO_WritePin(g_ledDrv_info.p_Ports[g_ledDrv_id], \
                      g_ledDrv_info.p_pins[g_ledDrv_id],  \
                      (state == g_ledDrv_info.p_inits[g_ledDrv_id] ? GPIO_PIN_SET:GPIO_PIN_RESET));

    return EID_LED_DRV_NOERR;
}


ledDrv_err_t bsp_led_on(ledDrv_ID_t g_ledDrv_id)
{
    return bsp_led_set(g_ledDrv_id,true);
}

ledDrv_err_t bsp_led_off(ledDrv_ID_t g_ledDrv_id)
{
    return bsp_led_set(g_ledDrv_id,false);
}

ledDrv_err_t bsp_led_toggle(ledDrv_ID_t g_ledDrv_id)
{


    if(g_ledDrv_id > OUTPUTn)
    {
       return EID_LED_DRV_PARAM;
    }

    HAL_GPIO_TogglePin(g_ledDrv_info.p_Ports[g_ledDrv_id], \
                       g_ledDrv_info.p_pins[g_ledDrv_id]);

    return EID_LED_DRV_NOERR;
}











