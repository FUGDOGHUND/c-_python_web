#include "game.h"
#include <algorithm>
#include <cstdlib>
#include <string>

Game::Game(int width, int height) 
    : width_(width), height_(height), score_(0), 
      gameOver_(false), direction_("RIGHT") {
    snake_.emplace_back(width_ / 2, height_ / 2);
    spawnFood();
}

void Game::changeDirection(const std::string& direction) {
    if ((direction == "UP" && direction_ != "DOWN") ||
        (direction == "DOWN" && direction_ != "UP") ||
        (direction == "LEFT" && direction_ != "RIGHT") ||
        (direction == "RIGHT" && direction_ != "LEFT")) {
        direction_ = direction;
    }
}

void Game::update() {
    if (gameOver_) return;

    auto head = snake_.front();
    if (direction_ == "UP") head.second--;
    else if (direction_ == "DOWN") head.second++;
    else if (direction_ == "LEFT") head.first--;
    else if (direction_ == "RIGHT") head.first++;

    if (head.first < 0 || head.first >= width_ || 
        head.second < 0 || head.second >= height_) {
        gameOver_ = true;
        return;
    }

    if (std::find(snake_.begin(), snake_.end(), head) != snake_.end()) {
        gameOver_ = true;
        return;
    }

    snake_.insert(snake_.begin(), head);
    if (head == food_) {
        score_++;
        spawnFood();
    } else {
        snake_.pop_back();
    }
}

bool Game::isGameOver() const {
    return gameOver_;
}

int Game::getScore() const {
    return score_;
}

const std::vector<std::pair<int, int>>& Game::getSnake() const {
    return snake_;
}

std::pair<int, int> Game::getFood() const {
    return food_;
}

int Game::getWidth() const {
    return width_;
}

int Game::getHeight() const {
    return height_;
}

void Game::spawnFood() {
    int x, y;
    do {
        x = rand() % width_;
        y = rand() % height_;
        food_ = {x, y};
    } while (std::find(snake_.begin(), snake_.end(), food_) != snake_.end());
}

bool Game::checkCollision() {
    const auto& head = snake_.front();
    if (head.first < 0 || head.first >= width_ || 
        head.second < 0 || head.second >= height_) {
        return true;
    }
    
    for (size_t i = 1; i < snake_.size(); ++i) {
        if (snake_[i] == head) {
            return true;
        }
    }
    
    return false;
}
