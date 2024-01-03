#include "src/k-means.h"

int main() {
    // Read data points from file
    // and store them in a vector
    cout << "Reading data points from file...\n";
    vector<Point> points = readPoints("../data/data.csv");

    // Initialize the k-means object
    cout << "Initializing k-means object...\n";
    Kmeans kmeans(4, points);

    // Run the k-means algorithm
    cout << "Running k-means algorithm...\n";
    kmeans.fit();

    // Write the results to file
    cout << "Writing results to file...\n";
    writePoints("../data/output.csv", kmeans.getPoints());
}