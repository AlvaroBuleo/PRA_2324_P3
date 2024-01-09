bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp

bin/testHashTable: testHashTable.cpp HashTable.h Dict.h TableEntry.h
	g++ -o bin/testHashTable testHashTable.cpp HashTable.h Dict.h TableEntry.h

bin/testBSTree: testBSTree.cpp BSTree.h
	g++ -o bin/testBSTree testBSTree.cpp BSTree.h

clean:
	rm -rf *.o *.gch bin
