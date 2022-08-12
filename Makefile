CC = g++
INC = -I. -I../rapidjson/include -Iinclude -I/opt/homebrew/Cellar/glfw/3.3.6/include -I/opt/homebrew/Cellar/glew/2.2.0_1/include -I/opt/homebrew/Cellar/glm/0.9.9.8/include
LIB_DIRS = -L/opt/homebrew/Cellar/glfw/3.3.6/lib -L/opt/homebrew/Cellar/glew/2.2.0_1/lib
LIBS = -lglfw.3.3 -lGLEW.2.2.0 -framework OpenGL
OBJ_FOR_SERVER = server.o socket.o listening.o event_list.o player.o

all: server

server: $(OBJ_FOR_SERVER)
	$(CC) $(INC) -o server $(OBJ_FOR_SERVER)

server.o: source/server.cpp
	$(CC) $(INC) -c source/server.cpp -o server.o

socket.o: source/socket.cpp
	$(CC) $(INC) -c source/socket.cpp -o socket.o

listening.o: source/listening.cpp
	$(CC) $(INC) -c source/listening.cpp -o listening.o

event_list.o: source/event_list.cpp
	$(CC) $(INC) -c source/event_list.cpp -o event_list.o

player.o: source/player.cpp
	$(CC) $(INC) -c source/player.cpp -o player.o

clean: 
	rm -f *.o