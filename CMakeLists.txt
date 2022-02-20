cmake_minimum_required(VERSION 3.22)

project(Chessbox)
set(CMAKE_CXX_STANDARD 14)

set(LIB_SOURCES
    lib/ChessBasics.hpp
    lib/Color.cpp
    lib/Color.hpp
    lib/Control.cpp
    lib/Control.hpp
    lib/Direction.cpp
    lib/Direction.hpp
    lib/FEN.cpp
    lib/FEN.hpp
    lib/Geometry.cpp
    lib/Geometry.hpp
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
    lib/deps.h
    lib/Generators/AdjacentsGenerator.hpp
    lib/Generators/DirectionsGenerator.hpp
    lib/Generators/FileGenerator.hpp
    lib/Generators/KnightMoveGenerator.hpp
    lib/Generators/LinesGenerator.hpp
    lib/Generators/PawnCaptureGenerator.hpp
    lib/Generators/PawnMoveGenerator.hpp
    lib/Generators/RangesGenerator.hpp
    lib/Generators/RankGenerator.hpp
    lib/Generators/SquareGenerator.hpp
    )

message("libfiles: ${LIB_SOURCES}")
add_library(cbox STATIC ${LIB_SOURCES})

# unit tests
add_subdirectory(Testing/tau)
include_directories(Testing/tau lib)

set (TEST_SOURCES
    Testing/ColorTests.cpp
    Testing/ControlTests.cpp
    Testing/DirectionTests.cpp
    Testing/FENTests.cpp
    Testing/GeometryTests.cpp
    Testing/MoveTests.cpp
    Testing/MovecheckTests.cpp
    Testing/MovegenTests.cpp
    Testing/PieceTests.cpp
    Testing/PositionTests.cpp
    Testing/SquareTests.cpp
    Testing/SquaresTests.cpp
    Testing/StepsTests.cpp
    Testing/UnitTesting.cpp
    Testing/UnitTesting.hpp
    Testing/main.cpp)
    
add_executable(cbox_tests ${TEST_SOURCES})
target_link_libraries(cbox_tests cbox)
add_custom_target(unit_tests COMMAND cbox_tests)

# load tests
set (LOAD_TEST_SOURCES
    Loadtesting/Gentest.cpp
    Loadtesting/Gentest.hpp
    Loadtesting/Movedecoder.cpp
    Loadtesting/Movedecoder.hpp
    Loadtesting/Movetest.cpp
    Loadtesting/Movetest.hpp
    Loadtesting/main.cpp)
    
add_executable(cbox_load_tests ${LOAD_TEST_SOURCES})
target_link_libraries(cbox_load_tests cbox)
add_custom_target(load_tests COMMAND cbox_load_tests)


set(PERF_TEST_SOURCES
    Benchmarking/Benchmark.cpp
    Benchmarking/Benchmark.hpp
    Benchmarking/main.cpp)
add_executable(cbox_perf_tests ${PERF_TEST_SOURCES})
target_link_libraries(cbox_perf_tests cbox)
add_custom_target(perf_tests COMMAND cbox_perf_tests)
