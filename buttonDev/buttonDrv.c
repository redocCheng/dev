/**
  * @file       buttonDrv.c
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
#include "buttonDrv.h"
#include "stdbool.h"


/* Private typedef -----------------------------------------------------------*/


typedef struct
{
    GPIO_TypeDef* *p_Ports;
    const uint16_t *p_pins;
    const GPIO_PinState *p_inits;
    const uint16_t *p_pulls;

} buttonDrv_info_t;

/* Private define ------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/



/**
  * @brief 端口参数
  */
GPIO_TypeDef* BUTTON_PORT[INPUTn]  =
{
    KEY_EXPOUSE_IN_PORT,
    KEY_RELEASE_IN_PORT,
};


/**
  * @brief 电平参数
  */
uint16_t BUTTON_INIT[INPUTn]  =
{
    KEY_EXPOUSE_IN_INIT,
    KEY_RELEASE_IN_INIT,
};


/**
  * @brief 上下拉参数
  */
uint16_t BUTTON_PULL[INPUTn]  =
{
    KEY_EXPOUSE_IN_PULL,
    KEY_RELEASE_IN_PULL,
};


/**
  * @brief 引脚参数
  */
uint16_t BUTTON_PIN[INPUTn]  =
{
    KEY_EXPOUSE_IN_PIN,
    KEY_RELEASE_IN_PIN,
};


static const buttonDrv_info_t g_buttonDrv_info =
{
    BUTTON_PORT,
    BUTTON_PIN,
    BUTTON_INIT,
    BUTTON_PULL,
};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

buttonDrv_err_t bsp_button_init(buttonDrv_ID_t g_buttonDrv_id)
{
    GPIO_InitTypeDef  gpioinitstruct = {0};

    BUTTONx_GPIO_CLK_ENABLE();

    if(g_buttonDrv_id > OUTPUTn)
    {
        return EID_BUTTON_DRV_PARAM;
    }

    gpioinitstruct.Pin    = g_buttonDrv_info.p_pins[g_buttonDrv_id];
    gpioinitstruct.Pull   = g_buttonDrv_info.p_pulls[g_buttonDrv_id];
    gpioinitstruct.Mode   = GPIO_MODE_INPUT;
    gpioinitstruct.Speed  = GPIO_SPEED_FREQ_MEDIUM;

    HAL_GPIO_Init(g_buttonDrv_info.p_Ports[g_buttonDrv_id], &gpioinitstruct);

	return EID_BUTTON_DRV_NOERR;
}


buttonDrv_err_t bsp_button_get(buttonDrv_ID_t g_buttonDrv_id,GPIO_PinState *status)
{
    GPIO_PinState bitstatus;

    if(g_buttonDrv_id > OUTPUTn)
    {
       return EID_BUTTON_DRV_PARAM;
    }

    bitstatus = HAL_GPIO_ReadPin(g_buttonDrv_info.p_Ports[g_buttonDrv_id],g_buttonDrv_info.p_pins[g_buttonDrv_id]);

    *state = ( bitstatus == g_buttonDrv_info.p_inits[g_buttonDrv_id] ) ? GPIO_PIN_SET : g_buttonDrv_id);

    return EID_BUTTON_DRV_NOERR;
}





