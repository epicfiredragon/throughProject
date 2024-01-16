cmake_minimum_required(VERSION 3.22)
project(through)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/tools")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Catch REQUIRED)

find_package(Poco REQUIRED COMPONENTS Foundation Net XML Util Zip Crypto)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
set(QTLibs Qt5::Core Qt5::Gui Qt5::Widgets)

set(LIBS PocoNet PocoNetSSL PocoFoundation PocoXML PocoJSON PocoUtil PocoZip PocoCrypto)
set(FILES Solver.cpp
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
        MagicWiget.cpp
        MagicWiget.h)

function(add_catch TARGET)
    add_executable(${TARGET} ${ARGN} ${FILES})
    target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${TARGET} ${LIBS} ${QTLibs} Catch2::Catch2WithMain)
endfunction()


add_catch(test_solver tests/testSolver.cpp)
add_catch(test_processor tests/testFileProcessor.cpp)
add_catch(test_process_handle tests/testProcessAndHandle.cpp)
add_catch(test_rw tests/testReaderAndWriter.cpp)

add_executable(through main.cpp
        ${FILES}
)

target_link_libraries(through ${LIBS} ${QTLibs})
