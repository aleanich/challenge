#include<iostream>
#include<vector>
#include<array>
#include<functional>
#include "basicZeroFun.hpp"
#include "reader.hpp"



std::array<std::vector<double>,2> ThetaMethod (std::function<double(double,double)> f,double u0,double T,int N,double theta,int SolverType=1) {

    std::array<std::vector<double>,2> sol={};
    std::function<double(double)> F;
    std::function<double(double)> dF;


    // Computing the step of discretization
    double h=T/N;

    // Vector of time steps
    std::vector<double> t(N+1,0.);
    for(int i=0;i<=N;i++) {
        t[i]=i*h;
    }

    // Approximation of the solution
    std::vector<double> u(N+1,0.);
    u[0]=u0; // Setting initial condition

    if(SolverType==1) {
        // Use of Newton method
        for(int i=1;i<=N;i++) {
            F=[&](double x){return x-u[i-1]-h*((1-theta)*f(t[i-1],u[i-1])+theta*f(t[i],x));};
            dF=[&](double x){return 1-(theta)*h*(f(t[i],x+1e-4)-f(t[i],x-1e-4))/(2*1e-4);}; // derivative of f approximated with central difference formula (using the same time step)
            std::tuple<double,bool> res=apsc::Newton(F,dF,u[i-1]); // Newton method to find the zero

            if (std::get<1>(res)) {
                u[i]=std::get<0>(res);
            }
            else 
                std::cerr << "Solution does not converge" << std::endl;        
            }   
        }
    else {
        // Use of secant method
        for(int i=1;i<=N;i++) {
            F=[&](double x){return x-u[i-1]-h*(theta*f(t[i-1],u[i-1])+(1-theta)*f(t[i],x));};
            std::tuple<double,bool> res=apsc::secant(F,u[i-1]-0.1,u[i-1]+0.1); // Secant method to find the zero

            if (std::get<1>(res)) {
                u[i]=std::get<0>(res);
                }
            else 
                std::cerr << "Solution does not converge" << std::endl;        
        }
    }

    sol[0]=t;
    sol[1]=u;
    return sol;
}

// Method for computing inf norm (Type=0) or norm 1(Type=0)
double sum(std::vector<double> v,int Type=0) {
    double res=v[0];
    if(Type==1) {
        for (auto i=1; i<v.size();i++) {
        res=res+v[i];
        }
        return res;
    }
    double max=v[0];
    for (auto i=1; i<v.size();i++) {
        if(v[i]>max)
            max=v[i];
    }
    return max;
    }

std::vector<double> ComputeError(std::function<double(double,double)> f,std::function<double(double)> fex, parameters param, std::vector<int> steps) {

    std::vector<double> abserr(steps.size(),0.);

    const auto &[N,u0,T,theta,k,solverType] = param;

    std::array<std::vector<double>,2> res=ThetaMethod(f,u0,T, steps[0],theta);
    std::vector<double> resex(res[0].size(),0.0);
    std::vector<double> err(res[0].size(),0.0);

    for(unsigned int i=0;i<res[1].size();i++) {
        resex[i]=fex(res[0][i]); 
        err[i]=fabs(resex[i]-res[1][i]); 
    }
    abserr[0]=sum(err);

    for (unsigned int i=1; i<steps.size();i++) {

        res=ThetaMethod(f,u0,T, steps[i],theta);
        resex={};
        err={};
        resex.resize(res[1].size());
        err.resize(res[1].size());

        for (unsigned int i=0;i<res[1].size();i++) {
            resex[i]=fex(res[0][i]); 
            err[i]=fabs(resex[i]-res[1][i]);
        }
        abserr[i]=sum(err);
    }

    return abserr;
}
