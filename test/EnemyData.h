

typedef struct {
    int health;
    int attack;
    int defense; //護盾
} Enemy;

typedef enum {
    ATTACK,             // 攻擊行動
    SPECIAL_ABILITY,    // 特殊能力行動
    // 添加其他行動類別
} EnemyAction;


