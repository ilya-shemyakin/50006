#pragma once
#include <vector>
#include "Structs.h"

EchoAccumulator echoStep(EchoAccumulator acc, const Polygon& p);
int duplicateEcho(std::vector<Polygon>& polygons, const Polygon& target);
