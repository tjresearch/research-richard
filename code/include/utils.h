#ifndef UTILS_H
#define UTILS_H

void stime(Time&);
void ptime(Time&);
ld rtime(Time&);

int randInt(int, int);
ld randDouble(ld, ld);

string padZeros(int, int);
string convertToString(Car&);
string convertToString(Edge&);
string convertToString(Vertex&);

ld distance(Vertex&, Vertex&);
ld distance(Car&, Car&);
ld distance(Car&, Vertex&);
// ld distance(Vertex&, int, int);
// ld distance(int, int, int, int);

bool isAllowedDestination(Vertex&);

#endif
