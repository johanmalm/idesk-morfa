cmake_minimum_required(VERSION 3.23)
project(idesk-morfa VERSION 0.0.1 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined")
set(CMAKE_AUTOMOC on)

find_package(Qt6 REQUIRED COMPONENTS Gui Widgets)
find_package(LayerShellQt REQUIRED)

include_directories(${CMAKE_BINARY_DIR} fdicons/include)

add_executable(idesk-morfa
	main.cpp
	mainwindow.cpp mainwindow.h
	settings.cpp settings.h
	desktop.cpp desktop.h
	item.cpp item.h
	fdicons/include/fdicons.h
	fdicons/src/database.c fdicons/include/database.h
	fdicons/src/ini.c fdicons/include/ini.h
	fdicons/src/lookup.c
)

target_link_options(idesk-morfa
	BEFORE PUBLIC -fsanitize=undefined PUBLIC -fsanitize=address
)

target_link_libraries(idesk-morfa
	PRIVATE
	LayerShellQtInterface
	Qt::Gui
	Qt::Widgets
)
