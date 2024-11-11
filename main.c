#include <16F877A.h>
#device ADC=10
#include <string.h>
#include <math.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES HS

#use delay(crystal=20000000)

#define LCD_ENABLE_PIN PIN_D3
#define LCD_RS_PIN PIN_D1
#define LCD_RW_PIN PIN_D2

#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7

#include <lcd.c>

//void lcd_scroll_left(); //ham con hien thi cuon lcd tu phai sang trai
//void lcd_scroll_right(); //ham con hien thi cuon lcd tu trai sang phai
void read_mq2();
void print_mq2();

    int i,done;
    float gas,output;
    
    
void read_mq2()
{
   gas = 0;               
   for(i=0;i<100;i++)
      {
         gas=gas+read_adc();       
         delay_ms(1);
      }
   gas = gas/100;
   gas = (gas*5000)/1024;        
   output = (300+gas*2);
}

void print_mq2()
{
            lcd_gotoxy(1,1); //cot 1, dong 1
            lcd_putc("  NO GAS LEAK!  ");        
            delay_ms(2518);
            lcd_gotoxy(1,1); //cot 1, dong 1
            lcd_putc("You're safe here");
            delay_ms(2518);
}

void main()
{       
           
    set_tris_A(0xFF); //input analog MQ2
    set_tris_D(0x00); //output cho LCD
    set_tris_B(0x00); //output cho LED va coi

    lcd_init(); //khoi dong lcd
    delay_ms(10);
    setup_adc(ADC_CLOCK_DIV_32); //xung clock chia cho 32
    setup_adc_ports(AN0); //thiet lap chan A0 cho ADC    
    set_adc_channel(0); //su dung kenh 0 cua ADC
    delay_us(10);

   while(TRUE)
   {
    
   read_mq2();
   
   done=ADC_done();//kiem tra ADC lam viec xong
   while(!done) //neu ADC chua lam viec xong
      {
         done = ADC_done (); //tiep tuc lam viec
      }
        
       if(output>=4850) //vuot nguong => canh bao
          {
            output_low(PIN_B0);  //tat LED xanh
            output_high(PIN_B1); //bat LED do
            output_high(PIN_B2); //bat coi
            delay_ms(799);
            output_low(PIN_B1);  //tat LED do
            output_low(PIN_B2);  //tat coi
            
            lcd_gotoxy(1,1); //cot 1, dong 1
            lcd_putc("  GAS DETECTED  ");
            lcd_gotoxy(1,2); //cot 1, dong 2
            printf(lcd_putc," -> %f PPM ",output);              
          }//if
          else if (output<4850 && output>=3925)           //an toan => KHONG canh bao   
          { 
            output_low(PIN_B2);  //tat coi
            output_low(PIN_B1);  //tat LED do
            output_high(PIN_B0); //bat LED xanh
            
            lcd_gotoxy(1,2); //cot 1, dong 2
            printf(lcd_putc," -> %f PPM ",output/1.5);
            print_mq2();
            
                        
           }//else if
           else if (output<4850 && output>=3000)           //an toan => KHONG canh bao   
          { 
            output_low(PIN_B2);  //tat coi
            output_low(PIN_B1);  //tat LED do
            output_high(PIN_B0); //bat LED xanh
            
            lcd_gotoxy(1,2); //cot 1, dong 2
            printf(lcd_putc," -> %f PPM ",output/2);
            print_mq2();
            
                        
           }//else if
           else if (output<4850 && output>=2000)           //an toan => KHONG canh bao   
          { 
            output_low(PIN_B2);  //tat coi
            output_low(PIN_B1);  //tat LED do
            output_high(PIN_B0); //bat LED xanh
            
            lcd_gotoxy(1,2); //cot 1, dong 2
            printf(lcd_putc," -> %f PPM ",output/2.5);
            print_mq2();
            
                        
           }//else if
           else if (output<4850 && output>=1201)           //an toan => KHONG canh bao   
          { 
            output_low(PIN_B2);  //tat coi
            output_low(PIN_B1);  //tat LED do
            output_high(PIN_B0); //bat LED xanh
            
            lcd_gotoxy(1,2); //cot 1, dong 2
            printf(lcd_putc," -> %f PPM ",output/3);
            print_mq2();
            
                        
           }//else if
           else if (output<4850 && output>=501)           //an toan => KHONG canh bao   
          { 
            output_low(PIN_B2);  //tat coi
            output_low(PIN_B1);  //tat LED do
            output_high(PIN_B0); //bat LED xanh
            
            lcd_gotoxy(1,2); //cot 1, dong 2
            printf(lcd_putc," -> %f PPM ",output/1.5);
            print_mq2();
            
                        
           }//else if
           else if (output<4850 && output>=300)           //an toan => KHONG canh bao   
          { 
            output_low(PIN_B2);  //tat coi
            output_low(PIN_B1);  //tat LED do
            output_high(PIN_B0); //bat LED xanh
            
            lcd_gotoxy(1,2); //cot 1, dong 2
            printf(lcd_putc," -> %f PPM ",output);
            print_mq2();
            
                        
           }//else if
           else            //an toan => KHONG canh bao   
          { 
            output_low(PIN_B2);  //tat coi
            output_low(PIN_B1);  //tat LED do
            output_high(PIN_B0); //bat LED xanh
           
            lcd_gotoxy(1,2); //cot 1, dong 2
            printf(lcd_putc," -> %f PPM ",output=300);
            print_mq2();
                  
           }//else     
   }//while
}//main


/*
char string[]={"              NO GAS LEAK              You are safe here!"};

void lcd_scroll_left()
{
   char i,j;
   while(TRUE)
   {
      for(j=0;j<=57;j++)
      {
         for(i=0;i<=16;i++)
         {
            lcd_gotoxy(i,1);
            printf(lcd_putc,"%c",string[i+j-1]);
         }//for i
      delay_ms(112);
      }//for j
   }//while
}//lcd_scroll_left

void lcd_scroll_right()
{
   char i,j;
   while(TRUE)
   {
      for(j=0;j<=64;j++)
      {
         for(i=0;i<=16;i++)
         {
            lcd_gotoxy(i,1);
            printf(lcd_putc,"%c",string[32+i-j-1]);
         }//for i
      delay_ms(112);
      }//for j
   }//while
}//lcd_scroll_right






*/


