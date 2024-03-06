//#include <msp430.h>
//#include <stdio.h>
//
//int b [6] = {0,0,0,0,0,0};
//unsigned char l = 65; //empiezan en el 65
//const int BUFFER_SIZE = 32;
//char send_buffer[BUFFER_SIZE];
//int buffer_current_pointer = 1;
//int buffer_end_pointer = 0;
//float nums[5]={4.44,3.22,2.00,5.77,8.97};
//int i = 0;
//
//void load_send_buffer(float val)
//{
//    if (buffer_current_pointer <= buffer_end_pointer)
//        return; // aún no hemos terminado de escribir lo antiguo!!
//
////escribimos la representación textual de "val" en el buffer, y
////guardamos la longitud escrita para saber luego cuantos chars enviar
//
////la función sprintf crea la representación de caracteres del número
////flotante con dos decimales, y nos devuelve la cantidad de chars resultante
//    buffer_current_pointer = 0;
//    buffer_end_pointer = sprintf(send_buffer, "%.2f\n\r", val) - 1;
//
////esperar a que el bit UCBUSY del registro UCA1STATW valga 0
//    while (UCA1STATW & UCBUSY);
////activar las interrupciones TX en UCA1IE
//    UCA1IE |= UCTXIE;
//
//}
//
//// Configures ACLK to 32 KHz crystal
//void config_ACLK_to_32KHz_crystal()
//{
//// By default , ACLK runs on LFMODCLK at 5 MHz /128 = 39 KHz
//// Reroute pins to LFXIN / LFXOUT functionality
//    PJSEL1 &= ~BIT4;
//    PJSEL0 |= BIT4;
//// Wait until the oscillator fault flags remain cleared
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
//
////diccionario para transformar letras a segmentos del LCD
//const char alphabetBig[26][2] = { { 0xEF, 0x00 }, /* "A" LCD segments a+b+c+e+f+g+m */
//                                  { 0xF1, 0x50 }, /* "B" */
//                                  { 0x9C, 0x00 }, /* "C" */
//                                  { 0xF0, 0x50 }, /* "D" */
//                                  { 0x9F, 0x00 }, /* "E" */
//                                  { 0x8F, 0x00 }, /* "F" */
//                                  { 0xBD, 0x00 }, /* "G" */
//                                  { 0x6F, 0x00 }, /* "H" */
//                                  { 0x90, 0x50 }, /* "I" */
//                                  { 0x78, 0x00 }, /* "J" */
//                                  { 0x0E, 0x22 }, /* "K" */
//                                  { 0x1C, 0x00 }, /* "L" */
//                                  { 0x6C, 0xA0 }, /* "M" */
//                                  { 0x6C, 0x82 }, /* "N" */
//                                  { 0xFC, 0x00 }, /* "O" */
//                                  { 0xCF, 0x00 }, /* "P" */
//                                  { 0xFC, 0x02 }, /* "Q" */
//                                  { 0xCF, 0x02 }, /* "R" */
//                                  { 0xB7, 0x00 }, /* "S" */
//                                  { 0x80, 0x50 }, /* "T" */
//                                  { 0x7C, 0x00 }, /* "U" */
//                                  { 0x0C, 0x28 }, /* "V" */
//                                  { 0x6C, 0x0A }, /* "W" */
//                                  { 0x00, 0xAA }, /* "X" */
//                                  { 0x00, 0xB0 }, /* "Y" */
//                                  { 0x90, 0x28 } /* "Z" */
//};
////Función para mostrar las letras mayúsculas del alfabeto contenidas
////en un vector de 6 elementos en el LCD de la placa.
//void ShowBuffer(int buffer[])
//{
//    LCDMEM[9] = alphabetBig[(buffer[5]) - 65][0];
//    LCDMEM[10] = alphabetBig[(buffer[5]) - 65][1];
//    LCDMEM[5] = alphabetBig[(buffer[4]) - 65][0];
//    LCDMEM[6] = alphabetBig[(buffer[4]) - 65][1];
//    LCDMEM[3] = alphabetBig[(buffer[3]) - 65][0];
//    LCDMEM[4] = alphabetBig[(buffer[3]) - 65][1];
//    LCDMEM[18] = alphabetBig[(buffer[2]) - 65][0];
//    LCDMEM[19] = alphabetBig[(buffer[2]) - 65][1];
//    LCDMEM[14] = alphabetBig[(buffer[1]) - 65][0];
//    LCDMEM[15] = alphabetBig[(buffer[1]) - 65][1];
//    LCDMEM[7] = alphabetBig[(buffer[0]) - 65][0];
//    LCDMEM[8] = alphabetBig[(buffer[0]) - 65][1];
//}
//
//void Initialize_LCD(){
//    PJSEL0 = BIT4 | BIT5; // For LFXT
//// Initialize LCD segments 0 - 21; 26 - 43
//    LCDCPCTL0 = 0xFFFF;
//    LCDCPCTL1 = 0xFC3F;
//    LCDCPCTL2 = 0x0FFF;
//// Configure LFXT 32 kHz crystal
//    CSCTL0_H = CSKEY >> 8; // Unlock CS registers
//    CSCTL4 &= ~LFXTOFF; // Enable LFXT
//    do
//    {
//        CSCTL5 &= ~LFXTOFFG; // Clear LFXT fault flag
//        SFRIFG1 &= ~OFIFG;
//    }
//    while (SFRIFG1 & OFIFG); // Test oscillator fault flag
//    CSCTL0_H = 0; // Lock CS registers
//// Initialize LCD_C
//// ACLK , Divider = 1 , Pre - divider = 16; 4 - pin MUX
//    LCDCCTL0 = LCDDIV__1 | LCDPRE__16 | LCD4MUX | LCDLP;
//// VLCD generated internally ,
//// V2 -V4 generated internally , v5 to ground
//// Set VLCD voltage to 2.60 v
//// Enable charge pump and select internal reference for it
//    LCDCVCTL = VLCD_1 | VLCDREF_0 | LCDCPEN;
//    LCDCCPCTL = LCDCPCLKSYNC; // Clock synchronization enabled
//    LCDCMEMCTL = LCDCLRM; // Clear LCD memory
//// Turn LCD on
//    LCDCCTL0 |= LCDON;
//    return;
//}
//void ShiftBuffer(int Buffer[], int a) {
// Buffer[5] = Buffer[4];
//  Buffer[4] = Buffer[3];
//  Buffer[3] = Buffer[2];
//  Buffer[2] = Buffer[1];
//  Buffer[1] = Buffer[0];
//  Buffer[0] = a;
//}
//
//void main(void){
//    PM5CTL0 &= ~LOCKLPM5;
//    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
//
//    Initialize_LCD();
//    config_ACLK_to_32KHz_crystal();
//
//    //Configuracion de reloj de 8MHz
//    CSCTL0_H = CSKEY >> 8; // Unlock clock registers
//    CSCTL1 = DCOFSEL_3 | DCORSEL; // Set DCO to 8MHz
//    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
//    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1; // Set all dividers
//    CSCTL0_H = 0; // Lock CS registers
//
//    __enable_interrupt();
//    //CONFIGURAMOS LOS PINES 4 Y 5 DEL PUERTO 3 PARA LA COMUNICACION DE LA UART
//     P3SEL0  |= BIT4;
//     P3SEL0  |= BIT5;
//     P3SEL1 &= ~BIT4;
//     P3SEL1 &= ~BIT5;
//
////     UCA1IE |= BIT0; //INTERRUPCION DE RECEPCION
////     UCA1IE |= BIT1; //INTERRUPCION DE TRANSMISION
//
//     UCA1IFG &= ~BIT1;
//     UCA1IFG &= ~BIT0;
//
//    // Configure USCI_A1 for UART mode
//    UCA1CTLW0 = UCSWRST; // Put eUSCI in reset
//    UCA1CTLW0 |= UCSSEL__SMCLK; // CLK = SMCLK
//
//    // Baud Rate calculation
//    // 8000000/(16*9600) = 52.083
//    // Fractional portion = 0.083
//    // User Guide Table 21-4: UCBRSx = 0x04
//    // UCBRFx = int ( (52.083-52)*16) = 1
//    UCA1BR0 = 52; // 8000000/16/9600
//    UCA1BR1 = 0x00;
//    UCA1MCTLW |= UCOS16 | UCBRF_1 | 0x4900;
//    UCA1CTLW0 &= ~UCSWRST; // Initialize eUSCI
//
//    UCA1IE |= UCTXIE;
//    UCA1IE |= UCRXIE;
//
//    // Inicializar Timer0
//    TA0CTL = TASSEL__ACLK | ID__8 | MC__UP; // ACLK/8, modo Up
//    TA0CCR0 = 3276; // 32,768 Hz / 8 = 4096 Hz -> 4096 Hz / 4096 = 1 Hz
//    TA0CCTL0 |= CCIE; // Habilitar interrupción de comparación del Timer0
//
//    __low_power_mode_0();
//    __no_operation();
//
//}
//
//#pragma vector=TIMER0_A0_VECTOR
//__interrupt void Timer0_A0_ISR(void) {
//    load_send_buffer(nums[i]); // Valor a enviar por la UART
//    i++;
//    if(i > 4){
//        i = 0;
//    }
//    UCA1IE |= UCTXIE;         // Activar interrupciones de transmisión UART
//}
//
//#pragma vector=USCI_A1_VECTOR
//__interrupt void USCI_A1_ISR(void){
//    // interrupción en recepción
//    //UCA1TXBUF almacena datos que serán transmitidos a través de la UART
//    if(UCA1IFG & UCRXIFG){
//      int letter = UCA1RXBUF;
//      if (letter != 13){
//      ShiftBuffer(b,letter);
//      ShowBuffer(b);
//
//      }
//    }
//    if (UCA1IFG & UCTXIFG) {
//            if (buffer_current_pointer > buffer_end_pointer) {
//                // Hemos vaciado el buffer, desactivar interrupciones TX
//                UCA1IE &= ~UCTXIE; // Desactivar interrupciones TX
//            } else {
//                // Enviar el caracter apuntado por buffer_current_pointer
//                UCA1TXBUF = send_buffer[buffer_current_pointer];
//
//                // Avanzar buffer_current_pointer a la siguiente posición
//                buffer_current_pointer++;
//
//                // Limpiar bit de interrupción pendiente
//                UCA1IFG &= ~UCTXIFG;
//            }
//        }
//
//}
//
//
//
