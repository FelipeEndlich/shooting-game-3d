#include "scene.hpp"
#include "svg_reader.hpp"

using ::game::SceneObjectType;
using ::game::SVGList;
using ::game::GameScene;
using ::graphics::shapes::Cuboid;

GameScene::GameScene(const char* scene_path) {
    SVGList reader(scene_path);
    auto scene_objects = reader.scene_objects();

    for (auto scene_object : scene_objects) {
        SceneObjectType t = scene_object.t;
        Cuboid r = scene_object.r;

        if (t == SceneObjectType::HERO)
            hero = new Cuboid(r);
        else if (t == SceneObjectType::ENEMY)
            enemies.push_back(new Cuboid(r));
        else if (t == SceneObjectType::OBSTACLE)
            obstacles.push_back(new Cuboid(r));
        else if (t == SceneObjectType::BACKGROUND)
            background = new Cuboid(r);
    }
}

void GameScene::Draw() {
    background->Draw();
    for (auto obstacle : obstacles)
        obstacle->Draw();
    for (auto enemy : enemies)
        enemy->Draw();
    hero->Draw();
}