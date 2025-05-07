# Multithreaded Shortest Path Graph Algorithm Documentation

## Project Overview

This project implements an All-Pairs Shortest Path (APSP) algorithm for graphs with positive weights. It uses a multithreaded approach to calculate shortest paths between all pairs of nodes in a graph by running Dijkstra's algorithm in parallel. The implementation supports reading graph data from `.gr` files, executing the algorithm with a configurable number of threads, and includes tools for measuring performance and validating correctness.

## Core Components

### Data Structures

- **Binary Heap** (`bh.h`, `bh.c`): A priority queue implementation used by Dijkstra's algorithm.
- **Adjacency List** (`adjlist.h`, `adjlist.c`): Graph representation using adjacency lists.
- **Common Data Types** (`commonnames.h`): Defines key data structures like:
  - `bindij_node`: Represents a node with priority in the binary heap
  - `vector`: A simple dynamic array implementation
  - `adjList`: A list of adjacent nodes with weights
  - `sp_vector`: Stores shortest path data (distances and parent nodes)

### Main Algorithms

- `dijkstra()`: Implements Dijkstra's single-source shortest path algorithm.
- `dijkstra_thread()`: Thread function that runs Dijkstra's algorithm for a subset of nodes.
- `apsp_dijkstra()`: All-pairs shortest path implementation using multiple threads.

### Utility Functions

- `read_adjlist_from_gr()`: Reads a graph from a `.gr` file format.
- `display_mat()`: Displays the distance matrix.
- `display_path()`: Displays the path between two nodes.

## How to Run the Code

1. **Compile the project**: (Assuming a Makefile exists)
   ```
   make all
   ```

2. **Generate a random test graph** (Optional):
   ```
   python gen_random_graph.py --nodes 100 --density 0.1 --weight_min 1 --weight_max 1000 --output tests/test.gr
   ```

3. **Run the main program**:
   ```
   ./bin/test_performance [thread_count] [graph_file]
   ```
   
   For example:
   ```
   ./bin/test_performance 4 tests/test.gr
   ```

4. **For performance testing across multiple configurations**:
   ```
   python performance_driver.py
   ```

5. **For validation testing**:
   ```
   python validation_driver.py
   ```

## Target Files

- **main.c**: Entry point of the application, processes command line arguments and runs the APSP algorithm.
- **test_performance.c**: Focused on measuring execution time with different thread counts and graphs.
- **validation_test.c**: Outputs APSP matrix for correctness verification.
- **tests_bh.c**: Contains unit tests for the binary heap and other components.

## Performance Testing

The `performance_driver.py` script automates testing across different thread counts (1, 2, 4, 8, 16) and input files, producing a CSV file with timing results.

## Validation

The `validation_driver.py` script compares the output of the C implementation with NetworkX's Dijkstra implementation for correctness verification.

## Graph File Format

The program reads `.gr` files in the following format:
- First line: `p sp [number_of_nodes] [number_of_edges]`
- Edge lines: `a [from_node] [to_node] [weight]`

## Notable Implementation Details

- The project uses POSIX threads for parallelization.
- Node numbering in `.gr` files is 1-based but converted to 0-based internally.
- The current implementation only works with directed graphs with positive weights.
- `display_path()` function can be used to trace the actual shortest path between nodes.

This implementation is designed to demonstrate the performance advantages of parallelizing the APSP computation, especially for large graphs.