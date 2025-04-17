#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <utility>

class Game {
public:
    Game(int width, int height);
    void reset() {
        snake_.clear();
        snake_.emplace_back(width_ / 2, height_ / 2);
        score_ = 0;
        gameOver_ = false;
        direction_ = "RIGHT";
        spawnFood();
    }
    void changeDirection(const std::string& direction);
    void update();
    bool isGameOver() const;
    int getScore() const;
    const std::vector<std::pair<int, int>>& getSnake() const;
    std::pair<int, int> getFood() const;
    int getWidth() const;
    int getHeight() const;

private:
    void spawnFood();
    bool checkCollision();

    int width_;
    int height_;
    int score_;
    bool gameOver_;
    std::string direction_;
    std::vector<std::pair<int, int>> snake_;
    std::pair<int, int> food_;
};

#endif // GAME_H
