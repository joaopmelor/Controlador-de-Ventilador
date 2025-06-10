#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Justweb_PEDRO_2.4GHz";
const char* password = "";

// Pinos do L298N
#define IN1 19
#define IN2 21
#define ENA 18  // Pino PWM, mas aqui usaremos digital

WebServer server(80);

// Velocidade em níveis fixos
int velocidade = 255; // Máxima

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado!");
  Serial.println(WiFi.localIP());

  // Rotas
  server.on("/", handleRoot);
  server.on("/on", ligarMotorAlta);
  server.on("/off", desligarMotor);
  server.on("/baixa", ligarMotorBaixa);
  server.on("/media", ligarMotorMedia);
  server.on("/alta", ligarMotorAlta);

  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<h1>Controle de Motor</h1>";
  html += "<a href='/on'>Ligar (Alta)</a><br>";
  html += "<a href='/baixa'>Ligar (Baixa)</a><br>";
  html += "<a href='/media'>Ligar (Média)</a><br>";
  html += "<a href='/alta'>Ligar (Alta)</a><br>";
  html += "<a href='/off'>Desligar</a><br>";
  server.send(200, "text/html", html);
}

void ligarMotorBaixa() {
  velocidade = 100;
  analogWrite(ENA, velocidade);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  server.send(200, "text/plain", "Motor ligado em velocidade baixa.");
}

void ligarMotorMedia() {
  velocidade = 180;
  analogWrite(ENA, velocidade);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  server.send(200, "text/plain", "Motor ligado em velocidade média.");
}

void ligarMotorAlta() {
  velocidade = 255;
  analogWrite(ENA, velocidade);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  server.send(200, "text/plain", "Motor ligado em velocidade alta.");
}

void desligarMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  server.send(200, "text/plain", "Motor desligado.");
}