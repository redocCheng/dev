/**
  * @file       main.c
  * @brief      主程序
  * @author     redoc
  * @version    v1.0
  * @date       2017-09-20
  *
  * @note
  * [2016-09-20] <redoc> v1.0
  * 初始版本
  *
  * @remark
  */

/* Includes ------------------------------------------------------------------*/
#include "includes.h"
#include "buttonDev.h"
#include "ledDev.h"

/* typedef -----------------------------------------------------------*/

typedef struct
{
    uint8_t (*process) (void *testDev);
    
}testDev_fun_t;

typedef struct
{
    ledDev_t *p_led0;
    ledDev_t *p_led1;
    buttonDev_t *p_button0;
    testDev_fun_t g_testDev_fun;
    
}testDev_t;

/* define ------------------------------------------------------------*/
/* macro -------------------------------------------------------------*/
#define ENABLE_INT()	__ASM volatile("cpsie i")           /* 使能全局中断 */
#define DISABLE_INT()	__ASM volatile("cpsid i")           /* 禁止全局中断 */

/* variables ---------------------------------------------------------*/
const uint8_t projectTab[] = {"button"};                  /**<  项目名称   */
const uint8_t versionsTab[] = {"V1.1.03beta"};        /**<  版本信息   */
const uint8_t userNameTab[] = {"redoc"};               /**<  用户名     */



ledDev_t led0;
ledDev_t led1;
buttonDev_t button0;
testDev_t testDev1;



/* function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);


/* functions ---------------------------------------------------------*/

uint8_t led_init(void)
{
    if(EID_LED_NOERR != ledDev_regist(&led0,LED0_OUT))
    {
        return false;
    }

    if(EID_LED_NOERR != ledDev_regist(&led1,LED1_OUT))
    {
        return false;
    }

    return true;
}

uint8_t button_init(void)
{
    if(EID_BUTTON_NOERR != buttonDev_regist(&button0,KEY_EXPOUSE_IN))
    {
        return false;
    }

    return true;
}

uint8_t testDev_process(void *testDev)
{
    GPIO_PinState state;
    testDev_t *p_testDev = (testDev_t *)testDev;


    if(EID_BUTTON_NOERR == p_testDev->p_button0->g_buttonDev_fun.button_get(p_testDev->p_button0,&state))
    {
        if(state)
        {
            p_testDev->p_led0->g_ledDev_fun.led_on(p_testDev->p_led0);
            p_testDev->p_led1->g_ledDev_fun.led_off(p_testDev->p_led1);
        }
        else
        {
            p_testDev->p_led0->g_ledDev_fun.led_off(p_testDev->p_led0);
            p_testDev->p_led1->g_ledDev_fun.led_on(p_testDev->p_led1);
        }
    }

    return true;
}

uint8_t testDev_regist(testDev_t *p_testDev)
{
    if(EID_LED_REGIST == ledDev_getRegState(&led0))
        return false;

    if(EID_LED_REGIST == ledDev_getRegState(&led1))
        return false;

    if(EID_BUTTON_REGIST == buttonDev_getRegState(&button0))
        return false;

    p_testDev->p_led0 = &led0;
    p_testDev->p_led1 = &led1;
    p_testDev->p_button0 = &button0;
    p_testDev->g_testDev_fun.process = testDev_process;

    return true;
}



/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    HAL_Init();
    SystemClock_Config();

    DISABLE_INT();

    led_init();
    button_init();
    testDev_regist(&testDev1);

    ENABLE_INT();

    while (1)
    {

        testDev1.g_testDev_fun.process(&testDev1);

    }
}

/**
  * @brief      系统时钟配置
  * @param      void
  *
  * @return     void
  * @remark
  */
static void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef clkinitstruct = {0};
    RCC_OscInitTypeDef oscinitstruct = {0};

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
    oscinitstruct.HSEState        = RCC_HSE_ON;
    oscinitstruct.HSEPredivValue  = RCC_HSE_PREDIV_DIV1;
    oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
    oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
    oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&oscinitstruct)!= HAL_OK)
    {
        /* Initialization Error */
        while(1);
    }

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
       clocks dividers */
    clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
    clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;
    if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2)!= HAL_OK)
    {
        /* Initialization Error */
        while(1);
    }
}

/**
  * @brief      系统中断配置
  * @param      void
  *
  * @return     void
  * @remark
  */
void HAL_MspInit(void)
{
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    /* System interrupt init*/
    /* MemoryManagement_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
    /* BusFault_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
    /* UsageFault_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
    /* DebugMonitor_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, INT_PRO_SYSTICK, 0);
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif



