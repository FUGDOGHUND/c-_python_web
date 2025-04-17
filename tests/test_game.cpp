#define BOOST_TEST_MODULE GameTests
#include <boost/test/included/unit_test.hpp>
#include "../include/game.h"

BOOST_AUTO_TEST_SUITE(GameLogicTests)

BOOST_AUTO_TEST_CASE(TestInitialization) {
    Game game(20, 20);
    BOOST_CHECK_EQUAL(game.getScore(), 0);
    BOOST_CHECK_EQUAL(game.isGameOver(), false);
    BOOST_CHECK_EQUAL(game.getSnake().size(), 1);
}

BOOST_AUTO_TEST_CASE(TestCollision) {
    Game game(5, 5);
    // Принудительно создаем столкновение
    auto& snake = const_cast<std::vector<std::pair<int,int>>&>(game.getSnake());
    snake.push_back({1,1});
    snake.push_back({1,1});
    game.update();
    BOOST_CHECK(game.isGameOver());
}

BOOST_AUTO_TEST_CASE(TestReset) {
    Game game(20, 20);
    game.changeDirection("UP");
    game.update();
    game.reset();
    BOOST_CHECK_EQUAL(game.getScore(), 0);
    BOOST_CHECK_EQUAL(game.isGameOver(), false);
    BOOST_CHECK_EQUAL(game.getSnake().size(), 1);
}

BOOST_AUTO_TEST_SUITE_END()


