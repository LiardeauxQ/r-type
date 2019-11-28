use amethyst::ecs::prelude::{Component, DenseVecStorage};

pub struct Spawner;

impl Component for Spawner {
    type Storage = DenseVecStorage<Self>;
}