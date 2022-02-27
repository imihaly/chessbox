cmake_minimum_required(VERSION 3.22)

project(Chessbox)
set(CMAKE_CXX_STANDARD 14)

set(LIB_SOURCES
    lib/chessbox.hpp
    lib/Color.cpp
    lib/Color.hpp
    lib/Control.cpp
    lib/Control.hpp
    lib/Direction.cpp
    lib/Direction.hpp
    lib/FEN.cpp
    lib/FEN.hpp
    lib/BB.cpp
    lib/BB.hpp
    lib/Move.cpp
    lib/Move.hpp
    lib/Movecheck.cpp
    lib/Movecheck.hpp
    lib/Movegen.cpp
    lib/Movegen.hpp
    lib/Piece.cpp
    lib/Piece.hpp
    lib/Position.cpp
    lib/Position.hpp
    lib/Square.cpp
    lib/Square.hpp
    lib/Squares.cpp
    lib/Squares.hpp
    lib/Step.cpp
    lib/Step.hpp
    lib/Generators/AdjacentsGenerator.hpp
    lib/Generators/DirectionsGenerator.hpp
    lib/Generators/FileGenerator.hpp
    lib/Generators/KnightMoveGenerator.hpp
    lib/Generators/LineGenerator.hpp
    lib/Generators/PawnCaptureGenerator.hpp
    lib/Generators/PawnMoveGenerator.hpp
    lib/Generators/RangeGenerator.hpp
    lib/Generators/RankGenerator.hpp
    lib/Generators/SquareGenerator.hpp
    )

message("libfiles: ${LIB_SOURCES}")
add_library(cbox STATIC ${LIB_SOURCES})

# unit tests
add_subdirectory(tests/unit_tests/tau)
include_directories(tests/unit_tests/tau lib)

set (TEST_SOURCES
    tests/unit_tests/ColorTests.cpp
    tests/unit_tests/ControlTests.cpp
    tests/unit_tests/DirectionTests.cpp
    tests/unit_tests/FENTests.cpp
    tests/unit_tests/BBTests.cpp
    tests/unit_tests/MoveTests.cpp
    tests/unit_tests/MovecheckTests.cpp
    tests/unit_tests/MovegenTests.cpp
    tests/unit_tests/PieceTests.cpp
    tests/unit_tests/PositionTests.cpp
    tests/unit_tests/SquareTests.cpp
    tests/unit_tests/SquaresTests.cpp
    tests/unit_tests/StepsTests.cpp
    tests/unit_tests/UnitTesting.cpp
    tests/unit_tests/UnitTesting.hpp
    tests/unit_tests/main.cpp)
    
add_executable(cbox_tests ${TEST_SOURCES})
target_link_libraries(cbox_tests cbox)
add_custom_target(unit_tests COMMAND cbox_tests)


set(PERF_TEST_SOURCES
    tests/perf_tests/Benchmark.cpp
    tests/perf_tests/Benchmark.hpp
    tests/perf_tests/main.cpp)
add_executable(cbox_perf_tests ${PERF_TEST_SOURCES})
target_link_libraries(cbox_perf_tests cbox)
add_custom_target(perf_tests COMMAND cbox_perf_tests)
