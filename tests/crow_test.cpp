#include <crow.h>
#include <boost/asio.hpp>
#define BOOST_TEST_MODULE CrowTests
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(TestCrowServer) {
    crow::SimpleApp app;
    
    CROW_ROUTE(app, "/test")([](){
        return "OK";
    });
    
    std::thread server_thread([&](){
        app.port(18080).multithreaded().run();
    });
    
    // Даем серверу время на запуск
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    // Тестируем запрос
    boost::asio::io_service io;
    boost::asio::ip::tcp::socket socket(io);
    socket.connect(boost::asio::ip::tcp::endpoint(
        boost::asio::ip::address::from_string("127.0.0.1"), 18080));
    
    std::string request = "GET /test HTTP/1.1\r\n\r\n";
    boost::asio::write(socket, boost::asio::buffer(request));
    
    char response[1024];
    size_t len = socket.read_some(boost::asio::buffer(response));
    
    app.stop();
    server_thread.join();
    
    BOOST_CHECK(std::string(response, len).find("200 OK") != std::string::npos);
}