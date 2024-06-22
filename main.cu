#include "utils/ppm.hpp"
#include "test.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdio> // For sscanf

void printUsage() 
{
    std::cerr << "Usage: " << std::endl
              << " \t -f <F>: <F> image file name"
              << std::endl << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) 
{   
    char fileName[2048];

    // Parse program arguments
    if (argc == 1) 
    {
        std::cerr << "Please give a file..." << std::endl;
        printUsage();
    }

    for (int i = 1; i < argc; ++i) 
    {
        if (!strcmp(argv[i], "-f")) 
        {
            if (sscanf(argv[++i], "%2047s", fileName) != 1)
                printUsage();
        }
        else
            printUsage();
    }

    // ================================================================================================================
    // Get input image
    std::cout << "Loading image: " << fileName << std::endl;
    const los::Heightmap input(fileName);
    const int width = input.getWidth();
    const int height = input.getHeight();

    std::cout << "Image has " << width << " x " << height << " pixels" << std::endl;

    std::string baseSaveName = fileName;
    baseSaveName.erase(baseSaveName.end() - 4, baseSaveName.end()); // erase .ppm

    // Create 3 output images
    los::Heightmap outCPU(width, height);

    // ================================================================================================================

    // CPU sequential
    std::cout << "============================================" << std::endl;
    std::cout << "         Sequential version on CPU          " << std::endl;
    std::cout << "============================================" << std::endl;

    Point center(245, 497);
	
    const float timeCPU = naive_viewtestCPU(input, center, outCPU);

    std::string cpuName = baseSaveName + "resultat.ppm";
    outCPU.saveTo(cpuName.c_str());

    std::cout << "-> Done : " << timeCPU << " ms" << std::endl << std::endl;

    // ================================================================================================================

    // GPU CUDA

    return EXIT_SUCCESS;
}
