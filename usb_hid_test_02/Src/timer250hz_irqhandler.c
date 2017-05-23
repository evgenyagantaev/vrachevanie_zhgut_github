#include "timer250hz.h"


void TIM3_IRQHandler(void)
{
    if((TIM3->SR & TIM_SR_UIF) != 0) // update interrupt pending flag
    {
        // clear flag
        TIM3->SR &= ~TIM_SR_UIF;

        timer250hz_increment_tick();
    }
}
