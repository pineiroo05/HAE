void interrupt(){
     PORTC.B0 = 0;
     PORTC.B6 = 0;
     T0CON.TMR0ON = 0;
     INTCON.TMR0IF = 0;
}

void main() {
     ADCON1 = 0x07;
     TRISB.B0 = 1;
     TRISB.B1 = 1;
     TRISC.B0 = 0;
     TRISC.B6 = 0;
     
     T0CON = 0x06;
     INTCON.TMR0IF = 0;
     INTCON.TMR0IE = 1;
     INTCON.GIE = 1;
     
     while(1){
              if(T0CON.TMR0ON == 0){
                              if(PORTB.B0 == 1){
                                    int alfa1 = 18661;
                                    TMR0H = (alfa1>>8);
                                    TMR0L = alfa1;
                                    PORTC.B0 = 1;
                                    T0CON.TMR0ON = 1;
                              }else if(PORTB.B1 == 1){
                                    int alfa2 = 3036;
                                    TMR0H = (alfa2>>8);
                                    TMR0L = alfa2;
                                    PORTC.B6 = 1;
                                    T0CON.TMR0ON = 1;
                              }
              }
     }
}