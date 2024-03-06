//#include <msp430.h>
//
//unsigned char l = 65; //empiezan en el 65
//unsigned char letter; //para letra que nos envían desde el pc
//int numLetters = 0; //para saber el número de letras que llevamos
////para enseñar las 6 últimas
//
//// Función para configurar ACLK al cristal 32kHz
//void config_ACLK_to_32KHz_crystal() {
//    PJSEL1 &= ~BIT4;
//    PJSEL0 |= BIT4;
//    CSCTL0 = CSKEY;
//    do {
//        CSCTL5 &= ~LFXTOFFG;
//        SFRIFG1 &= ~OFIFG;
//    } while((CSCTL5 & LFXTOFFG) != 0);
//    CSCTL0_H = 0;
//    return;
//}
//
///**
// * main.c
// */
//int main(void)
//{
//    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
//    PM5CTL0 &= ~LOCKLPM5;
//
//    //Configuración del reloj de 8Mhz
//    CSCTL0_H = CSKEY >> 8; // Unlock clock registers
//    CSCTL1 = DCOFSEL_3 | DCORSEL; // Set DCO to 8 MHz
//    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
//    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1; // Set all dividers
//    CSCTL0_H = 0; // Lock CS registers
//
//     config_ACLK_to_32KHz_crystal();
//    __enable_interrupt();   // Configurar interrupciones globales
//
//    P1DIR |= BIT0; //lo asignamos como entrada
//    P1OUT &= ~BIT0; //y tambien como salida
//
//    P3SEL0 |= BIT4; //es por donde se comunica la UART de la placa, entrada
//    P3SEL0 |= BIT5; //es por donde se comunica la UART de la placa, entrada
//    P3SEL1 &= ~BIT5; //es por donde se comunica la UART de la placa, salida
//    P3SEL1 &= ~BIT4; //es por donde se comunica la UART de la placa, salida
//
//    UCA1IE |= BIT1; //activa interrupción en transmisión
//    UCA1IE |= BIT0; //activa interrupción en recepción
//
//    //Configuración del periférico USCI de la placa como UART
//    // Configure USCI_A1 for UART mode
//    UCA1CTLW0 = UCSWRST ; // Put eUSCI in reset
//    UCA1CTLW0 |= UCSSEL__SMCLK ; // CLK = SMCLK
//    // Baud Rate calculation
//    // 8000000/(16*9600) = 52.083
//    // Fractional portion = 0.083
//    // User Guide Table 21 -4: UCBRSx = 0 x04
//    // UCBRFx = int ( (52.083 -52) *16) = 1
//    UCA1BR0 = 52; // 8000000/16/9600
//    UCA1BR1 = 0x00 ;
//    UCA1MCTLW |= UCOS16 | UCBRF_1 | 0x4900 ;
//    UCA1CTLW0 &= ~ UCSWRST ; // Initialize eUSCI
//
//    // Configure interruptions to receive and transmit data in register UCA1IE
//    UCA1IE |= BIT1; //volvemos a activar interrupción en transmisión
//    UCA1IE |= BIT0; //volvemos a activar interrupción en recepción
//    //se hace dos veces porque el dispositivo de comunicación UART tiene
//    //dos posibles fuentes de interrupción
//
////     _BIS_SR(LPM4_bits + GIE); //modo bajo consumo
//
//    __low_power_mode_0();
//    __no_operation();
//}
//
//#pragma vector = USCI_A1_VECTOR //para las interrupciones de la UART
//__interrupt void USCI_A1_ISR(void)
//{
//    if (UCA1IFG & BIT1)
//    { //si el bit de transmisión está activado
//        UCA1TXBUF = l; //asignamos al registro de transmisión el valor de l
//        l++; //pasamos a otra letra
//        if (l > 65 + 25)
//        { //si nos hemos pasado de letras reiniciamos
//            l = 65;
//        }
//        __delay_cycles(100000);
//    }
//
//    __delay_cycles(1000);
//}
