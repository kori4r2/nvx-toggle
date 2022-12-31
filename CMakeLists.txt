cmake_minimum_required(VERSION 3.25)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

project(nvx-toggle)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)

# Find necessary Qt and Kf5Ath libraries.

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(KF5Auth)

set(HELPER "actionhelper.cpp")
set(SOURCES "main.cpp" "window.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui KF5::Auth)

add_executable(nvx-toggle-helper ${HELPER})
target_link_libraries(nvx-toggle-helper Qt5::Core KF5::Auth)

install(TARGETS nvx-toggle-helper DESTINATION ${KAUTH_HELPER_INSTALL_DIR})

kauth_install_helper_files(nvx-toggle-helper org.kde.nvxtoggle root)
kauth_install_actions(org.kde.nvxtoggle org.kde.nvxtoggle.actions)