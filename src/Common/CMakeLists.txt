set(OGRE_SAMPLES_COMMON_LIBRARY "OgreSamplesCommon")

# Sources

include_directories(${OGRE_INCLUDE_DIRS})

file( GLOB_RECURSE SOURCE_FILES ./*.cpp )
file( GLOB_RECURSE HEADER_FILES ./*.hpp )

ogre_add_component_include_dir(Hlms/Pbs)
ogre_add_component_include_dir(Hlms/Unlit)
ogre_add_component_include_dir(Hlms/Common)

add_library(${OGRE_SAMPLES_COMMON_LIBRARY} STATIC ${SOURCE_FILES} ${HEADER_FILES})

link_directories(${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${OGRE_SAMPLES_COMMON_LIBRARY} ${SDL2_LIBRARY} ${OGRE_HlmsPbs_LIBRARIES} ${OGRE_HlmsUnlit_LIBRARIES})
