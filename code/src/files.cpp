#include "global.h"

/*
 * Read in properties of vertices and edges (roads and intersections)
 */
void readNetworkFile(string file_name) {
	cout << "Reading in network file '" << file_name << "'" << endl;
	ifstream infile;
	infile.open(file_name);

	infile >> OUTPUT_BASE_NAME;
	infile >> VERTEX_COUNT >> EDGE_COUNT >> DESTINATION_COUNT >> DTD_RATE;

	graphVertices = vector<Vertex>(VERTEX_COUNT, Vertex());
	graphEdges = vector<Edge>(EDGE_COUNT, Edge());

	ld a, b, c;

	// Vertex data format: xCoordinate yCoordinate spawnRate
	for (int i = 0; i < VERTEX_COUNT; i++) {
		infile >> a >> b >> c;
		graphVertices[i] = Vertex(i, a, b, c);
	}


	// Edge data format: startVertexIndex endVertexIndex speedLimit
	for (int i = 0; i < EDGE_COUNT; i++) {
		infile >> a >> b >> c;
		graphEdges[i] = Edge(i, graphVertices[a], graphVertices[b], c, 1);
		graphVertices[a].edges.pb(&graphEdges[i]);
	}


	// Destinations
	for (int i = 0; i < DESTINATION_COUNT; i++) {
		infile >> a;
		allowedDestinations.insert(a);
	}


	// print out vertex data
	// for (int i = 0; i < VERTEX_COUNT; i++) {
	// 	cout << "vertex " << i << " " << convertToString(graphVertices[i]) << endl;
	// 	for (int j = 0; j < graphVertices[i].edges.size(); j++) {
	// 			cout << "v-e " << convertToString(*graphVertices[i].edges[j]) << endl;
	// 		}
	// 	}

	// print out edge data
	// for (int i = 0; i < EDGE_COUNT; i++) {
	// 	cout << "edge " << i << " " << convertToString(graphEdges[i]) << endl;
	// }

	cout << "Finished reading in network file '" << file_name << "'" << endl;
}


/*
 * Init output
 */
void initOutput() {
	cout << "Initializing output folder with base '" << OUTPUT_BASE_NAME << "'" << endl;

	OUTPUT_FOLDER_NAME = "../output/" + OUTPUT_BASE_NAME;
	int count = 0;
	string test = OUTPUT_FOLDER_NAME + padZeros(count, 4);
	while (!boost::filesystem::create_directories(test)) {
		test = OUTPUT_FOLDER_NAME + padZeros(++count, 4);
	}
	OUTPUT_FOLDER_NAME += padZeros(count, 4);
	OUTPUT_FILE_NAME = OUTPUT_FOLDER_NAME + "/" + OUTPUT_BASE_NAME + "_";
	cout << "OUTPUT_FOLDER_NAME: " << OUTPUT_FOLDER_NAME << endl;

	// write to general file which stores Edge and Vertex data and other parameters
	string general_file = OUTPUT_FILE_NAME + "global.txt";

	ofstream outfile;
	outfile.open(general_file);
	outfile << "{" << endl;

	outfile << "\"NUM_TIME_STEP\": " << NUM_TIME_STEP << "," << endl;
	outfile << "\"TIME_STEP_LENGTH\": " << TIME_STEP_LENGTH << "," << endl;

	outfile << "\"DTD_RATE\": " << DTD_RATE << "," << endl;

	outfile << "\"VERTEX_COUNT\": " << VERTEX_COUNT << "," << endl;
	outfile << "\"EDGE_COUNT\": " << EDGE_COUNT << "," << endl;
	outfile << "\"DESTINATION_COUNT\": " << DESTINATION_COUNT << "," << endl;

	outfile << "\"allowedDestinations\": [";
	bool first = true;
	for (int i: allowedDestinations) {
		if (first) {
			first = false;
		} else {
			outfile << ", ";
		}
		outfile << i;
	}
	outfile << "]" << endl;

	outfile << "}" << endl;

	outfile.close();

	cout << "General data file name: " << general_file << endl;
}


/*
 * Writes frame data to folder
 */
void writeFrameData() {
	// cout << "Writing frame to folder '" << OUTPUT_FOLDER_NAME << "'" << endl;

	string current_file = OUTPUT_FILE_NAME + padZeros(CURRENT_TIME_STEP, 6) + ".data";
	ofstream outfile;
	outfile.open(current_file);

	outfile << "{" << endl;
	outfile << "\"frame\": " << CURRENT_TIME_STEP << "," << endl;

	outfile << "\"CURRENT_TIME\": " << CURRENT_TIME << "," << endl;
	outfile << "\"CURRENT_CAR_COUNT\": " << CURRENT_CAR_COUNT << "," << endl;
	outfile << "\"TOTAL_CAR_COUNT\": " << TOTAL_CAR_COUNT << "," << endl;
	outfile << "\"EVENT_COUNT\": " << EVENT_COUNT << "," << endl;
	outfile << "\"TOTAL_TRIP_TIME\": " << TOTAL_TRIP_COUNT << "," << endl;

	outfile << "\"graphCars\": {" << endl;
	bool first = true;
	for (auto it : graphCars) {
		if (first) {
			first = false;
		} else {
			outfile << "," << endl;
		}
		outfile << "\"" << it.second.id << "\": " << it.second.toString();
	}
	outfile << endl;
	outfile << "}," << endl;

	outfile << "\"graphEdges\": [" << endl;
	for (int i = 0; i < graphEdges.size(); i++) {
		if (i > 0) {
			outfile << "," << endl;
		}
		outfile << graphEdges[i].toString();
	}
	outfile << endl;
	outfile << "]," << endl;

	outfile << "\"graphVertices\": [" << endl;
	for (int i = 0; i < graphVertices.size(); i++) {
		if (i > 0) {
			outfile << "," << endl;
		}
		outfile << graphVertices[i].toString();
	}
	outfile << endl;
	outfile << "]," << endl;

	outfile << "\"graphEvents\": [" << endl;
	first = true;
	for (auto it : graphEvents) {
		if (first) {
			first = false;
		} else {
			outfile << "," << endl;
		}
		outfile << it.second.toString();
	}
	outfile << endl;
	outfile << "]" << endl;

	outfile << "}" << endl;


	outfile.close();

	// cout << "Finished writing frame " << CURRENT_TIME_STEP << " to '" << current_file << "'" << endl;
}
