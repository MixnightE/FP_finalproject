#include <stdlib.h>

#define MAX_MAP_HEIGHT 9
#define MAX_ROOM_LINK_SIZE 4
#define MAX_ROOM_SIZE_PER_FLOOR (1 << 4)

typedef enum roomType
{
    TYPE_ENEMY,
    TYPE_EVENT
} RoomType;

typedef struct Room
{
    RoomType type;
    struct Room *link[MAX_ROOM_LINK_SIZE];
} room;

typedef struct Map
{
    room *root;
    int height;
} map;

void generate_map(map *mp)
{
    mp->root = (room *)malloc(sizeof(room));
    mp->height = MAX_MAP_HEIGHT;
    room *table[MAX_MAP_HEIGHT][MAX_ROOM_SIZE_PER_FLOOR];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < (1 << i); j++)
        {
            table[i][j] = (room *)malloc(sizeof(room));
        }
    }
}