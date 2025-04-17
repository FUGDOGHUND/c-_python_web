#define BOOST_TEST_MODULE BoostTests
#include <boost/test/included/unit_test.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

BOOST_AUTO_TEST_SUITE(BoostIntegrationTests)

BOOST_AUTO_TEST_CASE(TestAsioBasic) {
    boost::asio::io_service io;
    bool callback_called = false;
    
    boost::asio::steady_timer timer(io);
    timer.expires_after(std::chrono::milliseconds(50));
    timer.async_wait([&](const boost::system::error_code&) {
        callback_called = true;
    });
    
    io.run();
    BOOST_CHECK(callback_called);
}

BOOST_AUTO_TEST_CASE(TestThreadCreation) {
    bool thread_ran = false;
    boost::thread thread([&]() {
        thread_ran = true;
    });
    
    thread.join();
    BOOST_CHECK(thread_ran);
}

BOOST_AUTO_TEST_CASE(TestSystemError) {
    try {
        throw boost::system::system_error(
            boost::system::error_code(404, boost::system::system_category()),
            "Test error"
        );
    } catch (const std::exception& e) {
        BOOST_CHECK(std::string(e.what()).find("Test error") != std::string::npos);
    }
}

BOOST_AUTO_TEST_SUITE_END()