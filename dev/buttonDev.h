/**
  * @file       buttonDev.h
  * @brief      输出初始化头文件
  * @author     redoc
  * @version    v1.0
  * @date       2016-08-20
  *
  * @note
  * [2016-08-20] <redoc> v1.0
  * 初始版本
  *
  * @remark
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTON_DEV_H
#define __BUTTON_DEV_H

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif


/* types ------------------------------------------------------------*/

/**
  * @brief 输入口定义
  */
typedef enum
{
    KEY_EXPOUSE_IN=0,       //曝光按键
    KEY_RELEASE_IN,         //一键释放按键

    BUTTON_ID_MAX,

} buttonDev_id_t;

typedef enum
{
    EID_BUTTON_REGIST = -2,
    EID_BUTTON_PARAM = -1,
    EID_BUTTON_NOERR = 0,

}buttonDev_err_t;

typedef struct
{
    buttonDev_err_t (*button_get)(void *buttonDev,uint8_t *status);

} buttonDev_fun_t;

typedef struct
{
    buttonDev_fun_t g_buttonDev_fun;
	buttonDev_id_t g_buttonDevID;
}buttonDev_t;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* functions --------------------------------------------------------*/

buttonDev_err_t buttonDev_regist(buttonDev_t *p_buttonDev,buttonDev_id_t g_buttonDev_id);
buttonDev_err_t buttonDev_getRegState(buttonDev_t *p_buttonDev);



#ifdef __cplusplus
}
#endif


#endif


