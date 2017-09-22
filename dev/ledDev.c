/**
  * @file       ledDev.c
  * @brief      led输出驱动
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
#include "ledDev.h"
#include "stm32f1xx_hal.h"


/* Private typedef -----------------------------------------------------------*/

typedef struct
{
    GPIO_TypeDef* *p_Ports;
    const uint16_t *p_pins;
    const GPIO_PinState *p_inits;

} ledDev_info_t;

/* Private define ------------------------------------------------------------*/

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


/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

const GPIO_PinState GPIO_INIT[OUTPUTn] =
{
    LED0_OUT_INIT,
    LED1_OUT_INIT,
};

GPIO_TypeDef* GPIO_PORT[OUTPUTn] =
{
    LED0_OUT_PORT,
    LED1_OUT_PORT,
};

const uint16_t GPIO_PIN[OUTPUTn] =
{
    LED0_OUT_PIN,
    LED1_OUT_PIN,
};

static const ledDev_info_t g_ledDev_info =
{
    GPIO_PORT,
    GPIO_PIN,
    GPIO_INIT,
};

/* Private function prototypes -----------------------------------------------*/
static ledDev_err_t bsp_led_init(void *ledDev);
static ledDev_err_t bsp_led_set(void *ledDev,uint8_t state);
static ledDev_err_t bsp_led_get(void *ledDev,uint8_t *status);
static ledDev_err_t bsp_led_on(void *ledDev);
static ledDev_err_t bsp_led_off(void *ledDev);
static ledDev_err_t bsp_led_toggle(void *ledDev);

/* Private functions ---------------------------------------------------------*/


static ledDev_err_t bsp_led_init(void *ledDev)
{
    GPIO_InitTypeDef  gpioinitstruct = {0};
	ledDev_t *p_ledDev = (ledDev_t *)ledDev;

    LEDx_GPIO_CLK_ENABLE();

    if(p_ledDev->g_ledDev_id > OUTPUTn)
    {
        return EID_LED_PARAM;
    }

    gpioinitstruct.Pin    = g_ledDev_info.p_pins[p_ledDev->g_ledDev_id];
    gpioinitstruct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpioinitstruct.Pull   = GPIO_NOPULL;
    gpioinitstruct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(g_ledDev_info.p_Ports[p_ledDev->g_ledDev_id], &gpioinitstruct);

	return EID_LED_NOERR;
}

static ledDev_err_t bsp_led_set(void *ledDev,uint8_t state)
{
	ledDev_t *p_ledDev = (ledDev_t *)ledDev;

    if(p_ledDev->g_ledDev_id > OUTPUTn)
    {
       return EID_LED_PARAM;
    }

    HAL_GPIO_WritePin(g_ledDev_info.p_Ports[p_ledDev->g_ledDev_id], \
                      g_ledDev_info.p_pins[p_ledDev->g_ledDev_id],  \
                      (state == g_ledDev_info.p_inits[p_ledDev->g_ledDev_id] ? GPIO_PIN_SET:GPIO_PIN_RESET));

    return EID_LED_NOERR;
}

static ledDev_err_t bsp_led_get(void *ledDev,uint8_t *status)
{
    GPIO_PinState bitstatus;
	ledDev_t *p_ledDev = (ledDev_t *)ledDev;

    if(p_ledDev->g_ledDev_id > OUTPUTn)
    {
       return EID_LED_PARAM;
    }

    if ((g_ledDev_info.p_Ports[p_ledDev->g_ledDev_id]->IDR & g_ledDev_info.p_pins[p_ledDev->g_ledDev_id]) != (uint32_t)GPIO_PIN_RESET)
    {
        bitstatus = GPIO_PIN_SET;
    }
    else
    {
        bitstatus = GPIO_PIN_RESET;
    }

    *status = (( bitstatus == g_ledDev_info.p_inits[p_ledDev->g_ledDev_id] ) ? true : false);


    return EID_LED_NOERR;
}

static ledDev_err_t bsp_led_on(void *ledDev)
{
    return bsp_led_set(ledDev,true);
}

static ledDev_err_t bsp_led_off(void *ledDev)
{
    return bsp_led_set(ledDev,false);
}

static ledDev_err_t bsp_led_toggle(void *ledDev)
{
	ledDev_t *p_ledDev = (ledDev_t *)ledDev;

    if(p_ledDev->g_ledDev_id > OUTPUTn)
    {
       return EID_LED_PARAM;
    }

    HAL_GPIO_TogglePin(g_ledDev_info.p_Ports[p_ledDev->g_ledDev_id], \
                       g_ledDev_info.p_pins[p_ledDev->g_ledDev_id]);

    return EID_LED_NOERR;
}

/* Exported functions --------------------------------------------------------*/

ledDev_err_t ledDev_getRegState(ledDev_t *p_ledDev)
{
//    if(p_ledDev->p_cookie == NULL)
//        return EID_LED_REGIST;

    if( p_ledDev->g_ledDev_fun.led_set == NULL)
        return EID_LED_REGIST;

    if( p_ledDev->g_ledDev_fun.led_get == NULL)
        return EID_LED_REGIST;

    if(p_ledDev->g_ledDev_fun.led_on == NULL)
        return EID_LED_REGIST;

    if(p_ledDev->g_ledDev_fun.led_off == NULL)
        return EID_LED_REGIST;

    if(p_ledDev->g_ledDev_fun.led_toggle == NULL)
        return EID_LED_REGIST;

    return EID_LED_NOERR;
}

ledDev_err_t ledDev_regist(ledDev_t *p_ledDev,ledDev_id_t g_ledDev_id)
{

    p_ledDev->g_ledDev_id = g_ledDev_id;

    p_ledDev->g_ledDev_fun.led_set = bsp_led_set;
    p_ledDev->g_ledDev_fun.led_get = bsp_led_get;
    p_ledDev->g_ledDev_fun.led_on = bsp_led_on;
    p_ledDev->g_ledDev_fun.led_off = bsp_led_off;
    p_ledDev->g_ledDev_fun.led_toggle = bsp_led_toggle;

	if(EID_LED_NOERR != bsp_led_init(p_ledDev))
        return EID_LED_PARAM;

    bsp_led_off(p_ledDev);


    return ledDev_getRegState(p_ledDev);
}




