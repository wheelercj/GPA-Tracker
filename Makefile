OBJS = "GPA Tracker/main.cpp" "GPA Tracker/Course.cpp" "GPA Tracker/Courses.cpp"

CC = g++

OBJ_NAME = main

all :
	$(CC) $(OBJS) -std=c++11 -o $(OBJ_NAME)
