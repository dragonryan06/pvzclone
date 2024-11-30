#include "PlantPlacement.h"

// Constructor to initialize the grid
PlantPlacement::PlantPlacement() {
    // Initialize the grid with false values meaning no plant placed
    grid.resize(gridRows, std::vector<bool>(gridCols, false));
}

// Check if a point is inside the plant placement area
bool PlantPlacement::isInsideGrid(int x, int y) {
    return x >= placementStartX && x <= placementEndX && y >= placementStartY && y <= placementEndY;
}

// Get the grid cell corresponding to a touch point
bool PlantPlacement::getGridCell(int x, int y, int &row, int &col) {
    if (!isInsideGrid(x, y)) {
        return false;
    }
    row = (y - placementStartY) / cellHeight;
    col = (x - placementStartX) / cellWidth;
    return true;
}

// Place a plant on the grid and update the grid state
void PlantPlacement::placePlant(Plant &plant, int row, int col) {
    if (grid[row][col]) {
        // This cell is already occupied by a plant
        return;
    }

    // Update the grid to mark this cell as occupied
    grid[row][col] = true;

    // Set the plant's position based on the row and column
    plant.x = placementStartX + col * cellWidth;
    plant.y = placementStartY + row * cellHeight;

    // Now add plant