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
        for (int j = 0; j < this->data[0].coordinates.size(); j++) {
            newCentroid.coordinates.push_back(0.0);
        }
        int count = 0;
        for (Point p : this->data)
        {
            if (p.cluster == i)
            {
                for (int j = 0; j < this->data[0].coordinates.size(); j++) {
                    newCentroid.coordinates[j] += p.coordinates[j];
                }
                count++;
            }
        }
        if (count > 0)
        {
            for (int j = 0; j < this->data[0].coordinates.size(); j++) {
                newCentroid.coordinates[j] /= count;
            }
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

vector<Point> readPoints(string filename)
{
    vector<Point> points;
    string line;
    ifstream file(filename);

    if (file.is_open())
    {
        getline(file, line); // read header line

        int numDimensions = 0;
        stringstream headerStream(line);
        string headerBit;
        while (getline(headerStream, headerBit, ','))
        {
            numDimensions++;
        }
        while (getline(file, line))
        {
            vector<double> values(numDimensions);
            stringstream lineStream(line);
            string bit;

            for (int i = 0; i < numDimensions; i++)
            {
                getline(lineStream, bit, ',');
                values[i] = stod(bit);
            }

            Point p(values);
            points.push_back(p);
        }

        file.close();
    }
    else
    {
        cout << "Unable to open file\n";
    }
    return points;
}

void writePoints(string filename, vector<Point> points) {
    ofstream file(filename);
    for (int i=0; i < points[0].coordinates.size(); i++) {
        file << "f" << i+1 << ",";
    }
    file << "cluster" << endl;
    if (file.is_open()) {
        for (Point p : points)
        {
            for (double coordinate : p.coordinates) {
                file << coordinate << ",";
            }
            file << p.cluster << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file";
    }
}