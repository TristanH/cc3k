#include "Chamber.h"
using namespace std;

void Chamber::updateEnemies() {

}

void Chamber::addEnemy(Enemy *e) {
    enemies.push_back(e);
}

void Chamber::update() {
    updateEnemies();
}