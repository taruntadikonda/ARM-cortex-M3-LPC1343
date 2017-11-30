#ifndef __SYSTICK_H 
#define __SYSTICK_H

/* SysTick clock source */
#define SysTick_CLKSource_RCLK         (0xFFFFFFFB)
#define SysTick_CLKSource_CCLK         (0x00000004)

/* SysTick counter state */
#define SysTick_Counter_Disable        (0xFFFFFFFE)
#define SysTick_Counter_Enable         (0x00000001)
#define SysTick_Counter_Clear          (0x00000000)

/* CTRL TICKINT Mask */
#define CTRL_TICKINT_Set               (0x00000002)
#define CTRL_TICKINT_Reset             (0xFFFFFFFD)

/* SysTick Flag */
#define SysTick_FLAG_COUNT             (0x30)
#define SysTick_FLAG_SKEW              (0x5E)
#define SysTick_FLAG_NOREF             (0x5F)

/* Exported functions ------------------------------------------------------- */
void SysTick_Handler(void);
void delaySysTick(uint32_t tick);
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);
void SysTick_SetReload(uint32_t Reload);
void SysTick_CounterCmd(uint32_t SysTick_Counter);
void SysTick_ITConfig(FunctionalState NewState);
uint32_t SysTick_GetCounter(void);
FlagStatus SysTick_GetFlagStatus(uint8_t SysTick_FLAG);

#endif /* end __SYSTICK_H */

/******************************************************************************
**                            End Of File
******************************************************************************/
