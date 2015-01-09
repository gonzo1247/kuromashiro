
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

#add_subdirectory(client)

file(GLOB_RECURSE sources_client_f File/*.cpp File/*.h)
file(GLOB_RECURSE sources_client_l Login/*.cpp Login/*.h)
file(GLOB_RECURSE sources_client_resource resource/*.cp resource/*.h)
file(GLOB sources_localdir *.cpp *.h)

set(client_SRCS
  ${client_SRCS}
  ${sources_client_f}
  ${sources_client_l}
)

set(main_SRCS
${sources_client_f}
${sources_client_l}
${sources_resource}
${sources_localdir}
resource/bild3.bmp
resource/bild4.bmp
resource/bild5.bmp
resource/bitmap1.bmp
resource/bitmap2.bmp
#icon1.ico
resource/kuromashiro.aps
#kuromashiro.rc
main.cpp
#resource.h
)

add_subdirectory(Login)
add_subdirectory(File)
add_subdirectory(resource)



if( WIN32 )
  set(main_SRCS
    ${main_SRCS}
    ${sources_windows_Debugging}
 )   
 if (MSVC)
   set(main_SRCS
     ${main_SRCS}
     kuromashiro.rc
  )
 endif ()
endif ()




ADD_LIBRARY(main
resource/bild3.bmp
resource/bild4.bmp
resource/bild5.bmp
resource/bitmap1.bmp
resource/bitmap2.bmp
icon1.ico
resource/kuromashiro.aps
kuromashiro.rc
main.cpp
resource.h)

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/client/resource
  ${CMAKE_CURRENT_SOURCE_DIR}/client/File
  ${CMAKE_CURRENT_SOURCE_DIR}/client/Login
)

ADD_LIBRARY(client
File/CFile.cpp
File/CFile.h
Login/CLogin.cpp
Login/CLogin.h)




#add_executable(kuromashiro
#Login/CLogin.h
#Login/CLogin.cpp
#File/CFile.h
#File/CFile.cpp
#bild3.bmp
#bild4.bmp
#bild5.bmp
#bitmap1.bmp
#bitmap2.bmp
#icon1.ico
#kuromashiro.aps
#kuromashiro.rc
#main.cpp
#resource.h
#)

add_executable(kuromashiro WIN32
 # ${client_SRCS}
  ${main_SRCS}
)

add_library(client_libs STATIC
  ${client_SRCS}
  ${main_SRCS}
)

target_link_libraries(kuromashiro
 # File
 # Login
 # resource
client_libs
)




message ("   -> Prepared: client")

