# Decentralized Traffic Detection

## Project overview
I will simulate a road network and test the effectiveness of decentralized traffic detection (DTD) through car-to-car communication of local slowdowns. I will also determine the minimum density of DTD users necessary for effective decentralized traffic detection.

## Requirements
Ensure that your device has C++11 or higher.
The web server also requires Node.js

## Installation instructions
Pull or download this repository from GitHub
For the web server, run 'npm install NAME_OF_LIBRARY' to install libraries

## Run instructions
cd code/build

cmake .. && make

./main < input.txt

cd ../../web

node index.js

Go to localhost:8080/

