#include <stdint.h>

#define RCC_BASE (0x40023800)
#define RCC_AHB1ENR (*(volatile uint32_t*)(RCC_BASE + 0x30))
#define RCC_CR (*(volatile uint32_t*)(RCC_BASE))
#define GPIOC_BASE (0x40020800)
#define GPIOC_MODER (*(volatile uint32_t*)(GPIOC_BASE + 0x00))
#define GPIOC_ODR (*(volatile uint32_t*)(GPIOC_BASE + 0x14))
#define GPIOC_BSRR (*(volatile uint32_t*)(GPIOC_BASE + 0x18))
#define GPIOC_PUPDR (*(volatile uint32_t*)(GPIOC_BASE + 0x0C))
#define GPIOA_BASE (0x40020000)
#define GPIOA_MODER (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_ODR (*(volatile uint32_t*)(GPIOA_BASE + 0x14))

int main(void)
{
    RCC_AHB1ENR |= (1 << 2); //enable GPIOC clock
    asm("nop"); //delay for 2 cycles as per errata sheet
    asm("nop");
 
    GPIOC_MODER &= ~(3 << 13*2); //clear bits 26 and 27 for pin 13
    GPIOC_MODER |= (1 << 13*2); //set bts 26 and 27 as 01 for output
    
    while (1)
    {
        GPIOC_ODR |= (1 << 13); //toggle PC13 on
        for(uint32_t i = 0; i<1000000; i++)
        {
            asm("nop");
        }
        GPIOC_ODR &= ~(1 << 13); //toggle PC13 on
        for(uint32_t j = 0; j<1000000; j++)
        {
            asm("nop");
        }
    }
    
}