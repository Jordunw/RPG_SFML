#include "EntityCreator.h"

namespace ecs
{

    Entity EntityCreator::createGeneralCharacter(std::string name, Sprite sprite, std::string description, float depth)
    {
        Entity e = coordinator.createEntity();
        coordinator.addComponent<SpriteComponent>(e, { sprite });
        coordinator.addComponent<Description>(e, { description });
        coordinator.addComponent<Name>(e, { name });
        coordinator.addComponent<Depth>(e, { depth });
        coordinator.addComponent<Velocity>(e, {}); // keep this empty
        return e;
    }

    Entity EntityCreator::createGeneralCharacter(std::string name, std::string textureLocation, sf::Vector2i pos, std::string description, float depth)
    {
        Entity e = coordinator.createEntity();
        coordinator.addComponent<SpriteComponent>(e, { Sprite(textureLocation, pos.x, pos.y) });
        coordinator.addComponent<Description>(e, { description });
        coordinator.addComponent<Name>(e, { name });
        coordinator.addComponent<Depth>(e, { depth });
        coordinator.addComponent<Velocity>(e, {}); // keep this empty
        return e;
    }

    // generates new entity with stats & etc. based on class
    Entity EntityCreator::createPlayer(PlayerClass pClass, std::string name)
    {
        Entity e = coordinator.createEntity();
        coordinator.addComponent<Name>(e, { name });
        coordinator.addComponent<Depth>(e, { .5f });
        coordinator.addComponent<XP>(e, XP{ 0 });
        coordinator.addComponent<Level>(e, { 1 });
        coordinator.addComponent<Inventory>(e, { 12, std::vector<Entity>(12) });
        coordinator.addComponent<Balance>(e, { 0 });
        coordinator.addComponent<Velocity>(e, { {0.0f, 0.0f} });

        switch (pClass)
        {
        case PlayerClass::fighter:
            coordinator.addComponent<EntityType>(e, { EntityType::entity | EntityType::drawable });
            coordinator.addComponent<ClassName>(e, {"Fighter"});
            coordinator.addComponent<Description>(e, {"A noble soldier of the people, skilled in combat and tactics."});
            coordinator.addComponent<Stats>(e, { {20, 20}, 5.5, 17, 8.5 });
            coordinator.addComponent<Status>(e, {});
            coordinator.addComponent<LevelUpStats>(e, {12, 4, .4f, .65f});
            break;
        case PlayerClass::rogue:
            coordinator.addComponent<ClassName>(e, {"Rogue"});
            coordinator.addComponent<Description>(e, {"A cunning scoundrel who skulks at night and steals all he can."});
            coordinator.addComponent<Stats>(e, { {16, 16}, 8, 16, 6 });
            coordinator.addComponent<Status>(e, {});
            coordinator.addComponent<LevelUpStats>(e, { 10, 3, .55f, .7f });
            break;
        case PlayerClass::wizard:
            coordinator.addComponent<ClassName>(e, {"Wizard"});
            coordinator.addComponent<Description>(e, {"An eccentric hermit gifted with ancient arcane knowledge."});
            coordinator.addComponent<Stats>(e, { {12, 12}, 6, 16, 6 });
            coordinator.addComponent<Status>(e, {});
            coordinator.addComponent<LevelUpStats>(e, { 8, 2.5, .45f, .65f });
            break;
        case PlayerClass::barbarian:
            coordinator.addComponent<ClassName>(e, {"Barbarian"});
            coordinator.addComponent<Description>(e, {"A stout and ferocious warrior from a cold, barren land."});
            coordinator.addComponent<Stats>(e, { {24, 24}, 4, 12, 12 });
            coordinator.addComponent<Status>(e, {});
            coordinator.addComponent<LevelUpStats>(e, { 14, 74, .375f, .5f });
            break;
        case PlayerClass::catgirl:
            coordinator.addComponent<ClassName>(e, {"Catgirl"});
            coordinator.addComponent<Description>(e, {"A hybrid of a young girl and a small feline. It is wearing a maid outfit"});
            coordinator.addComponent<Stats>(e, { {4, 4}, 7.5, 14, 3 });
            coordinator.addComponent<Status>(e, {});
            coordinator.addComponent<LevelUpStats>(e, { 4, 1, .5f, .6f });
            break;
        default:
            throw std::runtime_error("somehow managed to pass in a nonexistent class to player creation function");
            break;
        }
    }

    // creates a new weapon entity
    Entity EntityCreator::createWeapon(WeaponType wType)
    {
        Entity e = coordinator.createEntity();
        coordinator.addComponent<Equipped>(e, { false });

        switch (wType)
        {
        case WeaponType::dagger:
            coordinator.addComponent<WeaponType>(e, WeaponType::dagger);
            coordinator.addComponent<Name>(e, { "Dagger" });
            coordinator.addComponent<TwoHanded>(e, { false });
            coordinator.addComponent<DamageMulti>(e, { 1.1f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::Class::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::light | WeaponEffects::quick });
            coordinator.addComponent<Description>(e, { "A small weapon with an iron blade and wooden grip." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::club:
            coordinator.addComponent<WeaponType>(e, WeaponType::club);
            coordinator.addComponent<Name>(e, { "Club" });
            coordinator.addComponent<TwoHanded>(e, { false });
            coordinator.addComponent<DamageMulti>(e, { 1.075f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::barbarian | Equippable::fighter });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::heavy });
            coordinator.addComponent<Description>(e, { "A heavy wooden stick meant for delivering powerful blows." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::greatclub:
            coordinator.addComponent<WeaponType>(e, WeaponType::greatclub);
            coordinator.addComponent<Name>(e, { "Greatclub" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.4f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::barbarian | Equippable::fighter });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::heavy });
            coordinator.addComponent<Description>(e, { "A massive wooden stick wtih metal bracings. This thing looks like it could pack a punch." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::axe:
            coordinator.addComponent<WeaponType>(e, WeaponType::axe);
            coordinator.addComponent<Name>(e, { "Axe" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.2f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::none });
            coordinator.addComponent<Description>(e, { "A small weapon with an iron blade and wooden grip." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::mace:
            coordinator.addComponent<WeaponType>(e, WeaponType::mace);
            coordinator.addComponent<Name>(e, { "Mace" });
            coordinator.addComponent<TwoHanded>(e, { false });
            coordinator.addComponent<DamageMulti>(e, { 1.125f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::barbarian | Equippable::fighter | Equippable::rogue });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::heavy });
            coordinator.addComponent<Description>(e, { "A long grip with a weighted head." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::quarterstaff:
            coordinator.addComponent<WeaponType>(e, WeaponType::quarterstaff);
            coordinator.addComponent<Name>(e, { "Quarterstaff" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.15f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::wizard | Equippable::rogue });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::stun | WeaponEffects::defense });
            coordinator.addComponent<Description>(e, { "A long wooden staff with a blunt metal head on either end. An offensive and defensive weapon." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::sickle:
            coordinator.addComponent<WeaponType>(e, WeaponType::sickle);
            coordinator.addComponent<Name>(e, { "Sickle" });
            coordinator.addComponent<TwoHanded>(e, { false });
            coordinator.addComponent<DamageMulti>(e, { 1.05f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::light });
            coordinator.addComponent<Description>(e, { "A tool used for harvesting crops such as wheat or the organs of your enemies." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::trident:
            coordinator.addComponent<WeaponType>(e, WeaponType::trident);
            coordinator.addComponent<Name>(e, { "Trident" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.3f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::bleed });
            coordinator.addComponent<Description>(e, { "A three prong, barbed trident." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::katana:
            coordinator.addComponent<WeaponType>(e, WeaponType::katana);
            coordinator.addComponent<Name>(e, { "Katana" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.4f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::wizard | Equippable::rogue | Equippable::fighter });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::light | WeaponEffects::quick });
            coordinator.addComponent<Description>(e, { "A curved, light, single-edged blade. Some believe the owner’s soul is bound to the katana’s blade, but that's just an urban legend... probably." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::battleaxe:
            coordinator.addComponent<WeaponType>(e, WeaponType::battleaxe);
            coordinator.addComponent<Name>(e, { "Battleaxe" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.5f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::barbarian | Equippable::rogue | Equippable::fighter });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::heavy | WeaponEffects::bleed });
            coordinator.addComponent<Description>(e, { "A Large, two-headed axe. A popular weapon among the dwarves." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::flail:
            coordinator.addComponent<WeaponType>(e, WeaponType::flail);
            coordinator.addComponent<Name>(e, { "Flail" });
            coordinator.addComponent<TwoHanded>(e, { false });
            coordinator.addComponent<DamageMulti>(e, { 1.175f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::quick });
            coordinator.addComponent<Description>(e, { "A spiked ball attached to a grip by a chain." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::glaive:
            coordinator.addComponent<WeaponType>(e, WeaponType::glaive);
            coordinator.addComponent<Name>(e, { "Glaive" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.35f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::fighter | Equippable::rogue });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::range });
            coordinator.addComponent<Description>(e, { "A long pole with a curved steel blade on the end. Useful for attacking enemies at a distance." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::halberd:
            coordinator.addComponent<WeaponType>(e, WeaponType::halberd);
            coordinator.addComponent<Name>(e, { "Halberd" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.30f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::fighter | Equippable::rogue });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::bleed | WeaponEffects::range });
            coordinator.addComponent<Description>(e, { "A long pole with an axe-like head on the end. There is a long, slim blade attached on top of the axe head." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::longsword:
            coordinator.addComponent<WeaponType>(e, WeaponType::longsword);
            coordinator.addComponent<Name>(e, { "Longsword" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.375f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::none });
            coordinator.addComponent<Description>(e, { "" }); // NEEDS DESCRIPTION
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::maul:
            coordinator.addComponent<WeaponType>(e, WeaponType::maul);
            coordinator.addComponent<Name>(e, { "Maul" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.1f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::barbarian | Equippable::fighter });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::none });
            coordinator.addComponent<Description>(e, { "" }); // NEEDS DESCRIPTION
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::morningstar:
            coordinator.addComponent<WeaponType>(e, WeaponType::morningstar);
            coordinator.addComponent<Name>(e, { "Morningstar" });
            coordinator.addComponent<TwoHanded>(e, { false });
            coordinator.addComponent<DamageMulti>(e, { 1.125f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::barbarian | Equippable::fighter });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::bleed });
            coordinator.addComponent<Description>(e, { "A blunt weapon with a spiked head." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::rapier:
            coordinator.addComponent<WeaponType>(e, WeaponType::rapier);
            coordinator.addComponent<Name>(e, { "Rapier" });
            coordinator.addComponent<TwoHanded>(e, { false });
            coordinator.addComponent<DamageMulti>(e, { 1.15f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::light | WeaponEffects::quick });
            coordinator.addComponent<Description>(e, { "A slender blade popular throughout the lands for its very light weight." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::pickaxe:
            coordinator.addComponent<WeaponType>(e, WeaponType::pickaxe);
            coordinator.addComponent<Name>(e, { "Pickaxe" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.175f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::barbarian });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::bleed });
            coordinator.addComponent<Description>(e, { "Diggy Diggy Hole!" });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::shortsword:
            coordinator.addComponent<WeaponType>(e, WeaponType::shortsword);
            coordinator.addComponent<Name>(e, { "Shortsword" });
            coordinator.addComponent<TwoHanded>(e, { false });
            coordinator.addComponent<DamageMulti>(e, { 1.14 });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::quick | WeaponEffects::light });
            coordinator.addComponent<Description>(e, { "A sword bigger than a dagger but smaller than a broadsword." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::battlehammer:
            coordinator.addComponent<WeaponType>(e, WeaponType::battlehammer);
            coordinator.addComponent<Name>(e, { "Battlehammer" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.5f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::fighter | Equippable::barbarian });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::stun | WeaponEffects::heavy });
            coordinator.addComponent<Description>(e, { "A large, bone crushing, double-headed hammer. Some of the finest dwarven warriors used this as their weapon of choice." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::woodenspoon:
            coordinator.addComponent<WeaponType>(e, WeaponType::woodenspoon);
            coordinator.addComponent<Name>(e, { "Wooden Spoon" });
            coordinator.addComponent<TwoHanded>(e, { false });
            coordinator.addComponent<DamageMulti>(e, { 1.01f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::bleed | WeaponEffects::light });
            coordinator.addComponent<Description>(e, { "A wooden spoon. May be useful for some yummy chicken noodle soup or gouging out your enemies eyes!" });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::sabre:
            coordinator.addComponent<WeaponType>(e, WeaponType::sabre);
            coordinator.addComponent<Name>(e, { "Sabre" });
            coordinator.addComponent<TwoHanded>(e, { false });
            coordinator.addComponent<DamageMulti>(e, { 1.175f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::quick });
            coordinator.addComponent<Description>(e, { "A long and curved sword. This blade is usually carried around by war generals." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::broadsword:
            coordinator.addComponent<WeaponType>(e, WeaponType::broadsword);
            coordinator.addComponent<Name>(e, { "Broadsword" });
            coordinator.addComponent<TwoHanded>(e, { false });
            coordinator.addComponent<DamageMulti>(e, { 1.18f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::fighter | Equippable::rogue | Equippable::barbarian });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::none });
            coordinator.addComponent<Description>(e, { "An average sized iron sword. Small enough to wield in one hand but just big enough to slay your enemies." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::greatsword:
            coordinator.addComponent<WeaponType>(e, WeaponType::greatsword);
            coordinator.addComponent<Name>(e, { "Greatsword" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.45f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::barbarian });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::heavy | WeaponEffects::defense });
            coordinator.addComponent<Description>(e, { "A massive sword with a long blade reaching around 5 feet. A weapon made for the mighty." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::handaxe:
            coordinator.addComponent<WeaponType>(e, WeaponType::handaxe);
            coordinator.addComponent<Name>(e, { "Handaxe" });
            coordinator.addComponent<TwoHanded>(e, { false });
            coordinator.addComponent<DamageMulti>(e, { 1.075f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::quick | WeaponEffects::light });
            coordinator.addComponent<Description>(e, { "An axe big enough to fit in one hand." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::fryingpan:
            coordinator.addComponent<WeaponType>(e, WeaponType::fryingpan);
            coordinator.addComponent<Name>(e, { "Frying Pan" });
            coordinator.addComponent<TwoHanded>(e, { false });
            coordinator.addComponent<DamageMulti>(e, { 1.05f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::stun });
            coordinator.addComponent<Description>(e, { "A sturdy piece of cookware. Useful for frying and searing foods. Now that you think of it, this may be pretty useful in the face of battle." });
            coordinator.addComponent<IsLegendary>(e, { false });
            break;
        case WeaponType::kelloggs:
            coordinator.addComponent<WeaponType>(e, WeaponType::kelloggs);
            coordinator.addComponent<Name>(e, { "Sword of Sir Kelloggs" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.7f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::quick | WeaponEffects::defense | WeaponEffects::range });
            coordinator.addComponent<LegendaryEffects>(e, { LegendaryEffects::flame });
            coordinator.addComponent<Description>(e, { "A large, flame red greatsword with a golden hilt. Tales say this once belonged to a famous witch slaying paladin. The blade emits bursts of fire with each slash." });
            coordinator.addComponent<IsLegendary>(e, { true });
            break;
        case WeaponType::henry:
            coordinator.addComponent<WeaponType>(e, WeaponType::henry);
            coordinator.addComponent<Name>(e, { "Henry's Flail" });
            coordinator.addComponent<TwoHanded>(e, { false });
            coordinator.addComponent<DamageMulti>(e, { 1.5f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::stun | WeaponEffects::light | WeaponEffects::quick });
            coordinator.addComponent<Description>(e, { "A flail with three gilded spiked-balls, a majestic tool of destruction. After a closer inspection, you can see small white stains covering the hilt and some white sludge has solidified in between the chain links. Still works!" });
            coordinator.addComponent<IsLegendary>(e, { true });
            break;
        case WeaponType::bonsai:
            coordinator.addComponent<WeaponType>(e, WeaponType::bonsai);
            coordinator.addComponent<Name>(e, { "Bonsai" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.7f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::light | WeaponEffects::bleed | WeaponEffects::quick });
            coordinator.addComponent<LegendaryEffects>(e, { LegendaryEffects::bloom });
            coordinator.addComponent<Description>(e, { "A large elegant katana with a black, steel blade. There is an inscription on the blade of what appears to be a branch with white flowers. There is a dark blue ribbon tied onto the hilt." });
            coordinator.addComponent<IsLegendary>(e, { true });
            break;
        case WeaponType::gfp:
            coordinator.addComponent<WeaponType>(e, WeaponType::gfp);
            coordinator.addComponent<Name>(e, { "Golden Frying Pan" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.8f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::stun | WeaponEffects::heavy });
            coordinator.addComponent<LegendaryEffects>(e, { LegendaryEffects::crush });
            coordinator.addComponent<Description>(e, { "It’s like a normal frying pan, but it’s made of solid gold!" });
            coordinator.addComponent<IsLegendary>(e, { true });
            break;
        case WeaponType::kingsdaggers:
            coordinator.addComponent<WeaponType>(e, WeaponType::kingsdaggers);
            coordinator.addComponent<Name>(e, { "King's Daggers" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.6f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::light | WeaponEffects::quick | WeaponEffects::bleed });
            coordinator.addComponent<LegendaryEffects>(e, { LegendaryEffects::necrosis });
            coordinator.addComponent<Description>(e, { "Two jet black daggers with a dark grey hilt and blood red gem embedded into the bottom of each of the hilts.  You can feel a dark power within them. These once belonged to an old king a long, long time ago. The king was a lizard AND a wizard… but what was his name?" });
            coordinator.addComponent<IsLegendary>(e, { true });
            break;
        case WeaponType::warpick:
            coordinator.addComponent<WeaponType>(e, WeaponType::warpick);
            coordinator.addComponent<Name>(e, { "Master's War Pick" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.65f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::stun | WeaponEffects::bleed });
            coordinator.addComponent<Description>(e, { "An old worn war pick. Its shaft is dark ebony inlaid with an image of a sailing ship in ivory. Its pick is sharp, cold steel. You can tell it has a long and storied history." });
            coordinator.addComponent<IsLegendary>(e, { true });
            break;
        case WeaponType::laevateinn:
            coordinator.addComponent<WeaponType>(e, WeaponType::laevateinn);
            coordinator.addComponent<Name>(e, { "Laevateinn" });
            coordinator.addComponent<TwoHanded>(e, { false });
            coordinator.addComponent<DamageMulti>(e, {  });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, {  });
            coordinator.addComponent<LegendaryEffects>(e, {  });
            coordinator.addComponent<Description>(e, { "Welded by Freyr, the Norse God of sunshine, Laevateinn is a magic wand whose power flows through its wielder." });
            coordinator.addComponent<IsLegendary>(e, { true });
            break;
        case WeaponType::thunderscry:
            coordinator.addComponent<WeaponType>(e, WeaponType::thunderscry);
            coordinator.addComponent<Name>(e, { "Thunder's Cry" });
            coordinator.addComponent<TwoHanded>(e, {  });
            coordinator.addComponent<DamageMulti>(e, {  });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, {  });
            coordinator.addComponent<LegendaryEffects>(e, {  });
            coordinator.addComponent<Description>(e, { "A weapon forged by Zeus himself.A slim, long, staff in the shape of a lightning bolt with a shining sea blue sapphire on top.You can see Greek inscriptions on the side of the staff.You can feel the energy of a storm flowing through it." });
            coordinator.addComponent<IsLegendary>(e, { true });
            break;
        case WeaponType::blarneystone:
            coordinator.addComponent<WeaponType>(e, WeaponType::blarneystone);
            coordinator.addComponent<Name>(e, { "Blarney Stone" });
            coordinator.addComponent<TwoHanded>(e, { true });
            coordinator.addComponent<DamageMulti>(e, { 1.7f });
            coordinator.addComponent<BuyPrice>(e, {}); // NEED BUY PRICES FOR EVERYTHING
            coordinator.addComponent<SellPrice>(e, {}); // NEED SELL PRICES FOR EVERYTHING
            coordinator.addComponent<Equippable>(e, { Equippable::all });
            coordinator.addComponent<WeaponEffects>(e, { WeaponEffects::stun | WeaponEffects::heavy });
            coordinator.addComponent<LegendaryEffects>(e, { LegendaryEffects::irishluck });
            coordinator.addComponent<Description>(e, { "Aye, aye aye! Brings a tear to me eye." });
            coordinator.addComponent<IsLegendary>(e, { true });
            break;
        default:
            throw std::runtime_error("somehow tried to create a nonexistent weapon type");
            break;
        }

        return e;
    }

    Entity EntityCreator::createArmor(ArmorType aType)
    {
        Entity e = coordinator.createEntity();
        
        switch (aType)
        {
        case ArmorType::crackedleather:
            coordinator.addComponent<ArmorType>(e, ArmorType::crackedleather);
            coordinator.addComponent<Name>(e, { "Cracked Leather Armor" });
            coordinator.addComponent<ProtectionMulti>(e, { 1.05f });
            coordinator.addComponent<ArmorWeakness>(e, { 0, 1, 1 }); // weak to thrust, normal against slash, normal against blunt force
            coordinator.addComponent<Description>(e, { "Old, cracked, and falling apart, this leather armor appears to have gone through a lot, and will probably not provide good protection. At least it's something, right?" });
            break;
        case ArmorType::leather:
            coordinator.addComponent<ArmorType>(e, ArmorType::leather);
            coordinator.addComponent<Name>(e, { "Leather Armor" });
            coordinator.addComponent<ProtectionMulti>(e, { 1.1f });
            coordinator.addComponent<ArmorWeakness>(e, { 0, 2, 1 });
            coordinator.addComponent<Description>(e, { "Very light and flexible armor made from the leather of a farm cow. Though it has a few minor imperfections, it seems to be in rather good condition." });
            break;
        case ArmorType::chainmail:
            coordinator.addComponent<ArmorType>(e, ArmorType::chainmail);
            coordinator.addComponent<Name>(e, { "Chainmail Armor" });
            coordinator.addComponent<ProtectionMulti>(e, { 1.3f });
            coordinator.addComponent<ArmorWeakness>(e, { 0, 2, 1 });
            coordinator.addComponent<Description>(e, { "Chain mail armor is very strong armor that was commonly used throughout Europe during the Middle Ages. Chain mail is incredibly flexible and almost impervious to slashing strikes, though thrusting weapons can go clean through. Wear with caution." });
            break;
        case ArmorType::rustedplate:
            coordinator.addComponent<ArmorType>(e, ArmorType::rustedplate);
            coordinator.addComponent<Name>(e, { "Rusted Plate Armor" });
            coordinator.addComponent<ProtectionMulti>(e, { 1.35f });
            coordinator.addComponent<ArmorWeakness>(e, { 1, 2, 0 });
            coordinator.addComponent<Description>(e, { "Rusted iron plate armor. Still provides good protection, but looks like it would shatter against a strong hit to the chest or side." });
            break;
        case ArmorType::ironplate:
            coordinator.addComponent<ArmorType>(e, ArmorType::ironplate);
            coordinator.addComponent<Name>(e, { "Iron Plate Armor" });
            coordinator.addComponent<ProtectionMulti>(e, { 1.4f });
            coordinator.addComponent<ArmorWeakness>(e, { 1, 2, 1 });
            coordinator.addComponent<Description>(e, { "Iron plate armor became incredibly popular in Europe starting in the 14th century due to how effective it was. Provides great protection against all types of attacks." });
            break;
        default:
            throw std::runtime_error("somehow tried to create a nonexistent armor type");
            break;
        }

        return e;
    }

    // potions definitely need to be completed and possibly redone, will come back to this later
    Entity EntityCreator::createPotion(PotionType pType)
    {
        Entity e = coordinator.createEntity();

        switch (pType)
        {
        case PotionType::healing:
            coordinator.addComponent<PotionType>(e, PotionType::healing);
            coordinator.addComponent<Name>(e, { "Healing Potion" });
            coordinator.addComponent<Tier>(e, {});
            coordinator.addComponent<EffectStrength>(e, {});
            coordinator.addComponent<Description>(e, {});
            break;
        case PotionType::regeneration:
            coordinator.addComponent<PotionType>(e, PotionType::regeneration);
            coordinator.addComponent<Name>(e, { "Regeneration Potion" });
            coordinator.addComponent<Tier>(e, {});
            coordinator.addComponent<EffectStrength>(e, {});
            coordinator.addComponent<Description>(e, {});
            break;
        case PotionType::strength:
            coordinator.addComponent<PotionType>(e, PotionType::strength);
            coordinator.addComponent<Name>(e, { "Strength Potion" });
            coordinator.addComponent<Tier>(e, {});
            coordinator.addComponent<EffectStrength>(e, {});
            coordinator.addComponent<Description>(e, {});
            break;
        case PotionType::defense:
            coordinator.addComponent<PotionType>(e, PotionType::defense);
            coordinator.addComponent<Name>(e, { "Defense Potion" });
            coordinator.addComponent<Tier>(e, {});
            coordinator.addComponent<EffectStrength>(e, {});
            coordinator.addComponent<Description>(e, {});
            break;
        case PotionType::invis:
            coordinator.addComponent<PotionType>(e, PotionType::invis);
            coordinator.addComponent<Name>(e, { "Invisibility Potion" });
            coordinator.addComponent<Tier>(e, {});
            coordinator.addComponent<EffectStrength>(e, {});
            coordinator.addComponent<Description>(e, {});
            break;
        default:
            throw std::runtime_error("somehow tried to create a nonexistent potion type");
            break;
        }
    }
}