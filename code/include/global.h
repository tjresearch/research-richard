#ifndef GLOBAL_H
#define GLOBAL_H

#include <algorithm>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <chrono>
#include <iostream>
#include <fstream>
#include <queue>
#include <math.h>
#include <experimental/filesystem>

using namespace std;

typedef long long ll;
typedef long double ld;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;

typedef vector<int> vi;
typedef vector<vector<int>> vi2;
typedef vector<vector<vector<int>>> vi3;
typedef vector<vector<vector<vector<int>>>> vi4;
typedef vector<ld> vd;
typedef vector<vector<ld>> vd2;
typedef vector<vector<vector<ld>>> vd3;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<string> vs;
typedef vector<vector<string>> vs2;

typedef unordered_set<int> seti;
typedef unordered_map<int, int> mapii;
typedef unordered_map<string, pi> mspi;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define mp make_pair
#define pb push_back
#define f first
#define s second
#define sz(x) (int)x.size()

// timing
typedef chrono::high_resolution_clock Clock;
typedef chrono::high_resolution_clock::time_point Time;

/********************************
	START OF GLOBAL VARIABLES
********************************/

extern Time PROGRAM_START_TIME;

extern string OUTPUT_BASE_NAME;
extern string OUTPUT_FOLDER_NAME;
extern string OUTPUT_FILE_NAME;

extern int NUM_TIME_STEP;
extern int CURRENT_TIME_STEP;
extern ld TIME_STEP_LENGTH;
extern ld CURRENT_TIME;

extern int VERTEX_COUNT;
extern int EDGE_COUNT;
extern int DESTINATION_COUNT;

extern ld DTD_RATE;

extern int CURRENT_CAR_COUNT;
extern int MAX_CAR_COUNT;
extern int TOTAL_CAR_COUNT;

extern ld COMMUNICATION_RANGE;
extern int EVENT_COUNT;
extern ld EVENT_LIFETIME;

extern ld TOTAL_TRIP_TIME;
extern int TOTAL_TRIP_COUNT;

extern ld MAX_SPEED;

/**
  * Forward declaration of classes
  * Used when two classes refer to each other
  */
class Car;
class Edge;
class Vertex;
class Event;

extern unordered_map<int, Car> graphCars;
extern vector<Edge> graphEdges;
extern vector<Vertex> graphVertices;
extern unordered_map<int, Event> graphEvents;

extern unordered_set<int> allowedDestinations;

/******************************
	END OF GLOBAL VARIABLES
******************************/

#include "Car.h"
#include "Edge.h"
#include "Vertex.h"
#include "Event.h"

#include "main.h"
#include "utils.h"
#include "navigation.h"
#include "communication.h"
#include "files.h"

#endif
