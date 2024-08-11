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


       // write buffer to file
        if (std::FILE* f1 = std::fopen("test", "wb"))
        {
            int v[] = {42, -1, 0, 1, 2, 3, 4 ,7}; // underlying storage of std::array is an array
            std::fwrite(v, sizeof v[0], 8, f1);
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
            //std::cout << buffer[i];
            if((buffer[i] == 0) and (i > p)){
              line.insert(line.end(), buffer + p, buffer + p + i -1 );
              data.push_back(line);
              line.clear();
              count += i - p;
              p = i;
            }
            //std::cout << "s=" << s << " p=" << p << std::endl;
          }
        }
        if (t > p){
          line.insert(line.end(), buffer + p, buffer + p + t );
          data.push_back(line);
          line.clear();
          count += t - p;
        }
        // std::cout << "s=" << s << " p=" << p << std::endl; 
        std::fclose(f);
        std::cout << "Read " << count << " bytes from file \"test\"." <<  std::endl;
      } 

      for (size_t i{0}; i<data.size(); i++){
        for (size_t j{0}; j<data[i].size(); j++)
          std::cout << data[i][j] << " ";
        std::cout << std::endl;
      }
  return 0;
}