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
#ifndef __LED_DEV_H
#define __LED_DEV_H

/* Includes ------------------------------------------------------------------*/
#include "ledDrv.h"


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
    ledDrv_err_t (*ledDrv_set)      (ledDrv_ID_t g_ledDrv_id, uint8_t state);
    ledDrv_err_t (*ledDrv_on)       (ledDrv_ID_t g_ledDrv_id);
    ledDrv_err_t (*ledDrv_off)      (ledDrv_ID_t g_ledDrv_id);
    ledDrv_err_t (*ledDrv_toggle)   (ledDrv_ID_t g_ledDrv_id);

} ledDev_fun_t;

typedef struct
{
    ledDev_fun_t p_ledDev_fun;
	ledDrv_ID_t g_ledDrvID;
}ledDev_t;


/* define -----------------------------------------------------------*/


/* constants --------------------------------------------------------*/

/* variables --------------------------------------------------------*/


/* macro ------------------------------------------------------------*/



/* functions --------------------------------------------------------*/
ledDev_err_t ledDev_regist(ledDev_t *p_ledDev,ledDrv_ID_t g_ledDrv_id);
ledDev_err_t ledDev_getRegState(ledDev_t *p_ledDev);


#ifdef __cplusplus
}
#endif


#endif








