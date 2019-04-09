/*
*Code inspired from Nick Gammon at https://gist.github.com/chrismeyersfsu/3317769
* Arduino SLAVE
/*
 * 
 */
 
#include <SPI.h>

volatile byte buf[3];

void setup (void)
{

  Serial.begin (9600);   // debugging

  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  digitalWrite(10,HIGH);//make SS pin High: Communication starts when this pin is made low and ends when made high
  digitalWrite(13,HIGH); // SCK is made High. I have found that making SCK(input) pin high When communicating with BBB reduces errors.
  // turn on SPI in slave mode
  SPCR |= _BV(SPE);

  // now turn on interrupts
  SPI.attachInterrupt();

} 

// SPI interrupt routine
ISR (SPI_STC_vect)
{
  int i;
  uint8_t c;
  //buf[0] = SPDR;

  for(i=0;i<2;i++)
  {
    while(!(SPSR & (1<<SPIF))){}
    buf[i] = SPDR; // grab byte from SPI Data Register
  }

} 

void loop (void)
{

 Serial.println((char)buf[0]);
 Serial.println((char)buf[1]);



/* Do what ever u want with data stored in buf
I just wanted 8 bytes to be sent. Modify as you wish
*/

}
