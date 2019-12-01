use amethyst::ecs::prelude::{Component, NullStorage};

#[derive(Default)]
pub struct Bullet;

impl Component for Bullet {
    type Storage = NullStorage<Self>;
}
