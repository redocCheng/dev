# dev

driver for hardware.

##使用方法

**1.定义句柄**
```
ledDev_t led0; 

```

**2.注册句柄**	

```
if(EID_LED_NOERR != ledDev_regist(&led0,LED0_OUT))
{
  return false;
}
```
> LED0_OUT是led驱动端口号

**3.调用函数**

```
led0.g_ledDev_fun.led_on(&led0);
delay_ms(1000);
led0.g_ledDev_fun.led_off(&led0);
```