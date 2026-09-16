#include "ECHO.h"
#include "Operators.h"
#include <numeric>
EchoAccumulator echoStep(EchoAccumulator acc, const Polygon& p) {
    acc.result_->push_back(p);
    if (p == acc.target_) {
        acc.result_->push_back(p);
        acc.count_++;
    }
    return acc;
}
int duplicateEcho(std::vector<Polygon>& polygons, const Polygon& target) {
    std::vector<Polygon> result{};
    result.reserve(polygons.size() * 2);
    EchoAccumulator acc{&result, 0, target};
    EchoAccumulator finalAcc = std::accumulate(
        polygons.begin(), polygons.end(), acc, echoStep);
    polygons = std::move(result);
    return finalAcc.count_;
}
