#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Polygon.h"

// COUNT команды
int countEven(const std::vector<Polygon>& figures);
int countOdd(const std::vector<Polygon>& figures);
int countByVertexCount(const std::vector<Polygon>& figures, int vertexCount);

// MAX/MIN команды
double maxArea(const std::vector<Polygon>& figures);
int maxVertexCount(const std::vector<Polygon>& figures);
double minArea(const std::vector<Polygon>& figures);
int minVertexCount(const std::vector<Polygon>& figures);

// AREA команды
double sumAreaEven(const std::vector<Polygon>& figures);
double sumAreaOdd(const std::vector<Polygon>& figures);
double sumAreaByVertexCount(const std::vector<Polygon>& figures, int vertexCount);
double meanArea(const std::vector<Polygon>& figures);

// Команда MAXSEQ (вариант 11)
int maxConsecutiveEqual(const std::vector<Polygon>& figures, const Polygon& target);

// Команда PERMS (вариант 11)
int countPermutations(const std::vector<Polygon>& figures, const Polygon& target);

#endif
