#include "global.h"

Vertex::Vertex(int i, ld x, ld y, ld spawnRate) {
	id = i;
	this->x = x;
	this->y = y;
	carSpawnRate = spawnRate;
}


void Vertex::spawnCar() {
	graphCars[TOTAL_CAR_COUNT] = Car(TOTAL_CAR_COUNT, *this, *possibleCarDestinations[randInt(0, possibleCarDestinations.size() - 1)], randDouble(0.0, 1.0) < DTD_RATE);
	TOTAL_CAR_COUNT++;
	currentCarProb--;
	CURRENT_CAR_COUNT++;
}

string Vertex::toString() {
	string ret = "{";

	ret += "\"id\": " + to_string(id) + ", " +
			"\"x\": " + to_string(x) + ", " +
			"\"y\": " + to_string(y) + ", " +
			"\"carSpawnRate\": " + to_string(carSpawnRate);

	ret += "}";
	return ret;
}
