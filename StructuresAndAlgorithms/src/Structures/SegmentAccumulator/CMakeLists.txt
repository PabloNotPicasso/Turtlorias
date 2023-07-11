build_library(SegmentTree)
build_library(SegmentSqrt)
build_library(SegmentBrute)

set(TARGET SegmentAccumulator)
set(SEGMENT_LIBS SegmentTree SegmentSqrt SegmentBrute)

add_gtest_test(${TARGET}_test "test/${TARGET}Test.cpp" ${SEGMENT_LIBS})