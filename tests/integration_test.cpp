#define BOOST_TEST_MODULE IntegrationTests
#include <boost/test/included/unit_test.hpp>
#include "../include/game.h"
#include <thread>
#include <chrono>

BOOST_AUTO_TEST_CASE(TestGameLogic) {
    Game game(20, 20);
    
    // Тест базовой функциональности
    BOOST_CHECK_EQUAL(game.getScore(), 0);
    game.changeDirection("RIGHT");
    game.update();
    BOOST_CHECK_GT(game.getSnake().front().first, 10);
}

BOOST_AUTO_TEST_CASE(TestGameOver) {
    Game game(5, 5);
    
    // Создаем столкновение
    game.changeDirection("RIGHT");
    game.update();
    game.changeDirection("DOWN");
    game.update();
    game.changeDirection("LEFT");
    game.update();
    
    BOOST_CHECK(game.isGameOver());
}

BOOST_AUTO_TEST_SUITE_END()