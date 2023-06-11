#include <stdio.h>

typedef struct {
    int health;
    int attack;
    int defense; //護盾
} Enemy;

typedef struct {
    int health;
    int defense; //護盾

    int debuff;
    int buff;
    int energy; //行動次數
} Player;

typedef enum {
    ATTACK,             // 攻擊行動
    SPECIAL_ABILITY,    // 特殊能力行動
    // 添加其他行動類別
} EnemyAction;

typedef struct {
    char name[50];
    int type;
    int value_1; // 數值123
    int value_2; //
    int value_3; //
    char description[100];
    // 可以添加其他屬性和數值

    int specialAbility; // 特殊能力（沒有就設為0)
} Card;

void battle(Player* player, Enemy* enemy) {
    while (player->health > 0 && enemy->health > 0) {
        // 玩家回合
        // 玩家選擇一張卡牌進行使用
        Card selectedCard = playerChooseCard();
        
        // 計算卡牌效果，如攻擊敵人、增加自身防禦等
        calculateCardEffect(&selectedCard, player, enemy);
        
        // 敵人回合
        // 敵人選擇一種行動方式，如攻擊玩家或使用特殊技能
        EnemyAction enemyAction = enemyChooseAction();
        
        // 根據敵人行動計算傷害或效果
        calculateEnemyAction(&enemyAction, player, enemy);
        
        // 檢查戰鬥是否結束
        if (player->health <= 0) {
            printf("You lose the battle!\n");
            break;
        } else if (enemy->health <= 0) {
            printf("You win the battle!\n");
            break;
        }
    }
}


// 玩家選擇一張卡牌
Card playerChooseCard() {
    // 實現卡牌選擇邏輯
}

// 計算卡牌效果
void calculateCardEffect(Card* card, Player* player, Enemy* enemy) {
    // 實現卡牌效果計算邏輯
}

// 敵人選擇一種行動方式
EnemyAction enemyChooseAction() {
    // 實現敵人行動選擇邏輯
}

// 根據敵人行動計算傷害或效果
void calculateEnemyAction(EnemyAction* action, Player* player, Enemy* enemy) {
    // 實現敵人
}

void calculateEnemyAction(EnemyAction* action, Player* player, Enemy* enemy) {
    switch (action->type) {
        case ATTACK:
            // 計算敵人對玩家的攻擊傷害
            int damage = enemy->attack - player->defense;
            if (damage > 0) {
                player->health -= damage;
                printf("Enemy attacked you for %d damage!\n", damage);
            } else {
                printf("Enemy's attack was blocked!\n");
            }
            break;
        case SPECIAL_ABILITY:
            // 實現敵人的特殊技能效果
            break;
        // 其他行動類型的處理
    }
    int specialAbility; // 特殊能力（沒有就設為0)
}

// 主程序
int main() {
    Player player;
    player.health = 100;
    player.defense = 5;

    Enemy enemy;
    enemy.health = 50;
    enemy.attack = 8;
    enemy.defense = 2;

    // 開始戰鬥
    battle(&player, &enemy);

    return 0;
}