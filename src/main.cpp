#include "global.h"

/**
  * Spawns new cars
  * Updates car positions
  * Checks if cars have arrived at destination
  */
void step_simulation() {
	// cout << "STEP " << CURRENT_TIME << endl;
	// cout << "CURRENT_CAR_COUNT " << CURRENT_CAR_COUNT << endl;
	// cout << "TOTAL_CAR_COUNT " << TOTAL_CAR_COUNT << endl;

	// Spawn cars
	for (int i = 0; i < graphVertices.size(); i++) {
		graphVertices[i].currentCarProb += TIME_STEP_LENGTH * graphVertices[i].carSpawnRate;
		while (randDouble(0.0, 1.0) < graphVertices[i].currentCarProb) {
			graphVertices[i].spawnCar();
		}
	}

	// Create and transfer Events between DTD cars based on the previous step's speeds
	createEvents();
	transferEvents();

	//testing
	int dtd_count = 0;
	for (auto it = graphCars.begin(); it != graphCars.end(); it++) {
		if (it->second.isDTD) dtd_count++;
	}

	// 	Car& car = it->second;
	// 	int count = 0;
	// 	for (int i = 0; i < EDGE_COUNT; i++) {
	// 		if (car.events[i].id != -1 && !car.events[i].hasExpired()) {
	// 			count++;
	// 		}
	// 	}
	// 	cout << "yoi: " << CURRENT_TIME << " " << count << endl;
	// 	break;
	// }

	// Run A* for newly spawned cars and increment number of Cars on each Edge accordingly
	for (auto it = graphCars.begin(); it != graphCars.end(); it++) {
		Car& car = it->second;
		if (car.roadIndex == -1) {
			car.route = astar(*car.start, *car.end, car.events);
			car.currentRoad = car.getNextRoad();
			car.currentRoadDistance = 0.0;
			graphEdges[car.currentRoad->id].numCarsPresent++;
		}
	}

	// Reset graphEdges car count
	for (int i = 0; i < graphEdges.size(); i++) {
		graphEdges[i].numCarsPresent = 0;
	}
	// Count number of Cars on each Edge
	for (auto it = graphCars.begin(); it != graphCars.end(); it++) {
		Car& car = it->second;
		graphEdges[car.currentRoad->id].numCarsPresent++;
	}

	// Update road speeds based on number of Cars on each Edge
	for (int i = 0; i < graphEdges.size(); i++) {
		graphEdges[i].updateActualSpeed();
	}

	vector<int> toErase;

	// Update car positions and check if Cars have reached destination
	for (auto it = graphCars.begin(); it != graphCars.end(); it++) {
		int id = it->first;
		Car& car = it->second;
		ld timeLeft = TIME_STEP_LENGTH;
		while (timeLeft > 0.0) {
			ld roadTime = (car.currentRoad->length - car.currentRoadDistance) / car.currentRoad->actualSpeed;
			if (timeLeft >= roadTime) {
				car.distanceTraveled += car.currentRoad->length - car.currentRoadDistance;
				timeLeft -= roadTime;

				if (car.currentRoad->end == car.end) { // Car has reached destination
					ld tripTime = car.getTimeElapsed() + (TIME_STEP_LENGTH - timeLeft);
					TOTAL_TRIP_TIME += tripTime;
					TOTAL_TRIP_COUNT++;
					CURRENT_CAR_COUNT--;
					toErase.pb(id);
					car.finished = true;
					break;
				} else {
					if (car.isDTD) {
						car.route = astar(*car.currentRoad->end, *car.end, car.events);
						car.roadIndex = -1;
					}
					car.currentRoad = car.getNextRoad();
					car.currentRoadDistance = 0.0;
				}
			} else {
				// cout << "crd " << car.currentRoad->actualSpeed * timeLeft << endl;
				car.distanceTraveled += car.currentRoad->actualSpeed * timeLeft;
				car.currentRoadDistance += car.currentRoad->actualSpeed * timeLeft;
				timeLeft = 0.0;
			}
			car.getLocation();
		}
		if (car.finished) {
			continue;
		}
		// cout << convertToString(car) << endl;
	}

	// Remove Cars that have arrived at their destination
	for (int key: toErase) {
		graphCars.erase(key);
	}

	// Increment time
	CURRENT_TIME += TIME_STEP_LENGTH;
	// cout << endl;
}

void init() {
	long long seed = 0;
	srand(seed);

	string network_file_name;
	cout << "Network file name: ";
	cin >> network_file_name;
	cout << endl;

	cout << "END OF INPUT PARAMETERS" << endl << endl;

	stime(PROGRAM_START_TIME);

	readNetworkFile(network_file_name);

	// setup possibleCarDestinations
	for (int i = 0; i < VERTEX_COUNT; i++) {
		findReachable(graphVertices[i]);
		// prints reachable car destinations for each node
		// cout << "i " << i << endl;
		// for (int j = 0; j < graphVertices[i].possibleCarDestinations.size(); j++) {
		// 	cout << "dest " << graphVertices[i].possibleCarDestinations[j]->id << endl;
		// }
	}

	// calculate MAX_SPEED
	for (int i = 0; i < EDGE_COUNT; i++) {
		MAX_SPEED = max(MAX_SPEED, graphEdges[i].speedLimit);
	}
	cout << "MAX_SPEED: " << MAX_SPEED << endl;

	initOutput();

	ptime(PROGRAM_START_TIME);
}

void printStats() {
	cout << endl << "Overall statistics: " << endl << endl;
	cout << "TOTAL_CAR_COUNT: " << TOTAL_CAR_COUNT << endl;
	cout << "TOTAL_TRIP_COUNT: " << TOTAL_TRIP_COUNT << endl;
	cout << "AVERAGE_TRIP_TIME: " << TOTAL_TRIP_TIME / TOTAL_TRIP_COUNT << endl;
	cout << endl;
}

int main(void) {
	init();

	writeFrameData();
	for (CURRENT_TIME_STEP = 0; CURRENT_TIME_STEP < NUM_TIME_STEP; CURRENT_TIME_STEP++) {
		step_simulation();
		writeFrameData();
	}

	printStats();

	cout << "Program finished." << endl;
	ptime(PROGRAM_START_TIME);
}
