#include "k-means.h"

// Constructor
Kmeans::Kmeans(int k_, vector<Point> data_)
{
    // Initialization of attributes
    k = k_;
    data = data_;

    // Call centroid initialization method
    initializeCentroids();
}

// Private methods

void Kmeans::initializeCentroids()
{
    // Code to randomly initialize the k centroids
    // from the data points
    vector<Point> centroids;
    srand(time(0));
    for (int i = 0; i < k; i++)
    {
        centroids.push_back(this->data[rand() % this->data.size()]);
    }
    this->centroids = centroids;
}

void Kmeans::updateCentroids()
{
    // Code to recompute the centroids
    // by averaging points of each cluster
    vector<Point> newCentroids;
    for (int i = 0; i < k; i++) {
        Point newCentroid;
        newCentroid.x = 0;
        newCentroid.y = 0;
        int count = 0;
        for (Point p : this->data)
        {
            if (p.cluster == i)
            {
                newCentroid.x += p.x;
                newCentroid.y += p.y;
                count++;
            }
        }
        if (count > 0)
        {
            newCentroid.x /= count;
            newCentroid.y /= count;
        }
        newCentroids.push_back(newCentroid);
    }
    this->centroids = newCentroids;
}

// Public methods

void Kmeans::fit()
{

    bool converged = false;

    while (!converged)
    {
        vector<Point> oldCentroids = this->centroids;

        // Assign each point to closest cluster
        for (int i = 0; i < this->data.size(); i++) {
            double minDistance = __DBL_MAX__;
            int cluster = -1;
            for (int j = 0; j < k; j++)
            {
                double distance = this->data[i].euclideanDistance(this->centroids[j]);
                if (distance < minDistance)
                {
                    minDistance = distance;
                    cluster = j;
                }
            }
            this->data[i].cluster = cluster; // Update the cluster of the point in data
        }

        // Update the centroids
        updateCentroids();

        // Check convergence
        double maxDistance = 0;
        for (int i = 0; i < k; i++) {
            double distance = oldCentroids[i].euclideanDistance(this->centroids[i]);
            if (distance > maxDistance)
            {
                maxDistance = distance;
            }
        }
        if (maxDistance < 0.0001) {converged = true;}
    }
}

vector<Point> Kmeans::getPoints() {
    // Return the points
    return data;
}

vector<Point> Kmeans::getCentroids()
{
    // Return current centroids
    return centroids;
}

vector<Point> readPoints(string filename) {
    vector<Point> points;
    string line;
    ifstream file(filename);

    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            double x, y;
            stringstream lineStream(line);
            string bit;
            getline(lineStream, bit, ',');
            x = stod(bit);
            getline(lineStream, bit, ',');
            y = stod(bit);
            points.push_back(Point(x, y));
        }
        file.close();
    } else {
        cout << "Unable to open file\n";
    }
    return points;
}

void writePoints(string filename, vector<Point> points) {
    ofstream file(filename);
    file << "x,y,cluster" << endl;
    if (file.is_open()) {
        for (Point p : points)
        {
            file << p.x << "," << p.y << "," << p.cluster << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file";
    }
}