import React from 'react';
import { Alert, Button, StyleSheet, Text, View } from 'react-native';

const IP_ESP32 = 'http://192.168.4.84';

export default function App() {

  const enviarComando = async (rota) => {
    try {
      const resposta = await fetch(`${IP_ESP32}/${rota}`);
      const texto = await resposta.text();
      Alert.alert('Resposta do ESP32', texto);
    } catch (erro) {
      Alert.alert('Erro', 'Não foi possível conectar ao ESP32.');
    }
  };

  return (
    <View style={styles.container}>
      <Text style={styles.titulo}>Controle do Motor</Text>

      <View style={styles.botao}>
        <Button title="Velocidade Baixa" onPress={() => enviarComando('baixa')} />
      </View>
      <View style={styles.botao}>
        <Button title="Velocidade Média" onPress={() => enviarComando('media')} />
      </View>
      <View style={styles.botao}>
        <Button title="Velocidade Alta" onPress={() => enviarComando('alta')} />
      </View>
      <View style={styles.botao}>
        <Button title="Desligar" color="red" onPress={() => enviarComando('off')} />
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#eef',
    alignItems: 'center',
    justifyContent: 'center',
    padding: 20,
  },
  titulo: {
    fontSize: 24,
    fontWeight: 'bold',
    marginBottom: 30,
  },
  botao: {
    marginVertical: 10,
    width: '80%',
  },
});
