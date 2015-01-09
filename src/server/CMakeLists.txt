
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

file(GLOB_RECURSE sources_Network Network/*.cpp Network/*.h)
file(GLOB sources_localdir *.cpp *.h)

set(server_SRCS
  ${server_SRCS}
  ${sources_network}
)

set(main_server_SRCS
 # ${sources_Network}
  ${sources_localdir}
  main.cpp
)

add_subdirectory(Network)



if( WIN32 )
  set(main_SRCS
    ${main_SRCS}
    ${sources_windows_Debugging}
 )   
 if (MSVC)
   set(main_SRCS
     ${main_SRCS}
     #kuromashiro.rc
  )
 endif ()
endif ()




ADD_LIBRARY(main_server
main.cpp
)

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/client/Network
)

ADD_LIBRARY(server
  Network/CSocket.cpp
   
)



add_executable(kuromashiro_server
  ${main_server_SRCS}
)

add_library(server_libs STATIC
  ${server_SRCS}
  ${main_server_SRCS}
)

target_link_libraries(kuromashiro_server
  server_libs
)




message ("   -> Prepared: server")

