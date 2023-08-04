default: dot

compile:
	g++ -DUNW_LOCAL_ONLY *.cpp -g -o backtrace -lunwind

execute: compile
	./backtrace

dot: execute
	dot -Tpng tree.dot -o tree.png

clean:
	rm -rf backtrace, tree.dot tree.png
