# K-means Clustering Project

This repository contains a C++ implementation of the K-means clustering algorithm. The project is structured to separate source code, build artifacts, and data files for easy navigation and use.

## Building the Project

Ensure you have CMake installed on your system. To build the project:

1. Navigate to the root directory of the project.
2. Create a build directory and navigate into it:
   ```bash
   mkdir build && cd build
   ```
3. Run CMake and then make:
   ```bash
   cmake ..
   make
   ```
4. The executable will be located in the `exec/` directory.

## Running the Program

### On Unix-based Systems (Linux, macOS)

After building, run the K-means clustering program:
   ```bash
   cd ../exec/
   ./kmeans
   ```

### On Windows
After building,run the K-means clustering program:
   ```bash
   cd ../exec/
   kmeans.exe
   ```

## Plotting the Results

If you have implemented a Python script (`plot.py`) to visualize the results:

1. Ensure Python is installed on your system.
2. Install the required Python packages:
   ```bash
   pip install -r requirements.txt
   ```
3. Run the script:
   ```bash
   python plot.py
   ```

## Data Format

The `data.csv` file should be in a format compatible with your K-means implementation. Typically, this would be a CSV file with numerical data points.

| x | y |
| :-------: | :-------: |
| 35.19   | 12.189  |
| 26.288  | 41.718  |
| 0.376   | 15.506  |
| ...     | ...    |


## Contributing

Feel free to fork this repository and submit pull requests to contribute to this project.

## License

This project is licensed under the terms of the GNU General Public License.

## Project Structure

```plaintext
K-means clustering
├─ src
│  ├─ k-means.cpp
│  └─ k-means.h
├─ data
│  ├─ data.csv
│  └─ output.csv
├─ exec
│  └─ kmeans
├─ build
├─ CMakeLists.txt
├─ LICENSE
├─ README.md
├─ requirements.txt
├─ main.cpp
└─ plot.py
```