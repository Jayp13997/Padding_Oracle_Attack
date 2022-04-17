all: attack

attack:	attack.cpp
	g++ -std=c++11 attack.cpp cipher.a -o attack

clean:
	rm -rf attack