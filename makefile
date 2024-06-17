all: bmp280

bmp280:
	g++ main.cpp bmp280.cpp -o bmp280 -lwiringPi -lpthread

clean:
	rm -rf bmp280
