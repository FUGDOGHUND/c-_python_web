#define BOOST_TEST_MODULE GameTests
#include <boost/test/included/unit_test.hpp>
#include "../include/game.h"

BOOST_AUTO_TEST_CASE(TestGameInitialization) {
    Game game(20, 20);
    BOOST_CHECK_EQUAL(game.getScore(), 0);
    BOOST_CHECK_EQUAL(game.isGameOver(), false);
    BOOST_CHECK_EQUAL(game.getSnake().size(), 1);
}

BOOST_AUTO_TEST_CASE(TestGameOver) {
    Game game(3, 3); // Маленькое поле для теста
    
    // Движемся до стенки
    game.changeDirection("RIGHT");
    game.update(); // (1,0)
    game.update(); // (2,0)
    game.update(); // (3,0) - выход за границы
    
    BOOST_CHECK_MESSAGE(game.isGameOver(), 
        "Game should be over when snake hits the wall");
}
