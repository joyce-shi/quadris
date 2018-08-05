CXX= g++
CXXFLAGS= -std=c++14 -Wextra -Wall -Werror=vla -MMD -g
OBJECTS= main.o grid.o cell.o ${BLOCKS} ${LEVELS} textdisplay.o gdisplay.o window.o
BLOCKS= block.o singleBlock.o blockI.o blockJ.o blockL.o blockO.o blockS.o blockT.o blockZ.o
LEVELS= level.o level0.o level1.o level2.o level3.o level4.o
DEPENDS= ${OBJECTS:.o=.d}
EXEC=quadris

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -lX11 -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
.PHONY: clean
