use amethyst::{
    core::{SystemDesc, Transform},
    derive::SystemDesc,
    ecs::prelude::{
        Entities, Join, LazyUpdate, Read, ReadExpect, ReadStorage, System, SystemData, World,
        WriteStorage,
    },
    input::{InputHandler, StringBindings},
};

use crate::common::{AssetType, SpriteSheetList};
use crate::components::{Player, AttackSpeed};
use crate::entities;

#[derive(SystemDesc)]
pub struct FireSystem;

impl<'s> System<'s> for FireSystem {
    type SystemData = (
        Entities<'s>,
        ReadStorage<'s, Player>,
        WriteStorage<'s, AttackSpeed>,
        ReadStorage<'s, Transform>,
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
            lazy_update,
            sprite_sheet_list,
            input,
        ) = data;

        for (player, transform, attack_speed) in (&players, &transforms, &mut attack_speeds).join() {
            if let Some(action) = input.action_is_down("flex") {
                if !action || (attack_speed.elapsed_time.elapsed() < attack_speed.frequency) {
                    continue;
                }
                if let Some(sprite_sheet) = sprite_sheet_list
                    .get(AssetType::Bullet)
                    .ok_or("Cannot fetch sprite sheet")
                    .ok() {
                    entities::spawn_bullet(&entities, sprite_sheet.clone(), &lazy_update, &transform);
                    attack_speed.elapsed_time.restart();
                }
            }
        }
    }
}
