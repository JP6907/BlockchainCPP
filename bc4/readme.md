### 增加的功能
- 创建交易对象、交易输入、交易输出
- 使用交易集代替原来区块中的字符串data
- findUnspentTransactions 包含为交易输出的交易
- findUTXO 查找未交易输出
- getBalance 计算账户余额


### 问题
findUnspentTransactions函数返回值使用vector<Transaction*>类型以及         
findUTXO函数返回值使用vector<TXOutput*>类型         
getBalance函数调用得到的值会是随机数？？？？？？          
但是把Transaction* 和TXOutput* 改成Transaction和TXOutput(不是指针类型)后就可以获得正确的数值


