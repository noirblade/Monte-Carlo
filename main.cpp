#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <chrono>
using namespace std;

#define CORD_MAX 20
#define SAMPLES_COUNT 10000

int checkPoint(const float coordinates[], int x, int y, int z){

    // ( x-cx ) ^2 + (y-cy) ^2 + (z-cz) ^ 2 < r^2
    float dx = (x-coordinates[0])*(x-coordinates[0]);
    float dy = (y-coordinates[1])*(y-coordinates[1]);
    float dz = (z-coordinates[2])*(z-coordinates[2]);
    float r = (coordinates[3]*coordinates[3]);

    // TODO Check if point is already calculated and exclude from sample
    if (dx + dy + dz <= r){
        return 1;
    }
    return 0;
}

float calcSphereVolume(float coordinates[]){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(-CORD_MAX,CORD_MAX);

    float hits = 0;
    for (int i = 0; i < SAMPLES_COUNT; i++){
        int x = distribution(generator);
        int y = distribution(generator);
        int z = distribution(generator);

        hits += checkPoint(coordinates, x, y, z);
    }
    float r = (2*coordinates[3]) * (2*coordinates[3]) * (2*coordinates[3]);
    return (hits/SAMPLES_COUNT) * r;
}

int main() {
    float coordinates[3];
    float volume = 0.0;

    ifstream inputFile ("energy.inp");
    if (inputFile.is_open())
    {
        int numSpheres = 0;
        inputFile >> numSpheres;

        for (int i = 0; i < numSpheres; i++){
            for (int j = 0; j < 4; j++){
                inputFile >> coordinates[j];
            }
            float subTotal = calcSphereVolume(coordinates);
            volume += subTotal;
            cout << "Sub total energy points " << fixed << setprecision(3) << subTotal << endl;
        }
        inputFile.close();
        cout << "Total energy points " << fixed << setprecision(3) << volume << endl;
    }
    return 0;
}