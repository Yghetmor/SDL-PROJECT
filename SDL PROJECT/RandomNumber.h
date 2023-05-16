#pragma once
#include <random>
#include <functional>

auto createUniformPseudoRandomNumberGenerator(int min, int max)
{
    std::random_device seeder;        // True random number generator to obtain a seed (slow) 
    std::default_random_engine generator{ seeder() };       // Efficient pseudo-random generator 
    std::uniform_int_distribution distribution{ min, max };   // Generate in [min, max] interval 
    return std::bind(distribution, generator);       // and in the darkness bind them! 
}