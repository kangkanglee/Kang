# 测试新的Op

测试方法：
* 将注册新Op的C++文件编译成so文件
* 编写python测试程序导入so文件
* 一个实际的例子

## 编译Op文件
通过下面的命令编译c++文件，编译通过可以生成so文件
```bash
TF_INC=$(python -c 'import tensorflow as tf; print(tf.sysconfig.get_include())')

g++ -std=c++11 -shared zero_out.cc -o zero_out.so -fPIC -I $TF_INC -O2
```
> 如果gcc版本是gcc5，需要带上参数`-D_GLIBCXX_USE_CXX11_ABI=0`，以保持兼容

## 编写python测试程序
通过Python API，“load_op_library”导入so文件，导出的结果是一个模块，之后就可以调用这个模块。
```python
import tensorflow as tf

out_module = tf.load_op_library('fact_out.so')
out = out_module.fact_out
```

## 一个实际的例子
注册新Op的C++文件(fact_out.cc)：
```C++
#include "tensorflow/core/framework/op.h"
#include "tensorflow/core/framework/op_kernel.h"

using namespace tensorflow;

REGISTER_OP("FactOut")
    .Output("fact: string")
        .Doc(R"doc(
        Output a fact about factorials.
        )doc");

        class FactOutOp : public OpKernel {
         public:
          explicit FactOutOp(OpKernelConstruction* context) : OpKernel(context) {}

          void Compute(OpKernelContext* context) override {
            Tensor* output_tensor = NULL;
            OP_REQUIRES_OK(context,
                           context->allocate_output(0, TensorShape(), &output_tensor));
            auto output = output_tensor->template scalar<string>();
            output() = "0! == 1";
          }
        };

REGISTER_KERNEL_BUILDER(Name("FactOut").Device(DEVICE_CPU), FactOutOp);
```

测试文件(fact_test.py)
```python
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import tensorflow as tf

class FactOutTest(tf.test.TestCase):
    def testFactOut(self):
        fact_out_module = tf.load_op_library('fact_out.so')
        with self.test_session():
            result = fact_out_module.fact_out()
            self.assertAllEqual(result.eval(),b'0! == 1')

if __name__ == '__main__':
    tf.test.main()
```
> 注意这里fact_out的命名。在c++文件里面是驼峰命名FactOut，在python里面引用时用下划线fact_out

输出如下：
```sh
-----------------------------------------------------------------
Ran 2 tests in 0.014s

OK
```

更多资料可以参考 //tensorflow/g3doc/how_tos/adding_an_op/index.md
