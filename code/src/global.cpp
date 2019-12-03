#include "global.h"

Time PROGRAM_START_TIME;

string OUTPUT_BASE_NAME;
string OUTPUT_FOLDER_NAME;
string OUTPUT_FILE_NAME;

int NUM_TIME_STEP = 1000; // total number of timesteps of simulation
int CURRENT_TIME_STEP = 0.0;
ld TIME_STEP_LENGTH = 1.0;  // measured in seconds
ld CURRENT_TIME = 0.0;

int VERTEX_COUNT;
int EDGE_COUNT;
int DESTINATION_COUNT;

ld DTD_RATE;

int CURRENT_CAR_COUNT = 0;
// int MAX_CAR_COUNT = 1000;
int TOTAL_CAR_COUNT = 0;

ld COMMUNICATION_RANGE = 100.0; // move to input file
int EVENT_COUNT = 0;
ld EVENT_LIFETIME = 200.0; // move to input file, could be dynamic, based on how long it would take for the car to get off that road.

// Trip statistics
ld TOTAL_TRIP_TIME;
int TOTAL_TRIP_COUNT;

ld MAX_SPEED = 0.0; // calculated in method 'init' (main.cpp)

unordered_map<int, Car> graphCars;
vector<Edge> graphEdges;
vector<Vertex> graphVertices;
unordered_map<int, Event> graphEvents;

unordered_set<int> allowedDestinations;
