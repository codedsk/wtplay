CXX         = g++
CPPFLAGS    = -Wall -g
CXXFLAGS    =
WITTYLIBS   = -lwt -lwthttp -lboost_signals
LDLIBS      = $(WITTYLIBS)

all: spiro

spiro: spiro.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDLIBS)
	strip $@

run: spiro
	test -L resources || ln -s /usr/share/Wt/resources .
	./spiro --docroot "." --http-addr 127.0.0.1 --http-port 8081

clean:
	rm -rf resources spiro
