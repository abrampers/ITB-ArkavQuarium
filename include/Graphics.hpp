#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "master.hpp"

//! Class Graphics. Draw game objects and handle user inputs
class Graphics {
 private:
  const char* fontPath = "assets/fonts/Oswald-Heavy.ttf";
  const int screenWidth, screenHeight;
  int mouse_x, mouse_y;

  std::chrono::high_resolution_clock::time_point start;
  SDL_Window* sdl_window;
  SDL_Surface* g_screen_surface;
  std::map<std::string, SDL_Surface*> loaded_surfaces;
  std::map<int, TTF_Font*> loaded_font_sizes;
  std::set<SDL_Keycode> pressed_keys;
  std::set<SDL_Keycode> tapped_keys;
  std::vector<std::tuple<int, int, int, int> > click_targets;
  int clicked_target;
  bool quit;

  SDL_Surface* loadSurface(std::string path);

 public:
  /* Constructor */
  //! A constructor.
  /*! Constructs a new Graphics object.
              \param int screen_width
              \param int screen_height
  */
  Graphics(int screen_width, int screen_height);

  /* Destructor */
  //! A destructor.
  /*! Destructs the Graphics object. */
  ~Graphics();

  /* Setup */
  //! Initialize game graphics and create the game window
  bool init();

  //! Unload all assets and close the game window
  void close();

  /* High level drawing */
  //! Draw the aquarium backround
  void drawAquarium();

  //! Draw the game's top bar UI
  /*!
          \param int coin_count
          \param int egg_count
  */
  void drawTopBar(int coin_count, int egg_count);

  //! Draw the game's main menu
  void drawMainMenu();

  //! Draw the game's win menu
  void drawWinMenu();

  //! Draw the game's lose menu
  void drawloseMenu();

  //! Draw a guppy on screen
  /*!
          \param int x
          \param int y
          \param int level
          \param State state
          \param int state_progress
  */
  void drawGuppy(int x, int y, int level, State state, int state_progress,
                 bool hungry);

  //! Draw a piranha on screen
  /*!
          \param int x
          \param int y
          \param State state
          \param int state_progress
  */
  void drawPiranha(int x, int y, State state, int state_progress, bool hungry);

  //! Draw a snail on screen
  /*!
          \param int x
          \param int y
          \param State state
          \param int state_progress
  */
  void drawSnail(int x, int y, State state, int state_progress);

  //! Draw a coin on screen
  /*!
          \param int x
          \param int y
  */
  void drawCoin(int x, int y, bool is_gold, int state_progress);

  //! Draw a pellet on screen
  /*!
          \param int x
          \param int y
          \param int state_progress
  */
  void drawPellet(int x, int y, int state_progress);

  /* Low level drawing */
  void clearScreen();
  void updateScreen();
  void drawImage(std::string filename, int x, int y);
  void drawText(std::string text, int font_size, int x, int y, unsigned char r,
                unsigned char g, unsigned char b);

  /* Time */
  //! Get time since graphics is initialized
  /*!
          \return double time sice graphics initialized
  */
  double timeSinceStart();

  /* Input handling */
  //! Handle OS inputs
  void handleInput();

  /* OS events handling */
  //! Check if user has closed the game window
  /*!
          \return bool whethet user closed game window
  */
  bool quitPressed();

  /* Keyboard events handling */
  //! Get pressed keys since handleInput() is last called
  /*!
          Key codes can be seen at: https://wiki.libsdl.org/SDL_Keycode on
     section "SDL_Keycode Value" \return const set<SDL_Keycode>& a set of
     pressed key codes
  */
  const std::set<SDL_Keycode>& getPressedKeys();

  //! Get tapped keys since handleInput() is last called
  /*!
          Key codes can be seen at: https://wiki.libsdl.org/SDL_Keycode on
     section "SDL_Keycode Value" \return const set<SDL_Keycode>& a set of tapped
     key codes
  */
  const std::set<SDL_Keycode>& getTappedKeys();

  /* Mouse events handling */
  //! Register a new click target
  /*!
          \param int x_min
          \param int x_max
          \param int y_min
          \param int y_max
          \return int the id of the newly registered click target
  */
  int addClickTarget(int x_min, int x_max, int y_min, int y_max);

  //! Remove all registered click targets
  void resetClickTargets();

  //! Get the last clicked target since handleInput() is called
  /*!
          \return int the id of the clicked target
  */
  int getClickedTarget();

  //! Get mouse x position
  /*!
          \return int mouse x position
  */
  int getMouseX();

  //! Get mouse y position
  /*!
          \return int mouse y position
  */
  int getMouseY();
};

#endif
