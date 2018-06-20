# MMSeg

## 1. 关于MMSeg

MMSeg 是台湾蔡志浩（Chih-Hao Tsai）发明的基于字符串匹配的中文分词方法，使用四种方法消除正向最大匹配策略遇到的歧义：

1. 备选词块(Chunk)的长度最大（默认相邻词块长度为3）
2. 备选词块的平均词长最大
3. 备选词块的词长变化最小
4. 备选词块中单字的出现词自由度最高（此项规则在JKOM方案中未使用）

详细说明参见 ( [mmseg分词算法及实现](https://blog.csdn.net/daniel_ustc/article/details/50488040) )

## 2. 关于MMSeg在JKOM Precise中的应用与修改

MMSeg用于在Precise系统中对文字部分（如体检综述）进行分词，且做了如下修改：

1. 修正了原始代码中Class Node析构函数的bug
2. 使用mutex将MMseg改为单例线程安全模式
3. 在MMSeg::getChunks()返回的Chunck结构体中增加对每个chunk是否为未登录词的标记
4. 将MMSeg::segment()修改为仅返回词典中包含的词，且以空格分隔
5. 新增MMSeg::unload()函数，以卸载当前使用的词典，以便重新加载新词典
6. 新增MMSeg::getInitStatus()函数，以获取当前词典加载状态

在以上修改基础之上，为了便于数据分析团队在python中以ctypes方式调用MMSeg，又对MMSeg做了封装，即源文件中src/MmsegWrapper.cpp src/MmsegWrapper.h，编译成libmmseg.so 后向python提供6个方法。

## 3. 关于MMSeg在JKOM Precise中的编译与测试

### 3.1 编译环境

Linux

1. Ubuntu 16.04（64位）
2. gcc 5.4.0

Mac

1. OS X Yosemite 10.10.4
2. gcc 8.1.0

### 3.2 Linux编译方法

1. 解压缩后进入目录，执行make命令
2. 编译完成后，生成两个文件，分别是 libs/libmmseg.so 和 bin/mmseg

### 3.3 Mac编译方法

1. 解压缩后进入目录，在命令行下执行编译命令
2. 编译动态库libmmseg.so

```bash
g++-8 -Ofast -march=native -funroll-loops -fPIC -std=c++11 -lm -Wall -Wno-unused -shared src/Mmseg.cpp src/MmsegWrapper.cpp -o ./libs/libmmseg.so
```

3. 编译可执行测试程序

```bash
g++-8 -Ofast -march=native -funroll-loops -fPIC -std=c++11 -lm -Wall -Wno-unused  src/Mmseg.cpp src/MmsegWrapper.cpp src/main.cpp  -L. -o ./bin/mmseg
```

### 3.3 测试方法

#### 3.3.1 使用 mmseg 测试

进入bin目录，有两种测试方法，区别是前者直接加载需要分词的文件，后者在命令行输入待分词的文字。

- 方法一：执行 ./mmseg ../data/words.dic ../scripts/jyzs.txt
- 方法二：执行 ./mmseg ../data/words.dic

#### 3.3.2 使用 mmseg.py 测试

进入scripts目录，执行以下命令(python 2.7执行通过）。

```bash
python ./mmseg.py
```

## 4. 关于Libmmseg 可通过ctypes 调用的函数说明

### 4.1 如何在python中加载mmseg库

ctypes为python默认库，无需安装。

```python
import  ctypes

mmseg = ctypes.CDLL("../libs/libmmseg.so")
```

### 4.1 getInstance()

功能|获取MMSeg实例
---|---|
输入参数|无
输出参数| MMSeg实例

#### Example：

```python
instance  = mmseg.getInstance()
```

### 4.2 delInstance()

功能|删除MMSeg实例
---|---|
输入参数| MMSeg实例
输出参数| 无

#### Example

```python
mmseg.delInstance(instance)
```

### 4.3 loadDict()

功能|加载字典
---|---|
输入参数|字典文件路径
输出参数| 整型，0表示成功，非0表示失败
其他|MMSeg实例生命周期内，可多次加载/卸载字典

#### Example

```python
mmseg.loadDict(instance, "../data/words.dic")
```

### 4.4 unloadDict()

功能|卸载词典
---|---|
输入参数| MMSeg实例
输出参数| 无

#### Example

```python
mmseg.unloadDict(instance)
```

### 4.5 copySegs()

功能|获取分词结果
---|---|
输入参数| 两个输入参数，MMSeg实例 和 <font color=red>utf8编码</font>的字符串
输出参数| 分词后结果，按序返回输入串中包含的词典用词，且以空格分隔
其他|MMSeg实例生命周期内，可以反复多次执行分词

#### Example

```python
s = mmseg.copySegs(instance, "双侧乳腺轻度小叶增生伴左乳结节")
data = ctypes.string_at(s, -1).decode("utf-8")
print(data)
```

### 4.6 releaseSegs()

功能|释放分词结果占用的资源
---|---|
输入参数| 需释放的分词结果资源
输出参数| 无

#### Example

```python
mmseg.releaseSegs(s)
```

### 4.7 完整样例

```python
import  ctypes

mmseg = ctypes.CDLL("../libs/libmmseg.so")
instance  = mmseg.getInstance()
mmseg.loadDict(instance, "../data/words.dic")
s = mmseg.copySegs(instance, "双侧乳腺轻度小叶增生伴左乳结节")
data = ctypes.string_at(s, -1).decode("utf-8")
mmseg.releaseSegs(s)
print(data)
mmseg.unloadDict(instance)
mmseg.delInstance(instance)
```
