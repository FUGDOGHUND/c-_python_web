#include "crow.h"
#include "game.h"
#include <memory>
#include <fstream>
#include <string>

std::string read_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        return "";
    }
    return std::string((std::istreambuf_iterator<char>(file)), 
                      std::istreambuf_iterator<char>());
}

int main() {
    crow::SimpleApp app;
    auto game = std::make_shared<Game>(20, 20);

    // Главная страница
    CROW_ROUTE(app, "/")([&app]{
        auto page = read_file("web/index.html");
        if (page.empty()) {
            return crow::response(404, "index.html not found");
        }
        return crow::response(page);
    });

    // Состояние игры
    CROW_ROUTE(app, "/state").methods("GET"_method)([&game]{
        crow::json::wvalue result;
        result["score"] = game->getScore();
        result["gameOver"] = game->isGameOver();
        
        auto& snake = game->getSnake();
        crow::json::wvalue::list snakeJson;
        for (const auto& segment : snake) {
            crow::json::wvalue segmentJson;
            segmentJson["x"] = segment.first;
            segmentJson["y"] = segment.second;
            snakeJson.push_back(std::move(segmentJson));
        }
        result["snake"] = std::move(snakeJson);
        
        auto food = game->getFood();
        result["food"]["x"] = food.first;
        result["food"]["y"] = food.second;
        
        return result;
    });

    // Управление игрой
    CROW_ROUTE(app, "/control").methods("POST"_method)([&game](const crow::request& req){
        auto data = crow::json::load(req.body);
        
        if (data.has("direction")) {
            game->changeDirection(data["direction"].s());
            game->update();
        }
        else if (data.has("action") && std::string(data["action"].s()) == "restart") {
            game->reset();
        }
        
        return crow::response(200);
    });

    // Статические файлы
    CROW_ROUTE(app, "/<string>")([&app](const crow::request& req, std::string filename){
        if (filename == "script.js") {
            auto js = read_file("web/script.js");
            if (js.empty()) return crow::response(404);
            auto res = crow::response(js);
            res.set_header("Content-Type", "application/javascript");
            return res;
        }
        else if (filename == "style.css") {
            auto css = read_file("web/style.css");
            if (css.empty()) return crow::response(404);
            auto res = crow::response(css);
            res.set_header("Content-Type", "text/css");
            return res;
        }
        return crow::response(404);
    });

    app.port(8080).multithreaded().run();
}
