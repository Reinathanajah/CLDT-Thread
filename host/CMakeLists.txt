add_executable(cldt_host
    main.c
    coordinator.c
    experiment_config.c
    twin_model.c
    estimator.c
    fidelity_gate.c
    policy.c
    broker_io.c
    run_recorder.c
)

target_include_directories(cldt_host PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cldt_host PRIVATE cldt_common)

if(MSVC)
    target_compile_options(cldt_host PRIVATE /W4)
else()
    target_compile_options(cldt_host PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
endif()
