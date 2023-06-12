#ifndef _CALLBACK_H_
#define _CALLBACK_H_

#include <game.h>

typedef struct EventParamData
{
    GtkWidget *stack;  // 儲存介面的堆疊
    GtkWidget *window; // 儲存視窗
} EventParam;

void StartButton_clicked_cb(GtkWidget *widget, gpointer data);

void SettingButton_clicked_cb(GtkWidget *widget, gpointer data);

void MainStack_visible_child_name_notify_cb(GObject *gobject, GParamSpec *pspec, gpointer user_data);

void DrawCardDeckButton_clicked_cb(GtkWidget *widget, gpointer data);

void FoldCardDeckButton_clicked_cb(GtkWidget *widget, gpointer data);

void HandCardChooseButton_clicked_cb(GtkWidget *widget, gpointer data);

void BattleRoundEndButton_clicked_cb(GtkWidget *widget, gpointer data);

void BattleRoundNextButton_clicked_cb(GtkWidget *widget, gpointer data);

void event_button_clicked(GtkButton *button, gpointer data);

void battle_button_clicked(GtkButton *button, gpointer data);

void LoseButton_clicked_cb(GtkButton *button, gpointer data);

void BackButton_clicked_cb(GtkButton *button, gpointer data);

void EventChooseButton1_clicked_cb(GtkButton *button, gpointer data);

void EventChooseButton2_clicked_cb(GtkButton *button, gpointer data);

void EndButton_clicked_cb(GtkButton *button, gpointer data);

void WinButton_clicked_cb(GtkButton *button, gpointer data);

// 將名為image_name的圖檔導入，回傳GdkPixbuf物件
GdkPixbuf *scale_image(const char *image_name, int new_width /*新的寬度*/);

#endif // _CALLBACK_H_