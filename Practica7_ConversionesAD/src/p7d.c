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
int nuevaMuestra = 0;
float tension = 0.0;
float lux = 0.0;
float Rldr = 0.0;
char salida[10];

void interrupt(){
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
     TRISC = 0x00;
     TRISE.B1 = 1;
     ADCON0 = 0x71;

     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);

     //Conversion AD
     PIR1.ADIF = 0;
     PIE1.ADIE = 1;
     INTCON.PEIE = 1;
     //Timer
     T0CON = 0x84;
     INTCON.TMR0IF = 0;
     INTCON.TMR0IE = 1;
     INTCON.GIE = 1;

     TMR0H = alfa >> 8;
     TMR0L = alfa;
     
     while(1){
              if(nuevaMuestra == 1){
                              tension = ((float)valor)*(5.0/1023.0);
                              Rldr = 15e3*((5/tension)-1);
                              lux = pow((Rldr/127410.0), (-1/0.8582));
                              FloatToStr(lux,salida);
                              Lcd_Out(1,1,salida);
                              Lcd_Out(1,8,"Lux");
                              nuevaMuestra = 0;
              }
     }
}