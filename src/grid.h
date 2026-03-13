#ifndef GRID_H
#define GRID_H
#include "common.h"
namespace gm {
  class Grid {
    public:
        Grid() = default;
        ~Grid() = default;
        void DrawGrid();
  };
}
#endif // GRID_H