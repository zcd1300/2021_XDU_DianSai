(以下目录分类按照MDK工程文档中的组名,子目录按照对应名称的代码文件分类)

# 目录

##  [APP](#APP分类)

1. main
2. freeRTOS

## [BSP](##BSP分类)

1. USART
2. DMA
3. GPIO
4. I2C

## [Driver](##Driver分类)

1. OLED
2. ESP8266
3. Time_soft

## [Task](##Task分类)

1. oled0.96
2. keyboard

## [一些可能需要注意的点](##一些可能要注意的点)

## [CubeMX配置图](##CubeMX配置)

# 正文

## APP分类 ##

1. main

   主函数负责时钟树配置和对外设的初始化函数调用，FreeRTOS内核以及任务线程的初始化、任务调度器启用。各个任务的具体实现在独立的文件中；

   

   ### 注意

   如果需要添加新的任务线程，对应的创建函数应该在调度器启动前被调用

   ![image-20210315154229882](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210315154229882.png)

   ![image-20210315154245659](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210315154245659.png)

2. FreeRTOS

   这个文件中是使用CubeMX配置后RTOS生成的可以完成添加新的线程。（但是我常直接在功能实现的文件中完成对新线程的配置，此工程也是）
   
   工程中使用了操作系统绝对延时，要在CubeMX中将 osDelayUntil 函数使能，或者在配置代码中手动使能.

## BSP分类 ##

1. USART

   * 两个串口使用的都是异步模式,并且通过DMA直接访问Flash,单片机接收部分实现采用的是空闲中断的变长接受.

   * usart1  波特率9600

     ​	串口1 的功能是将单片机的信息上传到电脑,方便对程序运行状态判断,同时会将串口1收到的**数据转发给串口3**以通过上位机修改wifi模块参数.,串口1单次接受最大100字节 ;

   * usart3 波特率115200

     ​	串口3 是与WiFi模块通信的接口;空闲变长接受,数据长度单词最大600字节.
     
   *  串口3转发串口1的语句默认注释掉,取消注释才可以在串口调试助手中看见Wifi回传的信息,实际运行时**建议注释掉**,不注释掉有几率导致内存溢出.![image-20210315162820021](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210315162820021.png)
     
   * DMA串口空闲接受的实现代码在usart.c文件中![image-20210315163551493](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210315163551493.png) 成功接受还需要在接收中断函数中调用下(在stm32f1xx_it.c 文件中)![image-20210315163658406](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210315163658406.png)
     

   **PS** **:**这里可以如果单片机RAM空间足够可以将接受缓冲区改更大,同时也要将RTOS对应线程分配的栈空间增大. 实测F103c8t6 当前参数能完成功能,RAM占用也已经较高.  还有另外一种方式: 将缓冲区数组换成环形队列(或者使用FreeRTOS提供的队列功能),但是我这里满足需求了没有换.有兴趣的可以优化下.

2. DMA

   DMA通道在CubeMX中配置完成后即可,这个文件没有特殊需求不用改动.

3. GPIO

   完成对GPIO引脚,时钟、输入输出模式、引脚速度的配置和对引脚初始电平设置,按需求可以修改.

4. I2C

   CubeMX自动生成,I2C速率设置为400k;100k屏幕刷新率比较低. (当需要传输\接收大量数据的时候建议使用中断,这个工程中超时传输即可满足)

   STM32芯片有硬件I2C,也可以使用GPIO模拟I2C.网上说硬件I2C有BUG,我使用的是HAL库硬件I2C,没有触发BUG. 
   
   (个人感觉如果硬件I2C没问题,模拟和硬件各有好处,硬件I2C可以使用中断触发、DMA减少CPU负担,模拟I2C的则可以有更灵活的引脚配置,根据需求选择.)

## Driver分类 ##

* oled

  oled屏幕驱动,包含对屏幕的各种操作(屏幕初始化、显存刷新、显示开关、像素控制、显示控制等具体操作见函数注释)，头文件中有对应的寄存器操作说明

* esp8266

  esp8266 AT驱动,实现对WiFi模块的操作(Wifi连接、Wifi模式设置、建立连接、检索指定内容等，详见函数注释)，对应头文件中包含了Wifi操作指令。除此还有对网络时间的抓取更新。

* Time_soft

  实现时钟的定时，因为FreeRTOS开启了绝对延时,可以通过一个进程加变量完成定时，而且保证时钟同时和其他功能运行也需要新的线程，便没有使用定时器。除此之外，实现时钟功能还可以使用定时器、RTC完成。这里不再拓展。

* oledfont

  没什么好说的，存放oled显示所需要的字库数据。

* bmp

  存放oled显示图片所需的数据。

  **PS：** 这里存放字库和图片数据的数组如果设计是不需要在程序运行时修改的话，建议将数组声明为静态数组，减少RAM占用。

## Task分类 ##

* oled096

  oled显示的逻辑代码，主要分为三个界面，由键盘控制切换<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210315184413498.png" alt="image-20210315184413498" style="zoom:25%;" />

  1. 默认界面，显示时间：年月日 时分秒 ，如果正确连接Wifi模块且可以联网的话，会自动抓取网络时间校准（校准大概需要几秒钟，具体根据网络状况。），网络时间来源为苏宁的授时网站。

     **注意：**如果使用Wifi的话，单通过串口供电大概率不能正常驱动Wifi模块，需要给Wifi外加供电。![20210315_183818](D:\CubeMX\DianSai\20210315_183818.jpg)

  2. 文字、图片显示界面

     可以通过键盘控制校徽移动，具体实现见代码<img src="D:\CubeMX\DianSai\20210315_183837.jpg" alt="20210315_183837" style="zoom:50%;" />

  3. LED灯控制界面![20210315_183857](D:\CubeMX\DianSai\20210315_183857.jpg) 

     按键控制单双灯流水、单独控制

  4. 屏幕亮度控制

     两个预留案件控制屏幕亮度，具体定义见代码；调整亮度时会有屏幕提示。

* keyboard

  键盘扫描，尝试过三种扫描方式，目前最多做到非相邻四个按键同时检测。如果有更好的方法可以替换，欢迎在Github上 https://github.com/zcd1300/2021_XDU_DianSai 提交迭代交流。



## 一些可能要注意的点 ##

​	1. 堆栈大小设置![image-20210315185720603](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210315185720603.png)

​	因为f103c8t6的Flash和RAM有限,这个分配是可以确定能跑起来的,栈空间过小过大可能导致异常,堆大小设置因为加了RTOS,具体看操作系统的内存管理.

2. FreeRTOS
3. 还有些注意点在上面的分类文档中提到了,这里就不在复述.

## CubeMX配置 ##

时钟树![image-20210315190226341](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210315190226341.png)

代码生成配置

<img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210315190322389.png" alt="image-20210315190322389" style="zoom: 33%;" /><img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210315190334953.png" alt="image-20210315190334953" style="zoom: 33%;" />

FreeRTOS总堆大小限制(字节)

![image-20210315190525599](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210315190525599.png)

其他的CubeMX选项可以在ioc文件找到,这里就不一一列举了。