# 專案架構

-   src ：存放原始碼和內部標頭檔
-   setting ：存放設定檔(.json, .txt, etc)
-   include ：存放公開標頭檔
-   dist ：存放專案產出
-   bin ：當專案產出為應用程式時，可用 bin 取代 dist
-   test ：存放測試程式
-   example ：存放範例程式
-   doc ：存放說明文件

-   README 或 README.md ：讀我檔案
-   INSTALL ：安裝說明
-   LICENSE ：專案的授權文件
-   HISTORY ：專案的版本釋出記錄
-   .gitignore ：讓 Git 忽略某些形態的目錄或檔案
-   .travis.yml ：Travis CI 的設定檔
-   Makefile ：make(1) 或 gmake(1) 預設的設定檔
-   configure ：Autotools 的命令稿
-   CMakeLists.txt ：cmake(1) 預設的設定檔

./
├── GUI
│ └── home.c
├── Makefile
├── README.md
├── bin
│ └── main.c
├── data
│ ├── buff.json
│ ├── card.json
│ └── enemy.json
├── dist
│ └── main.c
├── doc
│ ├── ForInstaller.md
│ └── standard.md
├── example
├── image
├── include
│ ├── Action.h
│ ├── Buff.h
│ ├── BuffAction.h
│ ├── Card.h
│ ├── CardAction.h
│ ├── Constant.h
│ ├── Enemy.h
│ ├── EnemyAction.h
│ ├── Field.h
│ ├── FuncTable.h
│ ├── Map.h
│ ├── Player.h
│ ├── Relic.h
│ ├── cJSON.h
│ ├── fileIO.h
│ └── head.h
├── myproject
├── setting
│ └── setting.json
├── src
│ ├── Action.c
│ ├── Buff.c
│ ├── Card.c
│ ├── CardAction.c
│ ├── Enemy.c
│ ├── EnemyAction.c
│ ├── FuncTable.c
│ ├── cJSON.c
│ └── fileIO.c
└── test
├── Bettle.c
├── Card.h
├── EnemyData.h
├── room.c
└── test.c
