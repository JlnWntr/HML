#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

#define MAX_MIDI_BYTES 3
#define MIDI_DATA unsigned char

int main(){
    std::vector<std::vector <MIDI_DATA>> data{};
    size_t count {0};

    if (std::FILE* f1 = std::fopen("test", "wb"))   {
        unsigned char v[] = {0, 2, 0, 0, 1, 0, 1, 2, 0, 3, 4, 0, 0 }; 
        std::fwrite(v, sizeof v[0], 13, f1);
        std::fclose(f1);
    }

    if (std::FILE* f {std::fopen("test", "rb")}) {   
    constexpr size_t buffer_length {256};
    MIDI_DATA buffer [buffer_length]; 
    size_t s {};
    size_t p {};
    size_t t {};
    std::vector<MIDI_DATA> line;
    while ((s = std::fread(buffer, sizeof buffer[0], buffer_length, f)) > 0){
        p = 0;
        t = s;
        for (size_t i{0}; i<s; i++){
        //std::cout << (int)buffer[i]<< std::endl;
        if((buffer[i] == 0) and (i > p)){
            line.insert(line.end(), buffer + p, buffer + p + i);
            data.push_back(line);
            line.clear();
            count += i - p;
            p = i + 1;
            //std::cout << "Null!" << std::endl;
        }
        // std::cout << "i=" << i << " s=" << s << " p=" << p << std::endl;
        }
    }
    if (t > p){
        line.insert(line.end(), buffer + p, buffer + t);
        data.push_back(line);
        line.clear();
        count += t - p;
    }
    //std::cout << "s=" << s << " p=" << p << std::endl; 
    std::fclose(f);
    std::cout << "Read " << count << " bytes from file \"test\"." <<  std::endl;
    } 

    for (size_t i{0}; i<data.size(); i++){
        for (size_t j{0}; j<data[i].size(); j++)
            std::cout << (int)data[i][j] << " ";
        std::cout << std::endl;
    }
    return 0;
}