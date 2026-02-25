void main() {
     unsigned short estado_anterior = 0;
     unsigned short estado_led = 1;
     ADCON1 = 0x07;
     TRISB.B2 = 1;
     TRISB.B3 = 0;
     
     while(1){
              if(PORTB.B2 == 1 && estado_anterior == 0){
                          estado_led = !(estado_led);
                          PORTB.B3 = estado_led;
              }
              estado_anterior = PORTB.B2;
              delay_ms(100);
     }
}