#ifndef GAME_H
#define GAME_H
#include "common.h"
#include "grid.h"
#include "snake.h"
#include <memory>
#include "food.h"
namespace gm {
  class Game: public Grid {
    public:
      Game();
      ~Game();
      int Run();
      void Draw();
      void Update(float);
      std::shared_ptr<gm::Snake> m_snake_;
      int m_frameCount_;
      std::shared_ptr<gm::Food> m_food_;
    private:
      bool m_gm_status_;
      // 边缘碰撞
      bool isEdgeCollision();
      // 自我碰撞
      bool isSelfCollision();
      // 食物碰撞
      bool isFoodCollision();
  };
}
#endif // GAME_H