# dbindextester
A simple db index tester.

这个测试实际是这样的：

首先需要继承interface这个类，然后写好这几个函数，在main函数中new一下然后begintest即可。然后初始化神马的得自己来做（毕竟我也不知道怎么初始化）

往里面传的是什么呢？key是一个int型的整数转化为一个4位的char的结果，所以肯定可能有'\0'，value不用说。

建议参考naiveinterface里面有关pagenum和pageposition的处理，这样value可以为char*类型，比较方便处理。

添加了多value的测试

但是注意有一个BANERRORUPDATE的选项，这个选项关闭的时候可能会出现错误的更新（比如已有key=1 value=2,3和key=1 value=3.4，然后把key=1 value=2,3的value更新为3,4），可以打开来避免这种更新操作的发生。

另外多value测试测试数不要太大，因为是个线性测试

具体接口参考naivemultidbinterface，其中find这个接口可以暂时不采用（因为多键测试是不会调用的）