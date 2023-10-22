#include "AssetsEditor.hpp"

namespace ae = assetseditor;

std::vector<std::unique_ptr<GameObject>> AssetLists[50];
std::string AssetListNames[50];

void ae::loop() {
	input();
	update();
	draw();
}

void ae::input() {

}

void ae::update() {

}

void ae::draw() {

}
