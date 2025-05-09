#ifndef HEADANGLE_H
#define HEADANGLE_H

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>
#include <QPainter>
#include <QPixmap>
#include <QMatrix>

class QDESIGNER_WIDGET_EXPORT HeadAngle : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor scaleColor READ getScaleColor WRITE setScaleColor)
    Q_PROPERTY(QColor outerCircleColor READ getOuterCircleColor WRITE setOuterCircleColor)
    Q_PROPERTY(QColor innerCircleColor READ getInnerCircleColor WRITE setInnerCircleColor)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)
    Q_PROPERTY(QColor windColor READ getWindColor WRITE setWindColor)
    Q_PROPERTY(QColor planeColor READ getPlaneColor WRITE setPlaneColor)
    Q_PROPERTY(uint precison READ getPrecison WRITE setPrecison)
    Q_PROPERTY(QFont font READ getFont WRITE setFont)
    Q_PROPERTY(QSizeF textBackground READ getRect WRITE setRect)
    Q_PROPERTY(bool ifShowWindAngle READ getShow WRITE setShow)

public:
    HeadAngle(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);
private:
    QColor m_outerCircleColor=Qt::white;        //外圆背景颜色
    QColor m_innerCircleColor=QColor(28,86,159);//内圆背景色
    QColor m_scaleColor=Qt::yellow;
    QColor m_textColor=Qt::black;
    QColor m_textRectColor=Qt::white;
    QColor m_planeColor=Qt::white;

    QColor m_windColor=Qt::yellow;
    double m_currentValue=0;
    double m_windAngle=0;
    int m_precision=1;//显示精度
    QFont m_font=QFont("Arial", 10);
    QSizeF m_rectWidthAndHeight=QSizeF(25,10);
    bool m_ifShowWind=true;
    void drawScale(QPainter *painter);//绘制刻度
    void drawPlane(QPainter *painter);//绘制图片
    void drawOuterCircle(QPainter *painter);//绘制外框圆
    void drawValue(QPainter *painter);
    void drawText(QPainter *painter);
    void drawInnerCircle(QPainter *painter);
    void DrawWindLine(QPainter *_painter);//绘制风向箭头
public:
    QColor getScaleColor() const;
    QColor getOuterCircleColor() const;
    QColor getInnerCircleColor() const;
    QColor getTextColor() const;
    QColor getTextRectColor()const;
    QColor getPlaneColor() const;
    uint getPrecison() const;
    QFont getFont()const;
    QSizeF getRect()const;
    QColor getWindColor()const;
    bool getShow()const;
public slots:
    void setPlaneAngle(double value);//设置航向角槽函数
    void setPlaneAngle(int value);
    void setWindAngle(double value);//设置风向槽函数
    void setWindAngle(int value);


    void setScaleColor(QColor color);
    void setOuterCircleColor(QColor color);
    void setInnerCircleColor(QColor color);
    void setTextColor(QColor color);
    void setTextRectColor(QColor color);
    void setPlaneColor(QColor color);
    void setPrecison(uint precision);
    void setFont(QFont font);
    void setRect(QSizeF widthAndHeight);
    void setWindColor(QColor color);
    void setShow(bool checked);
};

#endif
