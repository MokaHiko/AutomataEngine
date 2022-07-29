cmake_minimum_required(VERSION 3.0...3.20 FATAL_ERROR)

project(imgui)

file(GLOB SOURCES
	${PROJECT_SOURCE_DIR}/*.h
	${PROJECT_SOURCE_DIR}/*.cpp)

add_library(${PROJECT_NAME} ${SOURCES})