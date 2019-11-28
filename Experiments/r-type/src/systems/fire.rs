use amethyst::{
    core::{SystemDesc, Transform},
    derive::SystemDesc,
    ecs::prelude::{
        Entities, Join, LazyUpdate, Read, ReadExpect, ReadStorage, System, SystemData, World,
        WriteStorage,
    },
    input::{InputHandler, StringBindings},
};

use crate::common::{SpriteSheetList};
use crate::components::{Player, AttackSpeed, Team};
use crate::entities;

#[derive(SystemDesc)]
pub struct FireSystem;

impl<'s> System<'s> for FireSystem {
    type SystemData = (
        Entities<'s>,
        ReadStorage<'s, Player>,
        WriteStorage<'s, AttackSpeed>,
        ReadStorage<'s, Transform>,
        ReadStorage<'s, Team>,
        ReadExpect<'s, LazyUpdate>,
        ReadExpect<'s, SpriteSheetList>,
        Read<'s, InputHandler<StringBindings>>,
    );

    fn run(&mut self, data: Self::SystemData) {
        let (
            entities,
            players,
            mut attack_speeds,
            transforms,
            teams,
            lazy_update,
            sprite_sheet_list,
            input,
        ) = data;

        for (player, transform, attack_speed, team) in (&players, &transforms, &mut attack_speeds, &teams).join() {
            if let Some(action) = input.action_is_down("flex") {
                if !action || (attack_speed.elapsed_time.elapsed() < attack_speed.frequency) {
                    continue;
                }
                if let Some(sprite_sheet) = sprite_sheet_list
                    .get("bullet")
                    .ok_or("Cannot fetch sprite sheet")
                    .ok() {
                    entities::spawn_bullet(&entities, sprite_sheet.clone(), &lazy_update, &transform, &team);
                    attack_speed.elapsed_time.restart();
                }
            }
        }
    }
}
