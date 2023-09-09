#pragma once
#include <cstdint>

// Player tag
const uint32_t kCollisionAttributePlayer = 0b1;

// Enemy tag
const uint32_t kCollisionAttributeEnemy = 0b1 << 1;

//Goal tag
const uint32_t kCollisionAttributeGoal = 0b1 << 2;