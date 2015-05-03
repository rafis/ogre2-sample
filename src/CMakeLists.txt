# Configure Samples build

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Common)
include_directories(${SDL2_INCLUDE_DIR})

add_subdirectory(Common)

set( OGRE_SAMPLES_LIBRARIES "OgreSamplesCommon" ${OGRE_Overlay_LIBRARIES} )

add_subdirectory(${PROJECT_NAME})
