OBJS = main.o jsoncpp.o DFA.o DFAReader.o

DFAminimal: ${OBJS}
	g++ -o DFAminimal ${OBJS} -DJSON_IS_AMALGAMATION

main.o: main.cpp
	g++ -c $<

jsoncpp.o : jsoncpp.cpp json/json.h
	g++ -c $<

DFA.o : DFA.cpp DFA.h
	g++ -c $<

DFAReader.o : DFAReader.cpp DFAReader.h
	g++ -c $< -w

clean:
	rm DFAminimal ${OBJS}
