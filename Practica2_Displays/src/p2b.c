void main() {
     unsigned short numeros[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
     unsigned short unidades = 0;
     unsigned short decenas = 0;
     unsigned short centenas = 0;
     unsigned short millares = 0;
     unsigned short valor;

     ADCON1 = 0x07;
     TRISB = 0xFF;
     TRISC = 0x00;
     TRISD = 0x00;

     while(1){
              valor = PORTB;
              //Unidades
              PORTC = numeros[valor%10];
              PORTD.B3 = 0;
              delay_ms(5);
              PORTD.B3 = 1;
              //Decenas
              PORTC = numeros[(valor/10)%10];
              PORTD.B2 = 0;
              delay_ms(5);
              PORTD.B2 = 1;
              //Centenas
              PORTC = numeros[(valor/100)%10];
              PORTD.B1 = 0;
              delay_ms(5);
              PORTD.B1 = 1;
              //Millares
              PORTC = numeros[(valor/1000)%10];
              PORTD.B0 = 0;
              delay_ms(5);
              PORTD.B0 = 1;

     }
}