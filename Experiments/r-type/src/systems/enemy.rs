use amethyst::{
    core::{SystemDesc, Transform},
    derive::SystemDesc,
    ecs::prelude::{
        Entities, Join, LazyUpdate, ReadExpect, ReadStorage, System, SystemData, World,
        WriteStorage,
    },
};

use crate::common::SpriteSheetList;
use crate::components::{AttackSpeed, Spawner, Team};
use crate::entities;

#[derive(SystemDesc)]
pub struct EnemySystem;

impl<'s> System<'s> for EnemySystem {
    type SystemData = (
        Entities<'s>,
        ReadStorage<'s, Spawner>,
        WriteStorage<'s, AttackSpeed>,
        ReadStorage<'s, Transform>,
        ReadStorage<'s, Team>,
        ReadExpect<'s, LazyUpdate>,
        ReadExpect<'s, SpriteSheetList>,
    );

    fn run(&mut self, data: Self::SystemData) {
        let (
            entities,
            spawners,
            mut spawns_rate,
            transforms,
            teams,
            lazy_update,
            sprite_sheet_list
        ) = data;

        for (spawner, spawn_rate, transform, team)
            in (&spawners, &mut spawns_rate, &transforms, &teams).join() {
            if spawn_rate.elapsed_time.elapsed() < spawn_rate.frequency {
                continue;
            }
            if let Some(sprite_sheet) = sprite_sheet_list.get("enemy")
            {
                entities::spawn_enemy(&entities, sprite_sheet.clone(), &lazy_update, &transform, &team);
                spawn_rate.elapsed_time.restart();
            }
        }
    }
}
