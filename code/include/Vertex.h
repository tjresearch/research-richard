#ifndef VERTEX_H
#define VERTEX_H

/**
  * Vertex class is used to store information about intersections on the road network
  * It can also be used to form more fine roads to get a better representation of traffic
  */
class Vertex {
public:
	Vertex() {};
	Vertex(int, ld, ld, ld);

	int id;
	ld x, y;
	vector<Edge*> edges;

	ld currentCarProb = 0.0;
	ld carSpawnRate; // number of cars per second
	vector<Vertex*> possibleCarDestinations;
	void spawnCar();

	string toString();
};

#endif
