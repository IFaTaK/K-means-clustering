/**
 * Header file for K-means clustering implementation in C++.
 *
 * Defines Point struct to represent data points, functions for reading/writing
 * point data, and Kmeans class to perform k-means clustering on a dataset.
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
    vector<double> coordinates;
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
        coordinates.push_back(0.0);
        cluster = -1;
    }
    /**
     * Constructor to initialize x and y coordinates of Point.
     * Also initializes cluster to -1 and minDistance to infinity.
     */
    Point(vector<double> coordinates_)
    {
        coordinates = coordinates_;
        cluster = -1;
    }

    /**
     * Calculates the Euclidean distance between this point and the given point p.
     */
    double euclideanDistance(Point p)
    {
        double sum = 0.0;
        for (int i = 0; i < coordinates.size(); i++)
        {
            sum += pow(coordinates[i] - p.coordinates[i], 2);
        }
        return sqrt(sum);
    }
    
    bool operator!=(const Point& other) const {
        return coordinates != other.coordinates;
    }
};

vector<Point> readPoints(string filename);
void writePoints(string filename, vector<Point> points);

class Kmeans
{
private:
    int k;
    int n = 10;
    vector<Point> data;
    vector<Point> centroids;
    void initializeCentroids();
    void updateCentroids();
    void run();
    double silhouetteScore();
    double calculateInertia();
    

public:
    Kmeans(int k_, vector<Point> data_);
    Kmeans(int k_, vector<Point> data_, int n_);
    int optimalK();
    void fit();
    void fit(int k_);
    vector<Point> getPoints();
    vector<Point> getCentroids();
};

#endif // KMEANS_H
