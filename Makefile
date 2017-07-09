
test:
	g++ test.cpp -o build/unit-test
	./build/unit-test

clean:
	rm -rf build/*

docs:
	documentation readme image.h -s docs --polyglot 
