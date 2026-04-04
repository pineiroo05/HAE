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

unsigned int valor = 0;
float tension = 0;
char salida[13];
//int enteros = 0;
//int decimales = 0;

void interrupt(){
     valor = ADRESL + (ADRESH << 8);
     PIR1.ADIF = 0;
}

void main() {
     ADCON1 = 0xC4;
     TRISA.B3 = 1;
     TRISD = 0x00;
     
     ADCON0 = 0x59;
     
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);
     
     PIR1.ADIF = 0;
     PIE1.ADIE = 1;
     INTCON.PEIE = 1;
     INTCON.GIE = 1;
     
     while(1){
          ADCON0.GO = 1;
          Lcd_Cmd(_LCD_CLEAR);
          tension = ((float) valor)*(5.0/1023.0);
          FloatToStr(tension,salida);
          Lcd_Out(1,1,salida);
          Lcd_Chr_CP('V');
          delay_ms(1000);
     }
}