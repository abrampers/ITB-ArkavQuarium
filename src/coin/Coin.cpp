/* Implementation file of Coin */

#include "../coin/Coin.hpp"

const double COIN_MOVE_SPEED = 10; //TBD
const double COIN_DELETION_INTERVAL = 10; //TBD

Coin::Coin(double x, double y, int value, Aquarium *aquarium) : Aquatic(x, y, aquarium->getCurrTime(), COIN_MOVE_SPEED, aquarium) {
	last_bottom_time = 0;
	this->value = value;
}

int Coin::getValue() const {
	return value;
}

void Coin::updateState() {
	double current_time = this->getAquarium()->getCurrTime();
	move(current_time);
	if (this->getY() == this->getAquarium()->getYMax()) {
		if (current_time - last_bottom_time > COIN_DELETION_INTERVAL) {
			this->getAquarium()->deleteCoin(this);
		}
	}
	this->setLastCurrTime(current_time);
}

/* For coin, X is constant, Y always move downwards */
void Coin::move() {
	double current_time = this->getAquarium()->getCurrTime();
	double dy = this->getMoveSpeed() * ((current_time - this->getLastCurrTime()) / 1000); //Asumsi waktu dalam ms
	if (this->isInside()) {
		if (this->getY() + dy > this->getAquarium()->getYMax()) {
			this->setY(this->getAquarium()->getYMax());
			last_bottom_time = current_time;
		}
		else {
			this->setY(this->getY() + dy);
		}
	}
}