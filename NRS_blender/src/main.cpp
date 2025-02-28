#include <iostream>
#include <fstream>
#include <vector>
#include "Profiler.h"
#include <cstdint>
using namespace std;

#define Column_num 9

/* Data Load Function */ 
vector<vector<double>> LoadData(const string& filename) {
    vector<vector<double>> data;
    ifstream file(filename);

    if (file.is_open()) {
        vector<double> value(Column_num, 0.0); 
        while (true) {
            for (int i = 0; i < Column_num; ++i) {
                if (!(file >> value[i])) {
                    break;
                }
            }
            if (file.eof() && file.gcount() < 9) {
                break;
            }
            data.push_back(value); 
        }
        file.close();
    } else {
        cerr << "Can not open the file: " << filename << endl;
    }
    return data;
}

int main() {
    
    /* Parameter Initialization */
    double Sampling_time = 0.002; // Sampling time of controller
    double Starting_time = 3;
    double Last_resting_time = 3;
    double Acceleration_time = 0.5; // Maximum acceleration of desired trajectory
    double time_counter = 0; // Time counter (Do not modify)
    vector<vector<double>> blendedPath; // Blended path (Do not modify, Total output data)
    
    /* Data Load*/
    vector<vector<double>> Loaded_data = LoadData("../data/test_final_waypoints.txt");

    for (size_t i = 0; i < Loaded_data[0].size(); i++) {
        vector<double> time, data;
        time_counter = 0;
        for (const auto& row : Loaded_data) {
            time.push_back(time_counter*Sampling_time);
            data.push_back(row[i]);
            time_counter ++;
        }
        
        NRSProfiler profiler(time, data, Starting_time, Last_resting_time, Acceleration_time, Sampling_time);
        vector<vector<double>> result = profiler.AccDecProfiling();

        if(i == 0) {blendedPath.resize(result.size(), vector<double>(Column_num, 0.0));}

        uint64_t BP_counter = 0;
        for(const auto& row : result)
        {
            blendedPath[BP_counter][i] = row[1];
            BP_counter++;
        }

        string filename = "/home/wodbs/NRS_blender/data/output_result_" + to_string(i) + ".txt";
        profiler.SaveResultToFile(result, filename);
    }
    
    /* Save the total blended path */
    vector<double> time, data;
    NRSProfiler profiler(time, data, Starting_time, Last_resting_time, Acceleration_time, Sampling_time);
    string filename = "/home/wodbs/NRS_blender/data/total_blended_path.txt";
    profiler.SaveResultToFile(blendedPath, filename);
    return 0;
}
