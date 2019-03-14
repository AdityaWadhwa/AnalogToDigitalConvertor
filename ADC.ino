#define ComparatorOut 2
#define TransistorIn  4

volatile uint16_t count = 0;
volatile uint16_t lastCount = 0;

ISR(TIMER1_COMPA_vect) 
{
  count++;
}

void setup()
{
    
  // Set up Timer 1 to send a sample every interrupt.
  
  cli();
  
  // Set CTC mode (Clear Timer on Compare Match) (p.133)
  // Have to set OCR1A *after*, otherwise it gets reset to 0!
  TCCR1B = (TCCR1B & ~_BV(WGM13)) | _BV(WGM12);
  TCCR1A = TCCR1A & ~(_BV(WGM11) | _BV(WGM10));
  
  // No prescaler (p.134)
  TCCR1B = (TCCR1B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);
  
  // Set the compare register (OCR1A).
  // OCR1A is a 16-bit register, so we have to do this with
  // interrupts disabled to be safe.
  OCR1A = 260;    // this decides the speed of the counter, it needs to pe properly calibrated with the charging time of the capacitor
  
  // Enable interrupt when TCNT1 == OCR1A (p.136)
  TIMSK1 |= _BV(OCIE1A);
  
  sei();
 
  pinMode(A0,INPUT);              //connect pin A0 to the sweep arm of potentiometer
  pinMode(ComparatorOut,INPUT);
  pinMode(TransistorIn,OUTPUT);
  Serial.begin(9600);
}
void loop() 
{
  if(digitalRead(ComparatorOut))
  {
//    Serial.println("Capacitor charged");
    digitalWrite(TransistorIn,HIGH);
//    Serial.println("Transistor ON");
    noInterrupts();
    lastCount=count;
    count=0;
    Serial.print(analogRead(A0)); //prints ADC value as calculated by the Arduino's ADC
    Serial.print("\t");
    Serial.println(lastCount);    //prints ADC value as calculated by the external ADC
    delay(1000);                  //10 times RC
    digitalWrite(TransistorIn,LOW);
//    Serial.println("Transistor OFF");
    interrupts();
  }
}
