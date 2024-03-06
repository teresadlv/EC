//#include <msp430.h>
//
///**
//
//main.c*/
////3.1
//
//
//int main(void) {
//    WDTCTL = WDTPW | WDTHOLD;    // deshabilitar stop watchdog timer
//
//    PM5CTL0 &= ~LOCKLPM5;       // desabilitar alta impedancia E/S
//
//    P1SEL0 &= ~(BIT0);          // Se activa PIN 0 del puerto 1 como E/S general (SEL0)
//    P1SEL1 &= ~(BIT0);          // Se activa PIN 0 del puerto 1 como E/S general (SEL1)
//
//    P1DIR |= BIT0;              // P1.0 como salida, resto como entradas
//
//    P1OUT |= BIT0;
//
//    P1REN |= BIT1;              // enable pull on P1.1
//    P1OUT |= BIT1;              // set pull up on P1.1
//
//    while(1) {
//        if(!(P1IN & BIT1)){             // si P1.1 no está pulsado (1 default)
//            __delay_cycles(400000);
//            P1OUT ^= BIT0;              // XOR -->  se escribe 1 en P1.0
//        }
//
//    }
//       return 0;
//}
