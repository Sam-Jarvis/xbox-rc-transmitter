# RC Xbox Controller

## Instructions / notes to future self:
The RF24 library must be installed! If it isn't, including the "RF24.h" file will throw:
`src/utilities.hpp:10:10: fatal error: RF24/RF24.h: No such file or directory`

To install the library (link to Doxygen: https://tmrh20.github.io/RF24/index.html):
All on the pi
1. clone the official repo
2. `make`
3. `sudo make install`