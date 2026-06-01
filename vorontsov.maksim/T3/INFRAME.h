#pragma once
#include <vector>
#include "Structs.h"

BoundingBox getPolyBoundingBox(const Polygon& p);
BoundingBox mergeBoundingBoxes(BoundingBox acc, const Polygon& p);
bool isInsideBoundingBox(const Point& p, const BoundingBox& bb);
bool inFrame(const std::vector<Polygon>& polygons, const Polygon& target);
