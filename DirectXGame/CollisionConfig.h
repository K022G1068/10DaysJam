#pragma once
#include <cstdint>

// Player tag
const uint32_t kCollisionAttributePlayer = 0b1;

// Enemy tag
const uint32_t kCollisionAttributeEnemy = 0b1 << 1;

//Goal tag
const uint32_t kCollisionAttributeGoal = 0b1 << 2;

//Any
const uint32_t kCollisionAttributeAny = 0b1 << 3;

//Spot tag
const uint32_t kCollisionAttributeSpot = 0b1 << 4;