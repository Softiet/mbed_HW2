#include "mbed.h"
#include <string>


BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);

char table[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
// LAST digit + 128
DigitalOut redLED(LED1);

DigitalOut greenLED(LED2);

DigitalIn  Switch(SW3);

Serial pc( USBTX, USBRX );

AnalogOut Aout(DAC0_OUT);

AnalogIn Ain(A0);

int evaluate(float* ,float);
float data_gathered[300];


int main(){
    float samp_interval=0.005;
    int result;
    display = table[0];
    while(1){
        if(1){ // evaluate
            redLED = 1;
            greenLED = 0;
            display = 0;
            // gather data
            for(int i =0;i<300;i++){
                data_gathered[i] = Ain;
                wait(samp_interval);
            }
            // evaluate frequency
            result = evaluate(data_gathered,samp_interval);
            // output to PC
            for (int i = 0; i < 300; i++){
                 pc.printf("%1.3f\r\n", data_gathered[i]);
                wait(0.005);
            }
            // output frequency
            string temp = to_string(result);
            int length = temp.size();
            int display_clock = 0;
            int i = 0;
            int j = 0;
            while(1){
                display_clock++;
                j++;
                if(display_clock == 1000){
                    display_clock = 0;
                    if(i == length -1){
                        display = table[int(temp[i])-48]+128;
                        i = 0;
                    }
                    else{
                        display = table[int(temp[i])-48];
                        i++;
                    }
                }
                Aout = 0.5 + 0.5*sin(3.14159*2*result*j/1000);                
                if(j==999){
                    j = 0;
                }
                wait(0.001);  
            }
        }

        else{
            redLED = 0;
            greenLED = 1;
            display = 0;
        }
    }
}

/* the SSD control
    for (int i = 0; i<10; i = i+1){

      display = table[i];

      wait(1);

    }
*/