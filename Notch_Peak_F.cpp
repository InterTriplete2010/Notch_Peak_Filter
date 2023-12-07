#include <iostream>
#include <fstream>
#include <vector>
#include "Notch_Peak_F.h"

#define PI 3.141592653589793

int main()
{

int coeff_numb = 3;

double WO = 60.0 / (300.0 / 2);
double BW = WO / 35;
double AB = 20;

double q = 35;
double f0 = 60;
double fs = 300;
double BW_Comb = (f0 / (fs / 2)) / q;

NOP_FI::Notch_Peak_F NPF;

//Notch filter with the default dB level
std::vector<std::vector<double>> coeff_final = NPF.iirnotch_cpp(WO, BW);

for (int kk = 0; kk < 2; kk++)
{

    if (kk == 0)
    {

        std::cout << "Numerator notch: " << std::ends;

    }

    else
    {

        std::cout << "Denumerator notch: " << std::ends;

    }

    for (int ll = 0; ll < coeff_numb; ll++)

    {

        std::cout << coeff_final[kk][ll] << "\t" << std::ends;

    }

    std::cout << std::endl;

}

//Notch filter with the selected dB level
std::vector<std::vector<double>> coeff_final_dB = NPF.iirnotch_cpp(WO, BW, AB);

for (int kk = 0; kk < 2; kk++)
{

    if (kk == 0)
    {

        std::cout << "Numerator notch (dB): " << std::ends;

    }

    else
    {

        std::cout << "Denumerator notch(dB): " << std::ends;

    }

    for (int ll = 0; ll < coeff_numb; ll++)

    {

        std::cout << coeff_final_dB[kk][ll] << "\t" << std::ends;

    }

    std::cout << std::endl;

}

//Comb filter
std::vector<std::vector<double>> coeff_final_comb = NPF.iircomb_cpp(fs/f0,BW_Comb,"notch");
std::cout << "\n";

if (coeff_final_comb.size() > 0)
{

    for (int kk = 0; kk < 2; kk++)
    {

        if (kk == 0)
        {

            std::cout << "Numerator Comb: " << std::ends;

        }

        else
        {

            std::cout << "Denumerator Comb: " << std::ends;

        }

        for (int ll = 0; ll < (fs / f0) + 1; ll++)

        {

            std::cout << coeff_final_comb[kk][ll] << "\t" << std::ends;

        }

        std::cout << std::endl;

    }

}

//Comb filter (overload)
std::vector<std::vector<double>> coeff_final_comb_dB = NPF.iircomb_cpp(fs / f0, BW_Comb, AB, "notch");
std::cout << "\n";

if (coeff_final_comb.size() > 0)
{

    for (int kk = 0; kk < 2; kk++)
    {

        if (kk == 0)
        {

            std::cout << "Numerator Comb (dB): " << std::ends;

        }

        else
        {

            std::cout << "Denumerator Comb (dB): " << std::ends;

        }

        for (int ll = 0; ll < (fs / f0) + 1; ll++)

        {

            std::cout << coeff_final_comb_dB[kk][ll] << "\t" << std::ends;

        }

        std::cout << std::endl;

    }

}

//Peak filter
std::vector<std::vector<double>> coeff_final_peak = NPF.iircomb_cpp(fs / f0, BW_Comb, "peak");
std::cout << "\n";

if (coeff_final_peak.size() > 0)
{

    for (int kk = 0; kk < 2; kk++)
    {

        if (kk == 0)
        {

            std::cout << "Numerator Peak: " << std::ends;

        }

        else
        {

            std::cout << "Denumerator Comb: " << std::ends;

        }

        for (int ll = 0; ll < (fs / f0) + 1; ll++)

        {

            std::cout << coeff_final_peak[kk][ll] << "\t" << std::ends;

        }

        std::cout << std::endl;

    }
}

//Peak filter (Overload)
std::vector<std::vector<double>> coeff_final_peak_dB = NPF.iircomb_cpp(fs / f0, BW_Comb, AB, "peak");
std::cout << "\n";

if (coeff_final_peak.size() > 0)
{

    for (int kk = 0; kk < 2; kk++)
    {

        if (kk == 0)
        {

            std::cout << "Numerator Peak (dB): " << std::ends;

        }

        else
        {

            std::cout << "Denumerator Comb (dB): " << std::ends;

        }

        for (int ll = 0; ll < (fs / f0) + 1; ll++)

        {

            std::cout << coeff_final_peak_dB[kk][ll] << "\t" << std::ends;

        }

        std::cout << std::endl;

    }
}

std::vector<std::vector<double>> coeff_final_peak1 = NPF.iircomb_cpp(fs / f0, BW_Comb, "peak1");

//Create a complex sine wave
std::vector<double> test_sin(fs, 0.0);
double sf_1 = 20;
double sf_2 = 60;

std::ofstream myfile;
myfile.open("Waveform.txt");

for (double kk = 0; kk < fs; kk++)
{

    test_sin[kk] = sin(2 * PI * kk * sf_1 / fs) + sin(2 * PI * kk * sf_2 / fs);

    myfile << test_sin[kk];
    myfile << "\n";

}

if (coeff_final_comb.size() > 0)
{

    //std::vector<double> filt_sign = NPF.Filter_Data_NCP(coeff_final_comb, test_sin);
    //std::vector<double> filt_sign = NPF.Filter_Data_NCP(coeff_final_peak, test_sin);
    std::vector<double> filt_sign = NPF.Filter_Data_NCP(coeff_final_peak_dB, test_sin);

    //Write the output of the filter to a file
    std::ofstream myfile_I;
    myfile_I.open("Output_Filter.txt");
    for (int kk = 0; kk < filt_sign.size(); kk++)
    {

        myfile_I << filt_sign[kk];
        myfile_I << "\n";

    }

}

}
