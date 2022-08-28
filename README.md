## libmcrcon

A library for interfacing with a Minecraft servers RCON server

## Install 
 - Clone the github repo
 - Run `sudo ./install.sh`
 - Link program with `-lmcrcon`
 - You may need to run your programs with `LD_LIBRARY_PATH=/usr/local/lib` for them to work

## Example
The example provided shows a basic console, where you see 2773, replace that with your servers rcon password.

Then run `./test.sh` to compile and run the example