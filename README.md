# Programming Design Final Project

## The Rogue Game

### GroupMembers: 羅冠翔 顏鈺峰 莊順閎 王政崴 王子奕

## 1. Introduction

### Game Intro

Rough: The Card Game
It is a game that combines elements of card games and roguelikes.

The game allows players to assume the role of an adventurer, exploring uncharted territories filled with danger and mysterious trials. Players must construct powerful decks of cards and employ strategies to overcome various enemies and challenges.

Players need to choose cards to play each turn and respond to enemy attacks and abilities. Strategically using cards, managing resources, and health points are key to achieving victory in the game.

### Game Flow

```graphviz
digraph tree{
    "Player Start" -> "Battle/Event" -> "Choose Next Stage";
    "Choose Next Stage" -> "Battle/Event";
    "Choose Next Stage" -> "final boss";
}
```

## 2. Program Design

Program Flow

```graphviz
digraph tree{
    "Relic.h" [color=red];
    "Card.h" -> "Player.h";
    "Card.h" -> "Enemy.h";
    "Buff.h" -> "Card.h";
    "Buff.h" -> "Relic.h" -> "Field.h";
    "Player.h" -> "FuncTable.h";
    "Enemy.h" -> "FuncTable.h";
    "Field.h" -> "FuncTable.h";

}
```

### Program Flow

```graphviz
digraph tree{
"FuncTable.h" ->  "BuffAction.h";
    "Action.h" -> "CardAction.h";
    "BuffAction.h" -> "Action.h";
    "Action.h" -> "EnemyAction.h";
    "RelicAction.h" -> "Battle.h";
    "CardAction.h" -> "Battle.h";
    "EnemyAction.h" -> "Battle.h";
    "Battle.h" -> "Map.h";
    "FuncTable.h" -> "Event.h" -> "Map.h";
    "Map.h" -> "Game.h";
    "Game.h" -> "callback.h";
    "callback.h" -> "UI";
}
```

### Choose Card

```graphviz
digraph tree{
    "Player/Enemy選卡" -> "Buff結算" -> "CardAction";
}
```

### Battle

```graphviz
digraph tree{
    "ChooseCard(玩家回合開始)" -> "Choose玩家卡牌*n" -> "ChooseCard(玩家回合結束)" ->
    "ChooseCard(怪物回合開始)" -> "Choose怪物卡牌*n" -> "ChooseCard(怪物回合結束)" ->
    "ChooseCard(玩家回合開始)";
}

```

## 4.Advance Part

### GUI

```clike=

void StartButton_clicked_cb(GtkWidget *widget, gpointer data);

void SettingButton_clicked_cb(GtkWidget *widget, gpointer data);

void MainStack_visible_child_name_notify_cb(GObject *gobject, GParamSpec *pspec, gpointer user_data);

void DrawCardDeckButton_clicked_cb(GtkWidget *widget, gpointer data);

void BattleRoundEndButton_clicked_cb(GtkWidget *widget, gpointer data);

void setting_button_clicked(GtkWidget *widget, gpointer data);

void quit_button_clicked(GtkWidget *widget, gpointer data);

void event_button_clicked(GtkButton *button, gpointer data);

void battle_button_clicked(GtkButton *button, gpointer data);

```

## 5. demo

# FP_finalproject

## build

```bash=
brew install gtk+3
git clone https://github.com/MixnightE/FP_finalproject.git
# 主要是確定有<gtk/gtk.h>
cd our/project/place/directory # clone的資料夾
make
./myproject
```

The start
![](https://hackmd.io/_uploads/B1uNT9EP3.png)

The battle
![](https://hackmd.io/_uploads/BJaHp54wh.png)

github link
https://github.com/CCU5703/ProgrammingDesign_FinalProject.git
