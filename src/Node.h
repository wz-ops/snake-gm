#ifndef NODE_H
#define NODE_H
namespace gm {

  class Node {
    public:
      Node();
      Node(int x, int y);
      ~Node();
      int m_x_;
      int m_y_;
  };
}
#endif // NODE_H