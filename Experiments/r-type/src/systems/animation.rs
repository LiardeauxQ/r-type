use amethyst::{
    core::timing::Time,
    core::{SystemDesc, Transform},
    derive::SystemDesc,
    renderer::{SpriteRender},
    ecs::prelude::{Join, Read, ReadStorage, System, SystemData, World, WriteStorage},
};

use crate::components::{
    TimeAnimationList,
};

#[derive(SystemDesc)]
pub struct AnimationSystem;

impl<'s> System<'s> for AnimationSystem {
    type SystemData = (
        WriteStorage<'s, TimeAnimationList>,
        WriteStorage<'s, SpriteRender>,
        Read<'s, Time>,
    );

    fn run(&mut self, data: Self::SystemData) {
        let (
            mut animations,
            mut renders,
            time,
        ) = data;

        for (animation, render) in (&mut animations, &mut renders).join() {
            animation.substract_time(time.delta_time());
            if let Some(position) = animation.get_current_sprite() {
                render.sprite_number = position;
            }
        }
    }
}