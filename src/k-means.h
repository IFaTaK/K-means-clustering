/**
 * Header file defining Point struct and related functions for
 * representing points in 2D space and calculating distances.
 */
#ifndef KMEANS_H
#define KMEANS_H

#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/**
 * Struct to represent a point in 2D space. Contains coordinates x and y,
 * cluster assignment, and minimum distance to assigned cluster.
 *
 * Provides constructor for initializing coordinates, and euclideanDistance()
 * method to calculate distance between two points.
 */
struct Point
{
    double x, y;
    int cluster;

    /**
     * Default constructor for Point.
     * Initializes x and y to 0.0, cluster to -1, and minDistance to infinity.
     *
     * Constructor with x and y coordinates.
     * Initializes x and y to the given values, cluster to -1,
     * and minDistance to infinity.
     */
    Point()
    {
        x = 0.0;
        y = 0.0;
        cluster = -1;
    }
    /**
     * Constructor to initialize x and y coordinates of Point.
     * Also initializes cluster to -1 and minDistance to infinity.
     */
    Point(double x_, double y_)
    {
        x = x_;
        y = y_;
        cluster = -1;
    }

    /**
     * Calculates the Euclidean distance between this point and the given point p.
     */
    double euclideanDistance(Point p)
    {
        return sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));
    }
};

vector<Point> readPoints(string filename);
void writePoints(string filename, vector<Point> points);

class Kmeans
{
    private:
        int k;
        vector<Point> data;
        vector<Point> centroids;
        void initializeCentroids();
        void updateCentroids();
    public:
        Kmeans(int k_, vector<Point> data_);
        void fit();
        vector<Point> getPoints();
        vector<Point> getCentroids();
};

#endif // KMEANS_H
