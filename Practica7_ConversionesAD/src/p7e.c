sbit LCD_RS at PORTC.B2;
sbit LCD_EN at PORTC.B3;
sbit LCD_D7 at PORTC.B7;
sbit LCD_D6 at PORTC.B6;
sbit LCD_D5 at PORTC.B5;
sbit LCD_D4 at PORTC.B4;

sbit LCD_RS_Direction at TRISC.B2;
sbit LCD_EN_Direction at TRISC.B3;
sbit LCD_D7_Direction at TRISC.B7;
sbit LCD_D6_Direction at TRISC.B6;
sbit LCD_D5_Direction at TRISC.B5;
sbit LCD_D4_Direction at TRISC.B4;

unsigned int alfa = 3036;
unsigned int valor = 0;
unsigned int contador = 0;
unsigned int nuevaMuestra = 0;
float tension = 0.0;
float presion = 0.0;
float presionKpa = 0.0;
char salida[10];
char unidad[5];

void interrupt(){
     if(INTCON3.INT1IF == 1){
                       contador++;
                       if(contador > 7){
                                      contador = 0;
                       }
                       INTCON3.INT1IF = 0;
     }
     if(INTCON.TMR0IF == 1){
                      PORTB.B0 = ~PORTB.B0;
                      TMR0H = alfa >> 8;
                      TMR0L = alfa;
                      ADCON0.GO = 1;
                      INTCON.TMR0IF = 0;
     }
     if(PIR1.ADIF == 1){
                  valor = ADRESL + (ADRESH << 8);
                  nuevaMuestra = 1;
                  PIR1.ADIF = 0;
     }
}

void main() {
     ADCON1 = 0xC0;
     TRISB.B0 = 0;
     TRISB.B1 = 1;
     TRISC = 0x00;
     TRISE.B2 = 1;
     ADCON0 = 0x79;
     
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);
     
     //Boton
     INTCON2.INTEDG1 = 1;
     INTCON3.INT1IF = 0;
     INTCON3.INT1IE = 1;
     //Conversion AD
     PIR1.ADIF = 0;
     PIE1.ADIE = 1;
     INTCON.PEIE = 1;
     //Tmr0
     T0CON = 0x84;
     INTCON.TMR0IF = 0;
     INTCON.TMR0IE = 1;
     INTCON.GIE = 1;
     
     TMR0H = alfa >> 8;
     TMR0L = alfa;
     
     while(1){
              if(nuevaMuestra == 1){
                              tension = ((float)valor)*(5.0/1023.0);
                              presionKpa = (54.2*tension)-14.11;
                              if(contador == 0){
                                          presion = presionKpa;
                                          strcpy(unidad, "Kpa");
                              }else if(contador == 1){
                                    presion = presionKpa/6.8927;
                                    strcpy(unidad,"Psi");
                              }else if(contador == 2){
                                    presion = presionKpa/101.325;
                                    strcpy(unidad,"Atm");
                              }else if(contador == 3){
                                    presion = presionKpa/0.1;
                                    strcpy(unidad,"mBar");
                              }else if(contador == 4){
                                    presion = presionKpa/0.13328;
                                    strcpy(unidad,"mmHg");
                              }else if(contador == 5){
                                    presion = presionKpa/0.001;
                                    strcpy(unidad,"N/m2");
                              }else if(contador == 6){
                                    presion = presionKpa/98.1;
                                    strcpy(unidad,"Kg/cm3");
                              }else if(contador == 7){
                                    presion = presionKpa/98.1;
                                    strcpy(unidad,"kp/cm3");
                              }
                              Lcd_Cmd(_LCD_CLEAR);
                              FloatToStr(presion,salida);
                              Lcd_Out(1,1,salida);
                              Lcd_Out(1,8,unidad);
                              nuevaMuestra = 0;
              }
     }
}