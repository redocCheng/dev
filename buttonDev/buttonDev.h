/**
  * @file       buttonDev.h
  * @brief      输出初始化头文件
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



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTON_DEV_H
#define __BUTTON_DEV_H

/* Includes ------------------------------------------------------------------*/
#include "buttonDrv.h"


#ifdef __cplusplus
extern "C" {
#endif


/* types ------------------------------------------------------------*/


typedef enum
{
    EID_BUTTON_DEV_REGIST = -2,
    EID_BUTTON_DEV_PARAM = -1,
    EID_BUTTON_DEV_NOERR = 0,

}buttonDev_err_t;

typedef struct
{
    buttonDrv_err_t (*button_get)(buttonDrv_ID_t g_buttonDrv_id,GPIO_PinState *status);

} buttonDev_fun_t;

typedef struct
{
    buttonDev_fun_t g_buttonDev_fun;
	buttonDrv_ID_t g_buttonDrvID;
}buttonDev_t;


/* define -----------------------------------------------------------*/


/* constants --------------------------------------------------------*/

/* variables --------------------------------------------------------*/


/* macro ------------------------------------------------------------*/



/* functions --------------------------------------------------------*/
buttonDev_err_t buttonDev_regist(buttonDev_t *p_buttonDev,buttonDrv_ID_t g_buttonDrv_id);
buttonDev_err_t buttonDev_getRegState(buttonDev_t *p_buttonDev);


#ifdef __cplusplus
}
#endif


#endif








