sbit LCD_RS at PORTD.B2;
sbit LCD_EN at PORTD.B3;
sbit LCD_D7 at PORTD.B7;
sbit LCD_D6 at PORTD.B6;
sbit LCD_D5 at PORTD.B5;
sbit LCD_D4 at PORTD.B4;

sbit LCD_RS_Direction at TRISD.B2;
sbit LCD_EN_Direction at TRISD.B3;
sbit LCD_D7_Direction at TRISD.B7;
sbit LCD_D6_Direction at TRISD.B6;
sbit LCD_D5_Direction at TRISD.B5;
sbit LCD_D4_Direction at TRISD.B4;

unsigned short alfa = 28036;
unsigned int valor = 0;
unsigned int valorViejo = 9999;
float temp = 0.0;
char salida[15];

void interrupt(){
     if(INTCON.TMR0IF == 1){
          TMR0H = (alfa>>8);
          TMR0L = alfa;
          PORTE.B0 = ~PORTE.B0;
          ADCON0.GO = 1;
          INTCON.TMR0IF = 0;
     }
     if(PIR1.ADIF == 1){
          valor = ADRESL + (ADRESH<<8);
          PIR1.ADIF = 0;
     }
}

void main() {
     ADCON1 = 0xC4;
     TRISA.B3 = 1;
     TRISD = 0x00;
     TRISE.B0 = 0;
     
     ADCON0 = 0x59;
     
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);
     
     T0CON = 0x85;
     INTCON.TMR0IF = 0;
     INTCON.TMR0IE = 1;
     TMR0H = (alfa>>8);
     TMR0L = alfa;
     
     PIR1.ADIF = 0;
     PIE1.ADIE = 1;
     INTCON.PEIE = 0;
     INTCON.GIE = 1;
     
     while(1){
          if(valor != valorViejo){
               Lcd_Cmd(_LCD_CLEAR);
               temp = 100*(((float)valor)*(5.0/1023.0))-50;
               FloatToStr(temp, salida);
               Lcd_Out(1,1,salida);
               Lcd_Chr_CP(223);
               Lcd_Chr_CP('C');
               valorViejo = valor;
          }
     }
}