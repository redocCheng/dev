/**
  * @file       ledDev.h
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
#ifndef __LED_DRV_H
#define __LED_DRV_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"


#ifdef __cplusplus
extern "C" {
#endif


/* types ------------------------------------------------------------*/


typedef enum
{
    EID_LED_DEV_REGIST = -2,
    EID_LED_DEV_PARAM = -1,
    EID_LED_DEV_NOERR = 0,

}ledDev_err_t;

typedef struct
{
    ledDrv_Err_Typedef (*ledDrv_set)      (void *p_cookie, uint8_t state);
    ledDrv_Err_Typedef (*ledDrv_on)       (void *p_cookie);
    ledDrv_Err_Typedef (*ledDrv_off)      (void *p_cookie);
    ledDrv_Err_Typedef (*ledDrv_toggle)   (void *p_cookie);

} ledDev_fun_t;

typedef struct
{
    ledDev_fun_t g_ledDev_fun;
    void *p_cookie;

}ledDev_t;


/* define -----------------------------------------------------------*/


/* constants --------------------------------------------------------*/

/* variables --------------------------------------------------------*/


/* macro ------------------------------------------------------------*/



/* functions --------------------------------------------------------*/
ledDev_err_t ledDev_regist(ledDev_t *p_ledDev,void *p_cookie);
ledDev_err_t ledDev_getRegState(ledDev_t *p_ledDev);


#ifdef __cplusplus
}
#endif


#endif








