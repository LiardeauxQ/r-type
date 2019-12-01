use amethyst::{
    core::{SystemDesc, Transform},
    derive::SystemDesc,
    ecs::prelude::{Entities, Join, ReadStorage, ReadExpect, LazyUpdate, System, SystemData, World, WriteStorage},
};

use crate::common::{SpriteSheetList};
use crate::components::{Collidee, Collider, Damage, Health, Team, Bullet};
use crate::entities;

#[derive(SystemDesc)]
pub struct BounceSystem;

impl<'s> System<'s> for BounceSystem {
    type SystemData = (
        Entities<'s>,
        WriteStorage<'s, Collidee>,
        ReadStorage<'s, Collider>,
        ReadStorage<'s, Damage>,
        ReadStorage<'s, Transform>,
        ReadStorage<'s, Team>,
    );

    fn run(&mut self, data: Self::SystemData) {
        let (
            entities,
            mut collidees,
            colliders,
            damages,
            transforms,
            teams
        ) = data;

        for (entity, collider, damage, transform, team) in
            (&entities, &colliders, &damages, &transforms, &teams).join()
        {
            for (entity_collidee, collidee, damage_collidee, transform_collidee, team_collidee) in
                (&entities, &mut collidees, &damages, &transforms, &teams).join()
            {
                if entity == entity_collidee || team.id == team_collidee.id {
                    continue;
                }
                let x = transform_collidee.translation().x;
                let y = transform_collidee.translation().y;
                let cx = transform.translation().x;
                let cy = transform.translation().y;
                if x >= cx - 30.0 && x <= cx + 30.0 && y >= cy - 30.0 && y <= cy + 30.0 {
                    collidee.x_collision = true;
                    collidee.y_collision = true;
                    collidee.data.damage_amount = damage.amount;
                }
            }
        }
    }
}

#[derive(SystemDesc)]
pub struct CollisionSystem;

impl<'s> System<'s> for CollisionSystem {
    type SystemData = (
        Entities<'s>,
        WriteStorage<'s, Collidee>,
        WriteStorage<'s, Health>,
        ReadStorage<'s, Collider>,
        ReadStorage<'s, Transform>,
        ReadStorage<'s, Bullet>,
        ReadExpect<'s, LazyUpdate>,
        ReadExpect<'s, SpriteSheetList>,
    );

    fn run(&mut self, data: Self::SystemData) {
        let (
            entities,
            mut collidees,
            mut healths,
            colliders,
            transforms,
            bullets,
            lazy_update,
            sprite_sheet_list,
        ) = data;

        for (entity, collidee, health, collider, transform, ()) in
            (&entities, &mut collidees, &mut healths, &colliders, &transforms, !&bullets).join()
        {
            if handle_collision(collidee, health) {
                if let Some(sprite_sheet) = sprite_sheet_list.get("explosion") {
                    entities::spawn_explosion(&entities, sprite_sheet, &lazy_update, transform.clone());
                }
                entities.delete(entity);
            }
        }
    }
}

#[derive(SystemDesc)]
pub struct BulletCollisionSystem;

impl<'s> System<'s> for BulletCollisionSystem {
    type SystemData = (
        Entities<'s>,
        WriteStorage<'s, Collidee>,
        WriteStorage<'s, Health>,
        ReadStorage<'s, Collider>,
        ReadStorage<'s, Bullet>,
    );

    fn run(&mut self, data: Self::SystemData) {
        let (
            entities,
            mut collidees,
            mut healths,
            colliders,
            bullets,
        ) = data;

        for (entity, collidee, health, collider, bullet) in
            (&entities, &mut collidees, &mut healths, &colliders, &bullets).join()
            {
                if handle_collision(collidee, health) {
                    entities.delete(entity);
                }
            }
    }
}

fn handle_collision(collidee: &mut Collidee, health: &mut Health) -> bool {
    if collidee.x_collision || collidee.y_collision {
        health.current -= collidee.data.damage_amount;
        collidee.reset();
        if health.current <= 0 {
            return true;
        }
    }
    false
}