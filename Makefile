CXX := g++
AR := ar
CXXFLAGS := -std=c++17 -Wall -I./src

ifeq ($(OS),Windows_NT)
	RM := cmd /C del /Q
else
	RM := rm -f
endif

SRCS := src/enums.cpp src/task.cpp src/task_types.cpp src/project.cpp src/project_manager.cpp
OBJS := $(SRCS:.cpp=.o)

all: run

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(OBJS) main.cpp
	$(CXX) $(CXXFLAGS) main.cpp $(OBJS) -o task_manager

tests: $(OBJS) tests/test_main.cpp
	$(CXX) $(CXXFLAGS) tests/test_main.cpp $(OBJS) -o test_main
	./test_main

ifeq ($(OS),Windows_NT)
clean:
	@echo Cleaning build artifacts (Windows)...
	@setlocal enabledelayedexpansion & \
	set OBJS_WIN=$(subst /,\\,$(OBJS)) & \
	for %%F in (task_manager.exe task_manager test_main.exe test_main) do if exist %%F del /Q "%%F" >NUL 2>&1 & \
	for %%F in (!OBJS_WIN!) do if exist %%F del /Q "%%F" >NUL 2>&1
else
clean:
	@echo Cleaning build artifacts (Unix)...
	-@rm -f task_manager task_manager.exe test_main test_main.exe $(OBJS)
endif


.PHONY: all run tests clean
