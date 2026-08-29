set(CLDT_COMMON_SOURCES
    "src/cldt_protocol.c"
    "src/cldt_clock_sync.c"
    "src/cldt_control_profile.c"
    "src/cldt_metrics.c"
    "src/cldt_event_trace.c"
    "src/cldt_auth.c"
    "src/cldt_crc32c.c"
)

if(COMMAND idf_component_register)
    idf_component_register(
        SRCS ${CLDT_COMMON_SOURCES}
        INCLUDE_DIRS "include"
    )
else()
    add_library(cldt_common STATIC ${CLDT_COMMON_SOURCES})
    target_include_directories(cldt_common
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    if(MSVC)
        target_compile_options(cldt_common PRIVATE /W4)
    else()
        target_compile_options(cldt_common PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
    endif()
endif()
