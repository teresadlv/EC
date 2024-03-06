//#include <msp430.h>
///**
//* main.c
//*/
//    int main(void) {
//        WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
//        PM5CTL0 &= ~LOCKLPM5;
//
//        P1DIR |= BIT0; // Puts red led in out mode
//        P1DIR &= ~BIT1;
//
//        P1OUT |= BIT1;
//        P1REN |= BIT1;
//
//        P1IE |= BIT1;
//        P1IES |= BIT1;
//        P1IFG &= ~BIT1;
//
//        __bis_SR_register(LPM4_bits + GIE);
//
//
//    }
//    #pragma vector=PORT1_VECTOR
//        __interrupt void Port_1(void) {
//            P1OUT ^= BIT0;
//            P1IFG &= ~BIT1;
//        }




//
//#include <msp430.h>
///**
//* main.c
//*/
//int main(void)
//{
//    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
//    PM5CTL0 &= ~LOCKLPM5;
//
//    P9DIR |= BIT7; // Puts red led in out mode
//    P1DIR &= ~BIT2;
//
//    P1OUT |= BIT2;
//    P1REN |= BIT2;
//
//    P1IE |= BIT2;
//    P1IES |= BIT2;
//    P1IFG &= ~BIT2;
//
//    __bis_SR_register(LPM4_bits + GIE);
////    _BIS_SR(LPM4_bits + GIE);
//}
//#pragma vector=PORT1_VECTOR
//    __interrupt void Port_1(void) {
////    if (P1IFG & BIT1) {
//        P9OUT ^= BIT7;
//        P1IFG &= ~BIT2;
////    }
//    }
//
//
