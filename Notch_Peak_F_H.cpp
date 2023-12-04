#include <stdio.h>
#include <string>
#include <vector>
#include "Notch_Peak_F.h"

#define PI 3.141592653589793

using namespace NOP_FI;

std::vector<double> num_filt;   //Vector where to temporarily save the numerator
std::vector<double> den_filt;   // Vector where to temporarily save the denumerator
std::vector<std::vector<double> > save_filt_coeff;  //Matrix where to save the numerator and denominator. First row is the numerator; second row is the denominator

//Notch Filter
std::vector<std::vector<double>> Notch_Peak_F::iirnotch_cpp(double WO, double BW)
{

	//Reset the matrix to save the numerator
	num_filt.erase(num_filt.begin(), num_filt.begin() + num_filt.size());
	//Reset the matrix to save the denumerator
	den_filt.erase(den_filt.begin(), den_filt.begin() + den_filt.size());

	int numb_coeff = 3;

	//Default value
	double AB = abs(10*log10(0.5));	//it corresponds to abs(-3dB)

	//Normalize the input by PI
	WO = WO * PI;
	BW = BW * PI;

	double GB = pow(10,(-AB / 20));
	double BETA = (sqrt(1 - pow(GB, 2)) / GB)* tan(BW / 2);
	double GAIN = 1 / (1 + BETA);

	//Calculate the numerator
	for (int kk = 0; kk < numb_coeff; kk++)
	{

		if (kk != 1)
		{

			num_filt.push_back(GAIN);

		}

		else
		{

			num_filt.push_back(-GAIN*2*cos(WO));

		}

	}

	//Calculate the denominator
	for (int kk = 0; kk < numb_coeff; kk++)
	{

		switch (kk)
		{

		case 0:

			den_filt.push_back(1);
			break;

		case 1:

			den_filt.push_back(-2*GAIN*cos(WO));
			break;

		case 2:

			den_filt.push_back(2 * GAIN - 1);
			break;
		
		}

	}

	//Reset the matrix to save the coefficients
	save_filt_coeff.erase(save_filt_coeff.begin(), save_filt_coeff.begin() + save_filt_coeff.size());

	std::vector<double> temp_v;

	for (int ff = 0; ff < numb_coeff; ff++)
	{

		temp_v.push_back(0);

	}

	for (int hh = 0; hh < 2; hh++)
	{

		save_filt_coeff.push_back(temp_v);

	}


	//Save the coefficients in the output matrix
	for (int kk = 0; kk < 2; kk++)
	{

		for (int ll = 0; ll < numb_coeff; ll++)
		{

			if (kk == 0)
			{

				save_filt_coeff[kk][ll] = num_filt[ll];

			}

			else
			{

				save_filt_coeff[kk][ll] = den_filt[ll];

			}

		}

	}

	return save_filt_coeff;

}

//Comb filter
std::vector<std::vector<double>> Notch_Peak_F::iircomb_cpp(double order, double BW, std::string type_filt)
{

	//Reset the matrix to save the numerator
	num_filt.erase(num_filt.begin(), num_filt.begin() + num_filt.size());
	//Reset the matrix to save the denumerator
	den_filt.erase(den_filt.begin(), den_filt.begin() + den_filt.size());

	//Reset the matrix to save the coefficients
	save_filt_coeff.erase(save_filt_coeff.begin(), save_filt_coeff.begin() + save_filt_coeff.size());

	//If the order is not an integer value, then return an empty matrix of coefficients
	if (order != round(order))
	{

		return save_filt_coeff;

	}

	//Default value
	double AB = abs(10 * log10(0.5));	//it corresponds to abs(-3dB)

	//Normalize the input by PI
	BW = BW * PI;

	double GB = pow(10, (-AB / 20));

	if (type_filt.compare("notch") == 0)
	{

		double BETA = (sqrt(1 - pow(GB, 2)) / GB) * tan(order * BW / 4);
		double GAIN = 1 / (1 + BETA);

		//Calculate the numerator
		for (int kk = 0; kk < order + 1; kk++)
		{

			if (kk == 0)
			{

				num_filt.push_back(GAIN);

			}

			else if (kk == order)
			{

				num_filt.push_back(-GAIN);

			}

			else
			{

				num_filt.push_back(0);

			}

		}

		//Calculate the denominator
		for (int kk = 0; kk < order + 1; kk++)
		{

			if (kk == 0)
			{

				den_filt.push_back(1);

			}

			else if (kk == order)
			{

				den_filt.push_back(-(2 * GAIN - 1));

			}

			else
			{

				den_filt.push_back(0);

			}

		}

	}

	else if (type_filt.compare("peak") == 0)
	{
	
		double BETA = (GB / sqrt(1 - pow(GB, 2))) * tan(order * BW / 4);
		double GAIN = 1 / (1 + BETA);

		//Calculate the numerator
		for (int kk = 0; kk < order + 1; kk++)
		{

			if (kk == 0)
			{

				num_filt.push_back(1 - GAIN);

			}

			else if (kk == order)
			{

				num_filt.push_back(-(1 - GAIN));

			}

			else
			{

				num_filt.push_back(0);

			}

		}

		//Calculate the denominator
		for (int kk = 0; kk < order + 1; kk++)
		{

			if (kk == 0)
			{

				den_filt.push_back(1);

			}

			else if (kk == order)
			{

				den_filt.push_back(2 * GAIN - 1);

			}

			else
			{

				den_filt.push_back(0);

			}

		}


	}

	else
	{

		//Return an empty matrix, if the user did not entered either "notch" or "peak"
		return save_filt_coeff;

	}
	

		std::vector<double> temp_v;

		for (int ff = 0; ff < order + 1; ff++)
		{

			temp_v.push_back(0);

		}

		for (int hh = 0; hh < 2; hh++)
		{

			save_filt_coeff.push_back(temp_v);

		}


		//Save the coefficients in the output matrix
		for (int kk = 0; kk < 2; kk++)
		{

			for (int ll = 0; ll < order + 1; ll++)
			{

				if (kk == 0)
				{

					save_filt_coeff[kk][ll] = num_filt[ll];

				}

				else
				{

					save_filt_coeff[kk][ll] = den_filt[ll];

				}

			}

		}

	return save_filt_coeff;

}

//Filter the data by using the Direct-Form II Transpose, as explained in the Matlab documentation
std::vector<double> Notch_Peak_F::Filter_Data_NCP(std::vector<std::vector<double> > coeff_filt, std::vector<double> pre_filt_signal)
{

	std::vector<double> filt_signal(pre_filt_signal.size(), 0.0);

	std::vector<std::vector<double>> w_val;
	std::vector<double> temp_v;

	for (int ff = 0; ff < pre_filt_signal.size(); ff++)
	{

		temp_v.push_back(0);

	}

	for (int hh = 0; hh < coeff_filt[0].size(); hh++)
	{

		w_val.push_back(temp_v);

	}


	//Convolution product to filter the data
	for (int kk = 0; kk < pre_filt_signal.size(); kk++)
	{

		if (kk == 0)
		{

			filt_signal[kk] = pre_filt_signal[kk] * coeff_filt[0][0];

			for (int ww = 1; ww < coeff_filt[0].size(); ww++)
			{

				w_val[ww - 1][kk] = pre_filt_signal[kk] * coeff_filt[0][ww] - filt_signal[kk] * coeff_filt[1][ww];

			}

		}

		else
		{

			filt_signal[kk] = pre_filt_signal[kk] * coeff_filt[0][0] + w_val[0][kk - 1];

			for (int ww = 1; ww < coeff_filt[0].size(); ww++)
			{

				w_val[ww - 1][kk] = pre_filt_signal[kk] * coeff_filt[0][ww] + w_val[ww][kk - 1] - filt_signal[kk] * coeff_filt[1][ww];

				if (ww == coeff_filt[0].size() - 1)
				{

					w_val[ww - 1][kk] = pre_filt_signal[kk] * coeff_filt[0][ww] - filt_signal[kk] * coeff_filt[1][ww];

				}

			}

		}

	}


	return filt_signal;

}
