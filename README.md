# CIS-22C-Team-4
Here is where we will keep our code for the CIS 22C final group project. 
Project summary:
	Topic: Tablet convertible Laptops.
  
	Memebers: 
		Alex: File I/O 
		Andrew: Priority Queue
		Jasper: GUI
		Mohamed: Team Coordinator & Main
		Tin: Hash Tables
		Vu: BST Algorithms

### To Compile and run the program on Mac:

first install home-brew from [brew.sh](https://brew.sh) if you don't have it already.
then install two packages:
>brew install pkg-config

>brew install gtk

then use this command to compile the program (make sure you cd into the correct directory first)
>g++ \*.cpp -o program \`pkg-config --cflags gtk+-2.0\` \`pkg-config --libs gtk+-2.0\`

and then run it
>./program

### For Windows:

pkg-config and gtk should be available on windows too, then compile and run it like any other c++ program, but make sure to include the library flags etc.
>\`pkg-config --cflags gtk+-2.0\` \`pkg-config --libs gtk+-2.0\`

You may need to use the workaround described here: https://sungkwang.wordpress.com/2013/07/10/use-gcc-with-pkg-config-in-windows-7-mingw/
