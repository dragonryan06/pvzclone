#ifndef PLANTPLACEMENT_H
#define PLANTPLACEMENT_H

#include "engine/input.h"
#include <vector>
#include <memory>
#include <iostream>

// Have to define Plant here, not sure if I need to match it or make it different from the entity definittion
class Plant {
public:
    int x, y;        
    std::string type; 
};

// Creating the grid dimensions
class PlantPlacement {
    private:
        const int placementStartX = 9;
        const int placementStartY = 36;
        const int placementEndX = 311;
        const int placementEndY = 232;
        const int gridRows = 5;
        const int gridCols = 9;
        const int cellWidth = (placementEndX - placementStartX) / gridCols;
        const int cellHeight = (placementEndY - placementStartY) / gridRows;

        std::vector<std::vector<bool>> grid;

    public:
        // Defining functions for plant placement
        PlantPlacement();
        bool isInsideGrid(int x, int y);
        bool getGridCell(int x, int y, int &row, int &col);
        void placePlant(Plant &plant, int row, int col);
};

#endif