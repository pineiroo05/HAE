void interrupt(){
     PORTB.B3 = !PORTB.B3;
     INTCON3.INT2IF = 0;
}

void main() {
     ADCON1 = 0x07;
     TRISB.B2 = 1;
     TRISB.B3 = 0;
     
     INTCON2.INTEDG2 = 1;
     INTCON3.INT2IF = 0;
     INTCON3.INT2IE = 1;
     INTCON.GIE = 1;
     
     while(1){}
}