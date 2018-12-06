



/*
KMZ Brno
Ovladani zastavky pro Faller car autobus
(c)2018 T. Bartulec
*/

//Nastaveni portu
const int analogInPin1 = A2;  // Analog input pin 
const int digitalOutPin1 = 2; // Digital output pin 

const int analogInPin2 = A5;  // Analog input pin 
const int digitalOutPin2 = 3; // Digital output pin 

const int analogInPin3 = A7;  // Analog input pin 
const int digitalOutPin3 = 4; // Digital output pin 

//prejezdy
const int analogInPinP1 = A0;  // Analog input pin 
const int analogInPinP2 = A1;  // Analog input pin 
//const int analogInPinP3 = A3;  // Analog input pin 
//const int analogInPinP4 = A4;  // Analog input pin 



const int digitalOutPinP = 5; // Digital output pin 
const int digitalOutPinV = 6;

//magnet state mapping to pin value
const int MAGNET_OFF = 1;
const int MAGNET_ON = 0;

//velikost pole pro pocitani prumeru
const int PRUMER_SIZE = 10;
//Prah pro detekci prujezdu
const int PRAH = 20;
const int PRAH_PREJEZD = 25;
const int PRAH_PREJEZD2 = 20;


//Cas v zastavce. t=2*CAS_V_ZASTAVCE [ms]
const int CAS_V_ZASTAVCE = 4000;

int state1 = 0;
int state2 = 0;
int state3 = 0;
int stateP = 0;

int sensorValue1 = 0;        // value read
int outputValue1 = 0;        // magnet control

int sensorValue2 = 0;        // value read
int outputValue2 = 0;        // magnet control

int sensorValue3 = 0;        // value read
int outputValue3 = 0;        // magnet control

int sensorValueP1 = 0;        // value read
int sensorValueP2 = 0;        // value read
//int sensorValueP3 = 0;        // value read
//int sensorValueP4 = 0;        // value read
int outputValueP = 0;        // magnet control

int prumer_iterator1 = 0;
int prumer_matrix1[PRUMER_SIZE];
int prumer1;
int timer1 = 0;

int prumer_iterator2 = 0;
int prumer_matrix2[PRUMER_SIZE];
int prumer2;
int timer2 = 0;

int prumer_iterator3 = 0;
int prumer_matrix3[PRUMER_SIZE];
int prumer3;
int timer3 = 0;

int prumer_matrixP1[PRUMER_SIZE];
int prumerP1;
int prumer_matrixP2[PRUMER_SIZE];
int prumerP2;
/*int prumer_matrixP3[PRUMER_SIZE];
int prumerP3;
int prumer_matrixP4[PRUMER_SIZE];
int prumerP4;*/
int timerP = 0;
int prumer_iteratorP = 0;
int prejezdzpozdeni = 0;
int stavVyhybka = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(digitalOutPin1, OUTPUT);
  digitalWrite(digitalOutPin1, MAGNET_OFF);
  pinMode(digitalOutPin2, OUTPUT);
  digitalWrite(digitalOutPin2, MAGNET_OFF);
  pinMode(digitalOutPin3, OUTPUT);
  digitalWrite(digitalOutPin3, MAGNET_OFF);
  pinMode(digitalOutPinP, OUTPUT);
  digitalWrite(digitalOutPin3, MAGNET_OFF);
  pinMode(digitalOutPinV, OUTPUT);

}

void loop() {
  
  ///////////////////Zastavka 1
  
  // read the analog in value:
  sensorValue1 = analogRead(analogInPin1);
  //store sensor value
  prumer_matrix1[prumer_iterator1] = sensorValue1;
  prumer_iterator1++;

  //calculate median
  if(prumer_iterator1 == PRUMER_SIZE ){
    prumer1=0;
    for(int i=0;i<PRUMER_SIZE;i++){
      prumer1+=prumer_matrix1[i];
    }
    prumer1 = prumer1 / PRUMER_SIZE;
    prumer_iterator1=0;

    if(prumer1 < PRAH){
    //new state will be 1. check current one
      if(state1 == 0){
        //previous state was 0, report state change
        Serial.println();
        Serial.println("State 0 changed to 1");

        //activate output and start timer
        digitalWrite(digitalOutPin1, MAGNET_ON);
        Serial.println("Vystup 1 ON");
        timer1 = CAS_V_ZASTAVCE;
      }
      state1 = 1;
    }
    else
    {
      //new state will be 0. check current one
      if(state1 == 1){
        //previous state was 1, report state change
        Serial.println();
        Serial.println("State 1 changed to 0");  

       //prehod vyhybku
       stavVyhybka = !stavVyhybka;
       Serial.println();
       Serial.print("Vyhybka stav: ");  
       Serial.print(stavVyhybka);
       digitalWrite(digitalOutPinV, stavVyhybka);

      }
      state1 = 0;
    }
 }

/////////////// Zastavka 2
 // read the analog in value:
  sensorValue2 = analogRead(analogInPin2);
  //store sensor value
  prumer_matrix2[prumer_iterator2] = sensorValue2;
  prumer_iterator2++;

  //calculate median
  if(prumer_iterator2 == PRUMER_SIZE ){
    prumer2=0;
    for(int i=0;i<PRUMER_SIZE;i++){
      prumer2+=prumer_matrix2[i];
    }
    prumer2 = prumer2 / PRUMER_SIZE;
    prumer_iterator2=0;

    if(prumer2 < PRAH){
    //new state will be 1. check current one
      if(state2 == 0){
        //previous state was 0, report state change
        Serial.println();
        Serial.println("State 2 changed to 1");

        //activate output and start timer
        digitalWrite(digitalOutPin2, MAGNET_ON);
        Serial.println("Vystup 2 ON");
        timer2 = CAS_V_ZASTAVCE;
      }
      state2 = 1;
    }
    else
    {
      //new state will be 0. check current one
      if(state2 == 1){
        //previous state was 1, report state change
        Serial.println();
        Serial.println("State 2 changed to 0");     
      }
      state2 = 0;
    }
 }


////////////////////////////////////////////////// Zastavka 3

 // read the analog in value:
  sensorValue3 = analogRead(analogInPin3);
  //store sensor value
  prumer_matrix3[prumer_iterator3] = sensorValue3;
  prumer_iterator3++;

  //calculate median
  if(prumer_iterator3 == PRUMER_SIZE ){
    prumer3=0;
    for(int i=0;i<PRUMER_SIZE;i++){
      prumer3+=prumer_matrix3[i];
    }
    prumer3 = prumer3 / PRUMER_SIZE;
    prumer_iterator3=0;

    if(prumer3 < PRAH){
    //new state will be 1. check current one
      if(state3 == 0){
        //previous state was 0, report state change
        Serial.println();
        Serial.println("State 3 changed to 1");

        //activate output and start timer
        digitalWrite(digitalOutPin3, MAGNET_ON);
        Serial.println("Vystup 3 ON");
        timer3 = CAS_V_ZASTAVCE;
      }
      state3 = 1;
    }
    else
    {
      //new state will be 0. check current one
      if(state3 == 1){
        //previous state was 1, report state change
        Serial.println();
        Serial.println("State changed 3 to 0");     
      }
      state3 = 0;
    }
 }
 
 
//Vyhodnoceni casovacu
  if(timer1 > 0){
    if(timer1 == 1){
      digitalWrite(digitalOutPin1, MAGNET_OFF);
      Serial.println("Vystup 1 OFF");
    }
    timer1--;
 }

  if(timer2 > 0){
    if(timer2 == 1){
      digitalWrite(digitalOutPin2, MAGNET_OFF);
      Serial.println("Vystup 2 OFF");
    }
    timer2--;
 }


   if(timer3 > 0){
    if(timer3 == 1){
      digitalWrite(digitalOutPin3, MAGNET_OFF);
      Serial.println("Vystup 3 OFF");
    }
    timer3--;
 }


////////////////////////////////////////////////// Prejezd

 // read the analog in value:
  sensorValueP1 = analogRead(analogInPinP1);
  //store sensor value
  prumer_matrixP1[prumer_iteratorP] = sensorValueP1;

// read the analog in value:
  sensorValueP2 = analogRead(analogInPinP2);
//  store sensor value
  prumer_matrixP2[prumer_iteratorP] = sensorValueP2;

  // read the analog in value:
 // sensorValueP3 = analogRead(analogInPinP3);
  //store sensor value
 // prumer_matrixP3[prumer_iteratorP] = sensorValueP3;

  // read the analog in value:
 // sensorValueP4 = analogRead(analogInPinP4);
  //store sensor value
//  prumer_matrixP4[prumer_iteratorP] = sensorValueP4;
  prumer_iteratorP++;

  
  //calculate median
  if(prumer_iteratorP == PRUMER_SIZE ){
    prumerP1=0;
    for(int i=0;i<PRUMER_SIZE;i++){
      prumerP1+=prumer_matrixP1[i];
    }
    prumerP1 = prumerP1 / PRUMER_SIZE;
    prumerP1 = prumerP1 / 10;

    prumerP2=0;
    for(int i=0;i<PRUMER_SIZE;i++){
      prumerP2+=prumer_matrixP2[i];
    }
    prumerP2 = prumerP2 / PRUMER_SIZE;
    prumerP2 = prumerP2 / 10;

/*    prumerP3=0;
    for(int i=0;i<PRUMER_SIZE;i++){
      prumerP3+=prumer_matrixP3[i];
    }
    prumerP3 = prumerP3 / PRUMER_SIZE;
    prumerP3 = prumerP3 / 10;

    prumerP4=0;
    for(int i=0;i<PRUMER_SIZE;i++){
      prumerP4+=prumer_matrixP4[i];
    }
    prumerP4 = prumerP4 / PRUMER_SIZE;
    prumerP4 = prumerP4 / 10;
*/
    
    prumer_iteratorP=0;
  //     Serial.println(prumerP2);    

//    if((prumerP1 > PRAH_PREJEZD) && (prumerP2 > PRAH_PREJEZD) && (prumerP3 > PRAH_PREJEZD)  && (prumerP4 > PRAH_PREJEZD) ){
    if(( prumerP1 > PRAH_PREJEZD) &&(prumerP2 > PRAH_PREJEZD2) ){
    //No train, magnet off
//       digitalWrite(digitalOutPinP, MAGNET_OFF);
    prejezdzpozdeni--;
    if(prejezdzpozdeni < 0)
        prejezdzpozdeni = 0;
     
   //  Serial.println("PREJEZD OFF");    
    }
    else
    {
    //Train approaching, magnet ON
     //  digitalWrite(digitalOutPinP, MAGNET_ON);
         prejezdzpozdeni++;
      if(prejezdzpozdeni > 20)
        prejezdzpozdeni = 20;
   //   Serial.println("PREJEZD ON");
    }

    if(prejezdzpozdeni > 10)
    {
       digitalWrite(digitalOutPinP, MAGNET_ON);
      
    }
    else
    {
            digitalWrite(digitalOutPinP, MAGNET_OFF);

    }    
 }





 
   // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:  
 delay(2);
}
