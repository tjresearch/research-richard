#include "global.h"

Car::Car(int i, Vertex& st, Vertex& en, bool dtd) {
	id = i;
	start = &st;
	end = &en;
	isDTD = dtd;

	startTime = CURRENT_TIME;

	finished = false;
	roadIndex = -1;

	distanceTraveled = 0.0;

	events = vector<Event>(EDGE_COUNT, Event());
}

Edge* Car::getNextRoad() {
	return route[++roadIndex];
}


pd Car::getLocation() {
	if (roadIndex == -1) {
		return mp(start->x, start->y);
	}
	ld distanceRatio = currentRoadDistance / currentRoad->length;
	ld x = currentRoad->start->x * (1 - distanceRatio) + currentRoad->end->x * distanceRatio;
	ld y = currentRoad->start->y * (1 - distanceRatio) + currentRoad->end->y * distanceRatio;
	return mp(x, y);
}

ld Car::getTimeElapsed() {
	return CURRENT_TIME - startTime;
}

string Car::toString() {
	string ret = "{";

	ret += "\"id\": " + to_string(id) + ", " +
			"\"start\": " + to_string(start->id) + ", " +
			"\"end\": " + to_string(end->id) + ", " +
			"\"isDTD\": " + to_string(isDTD) + ", " +
			"\"startTime\": " + to_string(startTime) + ", " +
			"\"finished\": " + to_string(finished) + ", " +
			"\"roadIndex\": " + to_string(finished) + ", " +
			"\"distanceTraveled\": " + to_string(distanceTraveled) + ", ";

	string events_str = "[";
	for(int i = 0; i < events.size(); i++) {
		if (i > 0) {
			events_str += ", ";
		}
		events_str += to_string(events[i].id);
	}
	events_str += "]";
	ret += "\"events\": " +events_str;

	ret += "}";
	return ret;
}
