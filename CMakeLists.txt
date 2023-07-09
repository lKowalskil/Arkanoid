cmake_minimum_required(VERSION 3.12)
project(Arkanoid)

add_subdirectory(SDL)
add_subdirectory(SDL_image)
add_subdirectory(SDL_ttf)

include_directories(
  ${PROJECT_SOURCE_DIR}/includes
  ${PROJECT_SOURCE_DIR}/SDL/include
  ${PROJECT_SOURCE_DIR}/SDL_image/include
  ${PROJECT_SOURCE_DIR}/SDL_ttf/include
)

file(GLOB SOURCES "sources/*.cpp")
file(GLOB HEADERS "includes/*.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME}
  "$<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/SDL/Debug/SDL3.lib,${CMAKE_BINARY_DIR}/SDL/Release/SDL3.lib>"
  "$<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/SDL_image/Debug/SDL3_image.lib,${CMAKE_BINARY_DIR}/SDL_image/Release/SDL3_image.lib>"
  "$<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/SDL_ttf/Debug/SDL3_ttf.lib,${CMAKE_BINARY_DIR}/SDL_ttf/Release/SDL3_ttf.lib>"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/SDL/Debug/SDL3.dll,${CMAKE_BINARY_DIR}/SDL/Release/SDL3.dll>"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/SDL_image/Debug/SDL3_image.dll,${CMAKE_BINARY_DIR}/SDL_image/Release/SDL3_image.dll>"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/SDL_ttf/Debug/SDL3_ttf.dll,${CMAKE_BINARY_DIR}/SDL_ttf/Release/SDL3_ttf.dll>"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/assets
		"$<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/Debug/assets,${CMAKE_BINARY_DIR}/Release/assets>"

)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
