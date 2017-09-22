# dev
>  新的驱动函数思路，参考linux驱动，[rt-thread](https://github.com/RT-Thread/rt-thread)驱动的一些想法，当然他们的驱动都采用init、write、read、ctrl的模式，和周立功的《面向AMetal框架与接口的编程（上）》，还参考了[cube的一个帖子](http://www.stm32cube.com/question/458)，认为这样的便于扩展，同样的业务代码量增加不少，但感觉这样会有利于维护和可移植性。写这个希望获得一些建议和意见。

## 一、ledDev
led驱动。

### 1. 介绍

**ledDev句柄**
```
typedef enum
{
    LED0_OUT = 0,
    LED1_OUT,

    LED_MAX_OUT,

}ledDev_id_t;

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
```
> 定义了ledDev驱动的调用函数和id,led接口很多，使用这个识别，初始化需要给id赋值。为了方便排错，做id的时候最好从1开始（我这里还没做）。驱动函数中 **void *ledDev** 就是 **ledDev_t** 实例的一个指针，利用它函数获得它的ID号。

**句柄注册**
```
ledDev_err_t ledDev_regist(ledDev_t *p_ledDev,ledDev_id_t g_ledDev_id)
{
    p_ledDev->g_ledDev_id = g_ledDev_id;
    p_ledDev->g_ledDev_fun.led_set = bsp_led_set;
    p_ledDev->g_ledDev_fun.led_get = bsp_led_get;
    p_ledDev->g_ledDev_fun.led_on = bsp_led_on;
    p_ledDev->g_ledDev_fun.led_off = bsp_led_off;
    p_ledDev->g_ledDev_fun.led_toggle = bsp_led_toggle;

    if(EID_LED_NOERR != bsp_led_init(p_ledDev))
    {
        return EID_LED_PARAM;
    }
    
    bsp_led_off(p_ledDev);

    return ledDev_getRegState(p_ledDev);
}
```
> 句柄注册首先对句柄的参数和调用函数进行初始化，然后初始化硬件。
> 函数包括设置，获取，置位，复位，翻转，没有把初始化放进来。


### 2. 使用方法
**定义句柄**
```
ledDev_t led0; 

```
**注册句柄**	
```
if(EID_LED_NOERR != ledDev_regist(&led0,LED0_OUT))
{
  return false;
}
```
> LED0_OUT是led驱动端口号

**调用**

```
led0.g_ledDev_fun.led_on(&led0);
delay_ms(1000);
led0.g_ledDev_fun.led_off(&led0);
```
> demo: [dev/demo/app_led/user/main.c](https://github.com/redocCheng/dev/blob/master/demo/app_led/user/main.c) 


## 二、buttonDev
button驱动。

### 1. 介绍

**buttonDev句柄**

```
typedef struct
{
    buttonDev_err_t (*button_get)(void *buttonDev,uint8_t *status);

} buttonDev_fun_t;

typedef struct
{
    buttonDev_fun_t g_buttonDev_fun;
    buttonDev_id_t g_buttonDev_id;
    
}buttonDev_t;
```
> 获取电平采用指针的形式，反馈为是否获取成功

**句柄注册**

```
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
```

### 2. 使用方法
**定义句柄**
```
buttonDev_t button0;

```
**注册句柄**	
```
if(EID_BUTTON_NOERR != buttonDev_regist(&button0,BUTTON0_IN))
{
	return false;
}

return true;
```
> LED0_OUT是led驱动端口号

**调用**

```
uint8_t state;
 
if(EID_BUTTON_NOERR == button0.g_buttonDev_fun.button_get(&button0,&state))
{
	if(state)
	{
		...
	}
	else
	{
		...
	}
}
```
> demo: demo里添加testDev驱动，包含了 ledDev 和 buttonDev 的指针。
> 详见 [dev/demo/app_button/user/main.c](https://github.com/redocCheng/dev/blob/master/demo/app_button/user/main.c)
