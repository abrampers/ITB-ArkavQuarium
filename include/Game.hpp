#ifndef GAME_HPP
#define GAME_HPP

#include <math.h>

#include <iostream>
#include <sstream>

#include "Aquarium.hpp"
#include "Graphics.hpp"
#include "master.hpp"

//! Class Game. Control the game state and synchronize the game object state
class Game {
 private:
  /* Graphics */
  const int aquariumXStart;
  const int aquariumXEnd;
  const int aquariumYStart;
  const int aquariumYEnd;
  const double frameRate;
  Graphics graphics;

  /* Game state */
  Aquarium *aquarium;
  double game_start_time;

  /* Player state */
  int coin;
  int egg;

 public:
  /* Constructor */
  //! A constructor.
  /*! Constructs a new Game object. */
  Game();

  /* Destructor */
  //! A destructor.
  /*! Destructs the Game object. */
  ~Game();

  //! Initialize game state
  void initState();

  //! Load game state from an external file
  /*! \param string filename */
  void loadState(std::string filename);

  //! Save game state to an external file
  /*! \param string filename */
  void saveState(std::string filename);

  //! Start the game
  /*! \return GameState state of the last game */
  GameState startGame();

  //! Show the game main menu
  /*! \return GameState state of the last game */
  GameState showMainMenu();

  //! Show win menu
  /*! \return GameState state of the last game */
  GameState showWinMenu();

  //! Show lose menu
  /*! \return GameState state of the last game */
  GameState showloseMenu();

  //! Run game sequence
  void run();
};

#endif
