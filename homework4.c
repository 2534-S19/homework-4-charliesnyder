#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "homework4.h"
#include "myGPIO.h"
#include <stdlib.h>
int main(void)
{
    char rChar;
    const char *response = "\n\n\r2534 is the best course in the curriculum!\r\n\n";



    bool finished; //from FSM function


    // TODO: Declare the variables that main uses to interact with your state machine.


    // Stops the Watchdog timer.
    initBoard();
    initGPIO();

    // TODO: Declare a UART config struct as defined in uart.h.
    //       To begin, configure the UART for 9600 baud, 8-bit payload (LSB first), no parity, 1 stop bit.
    const eUSCI_UART_ConfigV1 uartConfig =
    {
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,               //SMCLK at 3MHz
    19,                                           //UCBR  at 19
    8,                                            //UCBRF at 8
    0x55,                                         //UCBRS at 0x55
    EUSCI_A_UART_NO_PARITY,                       // No Parity
    EUSCI_A_UART_LSB_FIRST,                       // LSB First
    EUSCI_A_UART_ONE_STOP_BIT,                    // One stop bit
    EUSCI_A_UART_MODE,                            // UART mode
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,// Oversampling
    EUSCI_A_UART_8_BIT_LEN                        // 8 bit
    };


    // TODO: Make sure Tx AND Rx pins of EUSCI_A0 work for UART and not as regular GPIO pins.



    // TODO: Initialize EUSCI_A0
    UART_initModule(EUSCI_A0_BASE, &uartConfig); //Transmits a byte from the UART model

    // TODO: Enable EUSCI_A0
    UART_enableModule(EUSCI_A0_BASE); //Disables the UART block


    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);  //High Output On Selected Pin


    while(1)
    {
        finished = false;

        // TODO: Check the receive interrupt flag to see if a received character is available.
        //       Return 0xFF if no character is available.
        if (UART_getInterruptStatus (EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)== EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
        {

            rChar = UART_receiveData(EUSCI_A0_BASE);




            // TODO: If an actual character was received, echo the character to the terminal AND use it to update the FSM.
            //       Check the transmit interrupt flag prior to transmitting the character.
            if (UART_getInterruptStatus (EUSCI_A0_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG) == EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG)
                UART_transmitData(EUSCI_A0_BASE, rChar);



            // TODO: If the FSM indicates a successful string entry, transmit the response string.
            //       Check the transmit interrupt flag prior to transmitting each character and moving on to the next one.
            //       Make sure to reset the success variable after transmission.
            finished = charFSM(rChar);
            if(finished)
            {
                UART_transmitData(EUSCI_A0_BASE, '\n');
                UART_transmitData(EUSCI_A0_BASE, '\n');
                UART_transmitData(EUSCI_A0_BASE, '2');
                UART_transmitData(EUSCI_A0_BASE, '5');
                UART_transmitData(EUSCI_A0_BASE, '3');
                UART_transmitData(EUSCI_A0_BASE, '4');
                UART_transmitData(EUSCI_A0_BASE, ' ');
                UART_transmitData(EUSCI_A0_BASE, 'i');
                UART_transmitData(EUSCI_A0_BASE, 's');
                UART_transmitData(EUSCI_A0_BASE, ' ');
                UART_transmitData(EUSCI_A0_BASE, 't');
                UART_transmitData(EUSCI_A0_BASE, 'h');
                UART_transmitData(EUSCI_A0_BASE, 'e');
                UART_transmitData(EUSCI_A0_BASE, ' ');
                UART_transmitData(EUSCI_A0_BASE, 'b');
                UART_transmitData(EUSCI_A0_BASE, 'e');
                UART_transmitData(EUSCI_A0_BASE, 's');
                UART_transmitData(EUSCI_A0_BASE, 't');
                UART_transmitData(EUSCI_A0_BASE, ' ');
                UART_transmitData(EUSCI_A0_BASE, 'c');
                UART_transmitData(EUSCI_A0_BASE, 'o');
                UART_transmitData(EUSCI_A0_BASE, 'u');
                UART_transmitData(EUSCI_A0_BASE, 'r');
                UART_transmitData(EUSCI_A0_BASE, 's');
                UART_transmitData(EUSCI_A0_BASE, 'e');
                UART_transmitData(EUSCI_A0_BASE, ' ');
                UART_transmitData(EUSCI_A0_BASE, 'i');
                UART_transmitData(EUSCI_A0_BASE, 'n');
                UART_transmitData(EUSCI_A0_BASE, ' ');
                UART_transmitData(EUSCI_A0_BASE, 't');
                UART_transmitData(EUSCI_A0_BASE, 'h');
                UART_transmitData(EUSCI_A0_BASE, 'e');
                UART_transmitData(EUSCI_A0_BASE, ' ');
                UART_transmitData(EUSCI_A0_BASE, 'c');
                UART_transmitData(EUSCI_A0_BASE, 'u');
                UART_transmitData(EUSCI_A0_BASE, 'r');
                UART_transmitData(EUSCI_A0_BASE, 'r');
                UART_transmitData(EUSCI_A0_BASE, 'i');
                UART_transmitData(EUSCI_A0_BASE, 'c');
                UART_transmitData(EUSCI_A0_BASE, 'u');
                UART_transmitData(EUSCI_A0_BASE, 'l');
                UART_transmitData(EUSCI_A0_BASE, 'u');
                UART_transmitData(EUSCI_A0_BASE, 'm');
                UART_transmitData(EUSCI_A0_BASE, '!');
                //char response[] = "2534 is the best course in the curriculum!";

            }

        }

    }
}








void initBoard()
{
    WDT_A_hold(WDT_A_BASE);
}











// TODO: FSM for detecting character sequence.
bool charFSM(char rChar)
{
    static enum {SX,S2,S25,S253,S2534} charstate =SX;
   // charstate = SX;
    //2,2toR,2to5,5toR,5to3,3toR,3to4,4toR,4toF
    bool finished = false;



    //int temp = 0;


    switch(charstate){

    case SX:

        if(rChar == '2'){
            charstate = S2;

        }
        else
            charstate = SX;
        break;

    case S2:

        if(rChar == '5'){
            charstate = S25;
        }
        else if(rChar == '2'){
            charstate = S2;
        }
        else
            charstate = SX;
        break;




    case S25:
        if(rChar == '3'){
            charstate = S253;
                }
        else if(rChar == '2'){
                    charstate = S2;
                }
        else
            charstate = SX;
        break;



    case S253:
          if(rChar == '4'){
            charstate = SX;
            finished = true;
                  }
          else if(rChar == '2'){
                      charstate = S2;
                  }
          else
            charstate = SX;
          break;




    }

    return finished;
}
