use amethyst::ecs::prelude::{Component, DenseVecStorage};

use crate::common::{Point, Size};

pub struct Frame {
    pub origin: Point,
    pub size: Size,
}

impl Frame {
    pub fn new(origin: Point, size: Size) -> Self {
        Frame { origin, size }
    }
}

impl Component for Frame {
    type Storage = DenseVecStorage<Self>;
}
