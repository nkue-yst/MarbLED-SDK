doc:
	doxygen
	rm -rf docs/
	mkdir docs/
	cp -r doxygen/html/* docs/

clean:
	rm -rf doxygen/ docs/
