use amethyst::{
    core::{Transform, SystemDesc},
    derive::SystemDesc,
    ecs::prelude::{Entities, Join, ReadStorage, System, SystemData, World, WriteStorage},
};

use crate::components::{Velocity, Circle, Collidee, Collider};
use crate::physics::{SphereCollision, Point, Collision};
use crate::rtype::{WIDTH, HEIGHT, CIRCLE_SIZE};

#[derive(SystemDesc)]
pub struct BounceSystem;

impl <'s> System<'s> for BounceSystem {
    type SystemData = (
        Entities<'s>,
        WriteStorage<'s, Collidee>,
        WriteStorage<'s, Collider>,
        ReadStorage<'s, Circle>,
        ReadStorage<'s, Transform>,
    );

    fn run(&mut self, data: Self::SystemData) {
        let (
            entities,
            mut collidees,
            mut colliders,
            circles,
            transforms
        ) = data;

        for (entity_collidee, trans_collidee, collidee, circle_collidee)
            in (&entities, &transforms, &mut collidees, &circles).join() {
            let x = trans_collidee.translation().x;
            let y = trans_collidee.translation().y;

            if x > WIDTH || x < 0.0 {
                collidee.x_collision = true;
            }
            if y > HEIGHT || y < 0.0 {
                collidee.y_collision = true;
            }
            for (entity_collider, collider, trans_collider, circle_collider)
                in (&entities, &mut colliders, &transforms, &circles).join() {
                if entity_collider == entity_collidee {
                    continue;
                }
                let p1 = Point::new(trans_collidee.translation().x,
                                    trans_collidee.translation().y);
                let p2 = Point::new(trans_collider.translation().x,
                                        trans_collider.translation().y);
                let coll1 = SphereCollision::new(circle_collidee.radius, p1);
                let coll2 = SphereCollision::new(circle_collider.radius, p2);

                if coll1.is_colliding_with(&coll2) {
                    collider = update_collision_from(&coll1.center, &coll2.center);
                }
            }
        }
    }
}

fn update_collision_from(p1: &Point, p2: &Point) -> Collider {
    let mut collider = Collider::default();

    if come_from_x_axe(p1, p2, CIRCLE_SIZE * 0.5) {
        collider.x_collision = true;
    } else if come_from_y_axe(p1, p2, CIRCLE_SIZE * 0.5) {
        collider.y_collision = true;
    } else {
        collider.x_collision = true;
        collider.y_collision = true;
    }
    collider
}

fn come_from_x_axe(p1: &Point, p2: &Point, range: f32) -> bool {
    if p2.y >= (p1.y - range) && p2.y <= (p1.y + range) {
        return true;
    }
    return false;
}

fn come_from_y_axe(p1: &Point, p2: &Point, range: f32) -> bool {
    if p2.x >= (p1.x - range) && p2.x <= (p1.x + range) {
        return true;
    }
    return false;
}