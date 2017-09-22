/**
  * @file       ledDev.h
  * @brief      LED驱动头文件
  * @author     redoc
  * @version    v1.0
  * @date       2016-08-20
  *
  * @note
  * [2016-08-20] <redoc> v1.0
  * 初始版本
  * @remark
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_DEV_H
#define __LED_DEV_H

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif


/* types ------------------------------------------------------------*/

typedef enum
{
    LED0_OUT = 0,
    LED1_OUT,

    LED_MAX_OUT,

}ledDev_id_t;

typedef enum
{
    EID_LED_REGIST = -2,
    EID_LED_PARAM = -1,
    EID_LED_NOERR = 0,

}ledDev_err_t;

typedef struct
{
    ledDev_err_t (*led_set)      (void *ledDev, uint8_t state);
    ledDev_err_t (*led_get)      (void *ledDev, uint8_t *status);
    ledDev_err_t (*led_on)       (void *ledDev);
    ledDev_err_t (*led_off)      (void *ledDev);
    ledDev_err_t (*led_toggle)   (void *ledDev);

} ledDev_fun_t;

typedef struct
{
    ledDev_fun_t g_ledDev_fun;
	ledDev_id_t g_ledDev_id;

}ledDev_t;


/* define -----------------------------------------------------------*/
/* constants --------------------------------------------------------*/
/* variables --------------------------------------------------------*/
/* macro ------------------------------------------------------------*/
/* functions --------------------------------------------------------*/

ledDev_err_t ledDev_regist(ledDev_t *p_ledDev,ledDev_id_t g_ledDev_id);
ledDev_err_t ledDev_getRegState(ledDev_t *p_ledDev);


#ifdef __cplusplus
}
#endif


#endif

