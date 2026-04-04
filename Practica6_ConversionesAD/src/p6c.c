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
float tempC = 0.0;
char salida[15];
unsigned int contador = 0; //0->celsius 1->kelvin 2->farenheit
unsigned int contadorViejo = 3;
char unidad = 'C';

void interrupt(){
      //Boton
      if(INTCON.INT0IF == 1){
            contador++;
            if(contador>2){
                  contador = 0;
            }
            INTCON.INT0IF = 0;
      }
      //Timer
      if(INTCON.TMR0IF == 1){
            TMR0H = (alfa>>8);
            TMR0L = alfa;
            PORTE.B0 = ~PORTE.B0;
            ADCON0.GO = 1;
            INTCON.TMR0IF = 0;
     }
     //AD
     if(PIR1.ADIF == 1){
            valor = ADRESL + (ADRESH<<8);
            PIR1.ADIF = 0;
     }
}

void main() {
     ADCON1 = 0xC4;
     TRISA.B3 = 1;
     TRISB.B0 = 1;
     TRISD = 0x00;
     TRISE.B0 = 0;
     
     ADCON0 = 0x59;
     
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);
     
     //Timer
     T0CON = 0x85;
     INTCON.TMR0IF = 0;
     INTCON.TMR0IE = 1;
     TMR0H = (alfa>>8);
     TMR0L = alfa;
     //Boton
     INTCON2.INTEDG0 = 0;
     INTCON.INT0IF = 0;
     INTCON.INT0IE = 1;
     //AD
     PIR1.ADIF = 0;
     PIE1.ADIE = 1;
     INTCON.PEIE = 1;
     INTCON.GIE = 1;
     
     while(1){
            if(valor != valorViejo || contador != contadorViejo){
                  tempC = 100*(((float)valor)*(5.0/1023.0))-50;
                  if(contador == 0){
                        temp = tempC;
                        unidad = 'C';
                  }else if(contador == 1){
                        temp = tempC + 273.15;
                        unidad = 'K';
                  }else if(contador == 2){
                        temp = 1.8*tempC+32;
                        unidad = 'F';
                  }
                  Lcd_Cmd(_LCD_CLEAR);
                  FloatToStr(temp, salida);
                  Lcd_Out(1,1,salida);
                  Lcd_Chr_CP(223);
                  Lcd_Chr_CP(unidad);
                  contadorViejo = contador;
                  valorViejo = valor;
            }
     }
}