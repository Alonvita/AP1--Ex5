# Alon Vita 311233431

CXX = g++
CXXFLAGS = -std=c++0x -pthread
RM = rm -f
#LIBS = -pthread -lboost_serialization -I.

game.o:
	# find game files
	find ../game -type f -name "*.cpp" > sources.txt
	# find server files
	find ../server -type f -name "*.cpp" >> sources.txt
	# find diplay files
	find ../display -type f -name "*.cpp" >> sources.txt
	# find shared_data files
	find ../shared_data -type f -name "*.cpp" >> sources.txt

client.o:
	# find client files
	find ../client -type f -name "*.cpp" -exec basename {} \; > sources.txt
	# compile files to .o
	$(CXX) $(CXXFLAGS) -o client.o @sources.txt
	

server: game.o
	#find all of the files
	$(CXX) $(CXXFLAGS) @sources.txt ../main/server_main.cpp -o server.out

client: game.o
	# find client flies
	find ../client -type f -name "*.cpp" >> sources.txt
	#find all of the files
	$(CXX) $(CXXFLAGS) @sources.txt ../main/client_main.cpp -o client.out

clean:
	$(RM) *.o
	$(RM) sources.txt
	$(RM) compile.txt
