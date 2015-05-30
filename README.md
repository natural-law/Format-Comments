#使用说明

##申请有道的API key
申请地址： http://fanyi.youdao.com/openapi

进入网页以后，点击“我是开发者”，然后填写一个邮箱和网站名字就可以了。

申请成功以后，修改脚本里面的
API_KEY和KEYFROM字段。

下面是我的脚本里面的值

```
KEYFROM = 'zilongshanren'
API_KEY = '1978571890'
```

现在里面的字段是我申请的，大家尽量用自己的。因为有道API的使用是有次数限制的，每小时不得超过1000次。

## 脚本运行说明

```
python ./parse_headers.py  -s 需要翻译的文件名 [-d 目标输出文件名]
```

示例: UIButton.h

```
python ./parse_headers.py -s ./src/UIButton.h -d ./dest/UIButton.h
```

上面的代码没有传入目标文件，则会覆盖源文件。

##注意
- 已经翻译一半的头文件不要使用这种方法。

- 本工具只在Mac下面测试过，如果Windows和Linux用户用不了，请提issue

- 大家翻译的工作流，推荐先用这个工具刷出一个头文件的机器自动翻译，然后手动调整校对好，再发PR给我review.

- 一个PR只包含一个头文件翻译，否则我不好Review.

