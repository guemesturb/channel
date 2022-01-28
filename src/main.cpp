#include "fluid.h"


int LX; // Simulation-box size in the X direction
int LY; // Simulation-box size in the Y direction
int NX;
int NY;
int NXP;
int NYP;
int IC;
bool PD;
grid_t grid;
vector<double> kx; 
vector<double> ky; 
vector<double> kxp;
vector<double> kyp;
double nu = 0.0005;

int main(int argc, char **argv) {
    
    // Domain size
    
    LX = 1; // Simulation-box size in the X direction
    LY = 1; // Simulation-box size in the Y direction
    NX = 128; // Number of grid points in the X direction
    NY = 128; // Number of grid points in the Y direction
    PD = true;
    double dx = double(LX) / double(NX);
    double dy = double(LY) / double(NY);

    // Initial conditions

    IC = 3;

    // Dealiasing

    NXP = NX * 3 / 2;
    NYP = NY * 3 / 2;

    // Time step setup

    double dt = 1.0/ double(NX) / 4.0; 
    double tmax = 0.5;
    double tout = 0.1;
    double nt = ceil(tmax/dt);
    int nout = ceil(tout/dt);

    // Fourier wavelengths

    kx = createWaveLength(NX, LX);
    ky = createWaveLength(NY, LY);
    kxp = createWaveLength(NXP, LX);
    kyp = createWaveLength(NYP, LY);

    // Grid generation

    vector<double> x = linspace(0, LX, NX + 1);
    vector<double> y = linspace(0, LY, NY + 1);
    
    // Initial conditions

    grid = meshGrid(vector<double>(x.begin(), x.end() - 1), vector<double>(y.begin(), y.end() - 1));

    vector<vector<complex<double>>> omegaHat = initialConditions();

    // Run Navier-Stokes

    for (int i=0; i<nt; i++){
        cout << "Iteration " << i << endl;
        omegaHat = rk4(omegaHat, dt);
    }


    ofstream output_file("omegaHat.txt");
    for (size_t i = 0; i < omegaHat.size(); i++) {
        for (size_t j = 0; j < omegaHat[0].size(); j++) {
            output_file << omegaHat[i][j].real() << "+" << omegaHat[i][j].imag() << "j\n";
        }
    }
    output_file.close();
    output_file.clear();

    vector<vector<complex<double>>> omega = applyIFFT2(omegaHat);

    output_file.open("omega.txt");
    for (size_t i = 0; i < omega.size(); i++) {
        for (size_t j = 0; j < omega[0].size(); j++) {
            output_file << omega[i][j].real() << "\n";
        }
    }

    cout << "Simulation is finished\n";
    
    return 0;
}

