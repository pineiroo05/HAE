unsigned int Q;
bit m;
//a = PORTA.B0
unsigned int alfa = 30536;

void interrupt(){
     TMR0H = (alfa>>8);
     TMR0L = alfa;
     if((Q == 0 && PORTA.B0 == 0) || (Q == 2 && (PORTA.B0 == 0 || PORTA.B0 == 1))){
           Q = 0;
           m = m;
     }else if((Q == 0 && PORTA.B0 == 1) || (Q == 1 && PORTA.B0 == 1)){
           Q = 1;
           m = m;
     }else if(Q == 1 && PORTA.B0 == 0){
           Q = 2;
           m = !m;
     }
     INTCON.TMR0IF = 0;
}

void main() {
     ADCON1 = 0x07;
     TRISA.B0 = 1;
     TRISA.B3 = 0;
     
     Q = 0;
     m = 0;
     
     T0CON = 0x81;
     INTCON.TMR0IF = 0;
     INTCON.TMR0IE = 1;
     INTCON.GIE = 1;
     
     TMR0H = (alfa>>8);
     TMR0L = alfa;
     
     while(1){
     
     }
}