#include <cmath> // sqrt, pow
#include <limits> // std::numeric_limits<double>::max()
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock::now(), std::chrono::system_clock::to_time_t()
#include <algorithm> // std::generate
#include <cstdio> // printf()
#include <iostream>
#include <utility> // std::pair

#include "divide_and_conquer.h"

typedef std::pair<double, double> point_T;
typedef std::pair<point_T, point_T> pointPair_T;

double dist(const point_T& a, const point_T& b){
    return sqrt(pow(b.first - a.first, 2)
              + pow(b.second - a.second, 2));
}

std::pair<double, pointPair_T> brutalSearch(const std::vector<point_T>& P){
    // if there is not enough point
    if (P.size() < 2) {
        return { -1, { { 0, 0 }, { 0, 0 } } };
    }

    double min_dist = std::numeric_limits<double>::max();
    pointPair_T closest_pair = { P[0], P[2]};

    for( auto i = P.begin(); i != P.end(); i++){
        for ( auto j = i + 1; j != P.end(); j++){
            double current_dist = dist(*i, *j);
            if(current_dist < min_dist){
                min_dist = current_dist;
                closest_pair.first = *i;
                closest_pair.second = *j;
            }
        }
    }
    return { min_dist, closest_pair };
}

std::pair<double, pointPair_T> optimizedSearch(const std::vector<point_T>& P,const std::vector<point_T>& Q){
    // avoid corner case
    if(P.size() <= 3){
        return brutalSearch(P);
    }
    // divide the point set into left and right parts.
    auto N = P.size();
    auto PL = std::vector<point_T>();
    auto PR = std::vector<point_T>();
    std::copy(P.begin(), P.begin() + N/2, std::back_inserter(PL));
    std::copy(P.begin() + N/2, P.end(), std::back_inserter(PR));
    double xM = P[(N-1)/2].first; // the middle point x coordinate
    auto QL = std::vector<point_T>();
    auto QR = std::vector<point_T>();
    std::copy_if(Q.begin(), Q.end(), std::back_inserter(QL), [&xM](const point_T& point){
        return point.first <= xM;
    });
    std::copy_if(Q.begin(), Q.end(), std::back_inserter(QR), [&xM](const point_T& point){
        return point.first > xM;
    });

    std::pair<double, pointPair_T> ret1 = optimizedSearch(PL, QL);
    std::pair<double, pointPair_T> ret2 = optimizedSearch(PR, QR);
    std::pair<double, pointPair_T> result = ( ret1.first <= ret2.first )? ret1 : ret2;
    double delta = result.first;
    auto strip = std::vector<point_T>();
    std::copy_if(Q.begin(), Q.end(), std::back_inserter(strip), [&delta, &xM](const point_T& point){
        return std::abs(xM - point.first) < delta;
    });

    for ( auto i = strip.begin(); i != strip.end(); i++ ){
        for ( auto k = i + 1; k != strip.end() &&
        (( k->second - i->second) < delta); k++) {
            auto new_dist = std::abs(dist(*k, *i));
            if ( new_dist < result.first) {
                result = { new_dist, { *k, *i } };
            }
        }
    }
    return result;
}

void print_result(const std::pair<double, pointPair_T>& result) {
    point_T a = result.second.first;
    point_T b = result.second.second;
    std::printf("Mini distance is %.1f; Points: (%.1f, %.1f), (%.1f, %.1f)\n",
                result.first, a.first, a.second, b.first, b.second);
}

void example(){
    std::default_random_engine re(std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now() ) );
    std::uniform_real_distribution<double> urd(-100.0, 100.0);

    std::vector<point_T> P(100);
    std::generate(P.begin(), P.end(), [&urd, &re]() {
        return point_T { urd(re), urd(re)};
    });

    std::pair<double, pointPair_T> answer = brutalSearch(P);
    std::cout << "Brute: ";
    print_result(answer);

    std::sort( P.begin(), P.end(), [](const point_T& a, const point_T& b) {
        return a.first < b.first;
    });
    auto Q = P;
    std::sort( Q.begin(), Q.end(), [](const point_T& a, const point_T& b) {
        return a.second < b.second;
    });

    answer = optimizedSearch(P, Q);
    std::cout << "Optimized: ";
    print_result(answer);
}
