// see https://www.boost.org/doc/libs/1_68_0/libs/test/doc/html/index.html

// only one translation unit should include the following line since it generates main
#define BOOST_TEST_MODULE CalculatorTests

// already did this in cmake
//#define BOOST_TEST_DYN_LINK

// since I installed boost via homebrew, the static lib is available
#include <boost/test/unit_test.hpp>

// single header variant if you don't have the static lib installed
//#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <Calc.hpp>


BOOST_AUTO_TEST_CASE( la ) {
    BOOST_CHECK_EQUAL(1, 1);
}


using namespace gened::calculator;

// you can do one-off testing like this
BOOST_AUTO_TEST_CASE( AddOperation ) {
    Calc *calculator = new Calc();
    BOOST_CHECK_EQUAL(calculator->add(2, 2), 4);
}


// define a test suite. Scroll down and you'll see the end statement
BOOST_AUTO_TEST_SUITE (CalculatorTests)

// a test fixture
class CalcTest {
    
protected:
    // protected so the macros can access it
    Calc *calculator = nullptr;
    int i;
public:
    CalcTest() {
        calculator = new Calc();
    }
    
    ~CalcTest() {
        if (calculator != nullptr) {
            delete calculator;
        }
    }
};

BOOST_AUTO_TEST_CASE (test2) {
    BOOST_TEST_MESSAGE("Auto Testing 2 + 2!");

    // without the fixture
    Calc *calculator = new Calc();
    BOOST_CHECK_EQUAL(calculator->add(2, 2), 4);
}

BOOST_FIXTURE_TEST_CASE(AddTest, CalcTest) {
    BOOST_TEST_MESSAGE("Fixture Testing 2 + 2!");

    
    auto result = calculator->add(2, 2);
    std::cout << "result is " << result << std::endl;
    
    // calculator is a member of the fixture
    BOOST_CHECK_EQUAL(calculator->add(2, 2), 4);
}


BOOST_AUTO_TEST_SUITE_END( )





#if 0
BOOST_AUTO_TEST_SUITE(ExampleTestSuite)

struct TestFixture {
    
    TestFixture() : i( 0 ) {
        
    }
    
    ~TestFixture() {
        printf("finished");
    }
    
    int i;
};

//BOOST_FIXTURE_TEST_CASE(BoostWarnTest, TestFixture) {
//    // Verify i is not 0
//    BOOST_REQUIRE_NO_THROW(i = 4/i);
//    // Verify i is equal to 3
//    BOOST_CHECK(i == 3);
//}


BOOST_FIXTURE_TEST_CASE(BoostWarnTest2, TestFixture)
{
    // Provide a test predicate (i.e. a conditional statement) that evaluates
    // to true to allow the test to pass and will not issue a warning.
    BOOST_WARN(true);
    
    // Provide a test predicate (i.e. a conditional statement) that evaluates
    // to false to force the test to fail and will issue a warning.
    BOOST_WARN(false);
}

BOOST_FIXTURE_TEST_CASE(BoostCheckTest, TestFixture)
{
    // Provide a test predicate (i.e. a conditional statement) that evaluates
    // to true to allow the test to pass and will not indicate a failed test.
    BOOST_CHECK(true);
    
    // Provide a test predicate (i.e. a conditional statement) that evaluates
    // to false to force the test to fail and will indicate a test failure.
    BOOST_CHECK(false);
}

BOOST_FIXTURE_TEST_CASE(BoostRequireTest, TestFixture)
{
    // Provide a test predicate (i.e. a conditional statement) that evaluates
    // to true to allow the test to pass and will not indicate a fatal test error.
    BOOST_REQUIRE(true);
    
    // Provide a test predicate (i.e. a conditional statement) that evaluates
    // to false to force the test to fail and will indicate a fatal test error.
    BOOST_REQUIRE(false);
}

BOOST_FIXTURE_TEST_CASE(BoostWarnMessageTest, TestFixture)
{
    // Provide a test predicate (i.e. a conditional statement) that evaluates
    // to true to allow the test to pass and will not issue a warning with
    // message.
    BOOST_WARN_MESSAGE(true, "This should pass");
    
    // Provide a test predicate (i.e. a conditional statement) that evaluates
    // to false to force the test to fail and will issue a warning with message.
    BOOST_WARN_MESSAGE(false, "This should fail");
}

BOOST_FIXTURE_TEST_CASE(BoostCheckMessageTest, TestFixture)
{
    // Provide a test predicate (i.e. a conditional statement) that evaluates
    // to true to allow the test to pass and not will indicate a failed test
    // with message.
    BOOST_CHECK_MESSAGE(true, "This should pass");
    
    // Provide a test predicate (i.e. a conditional statement) that evaluates
    // to false to force the test to fail and will indicate a test failure
    // with message.
    BOOST_CHECK_MESSAGE(false, "This should fail");
}

BOOST_FIXTURE_TEST_CASE(BoostRequireMessageTest, TestFixture)
{
    // Provide a test predicate (i.e. a conditional statement) that evaluates
    // to true to allow the test to pass and will not indicate a fatal test
    // error with message.
    BOOST_REQUIRE_MESSAGE(true, "This should pass");
    
    // Provide a test predicate (i.e. a conditional statement) that evaluates
    // to false to force the test to fail and will indicate a fatal test error
    // with message.
    BOOST_REQUIRE_MESSAGE(false, "This should fail");
}

BOOST_FIXTURE_TEST_CASE(BoostWarnThrowTest, TestFixture)
{
    // Provide a statement that is expected to throw with a specific exception.
    // Provide the expected exception as the second argument. Since the
    // exception types match, the test will pass and will not issue a warning.
    BOOST_WARN_THROW(
                     throw std::range_error("This should pass"),
                     std::range_error);
    
    // Provide a statement that is expected to throw with a specific exception.
    // Provide the expected exception as the second argument. Since the
    // exception types do not match, the test will not pass and will issue a
    // warning.
    BOOST_WARN_THROW(
                     throw std::range_error("This should fail"),
                     std::underflow_error);
}

BOOST_FIXTURE_TEST_CASE(BoostCheckThrowTest, TestFixture)
{
    // Provide a statement that is expected to throw with a specific
    // exception. Provide the expected exception as the second argument.
    // Since the exception types match, the test will pass and will
    // not issue a test failure.
    BOOST_CHECK_THROW(
                      throw std::range_error("This should pass"),
                      std::range_error);
    
    // Provide a statement that is expected to throw with a specific
    // exception. Provide the expected exception as the second argument.
    // Since the exception types do not match, the test will not pass and
    // will issue a test failure.
    BOOST_CHECK_THROW(
                      throw std::range_error("This should fail"),
                      std::underflow_error);
}

BOOST_FIXTURE_TEST_CASE(BoostRequireThrowTest, TestFixture)
{
    // Provide a statement that is expected to throw with a specific
    // exception. Provide the expected exception as the second argument.
    // Since the exception types match, the test will pass and will not
    // issue a fatal test error.
    BOOST_REQUIRE_THROW(
                        throw std::range_error("This should pass"),
                        std::range_error);
    
    // Provide a statement that is expected to throw with a specific
    // exception. Provide the expected exception as the second argument.
    // Since the exception types do not match, the test will not pass
    // and will issue a fatal test error.
    BOOST_REQUIRE_THROW(
                        throw std::range_error("This should fail"),
                        std::underflow_error);
}

BOOST_FIXTURE_TEST_CASE(BoostWarnNoThrowTest, TestFixture)
{
    // Provide a statement that is not expected to throw. If the statement
    // does not throw, the test will pass and not issue a warning.
    BOOST_WARN_NO_THROW(i = 1);
    
    // Provide a statement that is expected to not throw. If the statement
    // does throw, the test will fail and issue a warning.
    BOOST_WARN_NO_THROW(
                        throw std::range_error("This should fail"));
}

BOOST_FIXTURE_TEST_CASE(BoostCheckNoThrowTest, TestFixture)
{
    // Provide a statement that is not expected to throw. If the statement
    // does not throw, the test will pass and not issue a test failure.
    BOOST_CHECK_NO_THROW(i = 2);
    
    // Provide a statement that is expected to not throw. If the statement
    // does throw, the test will fail and issue a test failure.
    BOOST_CHECK_NO_THROW(
                         throw std::range_error("This should fail"));
}

BOOST_FIXTURE_TEST_CASE(BoostRequireNoThrowTest, TestFixture)
{
    // Provide a statement that is not expected to throw. If the statement
    // does not throw, the test will pass and not issue a test failure.
    BOOST_REQUIRE_NO_THROW(i = 3);
    
    // Provide a statement that is expected to not throw. If the statement
    // does throw, the test will fail and issue a test failure.
    BOOST_REQUIRE_NO_THROW(
                           throw std::range_error("This should fail"));
}


BOOST_AUTO_TEST_SUITE_END()

#endif
