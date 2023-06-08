
#include <Battle.h>

void all_initialize(Player *player, Enemy *enemy, Field *field, CardTable *cardtable, EnemyTable *enemytable)
{
    card_table_initialize(cardtable);
    enemy_table_initialize(enemytable);
    player_initialize(player, 80, 3);
    enemy_initialize(enemy);
    field_initialize(field);

    /* create player cards */

    card_create("Strike", "Deal 6 damage.", TYPE_ATK, 6, 0, 1, Strike, cardtable);
    card_create("Defend", "Gain 5 Block.", TYPE_SKL, 0, 0, 1, Defend, cardtable);
    card_create("Bash", "Deal 8 damage. Apply 2 Vulnerable.", TYPE_ATK, 8, 0, 2, Bash, cardtable);
    card_create("Inflame", "Gain 2 Strength.", TYPE_ABL, 0, 0, 1, Inflame, cardtable);

    /* create enemy cards */

    card_create("DarkStrike", "None.", TYPE_ATK, 0, 0, 0, DarkStrike, cardtable);
    card_create("Incantation", "None.", TYPE_SKL, 0, 0, 0, Incantation, cardtable);

    /* create enemy */

    CardDeck deck;
    BuffDeck buff;
    card_deck_initialize(&deck);
    buff_deck_initialize(&buff);

    add_card_into_deck(&deck, "DarkStrike");
    add_card_into_deck(&deck, "Incantation");

    enemy_create("Cultist", Cultist, 50, 0, &deck, &buff, enemytable);

    /*
    card_create("InfernalBlade", "Add a random card cost 0.\nExhaust.", InfernalBlade, false, TYPE_ATK, &table);
    card_create("Intimidate", "Apply 1 Weak to ALL enemies.\nExhaust.", Intimidate, false, TYPE_ATK, &table);
    card_create("Metallicize", "At the end of your turn, gain 3 Block.", Metallicize, false, TYPE_SKL, &table);
    card_create("PowerThrough", "Add 2 Wounds to your hand. Gain 15 Block.", PowerThrough, false, TYPE_SKL, &table);
    card_create("Pummel", "Deal 2 damage 4 times.\nExhaust.", Pummel, false, TYPE_ATK, &table);
    card_create("Rage", "Whenever you play Attack this turn, gain 3 Block.", Rage, false, TYPE_SKL, &table);
    card_create("Rampage", "Deal 8 damage. Increase this card's damage by 5.", Rampage, false, TYPE_ATK, &table);
    card_create("RecklessCharge", "Deal 7 damage. Shuffle a Dazed into your draw pile.", RecklessCharge, false, TYPE_ATK, &table);
    card_create("SearingBlow", "Deal 12 damage. Can be upgraded any number of times.", SearingBlow, false, TYPE_ATK, &table);
    // card_create("SecondWind", "Exhaust all non-Attack cards in your hand and gain 5 Block for each card Exhausted.", SecondWind, false, TYPE_SKL, &table);
    card_create("SeeingRed", "Gain 2 energy.\nExhaust.", SeeingRed, false, TYPE_ATK, &table);
    card_create("Sentinel", "Gain 5 Block. If this card is Exhausted, gain 2 energy.", Sentinel, false, TYPE_SKL, &table);
    card_create("SeverSoul", "Exhaust all non-Attack cards in your hand. Deal 16 damage.", SeverSoul, false, TYPE_ATK, &table);
    card_create("ShockWave", "Apply 3 Weak and Icon Vulnerable Vulnerable to ALL enemies.\nExhaust.", ShockWave, false, TYPE_ATK, &table);
    card_create("Uppercut", "Deal 13 damage. Apply 1 Weak. Apply 1 Vulnerable.", Uppercut, false, TYPE_ATK, &table);
    card_create("Whirlwind", "Deal 5 damage to ALL enemies X times.", Whirlwind, false, TYPE_ATK, &table);
    card_create("Strike", "Deal 6(9) damage.", Strike, false, TYPE_ATK, &table);
    card_create("Defend", "Gain 5(8) shield.", Defend, false, TYPE_SKL, &table);
    card_create("Bash", "Dealplayer_initialize 8(10) damage, apply 2(3) vulnerable.", Bash, false, TYPE_ATK, &table);
    card_create("Anger", "Deal 6(8) damage, add a copy of this card to the discard pile", Anger, false, TYPE_ATK, &table);
    card_create("Armament", "Gain 5 shield, upgrade a card in your hand.", Armament, false, TYPE_SKL, &table);
    card_create("Body Slam", "Deal damage equal to your current shield.", Body_Slam, false, TYPE_ATK, &table);
    card_create("Clash", "Deal 10(12) damage", Clash, false, TYPE_ATK, &table);
    card_create("Cleave", "Deal 8(11) damage to all enemy.", Cleave, false, TYPE_ATK, &table);
    card_create("Clothesline", "Deal 12(14) damage, apply 2 weak.", Clothesline, false, TYPE_ATK, &table);
    card_create("Headbutt", "Deal 9 damage, get a card from discard pile.", Headbutt, false, TYPE_ATK, &table);
    card_create("Heavy Blade", "Deal 14 damage.", Heavy_Blade, false, TYPE_ATK, &table);
    card_create("Iron Wave", "Deal 5 damage, and gain 5 shield.", Iron_Wave, false, TYPE_ATK, &table);
    card_create("Perfected Strike", "Deal 6 damage, and deal additional 2 damage if you have Strike.", Perfected_Strike, false, TYPE_ATK, &table);
    card_create("Pommel Strike", "Deal 9 damage, and draw 1 card.", Pommel_Strike, false, TYPE_ATK, &table);
    card_create("Shrug it Off", "Gain 8 shield, and draw 1 card.", Shrug_it_Off, false, TYPE_SKL, &table);
    card_create("Sword Boomerang", "Deal 3 damage to enemy 3 times.", Sword_Boomerang, false, TYPE_ATK, &table);
    card_create("Thunderclap", "Deal 4 damage, apply 1 vulnerable.", Thunderclap, false, TYPE_ATK, &table);
    card_create("True Grit", "Gain 7 shield, and random remove a card in hand.", True_Grit, false, TYPE_ATK, &table);
    */
}

void BattleTest(Player *player, Enemy *enemy, Field *field, CardTable *cardtable, EnemyTable *enemytable)
{
    call_enemy(enemy, "Cultist");
    for (int i = 0; i < 6; i++)
        add_card_into_deck(&(player->deck.deckCard), "Strike");
    for (int i = 0; i < 6; i++)
        add_card_into_deck(&(player->deck.deckCard), "Defend");
    add_card_into_deck(&(player->deck.deckCard), "Bash");
    add_card_into_deck(&(player->deck.deckCard), "Inflame");

    Battle(player, enemy, field, cardtable);
}

signed main(int argc, char *argv[])
{
    Player player;
    Enemy enemy;
    Field field;
    CardTable cardtable;
    EnemyTable enemytable;
    all_initialize(&player, &enemy, &field, &cardtable, &enemytable);
    BattleTest(&player, &enemy, &field, &cardtable, &enemytable);
    return 0;
}
