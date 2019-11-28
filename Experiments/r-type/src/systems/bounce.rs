use amethyst::{
    core::{SystemDesc, Transform},
    derive::SystemDesc,
    ecs::prelude::{Entities, Join, ReadStorage, System, SystemData, World, WriteStorage},
};

use crate::common::Point;
use crate::components::{Circle, Collidee, Collider, Damage, Health, Team};
use crate::physics::SphereCollision;
use crate::states::{HEIGHT, WIDTH};
use std::ptr;

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
        let (entities, mut collidees, colliders, damages, transforms, teams) = data;

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
        ReadStorage<'s, Collider>,
        WriteStorage<'s, Health>,
    );

    fn run(&mut self, data: Self::SystemData) {
        let (entities, mut collidees, colliders, mut healths) = data;

        for (entity, collidee, collider, health) in
            (&entities, &mut collidees, &colliders, &mut healths).join()
        {
            if collidee.x_collision || collidee.y_collision {
                health.current -= collidee.data.damage_amount;
                collidee.reset();
                if health.current <= 0 {
                    entities.delete(entity);
                }
            }
        }
    }
}