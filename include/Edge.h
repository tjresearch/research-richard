#ifndef EDGE_H
#define EDGE_H

/**
  * Edge class is used to represent roads in the road network
  * Stores information about speed limit, levels of traffic
  */
class Edge {
public:
	Edge() {};
	Edge(int id, Vertex&, Vertex&, ld, ld);

	int id;
	Vertex* start;
	Vertex* end;
	ld length;

	ld speedLimit;
	ld trafficModifier;
	int numCarsPresent;
	void updateActualSpeed();
	ld actualSpeed;

	string toString();
};

#endif
