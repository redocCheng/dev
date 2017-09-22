/**
  * @file       buttonDev.c
  * @brief      输出驱动
  * @author     redoc
  * @version    v1.0
  * @date       2017-09-20
  *
  * @note
  * [2017-09-20] <redoc> v1.0
  * 初始版本
  *
  * @remark
  */

/* Includes ------------------------------------------------------------------*/
#include "buttonDev.h"
#include "stm32f1xx_hal.h"


/* Private typedef -----------------------------------------------------------*/


typedef struct
{
    GPIO_TypeDef* *p_Ports;
    const uint16_t *p_pins;
    const GPIO_PinState *p_inits;
    const uint16_t *p_pulls;

} buttonDev_info_t;

/* Private define ------------------------------------------------------------*/

/**
  * @brief 输入口个数
  */
#define INPUTn                         BUTTON_ID_MAX


/**
  * @brief  KEY_EXPOUSE_IN     曝光按键
  */
#define KEY_EXPOUSE_IN_PIN              GPIO_PIN_6
#define KEY_EXPOUSE_IN_PORT             GPIOB
#define KEY_EXPOUSE_IN_PULL             GPIO_PULLUP
#define KEY_EXPOUSE_IN_INIT             GPIO_PIN_RESET

/**
  * @brief  KEY_RELEASE_IN     一键释放
  */
#define KEY_RELEASE_IN_PIN              GPIO_PIN_7
#define KEY_RELEASE_IN_PORT             GPIOB
#define KEY_RELEASE_IN_PULL             GPIO_PULLUP
#define KEY_RELEASE_IN_INIT             GPIO_PIN_RESET

/**
  * @brief 输入时钟使能
  */
#define BUTTONx_GPIO_CLK_ENABLE()           do { __HAL_RCC_GPIOB_CLK_ENABLE(); } while(0)

/**
  * @brief 输入时钟禁能
  */
#define BUTTONx_GPIO_CLK_DISABLE()              {__HAL_RCC_GPIOB_CLK_DISABLE();}

/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

GPIO_TypeDef* BUTTON_PORT[INPUTn]  =
{
    KEY_EXPOUSE_IN_PORT,
    KEY_RELEASE_IN_PORT,
};


GPIO_PinState BUTTON_INIT[INPUTn]  =
{
    KEY_EXPOUSE_IN_INIT,
    KEY_RELEASE_IN_INIT,
};


uint16_t BUTTON_PULL[INPUTn]  =
{
    KEY_EXPOUSE_IN_PULL,
    KEY_RELEASE_IN_PULL,
};

uint16_t BUTTON_PIN[INPUTn]  =
{
    KEY_EXPOUSE_IN_PIN,
    KEY_RELEASE_IN_PIN,
};


static const buttonDev_info_t g_buttonDev_info =
{
    BUTTON_PORT,
    BUTTON_PIN,
    BUTTON_INIT,
    BUTTON_PULL,
};

/* Private function prototypes -----------------------------------------------*/
static buttonDev_err_t bsp_button_init(void *buttonDev);
static buttonDev_err_t bsp_button_get(void *buttonDev,uint8_t *status);


/* Private functions ---------------------------------------------------------*/

static buttonDev_err_t bsp_button_init(void *buttonDev)
{
    GPIO_InitTypeDef  gpioinitstruct = {0};
	buttonDev_t *p_buttonDev = (buttonDev_t *)buttonDev;

    BUTTONx_GPIO_CLK_ENABLE();

    if(p_buttonDev->g_buttonDev_id > INPUTn)
    {
        return EID_BUTTON_PARAM;
    }

    gpioinitstruct.Pin    = g_buttonDev_info.p_pins[p_buttonDev->g_buttonDev_id];
    gpioinitstruct.Pull   = g_buttonDev_info.p_pulls[p_buttonDev->g_buttonDev_id];
    gpioinitstruct.Mode   = GPIO_MODE_INPUT;
    gpioinitstruct.Speed  = GPIO_SPEED_FREQ_MEDIUM;

    HAL_GPIO_Init(g_buttonDev_info.p_Ports[p_buttonDev->g_buttonDev_id], &gpioinitstruct);

	return EID_BUTTON_NOERR;
}


static buttonDev_err_t bsp_button_get(void *buttonDev,uint8_t *status)
{
    GPIO_PinState bitstatus;
	buttonDev_t *p_buttonDev = (buttonDev_t *)buttonDev;

    if(p_buttonDev->g_buttonDev_id > INPUTn)
    {
       return EID_BUTTON_PARAM;
    }

    bitstatus = HAL_GPIO_ReadPin(g_buttonDev_info.p_Ports[p_buttonDev->g_buttonDev_id],g_buttonDev_info.p_pins[p_buttonDev->g_buttonDev_id]);

    *status = ( (bitstatus == g_buttonDev_info.p_inits[p_buttonDev->g_buttonDev_id] ) ? true : false );

    return EID_BUTTON_NOERR;
}


/* Exported functions --------------------------------------------------------*/

buttonDev_err_t buttonDev_regist(buttonDev_t *p_buttonDev,buttonDev_id_t g_buttonDev_id)
{
    p_buttonDev->g_buttonDev_id = g_buttonDev_id;
    p_buttonDev->g_buttonDev_fun.button_get = bsp_button_get;

    if(EID_BUTTON_NOERR != bsp_button_init(p_buttonDev))
    {
        return EID_BUTTON_PARAM;
    }
    
    return buttonDev_getRegState(p_buttonDev);
}


buttonDev_err_t buttonDev_getRegState(buttonDev_t *p_buttonDev)
{
    if( p_buttonDev->g_buttonDev_fun.button_get == NULL)
    {
        return EID_BUTTON_REGIST;
    }
        
    return EID_BUTTON_NOERR;
}



