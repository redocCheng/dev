/**
  * @file       ledDev.c
  * @brief      �������
  * @author     redoc
  * @version    v1.0
  * @date       2016-09-20
  *
  * @note
  * [2016-09-20] <redoc> v1.0
  * ��ʼ�汾
  *
  * @remark
  */

/* Includes ------------------------------------------------------------------*/
#include "ledDev.h"
#include "ledDrv.h"



/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


ledDev_err_t ledDev_regist(ledDev_t *p_ledDev,void *p_cookie)
{
    ledDrv_ID_t *p_ledDrv_id = (ledDrv_ID_t) *p_cookie;

    if(EID_LED_DRV_NOERR != bsp_led_Init(p_ledDrv_id))
        return EID_LED_DEV_PARAM;

    bsp_led_Off(p_ledDrv_id);

    p_ledDev->p_cookie = p_ledDrv_id;

    p_ledDev->p_ledDev_fun.ledDrv_set = bsp_led_Set;
    p_ledDev->p_ledDev_fun.ledDrv_on = bsp_led_On;
    p_ledDev->p_ledDev_fun.ledDrv_off = bsp_led_Off;
    p_ledDev->p_ledDev_fun.ledDrv_toggle = bsp_led_Toggle;


    return EID_LED_DEV_NOERR;
}


ledDev_err_t ledDev_getRegState(ledDev_t *p_ledDev)
{
    if(p_ledDev->p_cookie == NULL)
        return EID_LED_DEV_REGIST;

    if( p_ledDev->p_ledDev_fun.ledDrv_set == NULL)
        return EID_LED_DEV_REGIST;

    if(p_ledDev->p_ledDev_fun.ledDrv_on == NULL)
        return EID_LED_DEV_REGIST;

    if(p_ledDev->p_ledDev_fun.ledDrv_off == NULL)
        return EID_LED_DEV_REGIST;

    if(p_ledDev->p_ledDev_fun.ledDrv_toggle == NULL)
        return EID_LED_DEV_REGIST;

    return EID_LED_DEV_NOERR;
}






