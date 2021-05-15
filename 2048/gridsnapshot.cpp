#include "gridsnapshot.h"
#include "grid.h"

GridSnapshot::GridSnapshot(Grid *g)
{
    size = g->size;
    score = g->score;
    largestTile = g->largestTile;
    moves = g->moves;
    emptySpaces = g->emptySpaces;
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (g->grid[r][c] != nullptr) {
                tiles.append(*(g->grid[r][c]));
            }
        }
    }
}
