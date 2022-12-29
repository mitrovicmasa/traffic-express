cmake_minimum_required(VERSION 3.5)

project(TrafficExpress VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)


set(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resource/resource.qrc)
qt_add_resources(RES_SOURCES ${RESOURCES})

include_directories(src/)
include_directories(headers/)
include_directories(src/collections)
include_directories(headers/collections/)

#[[
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        src/treasure.cpp
        headers/treasure.h
        src/wagon.cpp
        headers/wagon.h
        src/roundcard.cpp
        headers/roundcard.h
        src/game.cpp
        headers/game.h
        src/player.cpp
        headers/player.h
        src/card.cpp
        headers/card.h
        src/banditcard.cpp
        headers/banditcard.h
        src/neutralbullet.cpp
        headers/neutralbullet.h
        src/actioncard.cpp
        headers/actioncard.h
        src/bulletcard.cpp
        headers/bulletcard.h
)
]]
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.ui
        src/treasure.cpp
        src/wagon.cpp
        src/roundcard.cpp
        src/game.cpp
        src/player.cpp
        src/card.cpp
        src/banditcard.cpp
        src/neutralbullet.cpp
        src/actioncard.cpp
        src/bulletcard.cpp
        src/train.cpp
        src/hand.cpp
        src/deck.cpp
        src/table.cpp
        src/playerstats.cpp
        src/miniround.cpp
        src/playerperspective.cpp
        src/collections/treasurechest.cpp
        src/collections/cardcolection.cpp
        src/collections/wagonarray.cpp
        src/collections/playergroup.cpp
        src/collections/miniroundcollection.cpp
        src/collections/roundcardcollection.cpp
        src/collections/playerstatscollection.cpp
        src/collections/playerperspectivecollection.cpp
        src/singleplayerstatemachine.cpp
        src/sheriff.cpp
        src/dialoguebox.cpp
        src/roundcarddeck.cpp
        src/serializable.cpp
        src/client/playerclient.cpp
        )

set(PROJECT_HEADERS
        mainwindow.h
        headers/treasure.h
        headers/wagon.h
        headers/roundcard.h
        headers/game.h
        headers/player.h
        headers/card.h
        headers/banditcard.h
        headers/neutralbullet.h
        headers/actioncard.h
        headers/bulletcard.h
        headers/train.h
        headers/hand.h
        headers/deck.h
        headers/table.h
        headers/playerstats.h
        headers/miniround.h
        headers/playerperspective.h
        headers/collections/treasurechest.h
        headers/collections/cardcolection.h
        headers/collections/wagonarray.h
        headers/collections/playergroup.h
        headers/collections/miniroundcollection.h
        headers/collections/roundcardcollection.h
        headers/collections/playerstatscollection.h
        headers/collections/playerperspectivecollection.h
        headers/singleplayerstatemachine.h
        headers/sheriff.h
        headers/dialoguebox.h
        headers/roundcarddeck.h
        headers/serializable.h
        headers/client/playerclient.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TrafficExpress
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${RES_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TrafficExpress APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TrafficExpress SHARED
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TrafficExpress
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
            ${RES_SOURCES}
        )
    endif()
endif()

target_link_libraries(TrafficExpress PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(TrafficExpress PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS TrafficExpress
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TrafficExpress)
endif()
