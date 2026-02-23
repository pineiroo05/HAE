void main() {
     unsigned short numeros[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
     unsigned short i = 0;
     unsigned short unidades = 0;
     unsigned short decenas = 0;

     ADCON1 = 0x07;
     TRISA = 0x00;
     TRISD = 0x00;

     while(1){
              for(i=0; i<20; i++){
                       //Unidades
                       PORTA = 0xFF; //Limpieza de puertos
                       PORTD = numeros[unidades];
                       PORTA.B1 = 0;
                       PORTA.B0 = 1;
                       delay_ms(10);
                       //Decenas
                       PORTA = 0xFF; //Limpieza de puertos
                       PORTD = numeros[decenas];
                       PORTA.B0 = 0;
                       PORTA.B1 = 1;
                       delay_ms(10);
              }
              unidades++;
              if(unidades > 9){
                          decenas++;
                          unidades = 0;
              }
              if(decenas > 5){
                         decenas = 0;
              }
     }
}