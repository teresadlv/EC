//#include <msp430.h>
///**
// * main.c
// */
//
//volatile unsigned int i = 0;
//
//const unsigned char LCD_Num[10] = { 0xFC, 0x60, 0xDB, 0xF3, 0x67, 0xB7, 0xBF,
//                                    0xE0, 0xFF, 0xE7 };
////**********************************************************
//// Initializes the LCD_C module
//// *** Source: Function obtained from MSP430FR6989’s Sample Code ***
//void Initialize_LCD()
//{
//    PJSEL0 = BIT4 | BIT5; // For LFXT
//    // Initialize LCD segments 0 - 21; 26 - 43
//    LCDCPCTL0 = 0xFFFF;
//    LCDCPCTL1 = 0xFC3F;
//    LCDCPCTL2 = 0x0FFF;
//    // Configure LFXT 32kHz crystal
//    CSCTL0_H = CSKEY >> 8; // Unlock CS registers
//    CSCTL4 &= ~LFXTOFF; // Enable LFXT
//    do
//    {
//        CSCTL5 &= ~LFXTOFFG; // Clear LFXT fault flag
//        SFRIFG1 &= ~OFIFG;
//    }
//    while (SFRIFG1 & OFIFG); // Test oscillator fault flag
//    CSCTL0_H = 0; // Lock CS registers
//    // Initialize LCD_C
//    // ACLK, Divider = 1, Pre-divider = 16; 4-pin MUX
//    LCDCCTL0 = LCDDIV__1 | LCDPRE__16 | LCD4MUX | LCDLP;
//    // VLCD generated internally,
//    // V2-V4 generated internally, v5 to ground
//    // Set VLCD voltage to 2.60v
//    // Enable charge pump and select internal reference for it
//    LCDCVCTL = VLCD_1 | VLCDREF_0 | LCDCPEN;
//    LCDCCPCTL = LCDCPCLKSYNC; // Clock synchronization enabled
//    LCDCMEMCTL = LCDCLRM; // Clear LCD memory
//    //Turn LCD on
//    LCDCCTL0 |= LCDON;
//    return;
//}
////***************function that displays any 16-bit unsigned integer************
//inline void display_num_lcd(unsigned int n)
//{
//    int i = 0;
//    do
//    {
//        unsigned int digit = n % 10;
//        switch (i)
//        {
//        case 0:
//            LCDM8 = LCD_Num[digit];
//            break; // first digit
//        case 1:
//            LCDM15 = LCD_Num[digit];
//            break; // second digit
//        case 2:
//            LCDM19 = LCD_Num[digit];
//            break; // third digit
//        case 3:
//            LCDM4 = LCD_Num[digit];
//            break; // fourth digit
//        case 4:
//            LCDM6 = LCD_Num[digit];
//            break; // fifth digit
//        }
//        n /= 10;
//        i++;
//    }
//    while (i < 5);
//    return;
//}
////**********************************
//
//// Configures ACLK to 32 KHz crystal
//void config_ACLK_to_32KHz_crystal()
//{
//    // By default, ACLK runs on LFMODCLK at 5MHz/128 = 39 KHz
//    // Reroute pins to LFXIN/LFXOUT functionality
//    PJSEL1 &= ~BIT4;
//    PJSEL0 |= BIT4;
//    // Wait until the oscillator fault flags remain cleared
//    CSCTL0 = CSKEY; // Unlock CS registers
//    do
//    {
//        CSCTL5 &= ~LFXTOFFG; // Local fault flag
//        SFRIFG1 &= ~OFIFG; // Global fault flag
//    }
//    while ((CSCTL5 & LFXTOFFG) != 0);
//    CSCTL0_H = 0; // Lock CS registers
//    return;
//}
//
//    void main(void)
//    {
//
//        PM5CTL0 &= ~LOCKLPM5;       // disable high impeadance on I/O
//        WDTCTL = WDTPW | WDTHOLD;   // disable watchdog timer
//
//        P1SEL0 &= ~(BIT1 | BIT2); // Activo pines 1 y 2 del puerto 1 como E/S general ( SEL0 )
//        P1SEL1 &= ~(BIT1 | BIT2); // Activo pines 1,y 2 del puerto 1 como E/S general ( SEL1 )
//
//        P1DIR |= BIT0; // Puts red led in out mode -- pin 0 del puerto 1 como salida (optional)
//        P9DIR |= BIT7; // Puts green led int out mode -- pin 7 del puerto 9 como salida (optional)
//
//        // configuran los pines 1 y 2 del puerto 1 como entradas
//        P1DIR &= ~BIT1;
//        P1DIR &= ~BIT2;
//
//        // establecen los valores iniciales para los pines de salida (LEDs) como altos
//        P1OUT |= BIT0;
//        P9OUT |= BIT7;
//
//        // se habilitan las resistencias de pull-up/pull-down para los pines 1 y 2 del puerto 1.
//        P1REN |= BIT1;
//        P1REN |= BIT2;
//
//        // habilitan las interrupciones para los pines 1 y 2 del puerto 1.
//        P1IE |= BIT1;
//        P1IE |= BIT2;
//
//        // se configura la transición para las interrupciones (en este caso, de alto a bajo)
//        P1IES |= BIT1;
//        P1IES |= BIT2;
//
//        // limpian los flags de interrupción para los pines 1 y 2 del puerto 1.
//        P1IFG &= ~BIT1;
//        P1IFG &= ~BIT2;
//
//
//        // _BIS_SR(LPM4_bits + GIE);
//
//        // show the count.
//        TA0CTL = TASSEL_1 | TACLR | MC_1;
//        TA0CCR0 = 40000;
//        TA0CCTL0 = CCIE;
//
//        Initialize_LCD();
//        config_ACLK_to_32KHz_crystal();
//
//        __low_power_mode_0();
//        __no_operation();
//    }
//
//    #pragma vector = TIMER0_A0_VECTOR
//    interrupt void TIMER0_A0_ISR(void)
//    {
//        display_num_lcd(i);
//        i++;
//    }
//
//    #pragma vector=PORT1_VECTOR
//    interrupt void Port_1(void)
//    {
//    if (P1IFG & BIT1)
//    {
//        // stop the count
//        __delay_cycles(2000);
//        P1OUT ^= BIT0;
//        TA0CTL ^= BIT4;
//        P1IFG &= ~BIT1;
//    }
//    else if (P1IFG & BIT2)
//    {
//        // put the count to 0
//        __delay_cycles(2000);
//        i = 0;
//        P9OUT ^= BIT7;
//        P1IFG &= ~BIT2;
//        display_num_lcd(i);
//    }
//}
//
