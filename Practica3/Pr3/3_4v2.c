//#include <msp430.h>
//
//volatile unsigned int i = 0;
////unsigned int n = 0;
//
//// **********************************
//// Configures ACLK to 32 KHz crystal
//void config_ACLK_to_32KHz_crystal() {
//    // By default , ACLK runs on LFMODCLK at 5 MHz /128 = 39 KHz
//    // Reroute pins to LFXIN / LFXOUT functionality
//    PJSEL1 &= ~BIT4;
//    PJSEL0 |= BIT4;
//
//    // Wait until the oscillator fault flags remain cleared
//    CSCTL0 = CSKEY; // Unlock CS registers
//
//    do {
//        CSCTL5 &= ~LFXTOFFG; // Local fault flag
//        SFRIFG1 &= ~OFIFG; // Global fault flag
//    } while ((CSCTL5 & LFXTOFFG) != 0);
//
//    CSCTL0_H = 0; // Lock CS registers
//    return;
//}
//
//const unsigned char LCD_Num [10] = {0xFC, 0x60, 0xDB, 0xF3, 0x67, 0xB7, 0xBF, 0xE0, 0xFF,
//0xE7};
//// *************** function that displays any 16 - bit unsigned integer ************
//inline void display_num_lcd(unsigned int n) {
//    int i = 0;
//    do {
//        unsigned int digit = n % 10;
//
//        switch (i) {
//        case 0: LCDM8 = LCD_Num [digit]; break; // first digit
//        case 1: LCDM15 = LCD_Num [digit]; break; // second digit
//        case 2: LCDM19 = LCD_Num [digit]; break; // third digit
//        case 3: LCDM4 = LCD_Num [digit]; break;  // fourth digit
//        case 4: LCDM6 = LCD_Num [digit]; break; // fifth digit
//        }
//
//        n /= 10;
//        i ++;
//    } while (i < 5);
//    return;
//}
//
//// **********************************************************
//// Initializes the LCD_C module
//// *** Source : Function obtained from MSP430FR6989 Sample Code ***
//void Initialize_LCD() {
//    PJSEL0 = BIT4 | BIT5; // For LFXT
//
//    // Initialize LCD segments 0 - 21; 26 - 43
//    LCDCPCTL0 = 0xFFFF;
//    LCDCPCTL1 = 0xFC3F;
//    LCDCPCTL2 = 0x0FFF;
//
//    // Configure LFXT 32 kHz crystal
//    CSCTL0_H = CSKEY >> 8; // Unlock CS registers
//    CSCTL4 &= ~LFXTOFF; // Enable LFXT
//
//    do {
//        CSCTL5 &= ~LFXTOFFG; // Clear LFXT fault flag
//        SFRIFG1 &= ~OFIFG;
//    } while (SFRIFG1 & OFIFG); // Test oscillator fault flag
//
//    CSCTL0_H = 0; // Lock CS registers
//
//    // Initialize LCD_C
//    // ACLK , Divider = 1 , Pre - divider = 16; 4 - pin MUX
//    LCDCCTL0 = LCDDIV__1 | LCDPRE__16 | LCD4MUX | LCDLP;
//
//    // VLCD generated internally ,
//    // V2 -V4 generated internally , v5 to ground
//    // Set VLCD voltage to 2.60 v
//    // Enable charge pump and select internal reference for it
//    LCDCVCTL = VLCD_1 | VLCDREF_0 | LCDCPEN;
//    LCDCCPCTL = LCDCPCLKSYNC; // Clock synchronization enabled
//    LCDCMEMCTL = LCDCLRM; // Clear LCD memory
//
//    // Turn LCD on
//    LCDCCTL0 |= LCDON;
//
//    return;
//}
//
//int main(void) {
//
//    // disable watchdog
//    WDTCTL = WDTPW | WDTHOLD ;
//
//    // disable high impeadance on I/O
//    PM5CTL0 &= ~LOCKLPM5;
//
//    P1SEL0 &= ~(BIT1 | BIT2); // Activo pines 1 y 2 del puerto 1 como E/S general ( SEL0 )
//    P1SEL1 &= ~(BIT1 | BIT2); // Activo pines 1, y2 del puerto 1 como E/S general ( SEL1 )
//
//    P1REN |= BIT1 | BIT2; // enable pull on P1.1 and P1.2, rest disabled
//    P1OUT |= BIT1 | BIT2; // set pull -up on P1.1 and P1.2
//
//    P1IE |= BIT1 | BIT2;
//    P1IES |= BIT1 | BIT2; // P1.1 Falling edge
//    P1IFG &= ~P1IFG; // P1.1 clear pending interrupts
//
//    // Configuracion TIMER_A :
//    // TimerA0 , ACLK /1 , modo up , reinicia TACLR
//    TA0CTL = TASSEL__ACLK | ID__1 | MC__UP | TACLR;
//    TA0CCR0 = 40000; // Valor maximo de la cuenta
//    TA0CCTL0 = CCIE; // Habilita interrupcion de comparacion del canal 0 del Timer0
//
//    //
//    config_ACLK_to_32KHz_crystal();
//    Initialize_LCD();
//
//    __low_power_mode_0();
//    __no_operation();
//}
//
//#pragma vector = TIMER0_A0_VECTOR
//__interrupt void TIMER0_A0_ISR(void){
//    display_num_lcd(i);
//    i++;
//}
//
//// Rutina de interrupcion de TIMER1_A0
//# pragma vector = PORT1_VECTOR
//__interrupt void Port1 ( void ) {
//    if (P1IFG & BIT1){
//        //para la cuenta
//        __delay_cycles(2000);
//        TA0CTL ^= BIT4;
//        P1IFG &= ~BIT1;
//    }
//    else if (P1IFG & BIT2){
//       //resetea la cuenta
//        __delay_cycles(2000);
//        i = 0;
//        P1IFG &= ~BIT2;
//        display_num_lcd(i);
//    }
//}
