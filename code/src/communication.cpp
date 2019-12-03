#include "global.h"

/**
  * For each car, creates an event based on current speed
  */
void createEvents() {
	for (auto it = graphCars.begin(); it != graphCars.end(); it++) {
		Car& car = it->second;
		if (!car.isDTD) continue;
		if (car.roadIndex != -1) {
			graphEvents[EVENT_COUNT] = Event(EVENT_COUNT, car.currentRoad, car.currentRoad->actualSpeed, car.currentRoad->speedLimit, CURRENT_TIME);
			car.events[car.currentRoad->id] = &graphEvents[EVENT_COUNT++];
		}
	}
}

/**
  * Given two Cars, compare each of the stored Events for each road
  * Store the more recent Event for each road in both Cars
  */
void exchangeEvents(Car& c1, Car& c2) {
	for (int i = 0; i < EDGE_COUNT; i++) {
		if (c1.events[i]->id == -1) {
			c1.events[i] = c2.events[i];
		} else if (c2.events[i]->id == -1) {
			c2.events[i] = c1.events[i];
		} else {
			c1.events[i] = c2.events[i] = (c1.events[i]->startTime < c2.events[i]->startTime) ? c1.events[i] : c2.events[i];
		}
	}
}

/**
  * For each pair of Cars within 'COMMUNICATION_RANGE', exchange all Events
  */
void transferEvents() {
	for (auto it1 = graphCars.begin(); it1 != graphCars.end(); it1++) {
		Car& c1 = it1->second;
		if (!c1.isDTD) continue;
		auto it2 = it1;
		it2++;
		for (; it2 != graphCars.end(); it2++) {
			Car& c2 = it2->second;
			if (!c2.isDTD) continue;
			ld dist = distance(c1, c2);
			if (dist <= COMMUNICATION_RANGE) {
				exchangeEvents(c1, c2);
			}
		}
	}
}

/**
  * Removes all expired events from 'graphEvents'
  */
void cleanEvents() {
	vector<int> toErase;

	for (auto it = graphEvents.begin(); it != graphEvents.end(); it++) {
		Event& ev = it->second;
		if (ev.hasExpired()) {
			toErase.pb(it->first);
		}
	}

	for (int key: toErase) {
		graphEvents.erase(key);
	}
}
