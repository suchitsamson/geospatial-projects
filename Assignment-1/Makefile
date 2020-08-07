PROG = main
CC = g++ -std=c++17
CPPFLAGS = -g -Wall -fpermissive -Wno-sign-compare
OBJS = utilities.o Cell.o Point.o Grid.o GPOs.o main.o

$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS) $(LFLAGS) $(LIBS)

-include $(OBJS:.o=.d)

main.o : main.cpp headers.h
	$(CC) $(CPPFLAGS) -c main.cpp
	$(CC) -MM main.cpp > main.d
Point.o : GPOs/grid/Point.cpp headers.h
	$(CC) $(CPPFLAGS) -c GPOs/grid/Point.cpp
	$(CC) -MM GPOs/grid/Point.cpp > Point.d
Cell.o : GPOs/grid/Cell.cpp headers.h
	$(CC) $(CPPFLAGS) -c GPOs/grid/Cell.cpp
	$(CC) -MM GPOs/grid/Cell.cpp > Cell.d
GPOs.o : GPOs/GPOs.cpp headers.h
	$(CC) $(CPPFLAGS) -c GPOs/GPOs.cpp
	$(CC) -MM GPOs/GPOs.cpp > GPOs.d
Grid.o : GPOs/grid/Grid.cpp headers.h
	$(CC) $(CPPFLAGS) -c GPOs/grid/Grid.cpp
	$(CC) -MM GPOs/grid/Grid.cpp > Grid.d	
utilities.o : utilities/utilities.cpp headers.h
	$(CC) $(CPPFLAGS) -c utilities/utilities.cpp
	$(CC) -MM utilities/utilities.cpp > utilities.d


.PHONY : clean
clean:
	rm -f core $(PROG) $(OBJS) *.d

