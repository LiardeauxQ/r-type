use amethyst::ecs::prelude::{Component, DenseVecStorage};

pub struct CollisionData {
    pub damage_amount: i32,
    pub health_amount: i32,
    pub shield_amount: i32
}

impl CollisionData {
    pub fn reset(&mut self) {
        self.damage_amount = 0;
        self.health_amount = 0;
        self.shield_amount = 0;
    }
}

impl Default for CollisionData {
    fn default() -> Self {
        CollisionData {
            damage_amount: 0,
            health_amount: 0,
            shield_amount: 0,
        }
    }
}

pub struct Collidee {
    pub data: CollisionData,
    pub x_collision: bool,
    pub y_collision: bool,
}

impl Collidee {
    pub fn reset(&mut self) {
        self.data.reset();
        self.x_collision = false;
        self.y_collision = false;
    }
}

impl Component for Collidee {
    type Storage = DenseVecStorage<Self>;
}

impl Default for Collidee {
    fn default() -> Self {
        Collidee {
            data: CollisionData::default(),
            x_collision: false,
            y_collision: false,
        }
    }
}

pub struct Collider;

impl Component for Collider {
    type Storage = DenseVecStorage<Self>;
}