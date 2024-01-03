# K-means Clustering Project

This repository contains a C++ implementation of the K-means clustering algorithm. The project is structured to separate source code, build artifacts, and data files for easy navigation and use.

## Building the Project

Ensure you have CMake installed on your system. To build the project:

1. Navigate to the root directory of the project.
2. Create a `build` directory and navigate into it:
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

Run the implemented Python script (`plot.py`) to visualize the results:

1. Ensure Python is installed on your system.
2. Navigate to the directory containing `plot.py`. If it's in the parent directory of `exec`, use:
   ```bash
   cd ..
   ```
3. Install the required Python packages:
   ```bash
   pip install -r requirements.txt
   ```
4. Run the script:
   ```bash
   python plot.py
   ```
![Plotting result](assets/result.png)
*Plotting result : k-means clustering with 4 clusters using data.csv*

## Data Format

The `data.csv` file should be in a format compatible with the K-means implementation. Typically, this would be a CSV file with numerical data points.

| f1 | f2 | ... | fn |
| :-------: | :-------: | :-------: | :-------: |
| 35.19   | 12.189  | ... | 11.839 |
| 26.288  | 41.718  | ... | 23.832 |
| 0.376   | 15.506  | ... | 13.264 |
| ...     | ...     | ... | ... |
 
Data download from: [ieee-dataport](https://ieee-dataport.org/open-access/gaussian-blobs-varying-numbers-samples-centers-and-features)

After running the program, the results will be written to `output.csv`. This would be a CSV file with the following format: 

| f1 | f2 | ... | fn | cluster |
| :-------: | :-------: | :-------: | :-------: | :-------: |
| 35.19   | 12.189  | ... | 11.839 | 0
| 26.288  | 41.718  | ... | 23.832 | 2
| 0.376   | 15.506  | ... | 13.264 | 0
| ...     | ...     | ... | ... | ...

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
│  ├─ small_data_f2_c3.csv
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