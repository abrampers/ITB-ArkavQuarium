#ifndef PIRANHA_HPP
#define PIRANHA_HPP

#include "Aquatic.hpp"
#include "Fish.hpp"
#include "Guppy.hpp"
#include "LinkedList.hpp"

//! Class Piranha. Represents all Piranha object in Aquarium.
class Piranha : public Aquatic, public Fish {
 private:
  Guppy *nearest_guppy;

  /****************************/
  /* Private member functions */
  /****************************/
  void findNearestGuppy();
  bool nearestGuppyInRange();
  /* Euclidean distance from guppy to pellet */
  double distanceToGuppy(Guppy *p);

 public:
  /* Constructor */
  //! A constructor.
  /*! Constructs a new Piranha object.
      \param Aquarium *aquarium The Aquarium that contains the Piranha.
  */
  Piranha(Aquarium *aquarium);

  /***********/
  /* Methods */
  /***********/
  /* Implements pure virtual method from Aquatic */
  //! Implements pure virtual method from Aquatic
  void updateState() override;

  //! Implements pure virtual method from Aquatic
  void move() override;

  //! Implements pure virtual method from Aquatic
  void updateProgress() override;

  //! Implements pure virtual method from Aquatic
  void dead() override;

  /* Implements pure virtual method from Fish */
  //! Implements pure virtual method from Fish
  /*! Search for Guppy nearby, if the Guppy is in range, eat. */
  void eat() override;

  //! Implements pure virtual method from Fish
  /*! Drop coin every time Piranha eats. */
  void dropCoin() override;
};

#endif
