per instructions on:
http://urho3d.github.io/documentation/HEAD/_using_library.html

--------------------
bin/
needs CoreData/ and Data/ linked from Urho3D

also need to link in CMake/
-------------------

These firectories can be linked using the link.* files.
The shell file is tested and works, the bat file is untested..

------------------
Fullfilling above requirements,
You will need to obtain state geometry (not open source)
and run the command:

cmake .

followed by: 

make