// 1、随机生成fd

#ifndef FOOD_H
#define FOOD_H
#include <vector>
#include "Node.h"
namespace gm {
  class Food {
    public:
      Food();
      ~Food();
      void generate();
      std::vector<Node> fds() { return m_fds_; }
    private:
      std::vector<Node> m_fds_;
      int m_last_x_;
      int m_last_y_;
  };
}
#endif // FOOD_H