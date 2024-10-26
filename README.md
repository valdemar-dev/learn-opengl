# LearnOpenGL

## Premise
I wanted to learn some basic graphics programming,
so naturally, I chose OpenGL. (as low level as I could get)
For the programming language, I chose C. (a language and paradigm I have had no prior experience with)

Each commit in this repo will be made upon completion of a chapter in the LearnOpenGL book.

## LearnOpenGL
You can find the book here for free: https://learnopengl.com/

## Run this Project
To run, you can just `make && ./main`, which should work, probably.

For dependencies, you may need to install GLFW; as I'm not if sure that's pre-installed.
You'll also need `gcc`, or edit the `Makefile` to use some other C compiler.

## Special Considerations
The `LDFLAGS` in the makefile are for *my* machine, which is running Fedora 41,
and therefore may need (or may not need) to be tweaked if running on Windows.
