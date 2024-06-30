<<<<<<< HEAD
# Dynamics
一、輸入
 1.變數：質量、長度、初始角度、結束的角度 (角度要換成徑度)  
 2.型別：都要用double？

二、運算
 1.介於初始角度、結束時的角度間固定單位間隔角度的角速度、角加速度
 2.回傳角度和角加速度給main 

三、輸出
 1.要怎麼輸出讓影像看起來有加速感？
=======
# Dynamics documentation

## 輸入`main`
### 功能:
> 存取需要的參數，使用者輸入初始角度、結束的角度、棍子的質量及長度
>* 初始角度的型別
> ```c++
> double InitialAngle
> ```

>* 結束角度的型別
> ```c++
> double TerminalAngle
> ```

>* 棒子質量
>  ```c++
>  double StickMass
>  ```

>* 棒子長度
>  ```c++
>  double StickLength
>  ```

### 怎麼樣呼叫函式

## 計算`function`
> * 計算角速度
> ```c++
> double angspeed(   length, double degree)
> return angSpeed 
> ```

> * 計算角加速度
> ```c++
> double angAcceler(   length, double degree)
> return angAcceler;
> ```

## 輸出`main`
### 功能
> * 顯示出棍子從初始角度落下到結束的角度間的動態
> <br>
> Q可不可以在畫面中棍子移動到的位置顯示該位置的角速度與角加速度呢?例如有兩個角(加)速度值得顯示格，其中的數值會一直跳
> <br>
> Q計算角速度、角加速度的函示分別回傳到main的值可以在顯示時有幫助嗎?
> <br>
> Q顯示的時候是要如何顯示出加速度感用一貞一貞
>>>>>>> 00ff98f3fb0a9be88335ae62573964e300deb39b
