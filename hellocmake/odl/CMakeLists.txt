
# CmakeLists.txt in Test dir
# Make sure the compiler can find include files from our Hello library.
INCLUDE_DIRECTORIES(${HELLO_SOURCE_DIR}/Hello)
# Add binary called "helloWorld" that is built from the source file "test.cc".
# The extension is automatically found.
ADD_EXECUTABLE(helloWorld test)
# Link the executable to the Hello library.
TARGET_LINK_LIBRARIES(helloWorld Hello)
