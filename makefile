CFLAGS=-Wall -Wextra -DDEBUG -g -pedantic -std=c++14 -fpermissive
M=Map
T=MapTest
T1=test1
T2=test2
T3=minimal
T4=morse
T5=performance

all: $(M).hpp $(T).cpp
	g++ $(CFLAGS) $(M).hpp $(T).cpp -o $(T) -ldl
$(T1): $(M).hpp $(T1).cpp
	g++ $(CFLAGS) $(M).hpp $(T1).cpp -o $(T1) -ldl
$(T2): $(M).hpp $(T2).cpp
	g++ $(CFLAGS) $(M).hpp $(T2).cpp -o $(T2) -ldl
$(T3): $(M).hpp $(T3).cpp
	g++ $(CFLAGS) $(M).hpp $(T3).cpp -o $(T3) -ldl
$(T4): $(M).hpp $(T4).cpp
	g++ $(CFLAGS) $(M).hpp $(T4).cpp -o $(T4) -ldl
$(T5): $(M).hpp $(T5).cpp
	g++ $(CFLAGS) -O $(M).hpp $(T5).cpp -o $(T5) -ldl
clean:
	rm -rf *.o $(T) $(T1) $(T2) $(T3) $(T4) $(T5)
