CFLAGS:=-c -Wall -Weffc++ -g
LDFLAGS:=-lboost_system -lboost_locale -lboost_thread

all: WhatsappClient

WhatsappClient: bin/ConnectionHandler.o bin/Main.o bin/WhatsappClient.o  bin/HttpFrame.o bin/LoginFrame.o bin/Encoder.o bin/ErrorFrame.o bin/MessageFrame.o bin/WelcomeFrame.o bin/LogoutFrame.o bin/ListUsersFrame.o  bin/CreateGroupFrame.o bin/SendFrame.o bin/AddUserFrame.o bin/QueueFrame.o bin/RemoveUserFrame.o bin/ClientProtocol.o 
	g++ -o bin/client bin/ConnectionHandler.o bin/Main.o bin/WhatsappClient.o  bin/HttpFrame.o bin/LoginFrame.o bin/Encoder.o bin/ErrorFrame.o bin/MessageFrame.o bin/WelcomeFrame.o bin/LogoutFrame.o bin/ListUsersFrame.o bin/CreateGroupFrame.o bin/SendFrame.o bin/AddUserFrame.o bin/QueueFrame.o bin/RemoveUserFrame.o bin/ClientProtocol.o $(LDFLAGS) 

	
bin/ConnectionHandler.o: src/ConnectionHandler.cpp
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp

bin/Main.o: src/Main.cpp
	g++ $(CFLAGS) -o bin/Main.o src/Main.cpp
	
bin/WhatsappClient.o: src/WhatsappClient.cpp
	g++ $(CFLAGS) -o bin/WhatsappClient.o src/WhatsappClient.cpp
bin/HttpFrame.o: src/HttpFrame.cpp
	g++ $(CFLAGS) -o bin/HttpFrame.o src/HttpFrame.cpp
bin/LoginFrame.o:	src/LoginFrame.cpp
	g++ $(CFLAGS) -o bin/LoginFrame.o src/LoginFrame.cpp
bin/Encoder.o:          src/Encoder.cpp
	g++ $(CFLAGS) -o bin/Encoder.o src/Encoder.cpp
bin/LogoutFrame.o:          src/LogoutFrame.cpp
	g++ $(CFLAGS) -o bin/LogoutFrame.o src/LogoutFrame.cpp
bin/ListUsersFrame.o:          src/ListUsersFrame.cpp
	g++ $(CFLAGS) -o bin/ListUsersFrame.o src/ListUsersFrame.cpp
bin/CreateGroupFrame.o:          src/CreateGroupFrame.cpp
	g++ $(CFLAGS) -o bin/CreateGroupFrame.o src/CreateGroupFrame.cpp
bin/SendFrame.o:          src/SendFrame.cpp
	g++ $(CFLAGS) -o bin/SendFrame.o src/SendFrame.cpp
bin/AddUserFrame.o:          src/AddUserFrame.cpp
	g++ $(CFLAGS) -o bin/AddUserFrame.o src/AddUserFrame.cpp
bin/QueueFrame.o:          src/QueueFrame.cpp
	g++ $(CFLAGS) -o bin/QueueFrame.o src/QueueFrame.cpp
bin/RemoveUserFrame.o:          src/RemoveUserFrame.cpp
	g++ $(CFLAGS) -o bin/RemoveUserFrame.o src/RemoveUserFrame.cpp
bin/ClientProtocol.o:          src/ClientProtocol.cpp
	g++ $(CFLAGS) -o bin/ClientProtocol.o src/ClientProtocol.cpp
bin/WelcomeFrame.o: src/WelcomeFrame.cpp
	g++ $(CFLAGS) -o bin/WelcomeFrame.o src/WelcomeFrame.cpp

bin/MessageFrame.o: src/MessageFrame.cpp
	g++ $(CFLAGS) -o bin/MessageFrame.o src/MessageFrame.cpp

bin/ErrorFrame.o: src/ErrorFrame.cpp
	g++ $(CFLAGS) -o bin/ErrorFrame.o src/ErrorFrame.cpp	

	
run:
	bin/client 132.72.40.234 5584 
	
clean:
	rm -f bin/*
