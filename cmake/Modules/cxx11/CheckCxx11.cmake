IF ( NOT CXX11_TESTED )
    # we set this to true here because we have more paths where C++11 is supported than not
    # paths that don't support C++11 will set this back to false
    SET ( CXX11_SUPPORTED TRUE )

    # check compiler and version
    # and enable C++0x/C++11 for compilers that need an explicit option
    # I am looking at you, GCC and Clang...
    IF ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
        IF ( CMAKE_CXX_COMPILER_VERSION VERSION_LESS "" )
            SET ( CXX11_SUPPORTED FALSE )
        ELSEIF ( CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.7.0" )
            SET ( CXX11_DEFINES "-std=c++0x" )
        ELSE ()
            SET ( CXX11_DEFINES "-std=c++11" )
        ENDIF ()
    ELSEIF ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
        # clang seems to support -std=c++11 since forever... might have to adjust this stuff
        SET ( CXX11_DEFINES "-std=c++11" )
    ELSEIF ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
        # versions below Visual C++ 2010 don't support C++11
        IF ( CMAKE_CXX_COMPILER_VERSION VERSION_LESS "16.00" )
            SET ( CXX11_SUPPORTED FALSE )
        ENDIF ()
    ELSE ()
        SET ( CXX11_SUPPORTED FALSE )
    ENDIF ()

    SET ( CXX11_SUPPORTED ${CXX11_SUPPORTED} CACHE INTERNAL "C++11 is supported." )
    SET ( CXX11_DEFINES ${CXX11_DEFINES} CACHE INTERNAL "C++11 compiler definitions" )

    FUNCTION ( CXX11_TEST_FEATURE feature description )
        TRY_COMPILE ( feature_available "${CMAKE_CURRENT_BINARY_DIR}/cxx11" "${CMAKE_CURRENT_LIST_DIR}/cxx11_${feature}.cxx" COMPILE_DEFINITIONS ${CXX11_DEFINES} )
        STRING ( TOUPPER "${feature}" feature_u )
        SET ( CXX11_FEATURE_${feature_u} ${feature_available} CACHE INTERNAL "C++11 feature: ${description}" )
        MESSAGE ( STATUS "> ${description}: ${feature_available}" )
    ENDFUNCTION ()

    IF ( CXX11_SUPPORTED )
        MESSAGE ( STATUS "Checking C++11 support..." )
        CXX11_TEST_FEATURE ( auto "Type inference (auto and decltype keywords)" )
        CXX11_TEST_FEATURE ( trailingreturn "Trailing return types" )
        CXX11_TEST_FEATURE ( nullptr "Null pointer constant (nullptr)" )
        CXX11_TEST_FEATURE ( rangefor "Range based for loops" )
        CXX11_TEST_FEATURE ( lambda "Lambda expressions" )
        CXX11_TEST_FEATURE ( initlist "Initializer lists" )
        CXX11_TEST_FEATURE ( defaultdelete "Defaulted and deleted special functions" )
        CXX11_TEST_FEATURE ( overridefinal "Keywords override and final" )
        CXX11_TEST_FEATURE ( explicitcast "Explicit casting operators" )
        CXX11_TEST_FEATURE ( strongenum "Strongly typed enums" )
        CXX11_TEST_FEATURE ( variadic "Variadic templates" )
        CXX11_TEST_FEATURE ( staticassert "Static assertions" )
        CXX11_TEST_FEATURE ( userliteral "User-defined literals" )
        CXX11_TEST_FEATURE ( constexpr "Constant expressions" )
        CXX11_TEST_FEATURE ( noexcept "Keyword noexcept" )
        CXX11_TEST_FEATURE ( rvalueref "Rvalue references" )
        CXX11_TEST_FEATURE ( tmpalias "Template aliases" )
        MESSAGE ( STATUS "Done." )
    ELSE ()
        MESSAGE ( STATUS "C++11 is not supported by your compiler." )
    ENDIF ()
ENDIF ()
SET ( CXX11_TESTED TRUE CACHE INTERNAL "C++11 features have been tested." )

CONFIGURE_FILE ( "${CMAKE_CURRENT_LIST_DIR}/cxx11_features.hxx.in" "${CMAKE_CURRENT_BINARY_DIR}/cxx11/cxx11_features.hxx" )
INCLUDE_DIRECTORIES ( "${CMAKE_CURRENT_BINARY_DIR}/cxx11" )

FUNCTION ( CXX11_REQUIRE_FEATURES )
    IF ( NOT CXX11_SUPPORTED )
        MESSAGE ( FATAL "Your compiler does not support C++11." )
    ELSE ()
        FOREACH ( feature IN LISTS ARGV )
            STRING ( TOUPPER "${feature}" feature_u )
            IF ( NOT CXX11_FEATURE_${feature_u} )
                MESSAGE ( FATAL "Required C++11 features are missing." )
            ENDIF ()
        ENDFOREACH ()
    ENDIF()
ENDFUNCTION ()
