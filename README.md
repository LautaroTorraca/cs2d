# 🎮 TP Final - CS2D

Este proyecto es el Trabajo Práctico Final de la materia Taller de Programación, catedra Veiga. Desarrollamos un videojuego 2D multijugador con arquitectura cliente-servidor usando C++, SDL2pp, y Qt.

📌 Descripción

Este proyecto busca aplicar los conocimientos adquiridos a lo largo del cuatrimestre desarrollando un juego funcional con:

    Gráficos en 2D.

    Interacción en tiempo real.

    Un sistema de compra, disparo, colisiones y más.

🧰 Tecnologías Usadas

    C++

    SDL2

    SDL2_image / SDL2_mixer / SDL2_ttf

    SDL2pp (wrapper C++)

    Qt

    CMake

    GoogleTest (para pruebas)

    Git

## ⚙️ Instalación y Ejecución

🔧 Requisitos

Probado en Ubuntu 24.04. Necesitás tener instaladas las siguientes dependencias:

sudo apt update\
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev\
sudo apt install qt6-base-dev qt6-tools-dev-tools\
sudo apt install libsdl2-gfx-dev\
sudo apt install qt6-multimedia-dev

🧱 Compilar el proyecto

    Clonar el repositorio:

git clone https://github.com/totoruiz00/tp-grupal-taller-CS2D cs2d\
cd cs2d

    Creá la carpeta de build y generá el proyecto:

mkdir build\
cd build\
cmake ..\
make\

    Ejecutá los binarios:

./taller_server [port] \
./taller_client [port]

🗂️ Estructura del Proyecto

client/        # Código fuente del cliente (renderizado, input, audio)
server/        # Lógica del servidor y comunicación con clientes
common/        # Código compartido entre cliente y servidor (modelos, constantes, utilidades)
tests/         # Tests con GoogleTest
maps/          # Archivos YAML con los mapas disponibles
gameConstants/ # Archivos YAML con configuracion del juego
settings.yaml  # Configuracion de la resolución.
CMakeLists.txt