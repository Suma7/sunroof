#include <avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#define SET_BIT(PORT, PIN) PORT |= (1<<PIN)
#define CLR_BIT(PORT, PIN) PORT &= ~(1<<PIN)

//volatile int Driver_input = 0;
//volatile int Obstacle = 0;
struct {
  
  volatile unsigned int FLAG_ISR1:1;
  volatile unsigned int FLAG_ISR2:1;
}FLAG_BIT;
void output(int );
int pus_value;
typedef void (*funpointer)(void);
funpointer array_fp[2]={extint1};
int main(void)
{
    
  	SET_BIT(DDRC,PC4);
    SET_BIT(DDRC,PC5);
  	//SET_BIT(PORTC,3);
  
    
    //SET_BIT(DDRB, 5);
    //sei();
  Serial.begin(9600);
array_fp[0];
    while(1)
    {
      
        if (FLAG_BIT.FLAG_ISR1==0)
        {
          
          int Pin_read=0x00;
                  Pin_read=PINC;
         if(Pin_read & (1<<PC3)){
         SET_BIT(PORTC,5);
          CLR_BIT(PORTC,4); 
         }
        else
        {
        pus_value=ultra_sonicread();
           output(pus_value);}
        }
    
      else
      {
        CLR_BIT(PORTC, 5);
        CLR_BIT(PORTC, 4);
      }
       
    }
}
void extint1()
{
  EICRA|=(1<<ISC10);
    EICRA&=~(1<<ISC11);
    EIMSK|=(1<<INT1);
  sei();
}
ISR(INT1_vect)
            {
   			cli();
            FLAG_BIT.FLAG_ISR1=!FLAG_BIT.FLAG_ISR1;
            sei(); 
            }
int ultra_sonicread()
{
  
  SET_BIT(DDRD,PD4);
  SET_BIT(PORTD,PD4);
  _delay_ms(5);
  CLR_BIT(PORTD,PD4);
  CLR_BIT(DDRD,PD4);
  int time_duration = pulseIn(PD4,HIGH);
  float distance=0.343*time_duration*0.5*0.1;
  return(distance);
}
void output(int pus_value)
{
 if(pus_value<50){
          SET_BIT(PORTC,4);
          SET_BIT(PORTC,5);
 }
          else if(pus_value>50)
          {
           CLR_BIT(PORTC,4);
           CLR_BIT(PORTC,5);
          } 
}
