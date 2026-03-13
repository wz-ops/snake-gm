#include "grid.h"
#include "raylib.h"
using namespace gm;

void Grid::DrawGrid() {
    // -- 横向
    for (int y = 0; y < GetRenderHeight(); y += CELL_SIZE) {
      DrawLine(0, y, GetRenderWidth(), y, GRAY);
    }
    // -- 竖向
    for (int x = 0; x < GetRenderWidth(); x += CELL_SIZE) {
      DrawLine(x, 0, x, GetRenderHeight(), GRAY);
    }
}