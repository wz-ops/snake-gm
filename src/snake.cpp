#include "snake.h"
#include <memory>
#include "common.h"
using namespace gm;

Snake::Snake(): m_dir_(Down) {
    m_nodes_.push_back(Node(2, 2));
    m_nodes_.push_back(Node(3, 2));
    m_nodes_.push_back(Node(4, 2));
    m_nodes_.push_back(Node(5, 2));
    m_nodes_.push_back(Node(6, 2));
}

Snake::~Snake() {

}

int Snake::move() {
  auto headNode = m_nodes_.back();
  auto tailNode = m_nodes_.front();
  switch (m_dir_) {
    case Snake::Right:
      /*
        * 1、头追加一个
        * 2、尾删除一个
      */
      m_nodes_.push_back(Node(headNode.m_x_ + 1, headNode.m_y_));
      m_nodes_.pop_front();
      break;
    case Snake::Left:
      /*
        * 1、头追加一个，-1
        * 2、尾删除一个
      */
      m_nodes_.push_back(Node(headNode.m_x_ - 1, headNode.m_y_));
      m_nodes_.pop_front();
      break;
    case Snake::Up:
      /*
        * 1、头追加一个，y-1
        * 2、尾删除一个
      */
      m_nodes_.push_back(Node(headNode.m_x_, headNode.m_y_ - 1));
      m_nodes_.pop_front();
      break;
    case Snake::Down:
      /*
        * 1、头追加一个，y+1
        * 2、尾删除一个
      */
      m_nodes_.push_back(Node(headNode.m_x_, headNode.m_y_ + 1));
      m_nodes_.pop_front();
      break;
    default:
      return 1;
  }
  return 1;
}



void Snake::keyboardEvent() {
  // auto curTime = std::chrono::steady_clock::now();
  // // duration_cast用于将时间单位转换为浮点秒数
  // float deltaTime = std::chrono::duration<float>(curTime - m_lastTime_).count();
    // 监听键盘按下上下左右方向键
  if (IsKeyPressed(KEY_UP)) {
    m_dir_ = Up;
  } else if (IsKeyPressed(KEY_DOWN)) {
    m_dir_ = Down;
  } else if (IsKeyPressed(KEY_LEFT)) {
    m_dir_ = Left;
  } else if (IsKeyPressed(KEY_RIGHT)) {
    m_dir_ = Right;
  }
}

void Snake::pushBody(std::shared_ptr<Food> fd) {
  auto tailNode = m_nodes_.front();
  auto headNode = m_nodes_.back();
  bool isSameDir = true;
  auto snakeState = checkStatus(fd);
  if (snakeState.foodCollision) {
    switch (m_dir_) {
      case Left:
      case Right:
        if (snakeState.sameHDir) {
          m_nodes_.push_back(Node(tailNode.m_x_ - 1, tailNode.m_y_));
        } else {
          if (headNode.m_y_ > tailNode.m_y_) {
            m_nodes_.push_back(Node(tailNode.m_x_, tailNode.m_y_ - 1));
          } else {
            m_nodes_.push_back(Node(tailNode.m_x_, tailNode.m_y_ + 1));
          }
        }
        break;
      case Up:
      case Down:
        if (snakeState.sameVDir) {
          m_nodes_.push_back(Node(tailNode.m_x_, tailNode.m_y_ - 1));
        } else {
          if (headNode.m_x_ > tailNode.m_x_) {
            m_nodes_.push_back(Node(tailNode.m_x_ - 1, tailNode.m_y_));
          } else {
            m_nodes_.push_back(Node(tailNode.m_x_ + 1, tailNode.m_y_));
          }
        }
        break;
    }
  }
}

SnakeState Snake::checkStatus(std::shared_ptr<Food> fd) {
  auto headNode = m_nodes_.back();
  std::vector<Node> fds = fd->fds();
  SnakeState snakeState = { false, true, true };
  int headX = headNode.m_x_;
  int headY = headNode.m_y_;
  int index = 0;
  for (const auto& node : fds) {
    if (headNode.m_x_ == node.m_x_ && headNode.m_y_ == node.m_y_) {
      snakeState.foodCollision = true;
      // 移除fd vector
      fds.erase(fds.begin() + index);
    }
    if (headX != headNode.m_x_) (snakeState.sameHDir = false);
    if (headY != headNode.m_y_) (snakeState.sameVDir = false);
    index++;
  }
  return snakeState;
}
