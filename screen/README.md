# How to use `screen.h`

## 步驟
1. 初始化螢幕物件 `create_screen`
2. 畫東西上去 `draw_pendulum` or `draw_data_panel` or `screen_input`
3. 顯示出來 `screen_show`

<br>

## Data Type

* ### Screen (`struct`)

    螢幕物件，記錄了所有和螢幕顯示有關的資訊，也是`screen.h`的操作對象。使用`screen.h`的函式時，需要傳入。

    - - -

* ### screen_input_name (`enum`)

    適用於`screen_input`的參數
    1. `THETA`  : 單擺 和 X軸正向 的夾角
    2. `ALPHA`  : 單擺的角加速度
    3. `OMEGA`  : 單擺的角速度
    4. `LENGTH` : 單擺的長度
    5. `MASS`   : 單擺的質量
    6. `NONE`   : 沒在輸入

<br>

## Function

* ### create_screen

    * 功能：用來初始化 螢幕物件(`Screen`)
    * 參數：
        1. `screen_width`     : 螢幕顯示範圍的高度
        2. `screen_height`    : 螢幕顯示範圍的寬度
    * 回傳值：初始化好的物件 or NULL(初始化失敗)

    ```c++
    Screen create_screen()
    ```
    ```c++
    Screen create_screen(int screen_width, int screen_height)
    ```

    - - -

* ### set_screen_size

    * 功能：用來設定顯示範圍
    * 參數：
        1. `screen`           : 螢幕物件
        2. `screen_width`     : 螢幕顯示範圍的高度
        3. `screen_height`    : 螢幕顯示範圍的寬度
    * 回傳值：傳入的螢幕物件 or NULL(執行失敗)
    - 註：執行此函式會把螢幕清空

    ```c++
    Screen set_screen_size(Screen screen)
    ```
    ```c++
    Screen set_screen_size(Screen screen, int screen_width, int screen_height)
    ```

    - - -

* ### clean_screen

    * 功能：把螢幕清空，這樣就能畫新東西了
    * 參數：
        1. `screen` : 螢幕物件
    * 回傳值：傳入的螢幕物件 or NULL(執行失敗)

    ```c++
    Screen clean_screen(Screen screen)
    ```

    - - -

* ### draw_pendulum

    * 功能：把 單擺 畫出來
    * 參數：
        1. `screen`    : 螢幕物件
        2. `theta`     : 單擺 和 **X軸正向** 的夾角
        3. `length`    : 單擺的長度
    * 回傳值：傳入的螢幕物件 or NULL(執行失敗)

    ```c++
    Screen draw_pendulum(Screen screen, double theta, double length)
    ```

    - - -

* ### draw_data_panel

    * 功能：把 顯示當前數值的面板 畫出來
    * 參數：
        1. `screen` : 螢幕物件
        2. `theta`  : 單擺 和 X軸正向 的夾角
        3. `alpha`  : 單擺的角加速度
        4. `omega`  : 單擺的角速度
        5. `length` : 單擺的長度
        6. `mass`   : 單擺的質量
    * 回傳值：傳入的螢幕物件 or NULL(執行失敗)

    ```c++
    Screen draw_data_panel(Screen screen, char* theta, char* alpha, char* omega, char* length, char* mass)
    ```

    - - -

* ### screen_input

    * 功能：把 等待輸入的符號(I) 畫出來
    * 參數：
        1. `screen` : 螢幕物件
        2. `name`   : 正在輸入哪個參數
    * 回傳值：傳入的螢幕物件 or NULL(執行失敗)

    ```c++
    Screen screen_input(Screen screen, screen_input_name name)
    ```

    - - -

* ### screen_show

    * 功能：把 螢幕上的內容 顯示出來
    * 參數：
        1. `screen` : 螢幕物件
    * 回傳值：傳入的螢幕物件 or NULL(執行失敗)
    - 註：執行此函式會把螢幕清空

    ```c++
    Screen screen_show(Screen screen)
    ```