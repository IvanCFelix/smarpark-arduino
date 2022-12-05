#define PIN_TRIG D5  
#define PIN_ECHO D6

float tiempo;
float distancia;

void setup() {
   Serial.begin(9600);
   pinMode(PIN_TRIG, OUTPUT);
   pinMode(PIN_ECHO, INPUT);
}

void loop() {

   digitalWrite(PIN_TRIG, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   
   digitalWrite(PIN_TRIG, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(PIN_TRIG, LOW);
   
   tiempo = pulseIn(PIN_ECHO, HIGH);
   distancia = tiempo/58.3;

  if (distancia<= 15){
    String outstring  =   "SI hay un vehiculo" + String(distancia);
         Serial.println(outstring);

  }else{ 
     //Serial.println("no hay veiculos cercanos",distancia);

  }


   delay(1000);
}