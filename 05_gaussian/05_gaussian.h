//----------------------------------------------------------------------
// 05_gaussian.h
//----------------------------------------------------------------------

#ifndef GAUSSIAN_H
#define GAUSSIAN_H

// Return the value of the Gaussian probability function with mean mu
// and standard deviation sigma at the given x value.
double pdf(const double x, const double mu, const double sigma);

// Return the value of the cumulative Gaussian distribution function
// with mean mu and standard deviation sigma at the given z value.
double cdf(const double z, const double mu, const double sigma);

#endif
