#include<16F887.h>
#device *=16 ADC=8
#use delay(clock=20000000)
#fuses HS,NOWDT,PUT,NOPROTECT,BROWNOUT
#byte PORTD=0x08
#byte PORTB=0x06
#bit D0=0x08.0
#define LCD_ENABLE_PIN PIN_E2
#define LCD_RW_PIN     PIN_E1
#define LCD_RS_PIN     PIN_E0
// 4 pin data
#define LCD_DATA4      PIN_D4
#define LCD_DATA5      PIN_D5
#define LCD_DATA6      PIN_D6
#define LCD_DATA7      PIN_D7
#include<LCD.c>

void main(){

SETUP_ADC(ADC_CLOCK_DIV_2);
SETUP_ADC_PORTS(SAN0|VSS_VDD);
SET_ADC_channel(0) ;
delay_us(10);
SET_TRIS_D(0);
PORTD=0b00000000;
SET_TRIS_C(255);
SET_TRIS_E(0);
set_tris_a(0x0F);
lcd_init();
float proxi;


while(True){
  // SElECT 2.5V or 0.5mm boundary
  // IF BUTTON khong co tac dong la NO 
  // IF BUTTON duoc de lai thi la NC
  // NO: 0-2.5V light off, 2.5-5V light on
  // NC: 0-2.5V light on, 2.5-5V light off
  
   proxi=read_adc();
   if (proxi>0 && INPUT(PIN_C0)==1)//NO
   {
     lcd_putc('\f');
     PORTD=0b00000000;
     lcd_gotoxy(1,1);
     lcd_putc("CAMBIENTIEMCAN");
     lcd_gotoxy(1,2);
     printf(lcd_putc,"NON-DETECTED");
     delay_ms(300);
   }
   if(proxi == 0 && INPUT(PIN_C0)==1)//NO
  {
    PORTD=0b00000001;
    lcd_putc('\f');
    lcd_gotoxy(1,1);
    lcd_putc("CAMBIENTIEMCAN");
    lcd_gotoxy(1,2);
    printf(lcd_putc,"OBJ_DETECTED");
    delay_ms(300);
  }
  if(INPUT(PIN_C0)==0)//NC
  {
    lcd_putc('\f');
    PORTD=0b00000001;
    lcd_gotoxy(1,1);
    lcd_putc("CONGTACHANHTRINH");
    lcd_gotoxy(1,2);
    printf(lcd_putc,"OBJ_DETECTED");
    delay_ms(300);
  }
 }
}

