unsigned int alfa = 28036;
int valor_vref = 0;
int dMax = 0;
int dMin = 0;
int valor_vs = 0;
unsigned int estado = 0;

void interrupt(){
     if(INTCON.TMR0IF == 1){
          TMR0H = (alfa >> 8);
          TMR0L = alfa;
          ADCON0.GO = 1;
          INTCON.TMR0IF = 0;
     }
     if(PIR1.ADIF == 1){
          valor_vs = (ADRESH << 8) + ADRESL;
          PIR1.ADIF = 0;
          
          ADCON0 = 0x49;
          Delay_us(25);  
          ADCON0.GO = 1;
          while(ADCON0.GO == 1){
                asm nop;
          }

          valor_vref = (ADRESH << 8) + ADRESL;
          ADCON0=0x41;
          
          dMax = valor_vref + 8;
          dMin = valor_vref - 8;
          if(valor_vref > 1015){
                dMax = 1023;
          }
          if(valor_vref < 8){
                dMin = 0;
          }
          
          switch(estado){
                case 0:
                     if(1){
                           estado = 1;
                           PORTA.B2 = 0;
                     }else{
                           estado = 0;
                           PORTA.B2 = 0;
                     }
                     break;
                case 1:
                     if(PORTA.B4 == 0){
                           estado = 0;
                           PORTA.B2 = 0;
                     }else if(valor_vs <= dMin){
                           estado = 2;
                           PORTA.B2 = 1;
                     }else{
                           estado = 1;
                           PORTA.B2 = 0;
                     }
                     break;
                case 2:
                     if(PORTA.B4 == 0){
                           estado = 0;
                           PORTA.B2 = 0;
                     }else if(valor_vs < dMax){
                           estado = 2;
                           PORTA.B2 = 1;
                     }else{
                           estado = 1;
                           PORTA.B2 = 0;
                     }
                     break;
          }
          PIR1.ADIF = 0;
     }
}

void main() {
     ADCON1 = 0xC4;
     TRISA.B0 = 1; //Vs
     TRISA.B1 = 1; //Vref
     TRISA.B2 = 0; //C
     TRISA.B4 = 1; //e
     ADCON0 = 0x41;

     PIR1.ADIF = 0;
     PIE1.ADIE = 1;
     INTCON.PEIE = 1;

     T0CON = 0x81;
     INTCON.TMR0IF = 0;
     INTCON.TMR0IE = 1;
     INTCON.GIE = 1;
     TMR0H = (alfa >> 8);
     TMR0L = alfa;

     while(1){}
}