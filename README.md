Game of life in C - only code implementation that doesn't work right now is the klein bottle edge. To run, use the makefile in terminal - the command 'make' will automatically run the gcc compiler.

You must have SDL2 installed on your machine for the code to run. use 'sudo apt-get install libsdl2-dev' to install.

Usage: -w[width] -h[height] -e[edge] -r[red] -g[green] -b[blue] -s[sprite size] -f[filename]        -o[origin] OR ./life -H[help] if lost.

for example, ./life -w 800 -h 600 -e torus -r 125 -g 125 -b 255 -s 8 -f ./conwaylife/acorn_106.lif -o 50,50 or
./life -w 800 -h 600 -e torus -r 100 -g 100 -b 100 -s 8 -f ./conwaylife/glider_106.lif -o 80,60 etc.

width/height in ints, edge should be torus or hedge, defaults to hedge if otherwise. RGB settings included, s is the sprite size (2, 4, 8, or 16), defaults to 8 otherwise. -f filename found in the conway_life folder, make sure to have the conway_life folder in the same directory/folder as all the other code, will seg fault otherwise. -o origin is an x,y point entered without spaces or else will seg fault.

Also, to adjust the speed of the render, find the 'if SDL_GetTicks() %x == 0' line in gl.c; making the % value higher will slow down the render speed, but I like to have it lower as it makes for cooler and faster animations and outputs.
