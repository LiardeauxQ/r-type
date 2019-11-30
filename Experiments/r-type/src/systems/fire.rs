use amethyst::{
    core::{SystemDesc, Transform},
    core::timing::Time,
    derive::SystemDesc,
    ecs::prelude::{
        Entities, Join, LazyUpdate, Read, ReadExpect, ReadStorage, System, SystemData, World,
        WriteStorage,
    },
    input::{InputHandler, StringBindings},
};

use crate::common::{SpriteSheetList};
use crate::components::{Player, AttackSpeed, Team, Movable, TimeAnimationList};
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
        ) = data;

        for (player, transform, attack_speed, team) in (&players, &transforms, &mut attack_speeds, &teams).join() {
            if attack_speed.elapsed_time.elapsed() < attack_speed.frequency || !player.can_fire {
                continue;
            }
            if let Some(sprite_sheet) = sprite_sheet_list.get("bullet") {
                let mut position = transform.clone();

                position.prepend_translation_x(player.width / 2.0);
                entities::spawn_bullet(&entities, sprite_sheet.clone(), &lazy_update, position, &team);
                attack_speed.elapsed_time.restart();
            }
        }
    }
}