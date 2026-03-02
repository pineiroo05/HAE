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

#include "Tecla12INT.h" //El fichero no es mio!!!!
char x;
char key;
int nuevaTecla;

void interrupt(){
     key = tecla();
     if(key!=0){
          nuevaTecla = 1;
     }
     x = PORTB;
     INTCON.RBIF = 0;
}

void main() {
     ADCON1 = 0x07;
     TRISB = 0xF0;
     TRISD = 0x00;
    
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);
    
     INTCON2.RBPU = 0;
     x = PORTB;
     INTCON.RBIF = 0;
     INTCON.RBIE = 1;
     INTCON.GIE = 1;
     
     while(1){
              if(nuevaTecla == 1){
                            Lcd_Chr_CP(key);
                            nuevaTecla = 0;
              }
     }
}