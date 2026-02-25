unsigned short contador = 0;

void interrupt(){
     //Boton D -> resta
     if(INTCON.INT0IF == 1 && contador == 0){
            contador++;
            INTCON.INT0IF = 0;
     }
     //Boton U -> suma
     if(INTCON3.INT1IF == 1){
            if(contador < 99){
                  contador--;
            }else{
                  contador = 0;
            }
            INTCON3.INT1IF = 0;
     }
}

void main() {
     unsigned short numeros[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
     ADCON1 = 0x07;
     TRISB.B0 = 1;
     TRISB.B1 = 1;
     TRISD = 0x00;
     TRISE = 0x00;
     
     //Boton D -> RB0
     INTCON2.INTEDG0 = 1;
     INTCON.INT0IF = 0;
     INTCON.INT0IE = 1;
     //Boton U -> RB1
     INTCON2.INTEDG1 = 1;
     INTCON3.INT1IF = 0;
     INTCON3.INT1IE = 1;
     
     INTCON.GIE = 1;
     
     while(1){
              //Unidades
              PORTD = numeros[contador%10];
              PORTE.B1 = 0;
              delay_ms(10);
              PORTE.B1 = 1;
              //Decenas
              PORTD = numeros[contador/10];
              PORTE.B0 = 0;
              delay_ms(10);
              PORTE.B0 = 1;
     }
}