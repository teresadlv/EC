# include <msp430.h>
int main(void)
{

    /*volatile uint32_t;
    int i;*/
    // Stop watchdog timer. Ya que no lo necesitamos, lo desactivamos
    //WDT_A_hold(WDT_A_BASE);
    WDTCTL = WDTPW | WDTHOLD;

    // Set P1 .0 to output direction. Se configura el pin P1.0 como la salida
    /*GPIO_setAsOutputPin(
        GPIO_PORT_P1,
        GPIO_PIN0
        );*/
    P1SEL0 &= ~(BIT0); //ENTRADA SALIDA GENERAL

    P1DIR |= BIT0; //COMO SALIDA

    // Disable the GPIO power -on default high - impedance mode. Se desbloquea el dispositivo LPM5. Modo de bajo consumo
    // to activate previously configured port settings
   // PMM_unlockLPM5();
    PM5CTL0 &= ~LOCKLPM5;

    while (1)
    {
    // Toggle P1 .0 output. Se alterna su salida
   /* GPIO_toggleOutputOnPin(
        GPIO_PORT_P1,
        GPIO_PIN0
        );*/
      P1OUT ^= BIT0;

        // Delay
    //for (i =10000; i >0; i--);
    __delay_cycles(100000);
}
}
