#ifndef NAVIGATION_H
#define NAVIGATION_H

void findReachable(Vertex&);
vector<Edge*> astar(Vertex&, Vertex&, vector<Event>&);

#endif
