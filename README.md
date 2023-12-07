# Notch_Peak_Filter
Code to calculate the coefficients of a notch, comb or peak filter 

C++ code to calculate the coefficients of a notch, comb or peak filter. The name space is: NOP_FI.

Each filter function will return a 2 rows x N coefficients 2D vector, where Row 1 = Numerator and Row 2 = Denumerator. 

Notch Filter: the function is "std::vector<std::vector > iirnotch_cpp(double, double)". The first argument is the frequency to be notched normalized with respect the Nyquist frequency (0.0 < wo < 1), while the second one if the bandwidth (wo / N) of the filter. The default dB level of the bandwidth is ~3.0103 dB. This function has the overload "std::vector<std::vector > iirnotch_cpp(double, double, double)" allowing the user to choose the dB level of the bandwidth;

Comb/Peak Filter: the function is "std::vector<std::vector<double> > iircomb_cpp(double, double, std::string)". The first two argument is the ratio (or order) between the frequency to be notched (F0) and the sampling frequency (SF)(F0/SF), the second one is the band width of the filter expressed as: (F0/(SF/2))/Q and the third one is a string that can be either "notch" (for the comb filter) or "peak" (for the peak filter). The default dB level of the bandwidth is ~3.0103 dB. Please, remember that the ratio (order) needs to be an integer number. If the user inserts a ratio (order) that is not an integer, the code will return an empty matrix of coefficients. Also, if the user insert a string different from "notch" or "peak", the code will return an empty matrix of coefficients. This function has the overload "std::vector<std::vector<double> > iircomb_cpp(double, double, double, std::string)" allowing the user to choose the dB level of the bandwidth;

Filter the data: the method is "std::vector Filter_Data(std::vector<std::vector >, std::vector)". The two arguments are the filter coefficients and the signal to be filtered. It returns the filtered signal.

If you have any questions and/or want to report bugs, please e-mail me (Ale) at: pressalex@hotmail.com.
