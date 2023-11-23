# TPG - Taller de Programación I (7542/9508)
# Worms2D

![worms-logo](https://cdn.discordapp.com/attachments/1162524969142599822/1176873747249111070/pngegg.png?ex=65707416&is=655dff16&hm=ab3c9c99ee749053d6545c462345340b3ade8931082e20abc46a4c63a65aeec8&)

Worms2D es el proyecto final para la materia Taller de programación I (Cátedra Veiga - Facultad de Ing. UBA) y consta de una re-imaginación del popular juego de estrategia por turnos Worms Armageddon.

Para el proyecto se emplearon una serie de bibliotecas las cuales se listan como dependencias necesarias para correr el programa a continuación.

## Dependencias:

- Box2D // Engine de Físicas para juegos 2D.
- SDL2pp // Wrapper de la biblioteca SDL para tareas de renderizado y reproducción de audio.
- QT // Framework de diseño utilizado para la UI del juego.
- Google Tests // Suite para test unitarios en C++.
- LibYAML // Librería para facilitar el parseo y lectura de archivos YAML.

![worm-dependencias](https://cdn.discordapp.com/attachments/1162524969142599822/1176873875846463558/pngegg1.png?ex=65707435&is=655dff35&hm=e1bed770c3dea42b01800af9efa5ead113d4bc6d8d645dfb2497efc2278785c1&)

## Guía de instalación de las dependencias

- Box2D

```console
sudo apt install doxygen
...
```


- SDL2pp

```console
...
```

- QT

```console
sudo apt install qmake6 qt6-base-dev qt6-base-dev-tools qt6-multimedia-dev qt6-tools-dev
qt6-tools-dev-tools qt6-wayland qt6-wayland-dev qt6-wayland-dev-tools
libqt6multimedia6 libqt5multimedia5-plugins
```

- libYAML & GoogleTests
```console
sudo apt install libgtest-dev libyaml-cpp-dev libyaml-cpp0.7 -y
```

### Disclaimer

Se utilizo el [socket](https://github.com/eldipa/sockets-en-cpp), [queues y thread](https://github.com/eldipa/hands-on-threads/tree/master/libs) provistos por la catedra Veiga de Taller de Programacion I UBA. Bajo licencia GPL v2.
