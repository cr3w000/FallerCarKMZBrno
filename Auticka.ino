

// pripojeni pinu:
const int  zpomalVsPin = 2;    // Zpomalovaci usek vstup
const int zpomalVyPin = 3;    // Zpomalovaci usek vystup
const int vyhybkaVsPin = 4;   //Vyhybka detekce prujezdu
const int vyhybkaVyPin = 5;   //Vyhybka rizeni

//Deklarace casovace
const int zpomalInterval = 100;

 
// Deklarace promennych:
int zpomalPocetPrujezdu = 0;   // pocet prujezdu mistem zpomaleni
int zpomalVsStav = 0;
int zpomalVsPosledniStav = 0;
//cekani: smycka se opakuje kazdych 100ms. Pokud vstup detekuje prujezd, nastavi se na hodnotu zpomalInterval. Kazdou smycku se pak snizi o 1.  
//po dobu kdy je zpomalCekani vyssi nez 0, zpomalovaci vystup je aktivni a auticko stoji
int zpomalCekani = 0;         // cekani na povoleni prujezdu zpomalovacim usekem
int vyhybkaVsStav = 0;
int vyhybkaVsPosledniStav = 0;
int vyhybkaSmer = 0;     // smer vyhybky

void setup() {
    // initialize serial communication:
  Serial.begin(9600);
  Serial.println("Rizeni auticek na kolejisti");
  Serial.println("inicializace....");

    // initialize inputs:
  
  pinMode(zpomalVsPin, INPUT);
  pinMode(vyhybkaVsPin, INPUT);

  // initialize the outputs:
  pinMode(zpomalVyPin, OUTPUT);
  pinMode(vyhybkaVyPin, OUTPUT);

}


void loop() {

//////////////////////////ZPOMALOVANI
  // nacteni zpomalovaciho vstupu
  zpomalVsStav = digitalRead(zpomalVsPin);

  // compare the buttonState to its previous state
  if (zpomalVsStav != zpomalVsPosledniStav) {
    // if the state has changed
    if (zpomalVsStav == HIGH) {
      // zvysi pocet prujezdu pri detekci auticka
      zpomalPocetPrujezdu++;
      zpomalCekani = zpomalInterval;
      Serial.println("Zpomaleni on");
        Serial.println("Pocet prujezdu");  
        Serial.println(zpomalPocetPrujezdu); 
    } else {
      // auticko odjelo, nic se nedeje, jen odecti cas
      //tady je trochu mezera ze se neodecte cas v tomto cyklu, ale nemelo by to mit vliv na provoz
      Serial.println("Zpomaleni off");
    }
    
  } else {
     // zadna zmena na cidle, jen odecti cas
     if( zpomalCekani > 0) {
       zpomalCekani--;
       Serial.println(zpomalCekani);
       //pokud cas prave vyprsel, sniz pocet prujezdu. Pokud je nenulovy, nastav casovani znovu, tim se ohlida i druhe auticko aby do nej nenarazilo treti
       if(zpomalCekani == 0){
        zpomalPocetPrujezdu--;
        if(zpomalPocetPrujezdu > 0)
          zpomalCekani = zpomalInterval;

        Serial.println("Cas vyprsel");
        Serial.println("Pocet prujezdu");  
        Serial.println(zpomalPocetPrujezdu);  

      }
    }
  }
  // save the current state as the last state, for next time through the loop
  zpomalVsPosledniStav = zpomalVsStav;
 
  // pokud je pocet auticek ktere vjely do useku > 1, aktivuj vystup aby druhe auticko nemohlo projet a muselo cekat
  if (zpomalCekani > 0 && zpomalPocetPrujezdu > 1 ) {
    digitalWrite(zpomalVyPin, HIGH);
  } else {
    digitalWrite(zpomalVyPin, LOW);
  }



////////////////////////////VYHYBKA
  // nacteni vyhybkoveho vstupu
  vyhybkaVsStav = digitalRead(vyhybkaVsPin);
  if (vyhybkaVsStav != vyhybkaVsPosledniStav) {
    // if the state has changed
    Serial.println("Vyhybka zaznamenala prujezd");
    Serial.println(vyhybkaVsStav);
    if (zpomalVsStav == HIGH)
        vyhybkaSmer = !vyhybkaSmer;
   vyhybkaVsPosledniStav = vyhybkaVsStav;
   }

    digitalWrite(vyhybkaVyPin, vyhybkaSmer);

  
  //cekani 100ms
  delay(100);
}
