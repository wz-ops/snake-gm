#include "food.h"
#include "common.h"
#include <cstdlib>
#include "raylib.h"
using namespace gm;

Food::Food(): m_last_x_(0), m_last_y_(0) {
  m_last_x_ = GetScreenWidth() / CELL_SIZE;
  m_last_y_ = GetScreenHeight() / CELL_SIZE;
  for (int i = 0; i < FD_COUNT; i++) {
    // 避免fd重叠，但只生成FD_COUNT个fd
    const int x = rand() % m_last_x_;
    const int y = rand() % m_last_y_;
    if (x == m_last_x_ && y == m_last_y_) {
      i--;
      continue;
    }
    m_fds_.push_back(Node(x, y));
  }
}

Food::~Food() {

}

void Food::generate() {
  // 绘制圆形fd
  for (auto& node : m_fds_) {
    DrawCircle(node.m_x_ * CELL_SIZE + CELL_SIZE / 2, node.m_y_ * CELL_SIZE + CELL_SIZE / 2, (float)CELL_SIZE / 2, RED);
  }
}