=?=E-json extract and build examples=?=
__________________________________________________
[right][tutorial[001_Read | Next: Read a file]][/right]

All developpement software will start by getting the dependency and the sources.

=== Linux dependency packages ===
[code style=shell]
	sudo apt-get install g++ zlib1g-dev
	# if you want to compile with clang :
	sudo apt-get install clang
[/code]

=== Download instructions ===

Download the software :
[code style=shell]
	# create a working directory path
	mkdir your_workspace_path
	cd your_workspace_path
	# clone ewol and all sub-library
	git clone http://github.com/HeeroYui/ewol.git
	cd ewol
	git submodule init
	git submodule update
	cd ..
	# download examples
	git clone http://github.com/HeeroYui/example.git
[/code]

[note]
The full build tool documentation is availlable here : [[http://heeroyui.github.io/lutin/ | lutin]]
[/note]

=== Common build instructions ===

Compile software in debug for the curent platform :
[code style=shell]
	./ewol/build/lutin.py -mdebug ejson*
[/code]

