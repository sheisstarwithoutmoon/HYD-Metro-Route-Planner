# Hyderabad Metro Route Planner

Hyderabad Metro Route Planner is a command-line application that calculates the shortest route between stations on the Hyderabad Metro network using **Dijkstra's algorithm**. Built in **C++**, it supports finding paths with an optional intermediate station, displays **line color changes** (e.g., Red to Blue at Ameerpet), and provides **travel details** such as distance, time, fare, and number of stations. The CLI is enhanced with **metro-line themed color-coded outputs** for an engaging user experience.

---

## Features

- **Shortest Path Calculation**: Implements **Dijkstra's algorithm** to find the optimal route between two Hyderabad Metro stations, with support for an intermediate stop.
- **Line Color Changes**: Detects and displays metro **line transitions** (e.g., Red Line to Blue Line) along the route.
- **Travel Details**: Outputs estimated **distance (in km), travel time (in minutes), fare (in INR), and number of stations**.
- **Metro-Themed CLI**: Features an **color-coded station names** based on metro lines.
- **File-Based Data**: Reads **station names, line colors, and connectivity** from text files (`stationnames.txt`, `colorcodes.txt`, `nodes.txt`).
- **Interactive Menu**: Offers options to **find a route or exit**, with a smooth transition between screens.

---

## Prerequisites

- **C++ Compiler**: GCC (e.g., **MinGW for Windows**) or any **C++11-compatible** compiler.
- **Operating System**: Tested on **Windows** (uses `windows.h` for console manipulation).
- **Required Text Files**: Ensure the following files are in the project directory:
  - `stationnames.txt` (List of station names)
  - `colorcodes.txt` (Metro line colors)
  - `nodes.txt` (Graph representation of the metro network)

---

## Installation & Usage

1. **Clone the repository**:
   ```sh
   git clone https://github.com/sheisstarwithoutmoon/Hyderabad-Metro-Route-Planner.git
   cd Hyderabad-Metro-Route-Planner
   ```

2. **Compile the C++ program**:
   ```sh
   g++ main.cpp -o metro
   ```

3. **Run the program**:
   ```sh
   ./metro  # For Linux/macOS
   metro    # For Windows
   ```

---

## Example Usage

```sh
Enter the starting station: Miyapur
Enter the destination station: Raidurg
Shortest route found:
  Miyapur → JNTU College → KPHB Colony → ... → HITEC City → Raidurg
Total distance: 27.5 km
Estimated travel time: 45 minutes
Fare: ₹60
Number of stations: 15
```

---

## Contributors
