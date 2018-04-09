#include "Game.hpp"

#include <set>
#include <vector>

using namespace std;

Game::Game():
aquariumXStart(20),
aquariumXEnd(gameScreenWidth - 20),
aquariumYStart(200),
aquariumYEnd(gameScreenHeight - 100),
frameRate(gameFrameRate), 
graphics(gameScreenWidth, gameScreenHeight),
coin(0),
egg(0) {
    /* Initialize game graphics */
    bool succ = graphics.init();
    if (!succ) {
        cerr << "ERROR: Game initialization failed." << endl;
    }
}

/* Destructor */
Game::~Game() {
    delete aquarium;
    graphics.close();
}

/* Initialize game state */
void Game::initState() {
    aquarium = new Aquarium(aquariumXStart, aquariumYStart, aquariumXEnd, aquariumYEnd);
    game_start_time = graphics.timeSinceStart();
}

/* Load game state from an external file */
void Game::loadState(string filename) {
    /* TODO */
}

/* Save game state to an external file */
void Game::saveState(string filename) {
    /* TODO */
}

/* Start a game */
void Game::startGame() {

    bool running = true;

    while (running) {
        /* Start frame timer */
        double game_current_time = graphics.timeSinceStart();

        /* Reset mouse click targets */
        graphics.resetClickTargets();

        /* Update objects state */
        aquarium->updateState(game_current_time - game_start_time);
        LinkedList<Guppy*>& guppy_list = aquarium->getGuppyList();
        LinkedList<Piranha*>& piranha_list = aquarium->getPiranhaList();
        LinkedList<Snail*>& snail_list = aquarium->getSnailList();
        LinkedList<Pellet*>& pellet_list = aquarium->getPelletList();
        LinkedList<Coin*>& coin_list = aquarium->getCoinList();
        vector<int> coin_click_targets;

        /* Draw UI */
        graphics.drawAquarium();
        graphics.drawCoinText(coin);

        /* Draw Guppy */
        for (int i = 0; i < guppy_list.getLength(); i++) {
            Guppy *curr_guppy = guppy_list.get(i);
            double curr_guppy_x = curr_guppy->getX();
            double curr_guppy_y = curr_guppy->getY();
            int curr_guppy_level = curr_guppy->getLevel();
            State curr_guppy_state = curr_guppy->getState();
            int curr_guppy_state_progress = curr_guppy->getProgress();
            graphics.drawGuppy(curr_guppy_x, curr_guppy_y, curr_guppy_level, curr_guppy_state, curr_guppy_state_progress);
        }

        /* Draw Piranha */
        for (int i = 0; i < piranha_list.getLength(); i++) {
            Piranha *curr_piranha = piranha_list.get(i);
            double curr_piranha_x = curr_piranha->getX();
            double curr_piranha_y = curr_piranha->getY();
            State curr_piranha_state = curr_piranha->getState();
            int curr_piranha_state_progress = curr_piranha->getProgress();
            graphics.drawPiranha(curr_piranha_x, curr_piranha_y, curr_piranha_state, curr_piranha_state_progress);
        }
        
        /* Draw Snail and get coins */
        for (int i = 0; i < snail_list.getLength(); i++) {
            Snail *curr_snail = snail_list.get(i);
            double curr_snail_x = curr_snail->getX();
            double curr_snail_y = curr_snail->getY();
            State curr_snail_state = curr_snail->getState();
            int curr_snail_state_progress = curr_snail->getProgress();
            graphics.drawSnail(curr_snail_x, curr_snail_y, curr_snail_state, curr_snail_state_progress);
            coin += curr_snail->getCoin();
            curr_snail->resetCoin();
        }

        /* Draw Pellet */
        for (int i = 0; i < pellet_list.getLength(); i++) {
            Pellet *curr_pellet = pellet_list.get(i);
            double curr_pellet_x = curr_pellet->getX();
            double curr_pellet_y = curr_pellet->getY();
            int curr_pellet_state_progress = curr_pellet->getProgress();
            graphics.drawPellet(curr_pellet_x, curr_pellet_y, curr_pellet_state_progress);
        }

        /* Draw Coin and register mouse click targets */
        for (int i = 0; i < coin_list.getLength(); i++) {
            Coin *curr_coin = coin_list.get(i);
            double curr_coin_x = curr_coin->getX();
            double curr_coin_y = curr_coin->getY();
            graphics.drawCoin(curr_coin_x, curr_coin_y);
            int click_target = graphics.addClickTarget(
                curr_coin_x - coinClickRadius,
                curr_coin_x + coinClickRadius,
                curr_coin_y - coinClickRadius,
                curr_coin_y + coinClickRadius);
            coin_click_targets.push_back(click_target);
        }

        /* Handle input from OS */
        graphics.handleInput();

        /* Check mouse click events */
        int clicked_target = graphics.getClickedTarget();
        if (clicked_target == 0) {
            int x = graphics.getMouseX();
            int y = graphics.getMouseY();
            aquarium->createPellet(x, y);
        } else {
            for (int i = 0; i < coin_click_targets.size(); i++) {
                if (clicked_target == coin_click_targets[i]) {
                    coin += coin_list.get(i)->getValue();
                    aquarium->deleteCoin(coin_list.get(i));
                    break;
                }
            }
        }

        for (auto key : graphics.getPressedKeys()) {
            switch (key) {
            case SDLK_p:
                aquarium->createPiranha();
                break;
            case SDLK_g:
                aquarium->createGuppy();
                break;
            }
        }

        /* Quit loop if UI quit button is clicked */
        if (graphics.quitPressed()) {
            running = false;
        }
        
        /* Update objects on screen */
        graphics.updateScreen();

        /* Wait until frame time reaches 1 / frameRate */
        while (graphics.timeSinceStart() - game_current_time < 1.0 / frameRate);
        // cout << "FPS: " << 1.0 / (graphics.timeSinceStart() - game_current_time) << endl;
    }
}

/* Run game sequence */
void Game::run() {

    /* TODO: Show main menu */
    
    /* Init game states */
    initState();
    startGame();

}
