# DS870 - Sistemas Embarcados e IoT

## Trabalho 1 - Sensor de Estacionamento

### O algoritmo

A ideia do algoritmo é bem simples, funciona com uma técnica utilizada em jogos para ter estabilidade com o framerate.

Para calcular o intervalo de acionamento do buzzer, utiliza-se uma variável que guarda quanto tempo falta para ativar ele.

O fluxo do algoritmo é o seguinte:

- É feita a leitura da distância no sensor ultrassônico
- De acordo com a distância, realiza-se a operação de acionar de 0 a 3 leds
- Se o threshold da distância mudou, então subtrai-se do tempo restante o tempo específico da ultima distância - o tempo específico da distância atual
- Se o tempo que falta para acionar o buzzer é menor ou igual a zero:
  - Aciona-se ele por 50ms
  - A variável do tempo para acionar o buzzer é resetada
  - Utiliza-se mais um delay de 50ms
- Caso contrário, apenas utiliza-se um delay de 100ms para a próxima leitura
- Subtrai-se esses 100ms do tempo restante para acionar o buzzer

### IMPORTANTE

Este trabalho foi implementado inicialmente visando o Arduino Uno. Portanto, lembre-se de atualizar o arquivo `platformio.ini`, alterando o arduino de destino.
