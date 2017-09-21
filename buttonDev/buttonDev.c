/**
  * @file       buttonDev.c
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
#include "buttonDev.h"


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


buttonDev_err_t buttonDev_regist(buttonDev_t *p_buttonDev,buttonDrv_ID_t g_buttonDrv_id)
{

    if(EID_BUTTON_DRV_NOERR != bsp_button_init(g_buttonDrv_id))
        return EID_BUTTON_DEV_PARAM;

    p_buttonDev->g_buttonDrvID = g_buttonDrv_id;
    p_buttonDev->g_buttonDev_fun.button_get = bsp_button_get;


    return buttonDev_getRegState(p_buttonDev);
}


buttonDev_err_t buttonDev_getRegState(buttonDev_t *p_buttonDev)
{

    if( p_buttonDev->g_buttonDev_fun.led_get == NULL)
        return EID_BUTTON_DEV_REGIST;


    return EID_BUTTON_DEV_NOERR;
}






