// Copyright 2021 Elandaev Pavel

#include "../../modules/task_1/elandaev_p_integral_rectangle/rectangle.h"

// double RectangleIntegral(double start, double end, std::function<double(double)> f, double step) {
//    if (end < start)
//        throw "wrong interval";
//    if (step <= 0)
//        throw "wrong splitting: smallest";
//    if (step > end - start)
//        throw "step is biggest";
//    int countstep = static_cast<int>(end - start) / step;
//    double x;
//    double sum = 0.0;
//    for (double i = 0.0; i < countstep; i ++) {
//        x = start + i * step;
//        sum += f(x);
//    }
//    return (step * sum);
// }
void iterplus(std::vector<int> *B, int it, const std::vector<std::vector<double>> p) {
    if (B->operator[](it) == (p[it].size( ) - 1) ) {
        if ((it-1) < 0)
            return;
        B->operator[](it) = 0;
        iterplus(B, --it, p);
    } else {
        B->operator[](it)++;
    }
}
double RecInt(std::vector<double> start, std::vector<double> end, std::function<double(std::vector<double>)> f, double step) {
    std::vector<int> countstep;
    for (int i = 0; i < start.size(); i++) {
        if (end[i] < start[i])
            throw "wrong segment";
        if (step > end[i] - start[i])
            throw "step is biggest";
        countstep.push_back(static_cast<int>((end[i] - start[i]) / step));
    }
    if (step <= 0)
        throw "wrong splitting: smallest";
    std::vector<std::vector<double> > point;
    point.resize(start.size());
    int64_t countTrial = 1;
    for (int i = 0; i < start.size(); i++) {
        for (int j = 0; j < countstep[i]; j++) {
            point[i].push_back(start[i] + j * step);
        }
        countTrial *= point[i].size();
    }
    double sum = 0.0;
    std::vector<int> B(start.size());
    for (int i = 0; i < start.size(); i++) {
        B[i] = 0;
    }
    std::vector<double> Trial(start.size());
    int dim = static_cast<int>(start.size() - 1);
    for (int i = 0; i < countTrial; i++) {
        for (int j = 0; j < start.size(); j++) {
            Trial[j] = point[j][B[j]];
        }
        iterplus(&B, dim, point);
        sum += f(Trial);
    }
    return sum * pow(step, dim+1);
}


