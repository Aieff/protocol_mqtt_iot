#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Configurações da rede Wi-Fi
const char *ssid = "Gabriel";
const char *password = "gabriel2468";

// Configurações do broker MQTT
const char *mqttServer = "a6c778c2dc0d4e97979552edaf3f2614.s2.eu.hivemq.cloud";
const int mqttPort = 8883;
const char *mqttUsername = "gabrieladmin";
const char *mqttPassword = "Gabriel1@";

// Configurações do cliente MQTT
const char *clientId = "ESP8266";
const char *topic = "administrador";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando...");

  // Conecta-se à rede Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando à rede Wi-Fi...");
  }
  Serial.println("Conectado à rede Wi-Fi");

  // Configuração do cliente MQTT
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  // Conecta-se ao broker MQTT
  connectToMQTT();
}

void loop() {
  // Mantém a conexão MQTT ativa
  if (!client.connected()) {
    connectToMQTT();
  }

  // Aguarda mensagens do broker
  client.loop();
}

void connectToMQTT() {
  // Conecta-se ao broker MQTT
  while (!client.connected()) {
    Serial.println("Conectando ao broker MQTT...");
    if (client.connect(clientId, mqttUsername, mqttPassword)) {
      Serial.println("Conectado ao broker MQTT");
      // Inscreve-se no tópico para receber mensagens
      client.subscribe(topic);
    } else {
      Serial.print("Falha na conexão, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando reconectar em 5 segundos...");
      delay(5000);
    }
  }
}

void callback(char *receivedTopic, byte *payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(receivedTopic);

  Serial.print("Conteúdo: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
