#ifndef CAR_H
#define CAR_H

/**
  * Car class is used to store information about individual cars on the road network
  * It stores start and end vertices, current time, and current location
  */
class Car {
public:
	Car() {};
	Car(int, Vertex&, Vertex&, bool);

	int id;
	ld x, y;
	Vertex* start;
	Vertex* end;
	bool isDTD;

	bool finished; // if car has started driving
	vector<Edge*> route;
	int roadIndex;
	Edge* getNextRoad();

	Edge* currentRoad;
	ld currentRoadDistance;
	pd getLocation();

	ld distanceTraveled;

	vector<Event*> events;

	ld startTime;
	ld getTimeElapsed();

	string toString();
};

#endif
