target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    Settings/Settings.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ui
    Settings
)

add_subdirectory(ui)
target_link_libraries(ui PUBLIC App)

add_library(App INTERFACE)
target_link_libraries(App INTERFACE ui)
