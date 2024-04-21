/******************************************************************************************************
 * @file  Particle.cpp
 * @brief Implementation of the Particle class
 ******************************************************************************************************/

#include "Particle.hpp"

Particle::Particle(const vec2& pos, const vec2& speed, const vec2& force, float mass)
    : pos(pos), speed(speed), force(force), mass(mass) { }

