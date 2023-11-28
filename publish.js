const mqtt = require('mqtt');

// Configurações do broker MQTT
const mqttServer = 'a6c778c2dc0d4e97979552edaf3f2614.s2.eu.hivemq.cloud';
const mqttPort = 8883;
const mqttUsername = 'gabrieladmin'; // Substitua pelo seu nome de usuário MQTT
const mqttPassword = 'Gabriel1@';   // Substitua pela sua senha MQTT

// Configurações do cliente MQTT
const clientId = 'publicador';
const topic = 'administrador';  // Substitua pelo tópico desejado

// Criação do cliente MQTT
const client = mqtt.connect(`mqtts://${mqttServer}:${mqttPort}`, {
  clientId: clientId,
  username: mqttUsername,
  password: mqttPassword
});

// Função chamada quando a conexão é estabelecida
client.on('connect', function () {
  console.log('Conectado ao broker MQTT');

  // Publica uma mensagem no tópico especificado
  client.publish(topic, 'Olá aplicação em Javascript.2 estou fazendo um publish.', function (err) {
    if (!err) {
      console.log('Mensagem enviada com sucesso!');
    } else {
      console.error('Erro ao enviar mensagem:', err);
    }

    // Encerra a conexão após publicar a mensagem (opcional)
    client.end();
  });
});

// Função chamada quando ocorre um erro na conexão
client.on('error', function (error) {
  console.error('Erro na conexão:', error);
});
