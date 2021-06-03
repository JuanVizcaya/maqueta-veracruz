long eventoTime = 0;

int MTR_IN1 = 4;
int MTR_IN2 = 2;
int MTR_ENA = 3; // Analog
int MTR_LED = 7;
int MTR_SWITCH = 8;
int motor_switch;
bool MTR_ACTIVO = false;

int LEDS_A1 = 5; // Analog
int LEDS_A2 = 6; // Analog
int LEDS_A_SWITCH = 12;
int switch_a;

int LEDS_B1 = 9; // Analog
int LEDS_B2 = 10; // Analog
int LEDS_B3 = 11; // Analog
int LEDS_B_SWITCH = 13;
int switch_b;

int tiemposEncenderA1[3] = {0,10,20};
int tiemposApagarA1[3] = {2,12,22};
int statusA1 = 0;

int tiemposEncenderA2[10] = {2,5,8,11,14,17,20,23,26,29};
int tiemposApagarA2[10] = {0,3,6,9,12,15,18,21,24,27};
int statusA2 = 0;

int tiemposEncenderB1[6] = {2,7,12,17,22,27};
int tiemposApagarB1[6] = {3,8,13,18,23,28};
int statusB1 = 0;

int tiemposEncenderB2[15] = {1,3,5,7,9,11,13,15,17,19,21,23,25,27,29};
int tiemposApagarB2[15] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28};
int statusB2 = 0;

int tiemposEncenderB3[10] = {0,3,6,9,12,15,18,21,24,27};
int tiemposApagarB3[10] = {1,4,7,10,13,16,19,22,25,28};
int statusB3 = 0;

void setup() {
  Serial.begin(9600);
  // Output motor pines
  pinMode(MTR_IN1, OUTPUT);
  pinMode(MTR_IN2, OUTPUT);
  pinMode(MTR_ENA, OUTPUT);
  pinMode(MTR_LED, OUTPUT);
  pinMode(MTR_SWITCH, INPUT);

  // Input pines (switches)

  digitalWrite(MTR_IN1, LOW);
  digitalWrite(MTR_IN2, HIGH);

}

void motor() {
  motor_switch = digitalRead(MTR_SWITCH);
  if (motor_switch == HIGH) {
    if(!MTR_ACTIVO){
      digitalWrite(MTR_ENA, HIGH);
      delay(10);
      digitalWrite(MTR_ENA, LOW);
      MTR_ACTIVO = true;
    }
    
    digitalWrite(MTR_LED, HIGH);
    analogWrite(MTR_ENA, 10);

  } else {
    MTR_ACTIVO = false;
    digitalWrite(MTR_LED, LOW);
    digitalWrite(MTR_ENA, LOW);
  }
}

void apagaPrenderLeds(int *ledsApagar, int countApagar, int *ledsPrender, int countPrender) {
  if (countApagar > 0 or countPrender > 0) {
    for(int i=0; i<=255; i++) {
      for(int j=0; j<countPrender; j++) {
        analogWrite(ledsPrender[j], i);
      }
      for(int j=0; j<countApagar; j++) {
        analogWrite(ledsApagar[j], 255-i);
      }
      delay(1);
      
    }
  }
}

void loop()  {
  motor();
  int ledsPrender[5] = {};
  int countPrender = 0;
  int ledsApagar[5]= {};
  int countApagar = 0;
  int currentTime = (millis()-eventoTime)/1000;
  bool inArray = false;

  switch_a = digitalRead(LEDS_A_SWITCH);
  if(switch_a == HIGH) {
    // A1
    inArray = valueInArray(currentTime, tiemposEncenderA1, 3);
    if(inArray and statusA1 == 0) {
      ledsPrender[countPrender] = LEDS_A1;
      statusA1 = 1;
      countPrender++;
    }
    inArray = valueInArray(currentTime, tiemposApagarA1, 3);
    if(inArray and statusA1 == 1) {
      ledsApagar[countApagar] = LEDS_A1;
      statusA1 = 0;
      countApagar++;
    }
  
    // A2
    inArray = valueInArray(currentTime, tiemposEncenderA2, 10);
    if(inArray and statusA2 == 0) {
      ledsPrender[countPrender] = LEDS_A2;
      statusA2 = 1;
      countPrender++;
    }
    inArray = valueInArray(currentTime, tiemposApagarA2, 10);
    if(inArray and statusA2 == 1) {
      ledsApagar[countApagar] = LEDS_A2;
      statusA2 = 0;
      countApagar++;
    }
  } else {
    digitalWrite(LEDS_A1, LOW);
    digitalWrite(LEDS_A2, LOW);
  }

  switch_b = digitalRead(LEDS_B_SWITCH);
  if(switch_b == HIGH) {
    // B1
    inArray = valueInArray(currentTime, tiemposEncenderB1, 6);
    if(inArray and statusB1 == 0) {
      ledsPrender[countPrender] = LEDS_B1;
      statusB1 = 1;
      countPrender++;
    }
    inArray = valueInArray(currentTime, tiemposApagarB1, 6);
    if(inArray and statusB1 == 1) {
      ledsApagar[countApagar] = LEDS_B1;
      statusB1 = 0;
      countApagar++;
    }
  
    // B2
    inArray = valueInArray(currentTime, tiemposEncenderB2, 15);
    if(inArray and statusB2 == 0) {
      ledsPrender[countPrender] = LEDS_B2;
      statusB2 = 1;
      countPrender++;
    }
    inArray = valueInArray(currentTime, tiemposApagarB2, 15);
    if(inArray and statusB2 == 1) {
      ledsApagar[countApagar] = LEDS_B2;
      statusB2 = 0;
      countApagar++;
    }
  
    // B3
    inArray = valueInArray(currentTime, tiemposEncenderB3, 10);
    if(inArray and statusB3 == 0) {
      ledsPrender[countPrender] = LEDS_B3;
      statusB3 = 1;
      countPrender++;
    }
    inArray = valueInArray(currentTime, tiemposApagarB3, 10);
    if(inArray and statusB3 == 1) {
      ledsApagar[countApagar] = LEDS_B3;
      statusB3 = 0;
      countApagar++;
    }
  } else {
    digitalWrite(LEDS_B1, LOW);
    digitalWrite(LEDS_B2, LOW);
    digitalWrite(LEDS_B3, LOW);
  }
  

  
  // Ejecutar cambios de estado
  apagaPrenderLeds(ledsApagar, countApagar, ledsPrender, countPrender);

  // Reiniciar ciclo
  if(currentTime >= 30) {
    eventoTime = millis();
  }
}

bool valueInArray(int value, int *list, int listLen){
  bool response = false;
  for(int i=0; i<listLen; i++){
    if(value == list[i]) {
      response = true;
    }
  }
  return response;
}
