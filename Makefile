CC = g++
INC = -I. -I../rapidjson/include -Iinclude -I/opt/homebrew/Cellar/glfw/3.3.6/include -I/opt/homebrew/Cellar/glew/2.2.0_1/include -I/opt/homebrew/Cellar/glm/0.9.9.8/include
LIB_DIRS = -L/opt/homebrew/Cellar/glfw/3.3.6/lib -L/opt/homebrew/Cellar/glew/2.2.0_1/lib
LIBS = -lglfw.3.3 -lGLEW.2.2.0 -framework OpenGL
OBJ_FOR_SERVER = server.o socket.o listening.o event_list.o player.o message.o bullet.o time.o
OBJ_FOR_CLIENT = client.o renderer.o input.o socket.o object.o shader.o message.o bullet.o player.o time.o

all: server client

server: $(OBJ_FOR_SERVER)
	$(CC) $(INC) -o server $(OBJ_FOR_SERVER)

client: $(OBJ_FOR_CLIENT)
	$(CC) $(INC) $(LIBS) $(LIB_DIRS) -o client $(OBJ_FOR_CLIENT)

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

message.o: source/message.cpp
	$(CC) $(INC) -c source/message.cpp -o message.o

bullet.o: source/bullet.cpp
	$(CC) $(INC) -c source/bullet.cpp -o bullet.o

time.o: source/time.cpp
	$(CC) $(INC) -c source/time.cpp -o time.o

client.o: source/client.cpp
	$(CC) $(INC) -c source/client.cpp -o client.o

renderer.o: source/renderer.cpp
	$(CC) $(INC) -c source/renderer.cpp -o renderer.o

input.o: source/input.cpp
	$(CC) $(INC) -c source/input.cpp -o input.o

object.o: source/object.cpp
	$(CC) $(INC) -c source/object.cpp -o object.o

shader.o: source/shader.cpp
	$(CC) $(INC) -c source/shader.cpp -o shader.o

clean: 
	rm -f *.o