#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <complex> 
#include <fftw3.h>

using namespace std;

#define PI 3.14159265f

// Viscosity



struct grid_t{
  vector<vector<double>> XX;
  vector<vector<double>> YY;
};

struct complex_t{
  vector<vector<double>> real;
  vector<vector<double>> imag;
};

extern int NX;
extern int NY;
extern int NXP;
extern int NYP;
extern int LX;
extern int LY;
extern int IC;
extern bool PD;
extern grid_t grid;
extern vector<double> kx; 
extern vector<double> ky; 
extern vector<double> kxp;
extern vector<double> kyp;
extern double nu;

vector<double> createWaveLength(int, int);
vector<double> linspace(int, int, int);
vector<vector<complex<double>>> initialConditions();
vector<vector<complex<double>>> taylorVortex(double, double, double, double);
vector<vector<double>> sumMatrices(vector<vector<double>>, vector<vector<double>>);
vector<vector<complex<double>>> sumComplexMatrices(vector<vector<complex<double>>>, vector<vector<complex<double>>>);
grid_t meshGrid(vector<double>, vector<double>);

vector<vector<complex<double>>> applyFFT2(vector<vector<double>>);
vector<vector<complex<double>>> applyIFFT2(vector<vector<complex<double>>>);
vector<vector<complex<double>>> applyFFT2Complex(vector<vector<complex<double>>>);

vector<vector<complex<double>>> rk4(vector<vector<complex<double>>>, double);
vector<vector<complex<double>>> rhs(vector<vector<complex<double>>>);
vector<vector<complex<double>>> advection(vector<vector<complex<double>>>);
vector<vector<complex<double>>> pad(vector<vector<complex<double>>>);
vector<vector<complex<double>>> chop(vector<vector<complex<double>>>);