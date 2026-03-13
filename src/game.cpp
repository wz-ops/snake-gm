#include "Game.h"
#include <thread>
#include "raylib.h"
using namespace gm;

Game::Game(): m_gm_status_(true) {
    // 创建窗口
    InitWindow(300, 300, "SnakeGM");
    // 创建蛇
    m_snake_ = std::make_shared<Snake>();
    // 创建fd
    m_food_ = std::make_shared<Food>();
}

Game::~Game() {
    // 销毁窗口
    CloseWindow();
}

void Game::Draw() {
    // 绘制帧率
    SetTargetFPS(60);
    // 绘制网格
    DrawGrid();
    // 绘制fd
    m_food_->generate();
    // 绘制snake
    auto& body = (*m_snake_).body();
    for (auto& node : body) {
        DrawRectangle(node.m_x_ * CELL_SIZE, node.m_y_ * CELL_SIZE + 1, 9, 9, GREEN);
    }
}

int Game::Run() {
    // main loop
    while (!WindowShouldClose()) {
        BeginDrawing(); // 开始绘图
        ClearBackground(RAYWHITE); // 清空背景
        Draw();
        if (isEdgeCollision()) {
            // 弹窗提示 - 游戏结束
            // 绘制遮罩
            DrawRectangleRec({0,0,(float)GetScreenWidth(),(float)GetScreenHeight()}, Fade(BLACK, 0.5f));
            // 绘制text
            DrawText("Game Over", GetScreenWidth() / 2 - MeasureText("Game Over", 50) / 2, GetScreenHeight() / 2 - 50, 50, RED);
            // 禁止运行下边语句
            m_gm_status_ = false;
        };
        EndDrawing(); // 结束绘图
        if (m_gm_status_) {
            // 键盘事件
            m_snake_->keyboardEvent();
            // 更新snake
            Update(GetFrameTime());
            // fd eat
            std::thread([&](){
              m_snake_->pushBody(m_food_);
            }).join();
        }
    }
    return 0;
}

void Game::Update(float ft) {
    if (m_frameCount_ % 3 == 0)
        m_snake_->move();
    m_frameCount_++;
}

bool Game::isEdgeCollision() {
    // 获取snake head
    auto headNode = m_snake_ -> body().back();
    // 左边缘
    if (headNode.m_x_ <= 0) return true;
    // 右边缘
    if (headNode.m_x_ >= GetRenderWidth() / CELL_SIZE) return true;
    // 上边缘
    if (headNode.m_y_ <= 0) return true;
    // 下边缘
    if (headNode.m_y_ >= GetRenderHeight() / CELL_SIZE) return true;
    return false;
}