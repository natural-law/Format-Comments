# 使用说明

## 申请有道的API key
申请地址： http://fanyi.youdao.com/openapi

进入网页以后，点击“我是开发者”，然后按照提示填写所有的表单信息，同意条款后提交申请。

申请成功以后，修改脚本里面的
API_KEY和KEYFROM字段。

```
KEYFROM = 'zilo***nren'
API_KEY = '19*****90'
```

#### WARNING: 现在里面的字段是空的，大家用自己申请的KEY。另外，因为有道API的使用是有次数限制的，**每小时不得超过1000次，超过限制会被封IP**。

## 脚本运行说明

```
python ./parse_headers.py  -s 需要翻译的文件名 [-d 目标输出文件名]
```

示例: UIButton.h

```
python ./parse_headers.py -s ./src/UIButton.h -d ./dest/UIButton.h
```

如果没有传入目标文件，则会覆盖源文件：

```
python ./parse_headers.py -s ./cocos/2d/CCAction.h
```

CCAction.h会被自动翻译并覆盖到源文件中

## 注意

- **该工具只用来提升大家的工作效率，并不是代替大家的工作，自动翻译完成后一定要自审一遍所有翻译，因为有道的翻译很多是不可读或错误的**

- 已经翻译一半的头文件也可以使用，但是已经包含@~chinese的注释段不会被处理

- 本工具只在Mac下面测试过，如果Windows和Linux用户用不了，请提issue

- 大家翻译的工作流，推荐先用这个工具刷出一个头文件的机器自动翻译，然后手动调整校对好，再发PR给我review.

- 一个PR只包含一个头文件翻译，否则不好Review.

- 如果发现下面的错误，请升级python到2.7.6以上版本

    ```
    Traceback (most recent call last):
      File "parse_headers.py", line 21, in <module>
        elementRE = re.compile("(?P<element>@(?P<name>[\w~]+)\s?(?P<content>[^@]*)?)")
      File "/usr/local/Cellar/python/2.7.5/Frameworks/Python.framework/Versions/2.7/lib/python2.7/re.py", line 196, in compile
        return _compile(pattern, flags)
      File "/usr/local/Cellar/python/2.7.5/Frameworks/Python.framework/Versions/2.7/lib/python2.7/re.py", line 248, in _compile
        raise error, v # invalid expression
    sre_constants.error: nothing to repeat
    ```
