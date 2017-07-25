CPPFLAGS=-std=c++11 -Wall -Wextra -Wvla -O -pthread

TARNAME=ex3.tar
TARFILES=Matrix.hpp Makefile README Extension.pdf

HPP=Matrix.hpp
GCH=$(HPP).gch

Matrix: $(GCH)

$(GCH): $(HPP)
	$(CXX) $(CPPFLAGS) $<

tar:
	tar cvf $(TARNAME) $(TARFILES)

clean:
	rm -rf *.gch $(TARNAME)

.PHONY: clean