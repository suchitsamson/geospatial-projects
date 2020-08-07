PROG = main
CC = g++ -std=c++11
CPPFLAGS = -g -c -Wall
LDFLAGS = 
OBJS = main.o Group.o utilities.o GPOs.o Cell.o Point.o Grid.o IncrVisitor.o SPOs.o Visitor.o Value.o BasicGSQueries.o topkUsers.o 
SRCS = complexQueries/topkUsers.cpp basicGSQueries/BasicGSQueries.cpp SPOs/MemoryMap/Value.cpp SPOs/MemoryMap/SPOs.cpp GPOs/MemoryGrid/grid/Visitor.cpp GPOs/MemoryGrid/grid/IncrVisitor.cpp GPOs/MemoryGrid/grid/Point.cpp GPOs/MemoryGrid/grid/Grid.cpp GPOs/MemoryGrid/grid/Cell.cpp GPOs/MemoryGrid/GPOs.cpp utilities/Utilities.cpp utilities/Group.cpp

$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS)

-include $(OBJS:.o=.d)

main.o : main.cpp headersMemory.h
	$(CC) $(CPPFLAGS) -c main.cpp
	$(CC) -MM main.cpp > main.d
Group.o : utilities/Group.cpp headers.h
	$(CC) $(CPPFLAGS) -c utilities/Group.cpp
	$(CC) -MM -c utilities/Group.cpp > Group.d
utilities.o : utilities/utilities.cpp headers.h
	$(CC) $(CPPFLAGS) -c utilities/utilities.cpp
	$(CC) -MM utilities/utilities.cpp > utilities.d
GPOs.o : GPOs/MemoryGrid/GPOs.cpp headersMemory.h
	$(CC) $(CPPFLAGS) -c GPOs/MemoryGrid/GPOs.cpp
	$(CC) -MM GPOs/MemoryGrid/GPOs.cpp > GPOs.d
Cell.o : GPOs/MemoryGrid/grid/Cell.cpp headersMemory.h
	$(CC) $(CPPFLAGS) -c GPOs/MemoryGrid/grid/Cell.cpp
	$(CC) -MM GPOs/MemoryGrid/grid/Cell.cpp > Cell.d
Grid.o : GPOs/MemoryGrid/grid/Grid.cpp headersMemory.h
	$(CC) $(CPPFLAGS) -c GPOs/MemoryGrid/grid/Grid.cpp
	$(CC) -MM GPOs/MemoryGrid/grid/Grid.cpp > Grid.d
Point.o : GPOs/MemoryGrid/grid/Point.cpp headersMemory.h
	$(CC) $(CPPFLAGS) -c GPOs/MemoryGrid/grid/Point.cpp
	$(CC) -MM GPOs/MemoryGrid/grid/Point.cpp > Point.d
IncrVisitor.o : GPOs/MemoryGrid/grid/IncrVisitor.cpp headersMemory.h
	$(CC) $(CPPFLAGS) -c GPOs/MemoryGrid/grid/IncrVisitor.cpp
	$(CC) -MM GPOs/MemoryGrid/grid/IncrVisitor.cpp > IncrVisitor.d
Visitor.o : GPOs/MemoryGrid/grid/Visitor.cpp headersMemory.h
	$(CC) $(CPPFLAGS) -c GPOs/MemoryGrid/grid/Visitor.cpp
	$(CC) -MM GPOs/MemoryGrid/grid/Visitor.cpp > Visitor.d
SPOs.o : SPOs/MemoryMap/SPOs.cpp headersMemory.h
	$(CC) $(CPPFLAGS) -c SPOs/MemoryMap/SPOs.cpp
	$(CC) -MM SPOs/MemoryMap/SPOs.cpp > SPOs.d
Value.o : SPOs/MemoryMap/Value.cpp  headersMemory.h
	$(CC) $(CPPFLAGS) -c SPOs/MemoryMap/Value.cpp
	$(CC) -MM SPOs/MemoryMap/Value.cpp > Value.d
BasicGSQueries.o : basicGSQueries/BasicGSQueries.cpp headers.h
	$(CC) $(CPPFLAGS) -c basicGSQueries/BasicGSQueries.cpp
	$(CC) -MM basicGSQueries/BasicGSQueries.cpp > BasicGSQueries.d
topkUsers.o : complexQueries/topkUsers.cpp headers.h
	$(CC) $(CPPFLAGS) -c complexQueries/topkUsers.cpp
	$(CC) -MM complexQueries/topkUsers.cpp > topkUsers.d

.PHONY : clean 
clean:
	rm -f core $(OBJS) *.d

.PHONY: cleanest
cleanest:
	rm -f core $(PROG) $(OBJS) *.d
