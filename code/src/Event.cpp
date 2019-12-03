#include "global.h"

Event::Event(int i, Edge* r, ld as, ld sl, ld time) {
	id = i;
	road = r;
	actualSpeed = as;
	speedLimit = sl;

	startTime = time;
	lifetime = EVENT_LIFETIME; // can be dynamic
}

bool Event::hasExpired() {
	return CURRENT_TIME > (startTime + lifetime);
}

string Event::toString() {
	string ret = "{";
	if (id == -1) {
		ret += "\"id\": " + to_string(id);
	} else {
		ret += "\"id\": " + to_string(id) + ", " +
		"\"road\": " + to_string(road->id) + ", " +
		"\"actualSpeed\": " + to_string(actualSpeed) + ", " +
		"\"speedLimit\": " + to_string(speedLimit) + ", " +
		"\"startTime\": " + to_string(startTime) + ", " +
		"\"lifetime\": " + to_string(lifetime);
	}
	ret += "}";
	return ret;
}
