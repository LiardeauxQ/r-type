//
// Created by alex on 11/26/19.
//

#include "DummyBundle.hpp"

void DummyBundle::load(ecs::World& m_world, EventHandler& handler)
{
    auto p_position = ecs::Component("Position");

    p_position.addAttribute(ecs::ComponentAttribute(String("x"), ecs::AttributeType::INT, std::any(0)));
    p_position.addAttribute(ecs::ComponentAttribute(String("y"), ecs::AttributeType::INT, std::any(0)));
    p_position.addAttribute(ecs::ComponentAttribute(String("z"), ecs::AttributeType::INT, std::any(0)));

    auto p_velocity = ecs::Component("Velocity");

    p_velocity.addAttribute(ecs::ComponentAttribute(String("x"), ecs::AttributeType::INT, std::any(0)));
    p_velocity.addAttribute(ecs::ComponentAttribute(String("y"), ecs::AttributeType::INT, std::any(0)));
    p_velocity.addAttribute(ecs::ComponentAttribute(String("z"), ecs::AttributeType::INT, std::any(0)));

    auto p_health = ecs::Component("Health");

    p_health.addAttribute(ecs::ComponentAttribute(String("max"), ecs::AttributeType::INT, std::any(0)));
    p_health.addAttribute(ecs::ComponentAttribute(String("amount"), ecs::AttributeType::INT, std::any(0)));

    auto p_damage = ecs::Component("Damage");

    p_damage.addAttribute(ecs::ComponentAttribute(String("amount"), ecs::AttributeType::INT, std::any(0)));

    auto p_team = ecs::Component("Team");

    p_team.addAttribute(ecs::ComponentAttribute(String("id"), ecs::AttributeType::INT, std::any(0)));

    auto p_attack_speed = ecs::Component("AttackSpeed");

    p_attack_speed.addAttribute(ecs::ComponentAttribute(String("frequency"), ecs::AttributeType::INT, std::any(0)));
    p_attack_speed.addAttribute(ecs::ComponentAttribute(String("elapsed_time"), ecs::AttributeType::INT, std::any(0)));

    auto player = ecs::EntityBuilder()
            .with(p_position)
            .with(p_velocity)
            .with(p_health)
            .with(p_damage)
            .with(p_team)
            .with(p_attack_speed);
    m_world.storeEntity(player.build());

    auto s_position = ecs::Component("Position");

    s_position.addAttribute(ecs::ComponentAttribute(String("x"), ecs::AttributeType::INT, std::any(0)));
    s_position.addAttribute(ecs::ComponentAttribute(String("y"), ecs::AttributeType::INT, std::any(0)));
    s_position.addAttribute(ecs::ComponentAttribute(String("z"), ecs::AttributeType::INT, std::any(0)));

    auto s_velocity = ecs::Component("Velocity");

    s_velocity.addAttribute(ecs::ComponentAttribute(String("x"), ecs::AttributeType::INT, std::any(0)));
    s_velocity.addAttribute(ecs::ComponentAttribute(String("y"), ecs::AttributeType::INT, std::any(0)));
    s_velocity.addAttribute(ecs::ComponentAttribute(String("z"), ecs::AttributeType::INT, std::any(0)));

    auto s_team = ecs::Component("Team");

    s_team.addAttribute(ecs::ComponentAttribute(String("id"), ecs::AttributeType::INT, std::any(0)));

    auto s_attack_speed = ecs::Component("AttackSpeed");

    s_attack_speed.addAttribute(ecs::ComponentAttribute(String("frequency"), ecs::AttributeType::INT, std::any(0)));
    s_attack_speed.addAttribute(ecs::ComponentAttribute(String("elapsed_time"), ecs::AttributeType::INT, std::any(0)));

    auto spawner = ecs::EntityBuilder()
            .with(s_position)
            .with(s_velocity)
            .with(s_team)
            .with(s_attack_speed);
    m_world.storeEntity(spawner.build());
}

void DummyBundle::create_bullet(ecs::World &m_world, int team_id, int x, int y) {
    auto b_position = ecs::Component("Position");

    b_position.addAttribute(ecs::ComponentAttribute(String("x"), ecs::AttributeType::INT, std::any(x)));
    b_position.addAttribute(ecs::ComponentAttribute(String("y"), ecs::AttributeType::INT, std::any(y)));
    b_position.addAttribute(ecs::ComponentAttribute(String("z"), ecs::AttributeType::INT, std::any(0)));

    auto b_velocity = ecs::Component("Velocity");

    b_velocity.addAttribute(ecs::ComponentAttribute(String("x"), ecs::AttributeType::INT, std::any(0)));
    b_velocity.addAttribute(ecs::ComponentAttribute(String("y"), ecs::AttributeType::INT, std::any(0)));
    b_velocity.addAttribute(ecs::ComponentAttribute(String("z"), ecs::AttributeType::INT, std::any(0)));

    auto b_health = ecs::Component("Health");

    b_health.addAttribute(ecs::ComponentAttribute(String("max"), ecs::AttributeType::INT, std::any(0)));
    b_health.addAttribute(ecs::ComponentAttribute(String("amount"), ecs::AttributeType::INT, std::any(0)));

    auto b_damage = ecs::Component("Damage");

    b_damage.addAttribute(ecs::ComponentAttribute(String("amount"), ecs::AttributeType::INT, std::any(0)));

    auto b_team = ecs::Component("Team");

    b_team.addAttribute(ecs::ComponentAttribute(String("id"), ecs::AttributeType::INT, std::any(team_id)));

    auto bullet = ecs::EntityBuilder()
            .with(b_position)
            .with(b_velocity)
            .with(b_health)
            .with(b_damage)
            .with(b_team);
    m_world.storeEntity(bullet.build());
}
void DummyBundle::create_enemy(ecs::World &m_world, int team_id, int x, int y) {
    auto e_position = ecs::Component("Position");

    e_position.addAttribute(ecs::ComponentAttribute(String("x"), ecs::AttributeType::INT, std::any(x)));
    e_position.addAttribute(ecs::ComponentAttribute(String("y"), ecs::AttributeType::INT, std::any(y)));
    e_position.addAttribute(ecs::ComponentAttribute(String("z"), ecs::AttributeType::INT, std::any(0)));

    auto e_velocity = ecs::Component("Velocity");

    e_velocity.addAttribute(ecs::ComponentAttribute(String("x"), ecs::AttributeType::INT, std::any(0)));
    e_velocity.addAttribute(ecs::ComponentAttribute(String("y"), ecs::AttributeType::INT, std::any(0)));
    e_velocity.addAttribute(ecs::ComponentAttribute(String("z"), ecs::AttributeType::INT, std::any(0)));

    auto e_health = ecs::Component("Health");

    e_health.addAttribute(ecs::ComponentAttribute(String("max"), ecs::AttributeType::INT, std::any(0)));
    e_health.addAttribute(ecs::ComponentAttribute(String("amount"), ecs::AttributeType::INT, std::any(0)));

    auto e_damage = ecs::Component("Damage");

    e_damage.addAttribute(ecs::ComponentAttribute(String("amount"), ecs::AttributeType::INT, std::any(0)));

    auto e_team = ecs::Component("Team");

    e_team.addAttribute(ecs::ComponentAttribute(String("id"), ecs::AttributeType::INT, std::any(team_id)));

    auto enemy = ecs::EntityBuilder()
            .with(e_position)
            .with(e_velocity)
            .with(e_health)
            .with(e_damage)
            .with(e_team);
    m_world.storeEntity(enemy.build());
}
