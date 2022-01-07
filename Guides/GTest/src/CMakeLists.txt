add_library(DummyLib "Dummy/DummyClass.cpp")

add_gtest_test(simple_test "SimpleTest.cpp" DummyLib)
add_gtest_test(fixture_test "FixtureTest.cpp" DummyLib)
add_gtest_test(mock_test "MockTest.cpp" DummyLib)