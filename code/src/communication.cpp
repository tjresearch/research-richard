#include "global.h"

/**
  * For each car, creates an event based on current speed
  */
void createEvents() {
	for (auto it = graphCars.begin(); it != graphCars.end(); it++) {
		Car& car = it->second;
		if (!car.isDTD) continue;
		if (car.roadIndex != -1) {
			if (car.eventSent) {
				car.eventSent = false;
				graphEvents[EVENT_COUNT] = Event(EVENT_COUNT, car.currentRoad, car.currentRoad->actualSpeed, car.currentRoad->speedLimit, CURRENT_TIME);
				car.recentEvent = car.events[car.currentRoad->id] = &graphEvents[EVENT_COUNT++];
			} else {
				car.recentEvent->startTime = CURRENT_TIME;
			}
		}
	}
}

/**
  * Given two Cars, compare each of the stored Events for each road
  * Store the more recent Event for each road in both Cars
  */
void exchangeEvents(Car& c1, Car& c2) {
	for (int i = 0; i < EDGE_COUNT; i++) {
		if (c1.oldEvents[i]->id == -1) {
			c1.events[i] = c2.oldEvents[i];
			c2.eventSent = true;
		} else if (c2.oldEvents[i]->id == -1) {
			c2.events[i] = c1.oldEvents[i];
			c1.eventSent = true;
		} else {
			if (c1.oldEvents[i]->startTime < c2.oldEvents[i]->startTime) {
				c1.events[i] = c2.oldEvents[i];
				c2.eventSent = true;
			} else {
				c2.events[i] = c1.oldEvents[i];
				c1.eventSent = true;
			}
		}
	}
}

/**
  * For each pair of Cars within 'COMMUNICATION_RANGE', exchange all Events
  */
void transferEvents() {
	for (auto it = graphCars.begin(); it != graphCars.end(); it++) {
		Car& car = it->second;
		for (int i = 0; i < EDGE_COUNT; i++) {
			if (car.events[i]->hasExpired()) {
				car.events[i] = car.oldEvents[i] = &graphEvents[-1];
			}
			else {
				car.oldEvents[i] = car.events[i];
			}
		}
	}
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
	cout << "USING THIS WILL CAUSE eventOutput() from 'files.cpp' TO NOT WORK PROPERLY" << endl;
	return;
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
