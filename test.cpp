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
                        //   1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22
        unsigned char v[] = {0, 0, 0, 2, 0, 0, 0, 1, 0, 1, 2, 0, 3, 4, 0, 0, 0, 0 , 2,0, 1, 0}; 
        std::fwrite(v, sizeof v[0], 22, f1);
        std::fclose(f1);
    }



    if (std::FILE* f {std::fopen("test", "rb")}) {   
        constexpr size_t buffer_length {256};
        MIDI_DATA buffer [buffer_length]; 
        size_t s {};
        size_t p {};
        size_t t {};
        constexpr unsigned char T{0};
        std::vector<MIDI_DATA> line;
        while ((s = std::fread(buffer, sizeof buffer[0], buffer_length, f)) > 0){
            p = 0;
            t = s;
            for (size_t i{0}; i<s; i++){
                if(buffer[i] != T) continue;
                while(( buffer[p] == T ) and ( p<i ))  p++;
                if( buffer[p]== T ) continue;                           
                line.insert(line.end(), buffer + p, buffer + i);
                data.push_back(line);
                line.clear();           
                count += i - p; 
                p = i + 1 ;  
            }
        }    
        if (t > p){ //insert rest
            line.insert(line.end(), buffer + p, buffer + t );
            data.push_back(line);
            line.clear();
            count += t - p;
        }
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