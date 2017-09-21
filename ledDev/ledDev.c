/**
  * @file       ledDev.c
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
#include "ledDev.h"



/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


ledDev_err_t ledDev_regist(ledDev_t *p_ledDev,ledDrv_ID_t g_ledDrv_id)
{
    if(EID_LED_DRV_NOERR != bsp_led_init(g_ledDrv_id))
        return EID_LED_DEV_PARAM;

    bsp_led_off(g_ledDrv_id);


    p_ledDev->g_ledDrvID = g_ledDrv_id;

    p_ledDev->p_ledDev_fun.led_set = bsp_led_set;
    p_ledDev->p_ledDev_fun.led_get = bsp_led_get;
    p_ledDev->p_ledDev_fun.led_on = bsp_led_on;
    p_ledDev->p_ledDev_fun.led_off = bsp_led_off;
    p_ledDev->p_ledDev_fun.led_toggle = bsp_led_toggle;


    return ledDev_getRegState(p_ledDev);
}


ledDev_err_t ledDev_getRegState(ledDev_t *p_ledDev)
{
//    if(p_ledDev->p_cookie == NULL)
//        return EID_LED_DEV_REGIST;

    if( p_ledDev->p_ledDev_fun.led_set == NULL)
        return EID_LED_DEV_REGIST;

    if( p_ledDev->p_ledDev_fun.led_get == NULL)
        return EID_LED_DEV_REGIST;

    if(p_ledDev->p_ledDev_fun.le_on == NULL)
        return EID_LED_DEV_REGIST;

    if(p_ledDev->p_ledDev_fun.led_off == NULL)
        return EID_LED_DEV_REGIST;

    if(p_ledDev->p_ledDev_fun.led_toggle == NULL)
        return EID_LED_DEV_REGIST;

    return EID_LED_DEV_NOERR;
}






