#ifndef SNAKE_H
#define SNAKE_H
#include <deque>
#include <chrono>
#include <memory>
#include "Node.h"
#include "food.h"
namespace gm {
  struct SnakeState {
    bool foodCollision;
    bool sameHDir;
    bool sameVDir;
  };
  class Snake {
    public:
      enum Dir {
        Up,
        Down,
        Left,
        Right
      };
      Snake();
      ~Snake();
      void keyboardEvent();
      int move();
      // 碰撞fd
      SnakeState checkStatus(std::shared_ptr<Food> fd);
      void pushBody(std::shared_ptr<Food> fd);
      std::deque<Node>& body() { return m_nodes_; };
      std::deque<Node> m_nodes_;
      Dir m_dir_;
      std::chrono::time_point<std::chrono::steady_clock> m_lastTime_ = std::chrono::steady_clock::now();
    private:
  };
}
#endif // SNAKE_H