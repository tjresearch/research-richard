#include "global.h"

void stime(Time& st) { st = Clock::now(); }
void ptime(Time& st) { cout << "Execution Time: " << (int) ((Clock::now()-st).count()/1000000) << " ms" << endl << endl; }
ld rtime(Time& st) { return (Clock::now()-st).count();}

/**
  * Generates random integer from 'lower' to 'upper' (inclusive)
  */
int randInt(int lower, int upper) {
	return lower + rand() % (upper - lower + 1);
}

/**
  * Generates random decimal from 'lower' to 'upper' (exclusive)
  */
ld randDouble(ld lower, ld upper) {
	return lower + (rand() / (RAND_MAX + 1.0)) * (upper - lower);
}

string padZeros(int num, int length) {
	string ret = to_string(num);
	while (ret.length() < length) {
		ret  = "0" + ret;
	}
	return ret;
}

string convertToString(Car& c) {
	pd loc = c.getLocation();
	string dtd = c.isDTD ? "DTD" : "___";
	return "[c " + to_string(c.id) + " " + dtd + " (" + to_string(loc.f) + "," + to_string(loc.s) + ") " + to_string(c.getTimeElapsed()) + "]";
}

string convertToString(Edge& e) {
	return "[e " + to_string(e.id) + " " + to_string(e.speedLimit) + " " + convertToString(*e.start) + " " + convertToString(*e.end) + "]";
}

string convertToString(Vertex& v) {
	return "[v " + to_string(v.id) + " (" + to_string(v.x) + ", " + to_string(v.y) + ") " + to_string(v.carSpawnRate) + "]";
}

ld distance(Vertex& v1, Vertex& v2) {
	ld dx = v1.x - v2.x;
	ld dy = v1.y - v2.y;
	return sqrt(dx * dx + dy * dy);
}

ld distance(Car& c1, Car& c2) {
	pd p1 = c1.getLocation();
	pd p2 = c2.getLocation();
	ld dx = p1.first - p2.first;
	ld dy = p1.second - p2.second;
	return sqrt(dx * dx + dy * dy);
}

ld distance(Car& c1, Vertex& v2) {
	pd p1 = c1.getLocation();
	ld dx = p1.first - v2.x;
	ld dy = p1.second - v2.y;
	return sqrt(dx * dx + dy * dy);
}

// ld distance(Vertex& v1, int x2, int y2) {
// 	ld dx = v1.x - x2;
// 	ld dy = v1.y - y2;
// 	return sqrt(dx * dx + dy * dy);
// }
//
// ld distance(int x1, int y1, int x2, int y2) {
// 	ld dx = x1 - x2;
// 	ld dy = y1 - y2;
// 	return sqrt(dx * dx + dy * dy);
// }

bool isAllowedDestination(Vertex& v) {
	return DESTINATION_COUNT == -1 || allowedDestinations.find(v.id) != allowedDestinations.end();
}
