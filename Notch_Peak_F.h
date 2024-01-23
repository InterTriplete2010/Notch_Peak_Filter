#pragma once
#include <stdio.h>
#include <vector>

#ifndef Notch_Peak_F_H
#define Notch_Peak_F_H

#ifdef __cplusplus
extern "C" {  // only need to export C interface if
              // used by C++ source code
#endif

    namespace NOP_FI
    {

        class Notch_Peak_F

        {

        public:

            //Estimate the coeffients of a band-pass filter and return a 2 rows x N coefficients matrix. Row 1 = Numerator; Row 2 = Denumerator
            std::vector<std::vector<double> > iirnotch_cpp(double, double); //Notch filter
            std::vector<std::vector<double> > iirnotch_cpp(double, double, double); //Overload of the Notch filter allowing the user to specify the dB level of the bandwidth

            std::vector<std::vector<double> > iircomb_cpp(double, double, std::string); //Comb or peak filter
            std::vector<std::vector<double> > iircomb_cpp(double, double, double, std::string); //Overload of the Comb or peak filter allowing the user to specify the dB level of the bandwidth

            //Filter the data by using the Direct-Form II Transpose, as explained in the Matlab documentation
            std::vector<double> Filter_Data_NCP(std::vector<std::vector<double> >, std::vector<double>);

        };

    }

#endif

#ifdef __cplusplus

}

#endif
