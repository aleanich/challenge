// Class Reader for the parameter
#ifndef READER_HH
#define READER_HH

#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <iosfwd>
#include <iomanip>
#include <nlohmann/json.hpp>
#include "json.hpp"
#include <muParser.h>
#include <memory>

struct parameters
{
  //! Number of subintervals
  int N = 100;
  //! Initial condition
  double u0=0;
  //! Final time
  double T=1.;
  //! Theta [0,1]
  double theta=0.5;
  //! force term
  std::string f="-t*exp(-y)";
  //! exact solution
  std::string fex="log(1-t*t/2)";
  //! Number of refinement
  int k=4;
  //! type of solver (0 Newton, 1 Secant)
  int solverType = 0;
};
//! Prints parameters
std::ostream &operator<<(std::ostream & out, const parameters & p) 
    {
        out << "PARAMETER VALUES:"
            << "\n";
        out << "N= " << p.N << "\n";
        out << "u0= " << p.u0 << "\n";
        out << "T= " << p.T << "\n";
        out << "Theta= " << p.theta << "\n";
        out << "f= " << p.f << "\n";
        out << "fex= " << p.fex << "\n";
        out << "k= " << p.k << "\n";
        out << "Solver type=" << p.solverType << "\n\n";
        return out;
}


class Reader 
{
    private:
        const std::string file;

    public:
        Reader(const std::string & filename) : file(filename) {};

        parameters readParameters_json(bool verbose=false) const {
            // Parameter default constructor fills it with the defaults values
            parameters defaults;
            // checks if file exixts and is readable
            std::ifstream check(file);
            if(!check)
                {
                std::cerr << "ERROR: Parameter file " << file << " does not exist"
                            << std::endl;
                std::cerr << "Reverting to default values." << std::endl;
                if(verbose)
                    std::cout << defaults;
                check.close();
                return defaults;
                }
            else
                check.close();

            std::ifstream jfile(file);
            nlohmann::json ifile;
            jfile>>ifile;
            parameters values;
            // Read parameters from getpot ddata base
            //values.itermax = ifile.value("itermax", defaults.itermax);
            //values.toler = ifile.value("toler", defaults.toler);
            values.N = ifile.value("N", defaults.N); //.value cerca se è presente param L altrimenti prende quello di default
            values.u0 = ifile.value("u0", defaults.u0);
            values.T = ifile.value("T", defaults.T);
            values.theta = ifile.value("theta", defaults.theta);
            values.f = ifile.value("f", defaults.f);
            values.fex = ifile.value("fex", defaults.fex);
            values.k = ifile.value("k", defaults.k);
            values.solverType = ifile.value("solverType", defaults.solverType);
            if(verbose)
                {
                std::cout << "PARAMETER VALUES IN JSON FILE"
                            << "\n";
                std::cout<<std::setw(4)<<ifile;
                std::cout << std::endl;
                std::cout << "ACTUAL VALUES"
                            << "\n"
                            << values;
                }
            return values;
                    }

};

// Parser for multivariate functions
class MuparserFun2V
{
    private:
        double     m_var1;
        double     m_var2;
        mu::Parser m_parser;
    
    public:
        MuparserFun2V(const MuparserFun2V &m)
            : m_parser(m.m_parser)
        {
            m_parser.DefineVar("t", &m_var1);
            m_parser.DefineVar("y", &m_var2);
        };

        MuparserFun2V(const std::string &s)
        {
            try
            {
                m_parser.DefineVar("t", &m_var1);
                m_parser.DefineVar("y", &m_var2);
                m_parser.SetExpr(s);
            }
            catch (mu::Parser::exception_type &e)
            {
                std::cerr << e.GetMsg() << std::endl;
            }
        };

        double
        operator()(const double &t, const double &y)
        {
            double z = 0;

            m_var1 = t;
            m_var2 = y;

            try
            {
                z = m_parser.Eval();
            }
            catch (mu::Parser::exception_type &e)
            {
                std::cerr << e.GetMsg() << std::endl;
            }
            return z;
        };

};

// Parser for univariate functions
class MuparserFun1V
{
    private:
        double     m_var1;
        mu::Parser m_parser;
    
    public:
        MuparserFun1V(const MuparserFun1V &m)
            : m_parser(m.m_parser)
        {
            m_parser.DefineVar("t", &m_var1);
        };

        MuparserFun1V(const std::string &s)
        {
            try
            {
                m_parser.DefineVar("t", &m_var1);
                m_parser.SetExpr(s);
            }
            catch (mu::Parser::exception_type &e)
            {
                std::cerr << e.GetMsg() << std::endl;
            }
        };

        double
        operator()(const double &t)
        {
            double z = 0;

            m_var1 = t;

            try
            {
                z = m_parser.Eval();
            }
            catch (mu::Parser::exception_type &e)
            {
                std::cerr << e.GetMsg() << std::endl;
            }
            return z;
        };

};


#endif
