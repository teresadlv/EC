#include <msp430.h>

//MENSAJES
char mensaje_de_bienvenida[] =
        "BIENVENIDO PULSE EL BOTON IZQUIERDO PARA EMPEZAR ";
char jugador1[] = "JUGADOR UNO";
char jugador2[] = "JUGADOR DOS";

//BUFFER
int b[6] = { 0, 0, 0, 0, 0, 0 };

//VARIABLES DEL JUEGO
int case_number = 0;
int j = 0;
int contador = 3;
int k = 0;

//NUMEROS PARA EL DISPLAY_NUM
const unsigned char LCD_Num[10] = { 0xFC, 0x60, 0xDB, 0xF3, 0x67, 0xB7, 0xBF,
                                    0xE0, 0xFF, 0xE7 };
//LETRAS PARA EL DISPLAY LETTER
const char alphabetBig[27][2] = { { 0xEF, 0x00 }, /* "A" LCD segments a+b+c+e+f+g+m */
                                  { 0xF1, 0x50 }, /* "B" */
                                  { 0x9C, 0x00 }, /* "C" */
                                  { 0xF0, 0x50 }, /* "D" */
                                  { 0x9F, 0x00 }, /* "E" */
                                  { 0x8F, 0x00 }, /* "F" */
                                  { 0xBD, 0x00 }, /* "G" */
                                  { 0x6F, 0x00 }, /* "H" */
                                  { 0x90, 0x50 }, /* "I" */
                                  { 0x78, 0x00 }, /* "J" */
                                  { 0x0E, 0x22 }, /* "K" */
                                  { 0x1C, 0x00 }, /* "L" */
                                  { 0x6C, 0xA0 }, /* "M" */
                                  { 0x6C, 0x82 }, /* "N" */
                                  { 0xFC, 0x00 }, /* "O" */
                                  { 0xCF, 0x00 }, /* "P" */
                                  { 0xFC, 0x02 }, /* "Q" */
                                  { 0xCF, 0x02 }, /* "R" */
                                  { 0xB7, 0x00 }, /* "S" */
                                  { 0x80, 0x50 }, /* "T" */
                                  { 0x7C, 0x00 }, /* "U" */
                                  { 0x0C, 0x28 }, /* "V" */
                                  { 0x6C, 0x0A }, /* "W" */
                                  { 0x00, 0xAA }, /* "X" */
                                  { 0x00, 0xB0 }, /* "Y" */
                                  { 0x90, 0x28 }, /* "Z" */
                                  { 0x00, 0x00 } /* Espacio */
};

//INICIALIZACIONES
void Initialize_LCD()
{
    PJSEL0 = BIT4 | BIT5; // For LFXT
// Initialize LCD segments 0 - 21; 26 - 43
    LCDCPCTL0 = 0xFFFF;
    LCDCPCTL1 = 0xFC3F;
    LCDCPCTL2 = 0x0FFF;
// Configure LFXT 32 kHz crystal
    CSCTL0_H = CSKEY >> 8; // Unlock CS registers
    CSCTL4 &= ~LFXTOFF; // Enable LFXT
    do
    {
        CSCTL5 &= ~LFXTOFFG; // Clear LFXT fault flag
        SFRIFG1 &= ~OFIFG;
    }
    while (SFRIFG1 & OFIFG); // Test oscillator fault flag
    CSCTL0_H = 0; // Lock CS registers
// Initialize LCD_C
// ACLK , Divider = 1 , Pre - divider = 16; 4 - pin MUX
    LCDCCTL0 = LCDDIV__1 | LCDPRE__16 | LCD4MUX | LCDLP;
// VLCD generated internally ,
// V2 -V4 generated internally , v5 to ground
// Set VLCD voltage to 2.60 v
// Enable charge pump and select internal reference for it
    LCDCVCTL = VLCD_1 | VLCDREF_0 | LCDCPEN;
    LCDCCPCTL = LCDCPCLKSYNC; // Clock synchronization enabled
    LCDCMEMCTL = LCDCLRM; // Clear LCD memory
// Turn LCD on
    LCDCCTL0 |= LCDON;
    return;
}
// Configures ACLK to 32 KHz crystal
void config_ACLK_to_32KHz_crystal()
{
// By default , ACLK runs on LFMODCLK at 5 MHz /128 = 39 KHz
// Reroute pins to LFXIN / LFXOUT functionality
    PJSEL1 &= ~BIT4;
    PJSEL0 |= BIT4;
// Wait until the oscillator fault flags remain cleared
    CSCTL0 = CSKEY; // Unlock CS registers
    do
    {
        CSCTL5 &= ~LFXTOFFG; // Local fault flag
        SFRIFG1 &= ~OFIFG; // Global fault flag
    }
    while ((CSCTL5 & LFXTOFFG) != 0);
    CSCTL0_H = 0; // Lock CS registers
    return;
}

//BUFFER
void ShowBuffer(int buffer[])
{
    //CONTEMPLAMOS EL CASO DEL ESPACIO
    //POS5
    if (buffer[5] == ' ')
    {
        LCDMEM[9] = LCDBMEM[9] = 0;
        LCDMEM[10] = LCDBMEM[10] = 0;
    }
    else
    {
        LCDMEM[9] = alphabetBig[(buffer[5]) - 65][0];
        LCDMEM[10] = alphabetBig[(buffer[5]) - 65][1];
    }

    //POS4
    if (buffer[4] == ' ')
    {
        LCDMEM[5] = LCDBMEM[5] = 0;
        LCDMEM[6] = LCDBMEM[6] = 0;
    }
    else
    {
        LCDMEM[5] = alphabetBig[(buffer[4]) - 65][0];
        LCDMEM[6] = alphabetBig[(buffer[4]) - 65][1];
    }

    //POS3
    if (buffer[3] == ' ')
    {
        LCDMEM[3] = LCDBMEM[3] = 0;
        LCDMEM[4] = LCDBMEM[4] = 0;
    }
    else
    {
        LCDMEM[3] = alphabetBig[(buffer[3]) - 65][0];
        LCDMEM[4] = alphabetBig[(buffer[3]) - 65][1];
    }

    //POS2
    if (buffer[2] == ' ')
    {
        LCDMEM[18] = LCDBMEM[18] = 0;
        LCDMEM[19] = LCDBMEM[19] = 0;
    }
    else
    {
        LCDMEM[18] = alphabetBig[(buffer[2]) - 65][0];
        LCDMEM[19] = alphabetBig[(buffer[2]) - 65][1];
    }

    //POS1
    if (buffer[1] == ' ')
    {
        LCDMEM[14] = LCDBMEM[14] = 0;
        LCDMEM[15] = LCDBMEM[15] = 0;
    }
    else
    {
        LCDMEM[14] = alphabetBig[(buffer[1]) - 65][0];
        LCDMEM[15] = alphabetBig[(buffer[1]) - 65][1];
    }

    //POS0
    if (buffer[0] == ' ')
    {
        LCDMEM[7] = LCDBMEM[7] = 0;
        LCDMEM[8] = LCDBMEM[8] = 0;
    }
    else
    {
        LCDMEM[7] = alphabetBig[(buffer[0]) - 65][0];
        LCDMEM[8] = alphabetBig[(buffer[0]) - 65][1];
    }
}

void ShiftBuffer(int Buffer[], int a)
{
    Buffer[5] = Buffer[4];
    Buffer[4] = Buffer[3];
    Buffer[3] = Buffer[2];
    Buffer[2] = Buffer[1];
    Buffer[1] = Buffer[0];
    Buffer[0] = a;
}

//MOSTRAR NUMERO POR EL LCD
inline void display_num_lcd(unsigned int n)
{
    int i = 0;
    do
    {
        unsigned int digit = n % 10;

        switch (i)
        {
        case 0:
            LCDM8 = LCD_Num[digit];
            break; // first digit
        case 1:
            LCDM15 = LCD_Num[digit];
            break; // second digit
        case 2:
            LCDM19 = LCD_Num[digit];
            break; // third digit
        case 3:
            LCDM4 = LCD_Num[digit];
            break;  // fourth digit
        case 4:
            LCDM6 = LCD_Num[digit];
            break; // fifth digit
        }

        n /= 10;
        i++;
    }
    while (i < 5);
    return;
}

// MOSTRAR CADA LETRA DE UN MENSAJE EN LCD
void display_letter_lcd(char letter)
{
    ShiftBuffer(b, letter);
    ShowBuffer(b);
}

//PARA LIMPIAR EL LCD Y QUE NO SE SOLAPEN MENSAJES
void clear_LCD()
{
    LCDMEM[9] = LCDBMEM[9] = 0;
    LCDMEM[9 + 1] = LCDBMEM[9 + 1] = 0;
    LCDMEM[5] = LCDBMEM[5] = 0;
    LCDMEM[5 + 1] = LCDBMEM[5 + 1] = 0;
    LCDMEM[3] = LCDBMEM[3] = 0;
    LCDMEM[3 + 1] = LCDBMEM[3 + 1] = 0;
    LCDMEM[18] = LCDBMEM[18] = 0;
    LCDMEM[18 + 1] = LCDBMEM[18 + 1] = 0;
    LCDMEM[14] = LCDBMEM[14] = 0;
    LCDMEM[14 + 1] = LCDBMEM[14 + 1] = 0;
    LCDMEM[7] = LCDBMEM[7] = 0;
    LCDMEM[7 + 1] = LCDBMEM[7 + 1] = 0;

    LCDM14 = LCDBM14 = 0x00;
    LCDM18 = LCDBM18 = 0x00;
    LCDM3 = LCDBM3 = 0x00;
}

//PARA LIMPIAR EL LCD Y QUE NO SE MUESTRE EL MENSAJE ANTERIOR
void clear_buffer()
{
    int i = 0;
    for (i = 0; i < 6; i++)
    {
        b[i] = 0; // Establece todos los elementos del buffer a 0
    }
}


int main(void)
{
    PM5CTL0 &= ~LOCKLPM5;
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

    //INICIALIZACIONES

    Initialize_LCD();
    config_ACLK_to_32KHz_crystal();

    //CONFIGURO LOS BOTONES

    P1SEL0 &= ~(BIT1 | BIT2); // Activo pines 1 y 2 del puerto 1 como E/S general ( SEL0 )
    P1SEL1 &= ~(BIT1 | BIT2); // Activo pines 1, y2 del puerto 1 como E/S general ( SEL1 )

    P1REN |= BIT1 | BIT2; // enable pull on P1.1 and P1.2, rest disabled
    P1OUT |= BIT1 | BIT2; // set pull -up on P1.1 and P1.2

    P1IE |= BIT1 | BIT2;
    P1IES |= BIT1 | BIT2; // P1.1 Falling edge
    P1IFG &= ~P1IFG; // P1.1 LIMPIAMOS INTERRUPCIONES PENDIENTES

    //CONFIGURO LEDS

    P1DIR |= BIT0; // Puts red led in out mode -- pin 0 del puerto 1 como salida
    P9DIR |= BIT7; // Puts green led int out mode -- pin 7 del puerto 9 como salida

    // establecen los valores iniciales para los pines de salida (LEDs) como altos
    P1OUT &= ~BIT0;
    P9OUT &= ~BIT7;

    // INICIALIZAMOS Timer0

    TA0CTL = TASSEL__ACLK | ID__8 | MC__UP; // ACLK/8, modo Up
    TA0CCR0 = 3076;
    TA0CCTL0 |= CCIE; // Habilitar interrupción de comparación del Timer0

    __low_power_mode_0();
    __no_operation();
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void)
{
//MOSTRAMOS EL MENSAJE DE BIENVENIDA EN BUCLES USANDO EL TIMER0
    k = 0;
    display_letter_lcd(mensaje_de_bienvenida[j]);
    j++;
    if (mensaje_de_bienvenida[j] == '\0') // SI LLEGAMOS AL FINAL DEL MENSAJE
    {
        j = 0;
    }

}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    /*YA QUE SE PULSA EL BOTON PARA EMPEZAR EL JUEGO Y LUEGO PARA EMPEZAR, USAMOS CASE_NUMBER PARA SABER EN QUE
     * ESTADO DEL JUEGO ESTAMOS, CASE_NUMBER = 0 ES EL ESTADO INICIAL, EL JUGADOR AUN NO HA DADO A EMPEZAR
     * CASE_NUMBER = 1, EL JUGADOR HA DECIDIDO EMPEZAR, HACEMOS LA CUENTA ATRÁS Y SE ENCIENDEN LAS LEDS PARA
     * INDICAR QUE EMPIEZA EL JUEGO, CASE_NUMBER = 2 ESTADO TRANSITORIO PARA EMPEZAR DE NUEVO EN EL MENSAJE
     * DE BIENVENIDO Y REINICAR TODAS LAS VARIABLES QUE LO NECESITAN
    */

    //SI SE PULSA EL BOTON PARA EMPEZAR
    if (case_number == 0)
    { //INICIO DEL JUEGO
        if (P1IFG & BIT1)
        {
            clear_LCD(); //LIMPIAMOS EL MENSAJE DE BIENVENIDA
            clear_buffer(); //LIMPIAMOS EL MENSAJE DE BIENVENIDA DEL BUFFER
            TA0CTL &= ~MC__UP; //DESACTIVA LA INTERRUPCION DEL TIMER0
            case_number = 1; //PASAMOS AL SIGUIENTE ESTADO DEL JUEGO
            P1IFG &= ~P1IFG; //PARA QUE NO DETECTE MAS DE UNA PULSACION A LA VEZ
        }
    }

    if (case_number == 1)
    { //JUEGO

        while (contador > 0) //MOSTRAMOS EL CONTADOR
        {
            display_num_lcd(contador);
            __delay_cycles(700000);
            contador--;
            /*SI EL JUGADOR PULSA EL BOTON EN ESTE ESTADO, BORRAMOS EL BIT DE INTERRUPCION
             * PARA QUE NO GANE UN JUGADOR EN LA ETAPA DE CONTADOR
             */
            if (P1IFG & BIT1)
            {
                P1IFG &= ~P1IFG; //BORRAMOS BIT DE INTERRUPCION
            }
            else if (P1IFG & BIT2)
            {
                P1IFG &= ~P1IFG; //BORRAMOS BIT DE INTERRUPCION
            }
        }

        if (contador == 0) // SI SE HA ACABADO EL CONTADOR
        {
            //ACTIVAMOS LEDS PARA INDICAR EL COMIENZO DEL JUEGO
            P1OUT ^= BIT0;
            P9OUT ^= BIT7;

            if (P1IFG & BIT1)//JUGADOR 1
            {
                case_number = 2; //PASAMOS AL SIGUIENTE ESTADO DEL JUEGO
                while (k < 11) //SE MUESTRA EL MENSAJE DE "JUGADOR UNO" PARA INDICAR QUE HA GANADO
                {
                    P1OUT ^= BIT0;
                    P9OUT ^= BIT7;
                    display_letter_lcd(jugador1[k]);
                    __delay_cycles(300000);
                    k++;
                }
            }
            else if (P1IFG & BIT2) //JUGADOR 2
            {
                case_number = 2; //PASAMOS AL SIGUIENTE ESTADO DEL JUEGO
                while (k < 11) //SE MUESTRA EL MENSAJE DE "JUGADOR DOS" PARA INDICAR QUE HA GANADO
                {
                    P1OUT ^= BIT0;
                    P9OUT ^= BIT7;
                    display_letter_lcd(jugador2[k]);
                    __delay_cycles(300000);
                    k++;
                }
            }

            P1IFG &= ~P1IFG; //BORRAMOS BIT DE INTERRUPCION PARA QUE EL JUEGO PUEDA VOLVER A EMPEZAR

        }
    }

    if (case_number == 2)
    { //SE ACABA EL JUEGO, ESTADO TRANSITORIO
        //AÑADIMOS DELAY PARA QUE NO SEA INMEDIATO
        __delay_cycles(1000000);

        //APAGAMOS LAS LEDS PARA QUE NO SE MANTENGAN ENCENDIDAS AL REINICIAR EL JUEGO
        P1OUT &= ~BIT0;
        P9OUT &= ~BIT7;

        //LIMPIAMOS LCD Y BUFFER
        clear_LCD();
        clear_buffer();

        //REINICIAMOS VARIABLES
        contador = 3;
        j = 0;
        case_number = 0; //SE VUELVE AL PRINCIPIO DEL JUEGO

        //ACTIVAMOS OTRA VEZ LA INTERRUPCION DEL TIMER0
        TA0CTL ^= MC__UP;
    }

}

