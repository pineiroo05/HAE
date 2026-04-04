unsigned int alfa = 3036;

void interrupt(){
     PORTB.B0 = ~PORTB.B0;
     TMR0H = alfa >> 8;
     TMR0L = alfa;
     INTCON.TMR0IF = 0;
}

void main() {
     ADCON1 = 0x07;
     TRISB.B0 = 0;
     
     T0CON = 0x84;
     INTCON.TMR0IF = 0;
     INTCON.TMR0IE = 1;
     INTCON.GIE = 1;
     
     TMR0H = alfa >> 8;
     TMR0L = alfa;
     
     while(1){

     }
}