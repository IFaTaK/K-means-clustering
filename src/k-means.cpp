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

Kmeans::Kmeans(int k_, vector<Point> data_, int n_)
{
    // Initialization of attributes
    k = k_;
    data = data_;
    n = n_;

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


void Kmeans::run() {

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

double Kmeans::silhouetteScore()
{
    double silhouetteScore = 0.0;
    for (Point &point : this->data)
    {
        double a = 0.0;
        double b = __DBL_MAX__;
        int count = 0;  // Count of points in the same cluster as 'point'

        for (Point &otherPoint : this->data)
        {
            if (point.cluster == otherPoint.cluster && point != otherPoint)
            {
                double distance = point.euclideanDistance(otherPoint);
                a += distance;
                count++;
            }
            else if (point.cluster != otherPoint.cluster)
            {
                double distance = point.euclideanDistance(otherPoint);
                if (distance < b)
                {
                    b = distance;
                }
            }
        }

        if (count > 0)
        {
            a /= count;  // Corrected line
            double s = (b - a) / std::max(a, b);
            silhouetteScore += s;
        }
    }
    silhouetteScore /= data.size();
    return silhouetteScore;
}

double Kmeans::calculateInertia()
{
    double inertia = 0.0;
    for (Point &point : this->data)
    {
        double minDistance = __DBL_MAX__;
        for (Point &centroid : this->centroids)
        {
            double distance = point.euclideanDistance(centroid);
            if (distance < minDistance)
            {
                minDistance = distance;
            }
        }
        inertia += pow(minDistance, 2);
    }
    return inertia;
}


// Public methods

void Kmeans::fit(int k_)
{   
    double best_intertia = __DBL_MAX__;
    std::vector<Point> best_centroids;
    std::vector<Point> best_data;

    for (int i = 0; i < this->n; i++) {
        initializeCentroids();
        run();
        double inertia = calculateInertia();

        if (inertia < best_intertia) {
            best_intertia = inertia;
            best_centroids = this->centroids;
            best_data = this->data;
        }
    }

    this->centroids = best_centroids;
    this->data = best_data;
}

void Kmeans::fit()
{   
    this->k = optimalK();
    double best_intertia = __DBL_MAX__;
    std::vector<Point> best_centroids;
    std::vector<Point> best_data;

    for (int i = 0; i < this->n; i++) {
        initializeCentroids();
        run();
        double inertia = calculateInertia();

        if (inertia < best_intertia) {
            best_intertia = inertia;
            best_centroids = this->centroids;
            best_data = this->data;
        }
    }

    this->centroids = best_centroids;
    this->data = best_data;
}

int Kmeans::optimalK() {
    int bestK = 2; // Start with minimum number of clusters
    double bestScore = -1.0; // Initialize best silhouette score

    for (int k = 2; k <= 10; k++) {
        Kmeans kmeans(k, data); // Create Kmeans object with k clusters
        kmeans.run(); // Fit the data

        double score = kmeans.silhouetteScore(); // Calculate silhouette score

        if (score > bestScore) {
            bestScore = score;
            bestK = k;
        }
    }
    return bestK;
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