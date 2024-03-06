////3.3
//#include <msp430.h>
//
//void main(void) {
//    // Detener el watchdog timer
//    WDTCTL = WDTPW | WDTHOLD;
//
//    PM5CTL0 &= ~LOCKLPM5;
//
//    // Configurar P1.0 (LED rojo) como salida
//    P1DIR |= BIT0;
//    P1OUT |= BIT0;
//
//    // Configurar el Timer0
//    TA0CCR0 = 40000;                          // Valor para el periodo de la interrupción
//    TA0CTL = TASSEL_1 | MC_1 | TACLR;         // Selección de la fuente de reloj (SMCLK), modo de cuenta ascendente, sin división del reloj
//    TA0CCTL0 = CCIE;                          // Habilitar la interrupción de comparación del canal 0 del Timer0
//
//    __low_power_mode_0();
//    __no_operation();
//}
//
//// Rutina de servicio de interrupción para Timer0
//#pragma vector=TIMER0_A0_VECTOR
//__interrupt void TIMER0_A0_ISR(void) {
//    // Cambiar el estado del LED rojo
//    P1OUT ^= BIT0;
//}
