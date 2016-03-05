CXX=clang++
 #CXX=g++

run: Main.o BTree.o Node.o HashTable.o
	${CXX} Main.o BTree.o Node.o HashTable.o -o run

clean:
	/bin/rm -f *.o Main.o BTree.o Node.o HashTable.o run *.cpp~ *.h~ Makefile~

BTree.o: BTree.cpp
	${CXX} -c BTree.cpp

Node.o: Node.cpp
	${CXX} -c Node.cpp

HashTable.o: HashTable.cpp
	${CXX} -c HashTable.cpp

Main.o: Main.cpp
	${CXX} -c Main.cpp
