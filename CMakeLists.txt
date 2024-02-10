cmake_minimum_required(VERSION 3.27.0)

project(echo-client LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets Network WebSockets Concurrent UiTools REQUIRED)

add_executable(echo-client
  src/aoapplication.h src/aoapplication.cpp
  src/aoblipplayer.h src/aoblipplayer.cpp
  src/aobutton.h src/aobutton.cpp
  src/aocharbutton.h src/aocharbutton.cpp
  src/aoclocklabel.h src/aoclocklabel.cpp
  src/aoemotebutton.h src/aoemotebutton.cpp
  src/aoemotepreview.h src/aoemotepreview.cpp
  src/aoevidencebutton.h src/aoevidencebutton.cpp
  src/aoevidencedisplay.h src/aoevidencedisplay.cpp
  src/aoimage.h src/aoimage.cpp
  src/aolayer.h src/aolayer.cpp
  src/aomusicplayer.h src/aomusicplayer.cpp
  src/aopacket.h src/aopacket.cpp
  src/aosfxplayer.h src/aosfxplayer.cpp
  src/aotextarea.h src/aotextarea.cpp
  src/aoutils.h src/aoutils.cpp
  src/charselect.cpp
  src/chatlogpiece.h src/chatlogpiece.cpp
  src/courtroom.h src/courtroom.cpp
  src/datatypes.h
  src/debug_functions.h src/debug_functions.cpp
  src/demoserver.h src/demoserver.cpp
  src/discord_register.h
  src/discord_rich_presence.h src/discord_rich_presence.cpp
  src/discord_rpc.h
  src/emotes.cpp
  src/eventfilters.h
  src/evidence.cpp
  src/file_functions.h src/file_functions.cpp
  src/hardware_functions.h src/hardware_functions.cpp
  src/interfaces/server_dialog.h
  src/lobby.h src/lobby.cpp
  src/main.cpp
  src/networkmanager.h src/networkmanager.cpp
  src/options.h src/options.cpp
  src/packet_distribution.cpp
  src/path_functions.cpp
  src/scrolltext.h src/scrolltext.cpp
  src/text_file_functions.h src/text_file_functions.cpp
  src/widgets/add_server_dialog.h src/widgets/add_server_dialog.cpp
  src/widgets/aooptionsdialog.h src/widgets/aooptionsdialog.cpp
  src/widgets/direct_connect_dialog.h src/widgets/direct_connect_dialog.cpp
  src/widgets/edit_server_dialog.h src/widgets/edit_server_dialog.cpp
  resource.qrc
)

target_link_directories(echo-client PRIVATE external)

target_include_directories(echo-client PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/external
)

if(NOT TARGET echo-core)
include(FetchContent)
message("Fetching core...")
FetchContent_Declare(
    echo-core
    GIT_REPOSITORY https://github.com/Attorney-Online-Rerouted/echo-core.git
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/core
)
FetchContent_MakeAvailable(echo-core)
endif()

target_link_libraries(echo-client PRIVATE
  Qt6::Core
  Qt6::Gui
  Qt6::Widgets
  Qt6::Network
  Qt6::WebSockets
  Qt6::Concurrent
  Qt6::UiTools
  bass
  bassopus
  bassmidi
  discord-rpc
  echo-core
)

if(WIN32)
  set_target_properties(echo-client PROPERTIES WIN32_EXECUTABLE true)
  set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/resource/logo_ao2.rc")
  target_sources(echo-client PRIVATE ${APP_ICON_RESOURCE_WINDOWS})
endif()
