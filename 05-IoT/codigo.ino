// PINOS

const int TMP36 = A3;
const int LED_AMARELO = 11;
const int LED_LARANJA = 10;
const int LED_VERMELHO = 9;
const int LED_VERDE = 12;
const int BUZZER = 8;

// LIMITES DE TEMPERATURA

const float TEMP_AMARELA = 20.0;
const float TEMP_LARANJA = 30.0;
const float TEMP_VERMELHA = 40.0;

// CONFIGURAÇÃO

void setup(){
  pinMode(TMP36, INPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_LARANJA, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
}

// LEITURA DO TMP36

float lerTemperatura(){
  int leitura = analogRead(TMP36);
  // Converti a leitura analógica para tensão
  float tensao = leitura * (5.0 / 1023.0);
  // Fórmula do TMP36
  float temperatura = (tensao - 0.5) * 100.0;
  return temperatura;
}

// LOOP PRINCIPAL

void loop(){
  float temperatura = lerTemperatura();
  // Mostra a temperatura no Monitor Serial
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");
  // Apaga todos os LEDs antes de escolher o estado
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_LARANJA, LOW);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_VERDE, LOW);
  
  // TEMPERATURA NORMAL

  if (temperatura < TEMP_AMARELA){
    digitalWrite(LED_VERDE, HIGH);
    noTone(BUZZER);
  }
  
  // TEMPERATURA DE ATENÇÃO

  else if (temperatura < TEMP_LARANJA){
    digitalWrite(LED_AMARELO, HIGH);
    tone(BUZZER, 300, 150);
    delay(1000);
  }
  
  // TEMPERATURA DE ALERTA
  
  else if (temperatura < TEMP_VERMELHA){
  	digitalWrite(LED_LARANJA, HIGH);
    tone(BUZZER, 500, 200);
    delay(1000);
  }

  // TEMPERATURA CRÍTICA

  else{
    digitalWrite(LED_VERMELHO, HIGH);
    tone(BUZZER, 1500, 300);
    delay(300);
    noTone(BUZZER);
    delay(300);
  }
  delay(200);
}