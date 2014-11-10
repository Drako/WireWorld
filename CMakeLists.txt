PROJECT ( WireWorld CXX )
CMAKE_MINIMUM_REQUIRED ( VERSION 2.8.11 )

SET ( CMAKE_INCLUDE_CURRENT_DIR ON )

LIST ( APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules" )

INCLUDE ( CheckCxx11 )
CXX11_REQUIRE_FEATURES (
    auto
    trailingreturn
    nullptr
    lambda
    initlist
    rangefor
)

ADD_SUBDIRECTORY ( src )

