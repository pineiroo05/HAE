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

char x;
unsigned short numero[8];
unsigned short contador = 0;
unsigned short y = 20;

void interrupt(){
     if(PORTB.B5 == 0){
                 contador++;
                 if(contador > 19){
                             contador = 0;
                 }
     }
     x = PORTB;
     INTCON.RBIF = 0;
}

void main() {
     ADCON1 = 0x07;
     TRISB.B5 = 1;
     TRISD = 0x00;
     
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);
     //Lcd_Out_CP("Turno: "); Para el apartado c descomentar esto
     
     x = PORTB;
     INTCON.RBIF = 0;
     INTCON.RBIE = 1;
     INTCON.GIE = 1;
     
     while(1){
              if(contador != y){
                          ShortToStr(contador, numero);
                          Lcd_Out(1,1,numero);
                          //Lcd_Out(1,9, numero); Para el apartado c pongo esto en vez de la linea de arriba
                          y = contador;
              }
     }
}