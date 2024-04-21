# Particle Simulation
## Project Description
This project is a particles simulation, a lot of particles are created and it handles the physics of them being attracted to the center of the window.
The particles also collide with the borders of the window, resulting of the reversing of their speed vector's x (if it hits the left or right border) or
y (if it hits the upper or lower border) component.

## Setup
### Dependencies
On a Debian system you can install the needed dependencies using:
```shell
sudo apt install g++ cmake make libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev -y
```

### Clone Repository
```shell
git clone https://github.com/llikian/Particles-Simulation.git
cd Particles-Simulation
```

### Build
To build you can simply run the `build.sh` script at the root of the project using:
```shell
bash build.sh
```

You can also manually build it using:
```shell
cmake -B build && \
cmake --build build -j
```

Then you can run it using:
```shell
bin/Particles-Simulation
```

## Credits
The rendering is done using [SDL2](https://www.libsdl.org/).