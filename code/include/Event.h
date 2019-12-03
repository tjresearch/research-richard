#ifndef EVENT_H
#define EVENT_H

/**
  * Event class is used to store information about traffic on the road network
  * It stores which road the traffic is on, the actual speed of the road, the speed limit of the road, and when it occurred
  */
class Event {
public:
	Event() {id = -1;};
	Event(int, Edge*, ld, ld, ld);

	int id;
	Edge* road;
	ld actualSpeed;
	ld speedLimit;

	ld startTime;
	ld lifetime;
	bool hasExpired();

	string toString();
};

#endif
