#define PIN_TRIG D7 
#define PIN_ECHO D8

float tiempo;
float distancia;

#define TRIG_LOTE_DOS D5  
#define ECHO_LOTE_DOS D6

float tiempo2;
float distancia_lote2;
void setup() {
   Serial.begin(9600);
   pinMode(PIN_TRIG, OUTPUT);
   pinMode(PIN_ECHO, INPUT);
   pinMode(TRIG_LOTE_DOS, OUTPUT);
   pinMode(ECHO_LOTE_DOS, INPUT);
}

void loop() {
   digitalWrite(PIN_TRIG, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(4);
  digitalWrite(PIN_TRIG, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   
   tiempo = pulseIn(PIN_ECHO, HIGH);
   distancia = tiempo/58.3;
   
  if (distancia<= 15){
    String outstring  =   "SI hay un vehiculo en lote 1: " + String(distancia);
         Serial.println(outstring);

  }
   

   delay(200);

   digitalWrite(TRIG_LOTE_DOS, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(4);
  digitalWrite(TRIG_LOTE_DOS, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   
   tiempo2 = pulseIn(ECHO_LOTE_DOS, HIGH);
   distancia_lote2 = tiempo2/58.3;
   
  if (distancia_lote2<= 15){
    String outstring  =   "SI hay un vehiculo en lote 2: " + String(distancia_lote2);
         Serial.println(outstring);

  }

   delay(100);
 }