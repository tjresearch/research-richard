#include "global.h"

Edge::Edge(int i, Vertex& st, Vertex& en, ld sl, ld tm) {
	id = i;
	start = &st;
	end = &en;
	speedLimit = sl;
	trafficModifier = tm;

	length = distance(*start, *end);
	numCarsPresent = 0;
}

void Edge::updateActualSpeed() {
	actualSpeed = max(speedLimit / 10.0, speedLimit - max(numCarsPresent - 1, 0) * trafficModifier);
}

string Edge::toString() {
	string ret = "{";

	ret += "\"id\": " + to_string(id) + ", " +
			"\"start\": " + to_string(start->id) + ", " +
			"\"end\": " + to_string(end->id) + ", " +
			"\"actualSpeed\": " + to_string(actualSpeed) + ", " +
			"\"speedLimit\": " + to_string(speedLimit) + ", " +
			"\"trafficModifier\": " + to_string(trafficModifier) + ", " +
			"\"length\": " + to_string(length) + ", " +
			"\"numCarsPresent\": " + to_string(numCarsPresent);

	ret += "}";
	return ret;
}
