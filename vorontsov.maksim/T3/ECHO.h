#ifndef ECHO_H
#define ECHO_H
#include <vector>
#include "Structs.h"

EchoAccumulator echoStep(EchoAccumulator acc, const Polygon& p);
int duplicateEcho(std::vector<Polygon>& polygons, const Polygon& target);
#endif
