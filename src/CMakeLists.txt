# 
#              Copyright (C) 2019 Clovis Durand & Camille Magnan
# 
# -----------------------------------------------------------------------------

# CBitmap source code -------------------------------------
file(GLOB_RECURSE CBITMAP_SOURCES ${CMAKE_SOURCE_DIR}/CBitmap/src/*.cpp)

# CBitmap Library -----------------------------------------
add_library(CBitmap SHARED
    ${CBITMAP_SOURCES}
)

# Header files --------------------------------------------
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/inc/*.hpp)

include_directories(
    ${CMAKE_SOURCE_DIR}/inc
)

# Source files --------------------------------------------
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Target definition ---------------------------------------
add_executable(${CMAKE_PROJECT_NAME}
    ${SOURCES}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    CBitmap
)

# Install -------------------------------------------------
install(TARGETS CBitmap
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/inc
)

install(TARGETS ${CMAKE_PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)
