CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = a4q2
OBJECTS = cc3k.o CmdInterpreter.o Floor.o Display.o Cell.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

