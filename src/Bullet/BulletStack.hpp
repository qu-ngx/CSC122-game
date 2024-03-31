#ifndef BULLET_STACK_HPP
#define BULLET_STACK_HPP

#include <iostream>
#include "Bullet.hpp"
#include "lib/raymath.h"
#include "lib/raylib.h"

#define MAX_BULLET_COUNT 100
#define BULLET_VELOCITY 10.0
using namespace std;

class BulletStack
{
private:
    int topIndex;
    int stackSize;
    int capacity;
    void increaseCapacity()
    {
        capacity *= 2;
        Bullet *newStack = new Bullet[capacity];
        for (int i = 0; i < stackSize; i++)
        {
            newStack[i] = bullets[i];
        }
        delete[] bullets;
        bullets = newStack;
    }

public:
    Bullet *bullets;

    BulletStack()
    {
        capacity = MAX_BULLET_COUNT;
        bullets = new Bullet[capacity];
        topIndex = 0;
        stackSize = 0;
    }

    ~BulletStack()
    {
        delete[] bullets;
    }

    void push(const Bullet &card)
    {
        if (stackSize == capacity)
        {
            increaseCapacity();
        }
        bullets[topIndex++] = card;
        stackSize++;
    }

    void pop()
    {
        Bullet *bullet = bullets;
        if (stackSize == 0)
        {
            return; // This will return a default-constructed card
        }

        // It will shift elements to the left
        for (int i = topIndex; i < stackSize; i++)
        {
            bullets[i] = bullets[i + 1];
        }
    }

    Bullet *spawn_bullet()
    {
        for (size_t i = 0; i < capacity; i++)
        {
            if (bullets)
            {
                if (!bullets->dead)
                    continue;
                bullets->dead = false;
                return bullets;
            }
            pop();
        }
        return NULL;
    }

    void draw_bullets()
    {
        for (size_t i = 0; i < capacity; i++)
        {
            Bullet bullet = *bullets;
            if (bullets)
            {
                if (bullets->dead)
                    continue;
            }
            DrawLineV(bullet.position, Vector2Add(bullet.position, Vector2Scale(bullet.direction, -10)), YELLOW);
            pop();
        }
    }
};

#endif