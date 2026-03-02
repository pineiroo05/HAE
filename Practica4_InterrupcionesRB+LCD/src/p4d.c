char x;
unsigned short estado_led = 0;

void interrupt(){
     if(PORTB.B5 == 1){
           estado_led = 1;
     }else{
           estado_led = 0;
           PORTA.B0 = 0;
     }
     x = PORTB;
     INTCON.RBIF = 0;
}

void main() {
     ADCON1 = 0x07;
     TRISB.B5 = 1;
     TRISA.B0 = 0;
     
     x = PORTB;
     INTCON.RBIF = 0;
     INTCON.RBIE = 1;
     INTCON.GIE = 1;
     
     while(1){
              unsigned short i;
              if(estado_led == 1){
                    PORTA.B0 = 1;
                    for(i=0; i<50 && estado_led == 1; i++){
                             delay_ms(10);
                    }
                    PORTA.B0 = 0;
                    for(i=0; i<50 && estado_led == 1; i++){
                             delay_ms(10);
                    }
              }else{
                    PORTA.B0 = 0;
              }
     }
}