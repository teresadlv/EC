#include <stdio.h>
#include <msp430.h>


int main(void)
{

    // Detener el temporizador de vigilancia (Watchdog Timer)
        WDTCTL = WDTPW | WDTHOLD;

        // Configurar el pin P1.0 como salida
        P1DIR |= BIT0; //LED ROJO
        P9DIR |= BIT7; //LED VERDE

        // Desbloquear el dispositivo de LPM5
        PM5CTL0 &= ~LOCKLPM5;

        while(1) {
            // Alternar el estado del pin P1.0
            P1OUT ^= BIT0; //SE ACTIVA LED ROJO
            P9OUT ^= BIT7; //SE ACTIVA LED VERDE

            // Esperar un tiempo antes de continuar
            __delay_cycles(300000);
        }
    return 0;
}
