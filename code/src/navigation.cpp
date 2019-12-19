#include "global.h"

/**
  * Fills variable 'start.edges' with Vertices that can be reached from variable 'start'
  * variable 'start.edges' will not include variable 'start'
  */
void findReachable(Vertex& start) {
	vector<Vertex*> queue;
	queue.pb(&start);
	int index = 0;
	unordered_set<int> visited;
	visited.insert(start.id);
	while (index < queue.size()) {
		Vertex* state = queue[index];
		if (index > 0) {
			if (isAllowedDestination(*state)) {
				start.possibleCarDestinations.pb(state);
			}
		}
		for (Edge* e: state->edges) {
			if (visited.find(e->end->id) == visited.end()) {
				visited.insert(e->end->id);
				queue.pb(e->end);
			}
		}
		index++;
	}
}

/**
  * Returns the list of Edges that represents the fastest route from 'start' to 'end', using Events for real-time traffic data
  * Uses the A* algorithm on 'graphVertices' and 'graphEdges'
  */
vector<Edge*> astar(Vertex& start, Vertex& end, vector<Event*>& events) {
	unordered_map<int, int> parent; // <VertexIndex, EdgeIndex>
	unordered_map<int, ld> cost;
	parent[start.id] = -1;
	cost[start.id] = 0.0;

	auto compareVertex = [&] (Vertex& v1, Vertex& v2) -> bool {
		ld cur1 = 0.0;
		ld cur2 = 0.0;
		if (cost.find(v1.id) != cost.end()) {
			cur1 = cost[v1.id];
		}
		if (cost.find(v2.id) != cost.end()) {
			cur2 = cost[v2.id];
		}
		ld d1 = cur1 + distance(end, v1) / MAX_SPEED;
		ld d2 = cur2 + distance(end, v2) / MAX_SPEED;
		return d1 > d2;
	};

	priority_queue<Vertex, vector<Vertex>, decltype(compareVertex)> pq(compareVertex);
	pq.push(start);

	while (!pq.empty()) {
		Vertex state = pq.top();
		pq.pop();
		if (state.id == end.id) {
			vector<Edge*> route;
			int cur = state.id;
			while (parent[cur] != -1) {
				route.pb(&graphEdges[parent[cur]]);
				cur = graphEdges[parent[cur]].start->id;
			}
			reverse(route.begin(), route.end());
			return route;
		}
		for (Edge* e: state.edges) {
			ld cur_cost;
			if (events[e->id]->id == -1 || events[e->id]->actualSpeed == events[e->id]->speedLimit) {
				cur_cost = cost[state.id] + e->length / e->speedLimit;
			} else {
				// cout << "actualSpeed vs speedLimit " << events[e->id]->actualSpeed << " " << e->speedLimit << endl;
				cur_cost = cost[state.id] + e->length / events[e->id]->actualSpeed;
			}
			if (cost.find(e->end->id) == cost.end() || cur_cost < cost[e->end->id]) {
				cost[e->end->id] = cur_cost;
				parent[e->end->id] = e->id;
				pq.push(*e->end);
			}
		}
	}

	cout << "ERROR: No route found!" << endl;
}

/**
  * Returns the list of Edges that represents the fastest route from 'start' to 'end'
  * Uses the A* algorithm on 'graphVertices' and 'graphEdges'
  */
vector<Edge*> astar_old(Vertex& start, Vertex& end) {
	unordered_map<int, int> parent; // <VertexIndex, EdgeIndex>
	unordered_map<int, ld> cost;
	parent[start.id] = -1;
	cost[start.id] = 0.0;

	auto compareVertex = [&] (Vertex& v1, Vertex& v2) -> bool {
		ld cur1 = 0.0;
		ld cur2 = 0.0;
		if (cost.find(v1.id) != cost.end()) {
			cur1 = cost[v1.id];
		}
		if (cost.find(v2.id) != cost.end()) {
			cur2 = cost[v2.id];
		}
		ld d1 = cur1 + distance(end, v1) / MAX_SPEED;
		ld d2 = cur2 + distance(end, v2) / MAX_SPEED;
		return d1 > d2;
	};

	priority_queue<Vertex, vector<Vertex>, decltype(compareVertex)> pq(compareVertex);
	pq.push(start);

	while (!pq.empty()) {
		Vertex state = pq.top();
		pq.pop();
		if (state.id == end.id) {
			vector<Edge*> route;
			int cur = state.id;
			while (parent[cur] != -1) {
				route.pb(&graphEdges[parent[cur]]);
				cur = graphEdges[parent[cur]].start->id;
			}
			reverse(route.begin(), route.end());
			return route;
		}
		for (Edge* e: state.edges) {
			ld cur_cost = cost[state.id] + e->length / e->speedLimit;
			if (cost.find(e->end->id) == cost.end() || cur_cost < cost[e->end->id]) {
				cost[e->end->id] = cur_cost;
				parent[e->end->id] = e->id;
				pq.push(*e->end);
			}
		}
	}

	cout << "ERROR: No route found!" << endl;
}
