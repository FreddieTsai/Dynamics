# System Documentation

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
>  型別?

>* 棒子長度
>  型別?

###怎麼樣呼叫函式

##計算`function`
>*計算角速度
> ```c++
> double angspeed(   length, double degree)
> return angSpeed 
> ```

>*計算角加速度
> ```c++
> double angAcceler(   length, double degree)
> return angAcceler;
> ```

##輸出`main`
###功能
>*顯示出棍子從初始角度落下到結束的角度間的動態
>Q可不可以在畫面中棍子移動到的位置顯示該位置的角速度與角加速度呢?例如有兩個角(加)速度值得顯示格，其中的數值會一直跳
>Q計算角速度、角加速度的函示分別回傳到main的值可以在顯示時有幫助嗎?
>Q顯示的時候是要如何顯示出加速度感用一貞一貞




> * 設定使用者的Secret Key, KeyID
> ```java
> public void setKeyAndID(String secretKey, String KeyID);
> ```

> * 取得使用者的key&ID
> ```java
> public KeyAndID getKeyAndID()
> ```

> * 取得特定股票的歷史交易紀錄
> ```java
> public List<Deal> getHistoryRecord(String stockName);
> ```

> * 取得總盈虧
> ```java
> public double getTotalProfitAndLoss();
> ```

> * 將一筆交易記錄到History Record中
> ```java
> public void addDeal2HistoryRecord(String stockName, int stockCount, double profitAndLoss, int year, int month, int date);
> ```

> * 將對特定股票的單次觀察存入紀錄陣列recorder (List<MarketInfo>)中
> ```java
> public void addStockMarketInfo2Recorder(
>   String stockName, String mode,
>   double highPrice, double lowPrice, double openingPrice, double closingPrice,
>   int year, int month, int date
> )
> ```

> * 取得對特定股票在市場上的資訊的觀察紀錄陣列recorder (List<MarketInfo>)
> ```java
> public List<MarketInfo> getRecorder(String stockName, String mode);
> ```


## Stock `class`
### 方法 :
> * 建構式
> ```java
> public Stock(String stockName, double stockPrice, int stockCount);
> ```

> * 取得股票名稱
> ```java
> public String getStockName();
> ```

> * 取得股價
> ```java
> public double getStockPrice();
> ```

> * 取得持有的股數
> ```java
> public int getStockCount();
> ```


## StockBuyingSetting `class`
### 方法 :
> * 建構式
> ```java
> public StockBuyingSetting(
>    String stockName, double bidPrice, double offerStep, double stockCount
> );
> ```

> * 取得股票名稱
> ```java
> public String getStockName();
> ```

> * 取得目標買價
> ```java
> public double getBidPrice();
> ```

> * 取得上漲多少錢時賣出
> ```java
> public double getOfferStep();
> ```

> * 取得下跌多少錢時買入
> ```java
> public double getBidStep();
> ```

> * 取得該股票交易的股數
> ```java
> public int getStockCount();
> ```

> * 設定股票名稱
> ```java
> public void setStockName(String stockName);
> ```

> * 設定目標買價
> ```java
> public void setBidPrice(double bidPrice);
> ```

> * 設定上漲多少錢時賣出
> ```java
> public void setOfferStep(double offerStep);
> ```

> * 設定下跌多少錢時買入
> ```java
> public void setBidStep(double bidPrice);
> ```

> * 設定交易的股數
> ```java
> public void setStockCount(int stockCount);
> ```


## KeyAndID `class`
### 方法 :
> * 建構式
> ```java
> public KeyAndID(String secretKey, String keyID);
> ```

> * 取得使用者的Key ID
> ```java
> public String getKeyID();
> ```

> * 取得使用者的Secret Key
> ```java
> public String getsecretKey();
> ```

> * 設定使用者的Secret Key
> ```java
> public void setsecretKey(String secretKey);
> ```

> * 設定使用者的Key ID
> ```java
> public void setKeyID(String KeyID);
> ```


## HistoryRecord `class`
### 方法 :
> * 將一筆交易存入歷史紀錄的陣列
> ```java
> public void addADeal(Deal deal);
> ```

> * 取得特定股票的所有歷史交易紀錄
> ```java
> public List<Deal> getRecord(String stockName);
> ```

> * 取得(所有歷史交易)累積的盈虧
> ```java
> public double getProfitAndLoss();
> ```


## MarketInfo `class`
### 方法 : 
> * 取得股票名稱
> ```java
> public String getStockName();
> ```

> * 取得單一觀察的時間長度 (mode: 每日"DAY", 每周"WEEK", 每月"MON")
> ```java
> public String getMode();
> ```

> * 取得觀察的時間
> * (mode:時間) "DAY":YYYY-MM-DD, "WEEK":(起始的)YYYY-MM-DD, "MON":(起始的)YYYY-MM-DD
> ```java
> public String getDate();
> ```

> * 取得開盤價
> ```java
> public double getOpeningPrice();
> ```

> * 取得收盤價
> ```java
> public double getClosingPrice();
> ```

> * 取得最高價
> ```java
> public double getHighPrice();
> ```

> * 取得最低價
> ```java
> public double getLowPrice();
> ```


## StockMarketInfoRecorder `class`
### 方法 :
> * 建構式
> * mode : 單一觀察時間段的長度 (mode: 每日"DAY", 每周"WEEK", 每月"MON")(預設為"DAY")
> ```java
> public StockMarketInfoRecorder(String stockName, String mode);
> ```

> * 將單一時間段中，該股票的市場資訊放入紀錄陣列recorder (List<MarketInfo>)中
> * highPrice : 最高價
> * lowPrice : 最低價
> * openingPrice : 開盤價
> * closingPrice : 收盤價
> ```java
> public void addMarketInfo2Recorder(
>   String stockName, String mode,
>   double highPrice, double lowPrice, 
>   double openingPrice, double closingPrice,
>   int year, int month, int date
> )
> ```

> * 取得被紀錄的股票名稱
> ```java
> public String getStockName();
> ```

> * 取得單一觀察的時間段長度 (mode: 每日"DAY", 每周"WEEK", 每月"MON")(預設為"DAY")
> ```java
> public String getMode();
> ```
