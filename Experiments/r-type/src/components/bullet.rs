use amethyst::ecs::prelude::{Component, DenseVecStorage};

pub struct Bullet;

impl Component for Bullet {
    type Storage = DenseVecStorage<Self>;
}
