const mqtt = require('mqtt');

const client = mqtt.connect('ws://687af6d6752b4d1ea326b5ff8a11281a.s1.eu.hivemq.cloud:8884/mqtt');

client.on('connect', () => {

  console.log('Connected to MQTT Broker');

  client.subscribe('tópico');

});

client.on('message', (topic, message) => {

  console.log(`Received message on topic: ${topic}. Message: ${message.toString()}`);

  // Faça o que quiser com a mensagem recebida

});

// Publicar uma mensagem

client.publish('tópico', 'Você realizou uma conexão e enviou a mensagem');

// Para lidar com erros

client.on('error', (error) => {

  console.log(`Erro: ${error}`);

});