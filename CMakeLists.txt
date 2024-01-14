cmake_minimum_required(VERSION 3.22)
project(through)

set(CMAKE_CXX_STANDARD 20)

find_package(Poco REQUIRED COMPONENTS Foundation Net XML Util Zip)

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
        key.h)

target_link_libraries(through PocoNet PocoNetSSL PocoFoundation PocoJSON PocoUtil PocoZip PocoCrypto)
