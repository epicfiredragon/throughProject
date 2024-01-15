
cmake_minimum_required(VERSION 3.22)
project(through)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH              "${CMAKE_SOURCE_DIR}/tools/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

find_package(Poco REQUIRED COMPONENTS Foundation Net XML Util Zip Crypto)

add_executable(through main.cpp
        Solver.cpp
        Solver.h
        Writer.cpp
        Writer.h
        Reader.cpp
        Reader.h
        FileInfo.h
        TypeFile.h
        FileProcessor.cpp
        FileProcessor.h
        SolverType.h
        ProcessAndHandleFile.cpp
        ProcessAndHandleFile.h
        exeptions.h
        key.h
        testSolver.cpp
        testSolver.cpp)

target_link_libraries(through PocoNet PocoNetSSL PocoFoundation PocoXML PocoJSON PocoUtil PocoZip PocoCrypto)
