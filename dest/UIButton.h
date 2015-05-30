/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __UIBUTTON_H__
#define __UIBUTTON_H__

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */

NS_CC_BEGIN

class Label;
class SpriteFrame;

namespace ui{

    class Scale9Sprite;
/**@~english
 * Represents a push-button widget.
 * Push-buttons can be pressed, or clicked, by the user to perform an action.
 * @~chinese 
 * 代表一个按钮部件。
 * 可以按下按钮,或者点击,由用户来执行一个动作。
 */

class CC_GUI_DLL Button : public Widget
{

    DECLARE_CLASS_GUI_INFO

public:

    /**@~english
     * Default constructor.
     * @~chinese 
     * 默认构造函数。
     */

    Button();

    /**@~english
     * Default destructor.
     *
     * @~chinese 
     * 默认的析构函数。
     * 
     * @lua NA
     */

    virtual ~Button();

    /**@~english
     * Create a empty Button.
     * @~chinese 
     * 创建一个空的按钮。
     *@return @~english A empty Button instance.
     * @~chinese 一个空按钮实例。
     */

    static Button* create();

    /**@~english
     * Create a button with custom textures.
     * @~chinese 
     * 创建一个自定义的按钮纹理。
     * @param normalImage @~english normal state texture name.
     * @~chinese 正常状态结构的名字。
     * @param selectedImage  @~english selected state texture name.
     * @~chinese 选中状态结构名称。
     * @param disableImage @~english disabled state texture name.
     * @~chinese 禁用状态结构的名字。
     * @param texType    @see `TextureResType`
     * @return @~english a Button instance.
     * @~chinese 一个按钮的实例。
     */

    static Button* create(const std::string& normalImage,
                          const std::string& selectedImage = "",
                          const std::string& disableImage = "",
                          TextureResType texType = TextureResType::LOCAL);

    /**@~english
     * Load textures for button.
     *
     * @~chinese 
     * 加载纹理的按钮。
     * 
     * @param normal    @~english normal state texture name.
     * @~chinese 正常状态结构的名字。
     * @param selected    @~english selected state texture name.
     * @~chinese 选中状态结构名称。
     * @param disabled    @~english disabled state texture name.
     * @~chinese 禁用状态结构的名字。
     * @param texType    @see `TextureResType`
     */

    void loadTextures(const std::string& normal,
                      const std::string& selected,
                      const std::string& disabled = "",
                      TextureResType texType = TextureResType::LOCAL);

    /**@~english
     * Load normal state texture for button.
     *
     * @~chinese 
     * 加载纹理正常状态的按钮。
     * 
     * @param normal    @~english normal state texture.
     * @~chinese 正常状态纹理。
     * @param texType    @see `TextureResType`
     */

    void loadTextureNormal(const std::string& normal, TextureResType texType = TextureResType::LOCAL);

    /**@~english
     * Load selected state texture for button.
     *
     * @~chinese 
     * 负载选择国家纹理按钮。
     * 
     * @param selected    @~english selected state texture.
     * @~chinese 选定的国家结构。
     * @param texType    @see `TextureResType`
     */

    void loadTexturePressed(const std::string& selected, TextureResType texType = TextureResType::LOCAL);

    /**@~english
     * Load disabled state texture for button.
     *
     * @~chinese 
     * 加载纹理的按钮禁用状态。
     * 
     * @param disabled    @~english dark state texture.
     * @~chinese 黑暗状态纹理。
     * @param texType    @see `TextureResType`
     */

    void loadTextureDisabled(const std::string& disabled, TextureResType texType = TextureResType::LOCAL);

    /**@~english
     * Sets capInsets for button.
     * The capInset affects  all button scale9 renderer only if `setScale9Enabled(true)` is called
     *
     * @~chinese 
     * 集capInsets按钮。
     * capInset影响到所有按钮只有“setScale9Enabled scale9渲染器
     * 
     * @param capInsets    @~english capInset in Rect.
     * @~chinese capInset在矩形。
     */

    void setCapInsets(const Rect &capInsets);

    /**@~english
     * Sets capInsets for button, only the normal state scale9 renderer will be affected.
     *
     * @~chinese 
     * 集capInsets按钮,只有正常状态scale9渲染器将受到影响。
     * 
     * @param capInsets    @~english capInsets in Rect.
     * @~chinese capInsets在矩形。
     */

    void setCapInsetsNormalRenderer(const Rect &capInsets);

    /**@~english
     * Return the capInsets of normal state scale9sprite.
     * @~chinese 
     * 返回正常状态的capInsets scale9sprite。
     *@return @~english The normal scale9 renderer capInsets.
     * @~chinese 正常scale9渲染器capInsets。
     */

    const Rect& getCapInsetsNormalRenderer()const;

    /**@~english
     * Sets capInsets for button, only the pressed state scale9 renderer will be affected.
     *
     * @~chinese 
     * 集capInsets按钮,只有按下scale9渲染器将受到影响。
     * 
     * @param capInsets    @~english capInsets in Rect
     * @~chinese capInsets在矩形
     */

    void setCapInsetsPressedRenderer(const Rect &capInsets);

    /**@~english
     * Return the capInsets of pressed state scale9sprite.
     * @~chinese 
     * 返回的capInsets scale9sprite压状态。
     *@return @~english The pressed scale9 renderer capInsets.
     * @~chinese scale9渲染器capInsets施压。
     */

    const Rect& getCapInsetsPressedRenderer()const;

    /**@~english
     * Sets capInsets for button, only the disabled state scale9 renderer will be affected.
     *
     * @~chinese 
     * 集capInsets按钮,只有残疾人国家scale9渲染器将受到影响。
     * 
     * @param capInsets  @~english capInsets in Rect.
     * @~chinese capInsets在矩形。
     */

    void setCapInsetsDisabledRenderer(const Rect &capInsets);

    /**@~english
     * Return the capInsets of disabled state scale9sprite.
     * @~chinese 
     * 返回的capInsets scale9sprite禁用状态。
     *@return @~english The disabled scale9 renderer capInsets.
     * @~chinese 残疾人scale9渲染器capInsets。
     */

    const Rect& getCapInsetsDisabledRenderer()const;

    /**@~english
     * Enable scale9 renderer.
     *
     * @~chinese 
     * 启用scale9渲染器。
     * 
     * @param enable @~english Set to true will use scale9 renderer, false otherwise.
     * @~chinese 设置为true将使用scale9渲染器,否则假。
     */

    virtual void setScale9Enabled(bool enable);

    /**@~english
     * Query whether button is using scale9 renderer or not.
     * @~chinese 
     * 查询是否使用scale9渲染器按钮。
     *@return @~english whether button use scale9 renderer or not.
     * @~chinese 是否按钮使用scale9渲染器。
     */

    bool isScale9Enabled()const;

    /**@~english
     * Enable zooming action when button is pressed.
     *
     * @~chinese 
     * 启用按钮被按下时缩放操作。
     * 
     * @param enabled @~english Set to true will enable zoom effect, false otherwise.
     * @~chinese 设置为true将使缩放效果,否则假。
     */

    void setPressedActionEnabled(bool enabled);

    //override methods
    virtual void ignoreContentAdaptWithSize(bool ignore) override;
    virtual Size getVirtualRendererSize() const override;
    virtual Node* getVirtualRenderer() override;
    virtual std::string getDescription() const override;

    /**@~english
     * Return the inner title renderer of Button.
     * @~chinese 
     * 返回按钮的内部标题渲染器。
     * @return @~english The button title.
     * @~chinese 按钮标题。
     * @since v3.3
     */

    Label* getTitleRenderer()const;

    /**@~english
     * Change the content of button's title.
     * @~chinese 
     * 改变按钮的内容的标题。
     *@param text @~english The title in std::string.
     * @~chinese 标题在std::string。
     */

    void setTitleText(const std::string& text);

    /**@~english
     * Query the button title content.
     * @~chinese 
     * Query the按钮标题内容。
     *@return @~english Get the button's title content.
     * @~chinese 按钮的标题内容。
     */

    const std::string getTitleText() const;

    /**@~english
     * Change the color of button's title.
     * @~chinese 
     * 改变按钮的标题的颜色。
     *@param color @~english The title color in Color3B.
     * @~chinese 在Color3B标题颜色。
     */

    void setTitleColor(const Color3B& color);

    /**@~english
     * Query the button title color.
     * @~chinese 
     * 查询按钮标题的颜色。
     *@return @~english Color3B of button title.
     * @~chinese Color3B按钮的标题。
     */

    Color3B getTitleColor() const;

    /**@~english
     * Change the font size of button's title
     * @~chinese 
     * 改变按钮的标题的字体大小
     *@param size @~english Title font size in float.
     * @~chinese 标题字体大小在浮动。
     */

    void setTitleFontSize(float size);

    /**@~english
     * Query the font size of button title
     * @~chinese 
     * 查询按钮标题的字体大小
     *@return @~english font size in float.
     * @~chinese 字体大小在浮动。
     */

    float getTitleFontSize() const;

    /**@~english
     * Change the font name of button's title
     * @~chinese 
     * 改变按钮的标题的字体名称
     *@param fontName @~english a font name string.
     * @~chinese 字体名称字符串。
     */

    void setTitleFontName(const std::string& fontName);

    /**@~english
     * Query the font name of button's title
     * @~chinese 
     * 查询按钮的标题的字体名称
     *@return @~english font name in std::string
     * @~chinese 字体的名字在std::string
     */

    const std::string getTitleFontName() const;

    /**@~english
     * Sets the title's text horizontal alignment.
     *
     * @~chinese 
     * 设置标题的文本的水平对齐。
     * 
     * @param hAlignment @~english see TextHAlignment
     * @~chinese 看到TextHAlignment
     */

    void setTitleAlignment(TextHAlignment hAlignment);

    /**@~english
     * Sets the title's text vertical alignment.
     *
     * @~chinese 
     * 设置标题的文本垂直对齐。
     * 
     * @param hAlignment @~english see TextHAlignment.
     * @~chinese 看到TextHAlignment。
     * @param vAlignment @~english see TextVAlignment.
     * @~chinese 看到TextVAlignment。
     */

    void setTitleAlignment(TextHAlignment hAlignment, TextVAlignment vAlignment);

    /** @brief @~english When user pressed the button, the button will zoom to a scale.
     * The final scale of the button  equals (button original scale + _zoomScale)
     * @~chinese 当用户按下按钮,这个按钮将缩放比例。
     * 平等的最终规模按钮
     * @since v3.3
     */

    void setZoomScale(float scale);

    /**
     * @brief @~english Return a zoom scale
     * @~chinese 返回一个缩放比例
     * @return @~english the zoom scale in float
     * @~chinese 变焦范围内自由浮动
     * @since v3.3
     */

    float getZoomScale()const;

CC_CONSTRUCTOR_ACCESS:
    virtual bool init() override;
    virtual bool init(const std::string& normalImage,
                      const std::string& selectedImage = "",
                      const std::string& disableImage = "",
                      TextureResType texType = TextureResType::LOCAL);

    virtual Size getNormalTextureSize() const;

protected:
    virtual void initRenderer() override;
    virtual void onPressStateChangedToNormal() override;
    virtual void onPressStateChangedToPressed() override;
    virtual void onPressStateChangedToDisabled() override;
    virtual void onSizeChanged() override;

    void loadTextureNormal(SpriteFrame* normalSpriteFrame);
    void setupNormalTexture();
    void loadTexturePressed(SpriteFrame* pressedSpriteFrame);
    void setupPressedTexture();
    void loadTextureDisabled(SpriteFrame* disabledSpriteFrame);
    void setupDisabledTexture();

    void normalTextureScaleChangedWithSize();
    void pressedTextureScaleChangedWithSize();
    void disabledTextureScaleChangedWithSize();

    virtual void adaptRenderers() override;
    void updateTitleLocation();
    void updateContentSize();
    void createTitleRenderer();

    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;

    virtual Size getNormalSize() const;
protected:
    Scale9Sprite* _buttonNormalRenderer;
    Scale9Sprite* _buttonClickedRenderer;
    Scale9Sprite* _buttonDisableRenderer;
    Label* _titleRenderer;

    float _zoomScale;
    bool _prevIgnoreSize;
    bool _scale9Enabled;
    bool _pressedActionEnabled;

    Rect _capInsetsNormal;
    Rect _capInsetsPressed;
    Rect _capInsetsDisabled;

    Size _normalTextureSize;
    Size _pressedTextureSize;
    Size _disabledTextureSize;

    float _normalTextureScaleXInSize;
    float _normalTextureScaleYInSize;
    float _pressedTextureScaleXInSize;
    float _pressedTextureScaleYInSize;

    bool _normalTextureLoaded;
    bool _pressedTextureLoaded;
    bool _disabledTextureLoaded;
    bool _normalTextureAdaptDirty;
    bool _pressedTextureAdaptDirty;
    bool _disabledTextureAdaptDirty;

private:
    enum class FontType
    {
        SYSTEM,
        TTF,
        BMFONT
    };

    int _fontSize;
    FontType _type;
};

}

NS_CC_END
// end of ui group
/// @}

#endif /* defined(__CocoGUI__Button__) */
