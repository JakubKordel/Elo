CFLAGS=-Wall -pedantic -std=c++11

compile: main.o ./source/BuilderReader.o ./source/BuilderReader.h ./source/FilesFunctions.o ./source/FilesFunctions.h ./source/HistoryBuilder.o ./source/HistoryBuilder.h ./source/Match.o ./source/Match.h ./source/MatchLineConverter.o ./source/MatchLineConverter.h ./source/Menu.o ./source/Menu.h ./source/Player.o ./source/Player.h ./source/PlayerLineConverter.o ./source/PlayerLineConverter.h ./source/PlayersList.o ./source/PlayersList.h ./source/StringsBasicsFunctions.o ./source/StringsBasicsFunctions.h
	g++ $(CFLAGS) main.o ./source/BuilderReader.o ./source/FilesFunctions.o ./source/HistoryBuilder.o ./source/Match.o ./source/MatchLineConverter.o ./source/Menu.o ./source/Player.o ./source/PlayerLineConverter.o ./source/PlayersList.o ./source/StringsBasicsFunctions.o -o Elo

main.o: main.cpp 
	g++ -c $(CFLAGS) main.cpp

BuilderReader.o: ./source/BuilderReader.cpp ./source/BuilderReader.h
	g++ -c $(CFLAGS) ./source/BuilderReader.cpp

FilesFunctions.o: ./source/FilesFunctions.cpp ./source/FilesFunctions.h
	g++ -c $(CFLAGS) ./source/FilesFunctions.cpp

HistoryBuilder.o: ./source/HistoryBuilder.cpp ./source/HistoryBuilder.h
	g++ -c $(CFLAGS) ./source/HistoryBuilder.cpp

Match.o: ./source/Match.cpp ./source/Match.h
	g++ -c $(CFLAGS) ./source/Match.cpp

MatchLineConverter.o: ./source/MatchLineConverter.cpp ./source/MatchLineConverter.h
	g++ -c $(CFLAGS) ./source/MatchLineConverter.cpp

Menu.o: ./source/Menu.cpp ./source/Menu.h
	g++ -c $(CFLAGS) ./source/Menu.cpp

Player.o: ./source/Player.cpp ./source/Player.h
	g++ -c $(CFLAGS) ./source/Player.cpp

PlayerLineConverter.o: ./source/PlayerLineConverter.cpp ./source/PlayerLineConverter.h
	g++ -c $(CFLAGS) ./source/PlayerLineConverter.cpp

PlayersList.o: ./source/PlayersList.cpp ./source/PlayersList.h
	g++ -c $(CFLAGS) ./source/PlayersList.cpp

StringsBasicsFunctions.o: ./source/StringsBasicsFunctions.cpp ./source/StringsBasicsFunctions.h
	g++ -c $(CFLAGS) ./source/StringsBasicsFunctions.cpp

