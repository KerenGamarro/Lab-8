# Lab-8
Utilizando el microcontrolador STM32F4 (núcleo) y el Cube IDE
Este laboratorio consiste en que el estudiante, mediante el uso de Cube IDE y el
microcontrolador STM32F4, practique el uso de interrupciones de evento y el protocolo
de comunicación UART en lenguaje C.
El objetivo de este laboratorio es implementar rutinas en C que permitan al usuario crear
un juego de carreras, en donde mediante comunicación serial se debe enviar un comando
para iniciar una rutina de semáforo de inicio, luego ambos jugadores tendrán un botón y
cada vez que este botón sea presionado el jugador avanzará una casilla (contador de
décadas), finalmente cuando haya un ganador, el juego debe reiniciar y mediante la
terminal serial se debe enviar el resultado.
Parte A: Rutina de inicio con UART (20 pts) Entrega en Clase
Implemente una rutina para obtener datos de UART, el juego de carrera debe
estar “bloqueado” hasta que se detecte el comando de inicio “S”. Al detectar este
comando, el juego debe iniciar un semáforo en donde 3 LEDs enciendan durante
un segundo cada uno en el siguiente orden (rojo, amarillo verde).
Nota: Si los jugadores presionan sus botones antes de que se apage el led verde, el jugador no
debe avanzar de posición.
Parte B: Control Jugador 1 (30 pts) Entrega en Clase
Implemente una rutina para que le jugador 1 pueda avanzar. La lógica de esta
parte es la de un contador de décadas de 4 bits (recuerde que esta función debe
estar bloqueada hasta que finalice la rutina de inicio).
El botón debe implementarse con interrupciones, recuerde que los botones no
deben bloquearse entre sí y deben contar con anti-rebot.
Parte C: Control Jugador 2 (30 pts)
Implemente una rutina para que le jugador 1 pueda avanzar. La lógica de esta
parte es la de un contador de décadas de 4 bits (recuerde que esta función debe
estar bloqueada hasta que finalice la rutina de inicio).
EL botón debe implementarse con interrupciones, recuerde que los botones no
deben bloquearse entre sí y deben contar con anti-rebot.
Parte D: Rutina de Ganador (20 pts)
Cuando alguno de los dos jugadores llegue a la posición final (4) los botones
deben bloquearse, impidiendo a los jugadores seguir avanzando. Y mediante
comunicación UART debe enviar una notificación indicando quien fue el jugador
ganador. El juego no puede volver a iniciar hasta que se envíe el comando de
inicio del ejercicio 1.
