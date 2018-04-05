#ifndef AQUARIUM_HPP
#define AQUARIUM_HPP

#include "LinkedList.hpp"
#include "Aquatic.hpp"
#include "Coin.hpp"
#include "Guppy.hpp"
#include "Pellet.hpp"
#include "Piranha.hpp"
#include "Snail.hpp"

class Aquarium {
    private:
        const int xMax, yMax;
        int time;
        LinkedList<Coin*> content_coin;
        LinkedList<Guppy*> content_guppy;
        LinkedList<Pellet*> content_pellet;
        LinkedList<Piranha*> content_piranha;
        LinkedList<Snail*> content_snail;
    public:
        /* Constructor */
        Aquarium();

        /* Destructor */
        ~Aquarium();
        
        /* Operator Overloading */

        /* Setter & Getter */
        int getXMax() const;
        int getYMax() const;

        /* Methods */
        bool isInside(const Aquatic& aquatic);

        /* TODO: check if this is necessary */
        /* A function that will increment time and processes all content (coin moves down, etc.) */
        void advTime();
};

#endif