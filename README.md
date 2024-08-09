# Mini Midi Librarian
Minimal Midi Librarian console application

### Linux:
`g++ -std=c++17 hml.cpp rtmidi/RtMidi.cpp -o hml -Wall -D__LINUX_ALSA__ -lasound -lpthread`

### Crosscompile for Windows:
`x86_64-w64-mingw32-g++ -static-libstdc++ -static-libgcc -std=c++17 -o hml.exe hml.cpp rtmidi/RtMidi.cpp -lwinmm -D__WINDOWS_MM__ -D_WIN32 -Wall`
