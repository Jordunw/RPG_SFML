#pragma once
#include <vector>
#include "Equipment.h"
#include "Potions.h"
#include "Sprite.h"

const std::vector<double> goblin{ 3.5, 14, 0, 0, 4, 0 };
const std::vector<double> owlbear{ 10, 30, 0, 0, 0, 0 };
const std::vector<double> necromancer{ 0, 50, 0, 0, 0, 0 };
const std::vector<double> hillgiant{ 20, 130, 0, 0, 0, 0 };


const std::vector<std::vector<double>> enemies{ goblin, owlbear, necromancer, hillgiant };

//  fighter, rogue, wizard, barbarian, catgirl
const std::vector<bool> dagger_equip{ true, true, true, true, true };
const std::vector<bool> club_equip{ true, false, false, true, false };
const std::vector<bool> greatclub_equip{ true, false, false, true, false };
const std::vector<bool> axe_equip{ true, true, true, true, true };
const std::vector<bool> mace_equip{ true, true, false, true, false };
const std::vector<bool> quarterstaff_equip{ false, true, false, true, false };
const std::vector<bool> sickle_equip{ true, true, true, true, true };
const std::vector<bool> trident_equip{ true, true, true, true, true };
const std::vector<bool> katana_equip{ true, true, true, false, false };
const std::vector<bool> battleaxe_equip{ true, true, false, true, false };
const std::vector<bool> flail_equip{ true, true, true, true, true };
const std::vector<bool> glaive_equip{ true, true, false, false, false };
const std::vector<bool> halberd_equip{ true, true, false, false, false };
const std::vector<bool> longsword_equip{ true, true, true, true, true };
const std::vector<bool> maul_equip{ true, false, false, true, false };
const std::vector<bool> morningstar_equip{ true, false, false, true, false };
const std::vector<bool> rapier_equip{ true, true, true, true, true };
const std::vector<bool> pickaxe_equip{ false, false, false, true, false };
const std::vector<bool> shortsword_equip{ true, true, true, true, true };
const std::vector<bool> battlehammer_equip{ true, false, false, true, false };
const std::vector<bool> woodenspoon_equip{ true, true, true, true, true };
const std::vector<bool> sabre_equip{ true, true, true, true, true };
const std::vector<bool> broadsword_equip{ true, true, false, true, false };
const std::vector<bool> greatsword_equip{ false, false, false, true, false };
const std::vector<bool> handaxe_equip{ true, true, true, true, true };
const std::vector<bool> fryingpan_equip{ true, true, true, true, true };

/*
[0] Light   // always goes first
[1]	Heavy   // never goes first && lowers dexterity by 5%)
[2] Bleed   // 10% chance to cause a bleed (-10% total health for 3 turns))
[3] Quick   // ROGUE // (35% chance to attack twice per turn - also applies to duel wielding)
[4] Autism  // BARBARIAN // [[[[[[IN DEVELOPMENT]]]]]]
[5]	Stun    // 20% chance to stun the enemy - loses turn
[6] Range   // 20% dexterity increase
[7] Defense // 15% chance to block enemy attack
*/
const std::vector<bool> dagger_effects{ true, false, false, true, false, false, false };
const std::vector<bool> club_effects{ false, true, false, false, false, false, false, false };
const std::vector<bool> greatclub_effects{ false, true, false, false, false, false, false, false };
const std::vector<bool> axe_effects{ false, false, false, false, false, false, false, false };
const std::vector<bool> mace_effects{ false, true, false, false, false, false, false, false };
const std::vector<bool> quarterstaff_effects{ false, false, false, false, false, true, false, true };
const std::vector<bool> sickle_effects{ true, false, false, false, false, false, false, false };
const std::vector<bool> trident_effects{ false, false, true, false, false, false, false, false };
const std::vector<bool> katana_effects{ true, false, false, true, false, false, false, false };
const std::vector<bool> battleaxe_effects{ false, true, true, false, false, false, false, false };
const std::vector<bool> flail_effects{ false, false, false, true, false, false, false, false };
const std::vector<bool> glaive_effects{ false, false, false, false, false, false, true, false };
const std::vector<bool> halberd_effects{ false, false, true, false, false, false, true, false };
const std::vector<bool> longsword_effects{ false, false, false, false, false, false, false, false };
const std::vector<bool> maul_effects{ false, false, false, false, false, false, false, false };
const std::vector<bool> morningstar_effects{ false, false, true, false, false, false, false, false };
const std::vector<bool> rapier_effects{ true, false, false, true, false, false, false, false };
const std::vector<bool> pickaxe_effects{ false, false, true, false, false, false, false, false };
const std::vector<bool> shortsword_effects{ true, false, false, true, false, false, false, false };
const std::vector<bool> battlehammer_effects{ false, true, false, false, false, true, false, false };
const std::vector<bool> woodenspoon_effects{ true, false, true, false, false, false, false, false };
const std::vector<bool> sabre_effects{ false, false, false, true, false, false, false, false };
const std::vector<bool> broadsword_effects{ false, false, false, false, false, false, false, false };
const std::vector<bool> greatsword_effects{ false, true, false, false, false, false, false, true };
const std::vector<bool> handaxe_effects{ true, false, false, true, false, false, false, false };
const std::vector<bool> fryingpan_effects{ false, false, false, false, false, true, false, false };

// NEED EFFECTS
const std::vector<bool> kelloggs_effects{ false, false, false, false, false, false, false, false };
const std::vector<bool> henry_effects{ false, false, false, false, false, false, false, false };
const std::vector<bool> bonsai_effects{ false, false, false, false, false, false, false, false };
const std::vector<bool> goldenfryingpan_effects{ false, false, false, false, false, false, false, false };
const std::vector<bool> kingsdaggers_effects{ false, false, false, false, false, false, false, false };
const std::vector<bool> warpick_effects{ false, false, false, false, false, false, false, false };
const std::vector<bool> laevateinn_effects{ false, false, false, false, false, false, false, false };

std::vector<Weapon> weapons_vector{
    Weapon("Dagger", dagger_equip, false, 1.1, 0, dagger_effects, "A small weapon with an iron blade and wooden grip."),
    Weapon("Club", club_equip, false, 1.075, 0, club_effects, "A heavy wooden stick meant for delivering powerful blows."),
    Weapon("Greatclub", greatclub_equip, true, 1.4, 0, greatclub_effects, "A massive wooden stick wtih metal bracings. This thing looks like it could pack a punch."),
    Weapon("Axe", axe_equip, true, 1.2, 0, axe_effects, "A simple tool used for chopping wood."),
    Weapon("Mace", mace_equip, false, 1.125, 0, mace_effects, "A long grip with a weighted head."),
    Weapon("Quarterstaff", quarterstaff_equip, true, 1.15, 0, quarterstaff_effects, "A long wooden staff with a blunt metal head on either end. An offensive and defensive weapon."),
    Weapon("Sickle", sickle_equip, false, 1.05, 0, sickle_effects, "A tool used for harvesting crops such as wheat or the organs of your enemies."),
    Weapon("Trident", trident_equip, true, 1.3, 0, trident_effects, "A three prong, barbed trident."),
    Weapon("Katana", katana_equip, true, 1.4, 0, katana_effects, "A curved, light, single-edged blade. Some believe the owner's soul is bound to the katan's blade, but that is just an urban legend... probably."),
    Weapon("Battleaxe", battleaxe_equip, true, 1.5, 0, battleaxe_effects, "A large two-headed axe. A popular weapon among the dwarves."),
    Weapon("Flail", flail_equip, false, 1.175, 0, flail_effects, "A spiked ball attacked to a grip by a chain."),
    Weapon("Glaive", glaive_equip, true, 1.3, 0, glaive_effects, "A long pole with a curved steel blade on the end. Useful for attacking enemies from a distance."),
    Weapon("Halberd", halberd_equip, true, 1.35, 0, halberd_effects, "A long pole with an axe-like head on the end. There is a long blade attacked on top of the axe head as well."),
    Weapon("Longsword", longsword_equip, true, 1.375, 0, longsword_effects, ""),
    Weapon("Maul", maul_equip, true, 1.1, 0, maul_effects, ""),
    Weapon("Morningstar", morningstar_equip, false, 1.125, 0, morningstar_effects, "A blunt weapon with a spiked head."),
    Weapon("Rapier", rapier_equip, false, 1.15, 0, rapier_effects, "A slender sword popular throughout Europe for its very light weight. Don't forget the i."),
    Weapon("Pickaxe", pickaxe_equip, true, 1.175, 0, pickaxe_effects, "Diggy Diggy Hole!"),
    Weapon("Shortsword", shortsword_equip, false, 1.14, 0, shortsword_effects, "A sword bigger than a dagger but smaller than a broadsword. A short sword. Did we really have to explain this?"),
    Weapon("Battlehammer", battlehammer_equip, true, 1.5, 0, battlehammer_effects, "A large bone crushing double-headed hammer. Some of the finest dwarven warriors used this as their weapon of choice."),
    Weapon("Wooden spoon", woodenspoon_equip, false, 1.01, 0, woodenspoon_effects, "A wooden spoon. May be useful for some yummy chicken noodle soop or gouging out your enemies' eyes!"),
    Weapon("Sabre", sabre_equip, false, 1.175, 0, sabre_effects, "A long, curved, sword. This blade is  usually carried around by war generals."),
    Weapon("Broadsword", broadsword_equip, false, 1.18, 0, broadsword_effects, "An average sized iron sword. Small enough to wield in one hand but just big enough to slay your enemies."),
    Weapon("Greatsword", greatsword_equip, true, 1.45, 0, greatsword_effects, "A massive sword with a long blade reaching around 5 feet. A weapon made for the mighty."),
    Weapon("Handaxe", handaxe_equip, false, 1.075, 0, handaxe_effects, "An axe big enough to fit in one hand."),
    Weapon("Frying pan", fryingpan_equip, false, 1.05, 0, fryingpan_effects, "A sturdy piece of cookware. Useful for frying and searing foods. Now that you think of it, this may be pretty useful in battle."),
    Legendary("The Sword of Sir Kelloggs", true, 1.7, 0, kelloggs_effects, "A flame red greatsword with a golden hilt. Tales say this once belonged to a famous witch slaying paladin.", 0),
    Legendary("Henry's Flail", false, 0, 0, henry_effects, "A flail with three gilded spike balls, a majestic tool of destruction. After a closer inspection, you can see small white stains covering the hilt and some white sludge has solidified in between the chain links. Still works!", 1),
    Legendary("Bonsai", true, 1.7, 0, bonsai_effects, "An elegant katana with a black, steel blade. There is an inscription on the blade of what appears to be a branch with pink flowers. There is a dark blue ribbon tied onto the hilt.", 2),
    Legendary("Golden Frying Pan", true, 1.8, 0, goldenfryingpan_effects, "It's like a normal frying pan, but it's made of solid gold!", 3),
    Legendary("King's Daggers", true, 1.5, 0, kingsdaggers_effects, "Two jet black daggers with a dark grey hilt and blood red gem embedded into the bottom of each hilt.  You can feel a dark power within them. These once belonged to an old king a long, long time ago. The king was also a lizard AND a wizard... but what was his name?", 4),
    Legendary("Master's War Pick", true, 0, 0, warpick_effects, "An old worn war pick. Its shaft is dark ebony inlaid with an image of a sailing ship in ivory. Its pick is sharp, cold, steel. You can tell it has a long and storied history.", 5),
    Legendary("Laevateinn", false, 0, 0, laevateinn_effects, "Welded by Freyr, the Norse God of sunshine, Laevateinn is a magic wand who's power flows through its wielder.", 6)
};

std::vector<Armor> armor_vector{
    Armor("Cracked Leather Armor", 1.05, 0, "Old, cracked, and falling apart, this leather armor appears to have gone through a lot, and will probably not provide good protection. At least it's something, right?", { false,false }),
    Armor("Leather Armor", 1.1, 0, "Very light and flexible armor made from the leather of a farm cow. Though it has a few minor imperfections, it seems to be in rather good condition.", { false,false }),
    Armor("Chain Mail", 1.3, 0, "Chain mail armor is very strong armor that was commonly used throughout Europe during the Middle Ages. Chain mail is incredibly flexible and almost impervious to slashing strikes, though thrusting weapons can go clean through. Wear with caution.", { true,false }),
    Armor("Rusted Plate Armor", 1.35, 0, "Rusted iron plate armor. Still provides good protection, but looks like it would shatter against a strong hit to the chest or side.", { false,true }),
    Armor("Iron Plate Armor", 1.4, 0, "Iron plate armor became incredibly popular in Europe starting in the 14th century due to how effective it was.", {false, false})
};

std::vector<Potion> potion_vector{
    HealthPotion("Health Potion I", 0, .2, 1, "A basic health potion. Heals 20% health."),
    HealthPotion("Health Potion II", 0, .5, 2, "A mid tier health potion. Heals 50% health."),
    HealthPotion("Health Potion III", 0, 1, 3, "A high tier health potion. Fully heals the user's health."),
    RegenerationPotion("Regeneration Potion I", 0, .1, 1, "A basic regeneration potion. Heals 10% of the user's health each turn for 3 turns. *Only usable in battle*"),
    RegenerationPotion("Regeneration Potion II", 0, .25, 2, "A high tier regeneration potion. Heals 25% of the players health each turn for 3 turns. *Only usable in battle*"),
    StrengthPotion("Strength Potion I", 0, .2, 1, "A basic strength potion. Increases damage by 20% for 3 turns. *Only usable in battle*"),
    StrengthPotion("Strength Potion II", 0, .35, 2, "A high tier strength potion. Increases damage by 35% for 3 turns. *Only usable in battle*"),
    DefensePotion("Defense Potion I", 0, .2, 1, "A basic defense potion. Reduces incoming damage by 20% for 3 turns. *Only usable in battle*"),
    DefensePotion("Defense Potion II", 0, .35, 2, "A high tier defense potion. Reduces incoming damage by 35% for 3 turns. *Only usable in battle*"),
    InvisibilityPotion("Invisibility Potion", 0, .5, "An invisibility potion. Heavily increases your dexterity - Enemies are 50% less likely to hit you for 3 turns. *Only usable in battle*")
};