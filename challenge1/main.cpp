#include <iostream>
#include <fstream>
#include "ThetaMethod.hpp"
#include <cmath>
#include "reader.hpp"

int main() {

    // Importing parameters with json
    Reader r("parameters.json");
    parameters param=r.readParameters_json();

    const auto &[N,u0,T,theta,f_str,fex_str,k,solverType] = param; 

    MuparserFun2V f(f_str);
    MuparserFun1V fex(fex_str);

    // Computing numerical solution
    std::array<std::vector<double>,2> res=ThetaMethod(f,u0,T,N,theta,solverType);
    std::vector<double> resex(res[0].size(),0.);
    
    // Computing analitycal solution 
    for(unsigned int i=0;i<res[1].size();i++) {
        resex[i]=fex(res[0][i]); 
    }

    // Filling result.dat
    std::cout << "Result file: result.dat" << std::endl;
    std::ofstream file("result.dat");

    file << "#nodecoordinate\tcomputedsolution\texactsolution" << std::endl;
    for(unsigned int m = 0; m < res[1].size(); m++)
        {
        file.setf(std::ios::left, std::ios::adjustfield);
        file.width(16);
        file << res[0][m] << "\t\t" << res[1][m] << "\t\t" << resex[m] << "\n";
        }
    
    // Computing error vector
    std::vector<int> steps(k,0);
    for (unsigned int i=0;i<k;i++) {
        steps[i]=pow(2,i+3);
    }
    std::vector<double> err=ComputeError(param,steps);

    // Filling error.dat
    std::cout << "Error file: errors.dat" << std::endl;
    std::ofstream filerr("errors.dat");
    
    filerr << "#nodecoordinate\tcomputederr\tlogerror\th1error\th2error" << std::endl;
    for(unsigned int m = 0; m < err.size(); m++)
        {
        filerr.setf(std::ios::left, std::ios::adjustfield);
        filerr.width(16);
        filerr << log2(pow(steps[m],-1)) << "\t\t" << log2(err[m]) << "\t\t" << log2(pow(steps[m],-1)) << "\t\t" << log2(pow(steps[m],-2)) << "\n"; // loglog scale
        }
    filerr.close();
    file.close();
    return 0;
}